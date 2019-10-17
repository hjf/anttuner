#define DIR 7
#define STEP 8
#define EN 10
#define DRIVER_FAULT 9
#define NRF_CE 2
#define NRF_CS 3
#define NRF_PWR 1
#define VSENSE A0

#define MAX_STEPS 10800

//#define DEBUG

#ifdef DEBUG
#define MIN_US 50
#define MAX_US 1500
#else
#define MIN_US 35
#define MAX_US 1000
#endif

#include <avr/sleep.h>
#include <avr/wdt.h>

#include <RF24.h>
#include "tuner.h"

RF24 radio(NRF_CE, NRF_CS);

volatile bool interrupted;
bool step_state, await_adc;
int target_speed, current_speed, target_step, postdiv;
unsigned int wADC;
double t;
byte admux_copy;
struct antenna_response response;
byte stopcount;

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
#endif
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  pinMode(DRIVER_FAULT, INPUT_PULLUP);
  pinMode(NRF_PWR, OUTPUT);
  digitalWrite(NRF_PWR, LOW);
  delay(100);

  initializeRadio();



  response.current_step = 0;

  postdiv = 0;
  admux_copy = ADMUX; //backup del registro como lo deja Arduino
  ADCSRA |= _BV(ADEN);  // enable the ADC
}

void loop() {

  byte pipeNo;
  struct antenna_request req;

  while ( radio.available(&pipeNo)) {

    radio.read( &req, sizeof(struct antenna_request) );

    radio.writeAckPayload(pipeNo, &response, sizeof(struct antenna_response) );

    if (req.command == NOOP) {
      continue;
    }

    if (req.command == STOP) {
      response.status = STOPPED;
    }

    if (req.command == SET_ZERO) {
      response.status = STOPPED;
      response.current_step == 0;
    }

    if (req.command == GOTO) {



      if (req.relative) {
        target_step += req.motion_value;
        target_speed = MAX_US;
      }      else {
        target_step = req.motion_value;
        target_speed = MAX_US;
      }

      if (target_step > MAX_STEPS)
        target_step = MAX_STEPS;
      if (target_step < 0)
        target_step = 0;

      if (target_step > response.current_step)
        response.status = GOING_UP;
      if (target_step < response.current_step)
        response.status = GOING_DOWN;


    }


    if (!await_adc) {
#ifdef DEBUG
      TIMSK2 = (TIMSK2 & B11111110) | 0x01;
      TCCR2B = (TCCR2B & B11111000) | 0x01;
      ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
#else
      TIMSK1 = (TIMSK1 & B11111110) | 0x01;
      TCCR1B = (TCCR1B & B11111000) | 0x01;
      TCNT1H = 0xff;
      ADMUX = 0b10100010;//(_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
#endif

      ADCSRA |= _BV(ADSC);  // Start the ADC
      await_adc = true;
    }
  }

  if ((response.current_step <= 0  && response.status == GOING_DOWN) ||
      (response.current_step >= MAX_STEPS  && response.status == GOING_UP) ||
      (response.current_step <= target_step  && response.status == GOING_DOWN) ||
      (response.current_step >= target_step  && response.status == GOING_UP)
     )
  {
    response.status = STOPPED;
  }

  if (response.status == GOING_UP)
    digitalWrite(DIR, HIGH);
  if (response.status == GOING_DOWN)
    digitalWrite(DIR, LOW);



  if (response.status == GOING_UP || response.status == GOING_DOWN) {
    digitalWrite(EN, LOW);
    stopcount = 0;
  }
  else {
    if (stopcount == 255)
      digitalWrite(EN, HIGH);
    else
      stopcount++;
  }

  if (digitalRead(DRIVER_FAULT) == LOW)
    response.status = FAULT;

  if (await_adc && !bit_is_set(ADCSRA, ADSC)) {
    // Reading register "ADCW" takes care of how to read ADCL and ADCH.
    wADC = ADCW;

    // The offset of 324.31 could be wrong. It is just an indication.
    //t = (wADC - 324.31 ) / 1.22;
    t = wADC - (279);// + 100);// * 128;
    response.temperature = t;
    await_adc = false;
  } else {
    ADMUX = admux_copy;
    int rval = analogRead(A0);
    if (rval < 300) {
      goToSleep();

    }
  }

}

void goToSleep() {
  cli();

  TIMSK1 = (TIMSK1 & B11111110);// | 0x01;

  digitalWrite(NRF_PWR, HIGH); //apagar radio
  pinMode(0, INPUT);
  byte DDRA_copy = DDRA;
  byte DDRB_copy = DDRB;
  byte PORTA_copy = PORTA;
  byte PORTB_copy = PORTB;
  PORTA = 0x02; //NRF_PWR en HIGH
  PORTB = 0x00; //MOTOR_EN en HIGH
  DDRA = 0xfe; //todo out menos SENSE
  DDRB = 0xf8; //todo out menos FAULT

  ADCSRA &= ~ bit(ADEN); //apagar ADC
  PRR = 0xff; //maximo ahorro de energia
  MCUCR |= _BV(BODS); //apagar BOD en sleep

  GIMSK |= (1 << PCIE0);
  PCMSK0 = 1;
  wdt_disable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sei();
  sleep_cpu();
  //-------a dormir
  GIMSK &= ~ (1 << PCIE0);
  PCMSK0 = 0;
  PRR = 0;
  ADCSRA |= _BV(ADEN); //encender ADC


  PORTA = PORTA_copy;
  PORTB = PORTB_copy;
  DDRA = DDRA_copy;
  DDRB = DDRB_copy;
  digitalWrite(NRF_PWR, LOW); //encender radio
  delay(100);
  initializeRadio();
  TIMSK1 = (TIMSK1 & B11111110) | 0x01;
}

ISR(PCINT0_vect)
{
  sleep_disable();
  //digitalWrite(NRF_PWR, LOW); //encender radio

}

ISR(EXT_INT0_vect)
{
  sleep_disable();
  //digitalWrite(NRF_PWR, LOW); //encender radio

}

void initializeRadio() {
  radio.begin();
  radio.enableAckPayload();                     // Allow optional ack payloads
  radio.enableDynamicPayloads();                // Ack payloads are dynamic payloads
  radio.setPALevel(RF24_PA_LOW);

  radio.openWritingPipe(addresses[ROLE_ANTENNA]);
  radio.openReadingPipe(1, addresses[ROLE_CONTROLLER]);
  radio.startListening();
  radio.writeAckPayload(1, &response, sizeof(struct antenna_response));
}

#ifdef DEBUG
ISR(TIMER2_OVF_vect) {
#else
ISR(TIM1_OVF_vect) {
  TCNT1 = 0xff00;
#endif



  if (response.status == STOPPED || response.status == FAULT) {
    current_speed = 0;
    step_state = 0;
    digitalWrite(STEP, step_state);
    return;
  }

  if (postdiv)
  {
    postdiv--;
    return;
  }

  if (abs(target_step - response.current_step) > 50) {
    if (current_speed < target_speed)
      current_speed += 8;
    if (current_speed > target_speed)
      current_speed = target_speed;
  } else {
    current_speed -= 8;
    if (current_speed < 1)
      current_speed = 1;
  }

  postdiv = MIN_US + (MAX_US - current_speed);

  step_state = !step_state;
  digitalWrite(STEP, step_state);

  if (step_state) {
    if (response.status == GOING_UP)
      response.current_step++;
    if (response.status == GOING_DOWN)
      response.current_step--;
  }

}
