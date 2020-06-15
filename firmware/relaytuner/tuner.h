#ifndef TUNER_H
#define TUNER_H
#define ROLE_CONTROLLER 0
#define ROLE_ANTENNA 1
#define ROLE_SWITCH 2
#define ROLE_RELAYTUNER 3

#define SWITCH_MAX_OUTPUTS 4
#define SWITCH_MAX_ANTENNAS 12
#define RADIO_RATE RF24_250KBPS
#define RADIO_CHANNEL 113
#define RADIO_CRC RF24_CRC_16

#define TUNER_MAGIC_NUMBER 0x8f7a3098
extern byte addresses[][6];

enum relaytuner_command {
  RELAYTUNER_NOOP,
  RELAYTUNER_CHANGE
};

struct relaytuner_request {
  enum relaytuner_command command;
  char set_shunt_l;
  char set_series_l;
  char set_shunt_c;
  unsigned long magic;
};

struct relaytuner_response {
  char shunt_l;
  char series_l;
  char shunt_c;
  unsigned long magic;
};

enum switch_command {
  SWITCH_NOOP,
  SWITCH_CHANGE
};

struct switch_request {
  enum switch_command command;
  char set_output[4];
};

struct switch_response {
  int temperature;
  char current_output[4];
};

enum antenna_status {
  STOPPED,
  GOING_UP,
  GOING_DOWN,
  FAULT
};

struct antenna_response {
  int current_step;
  int temperature;
  enum antenna_status status;

};

enum antenna_command {
  NOOP,
  GOTO,
  MOVE_CONTINUOUS,
  SET_ZERO,
  STOP
};

struct antenna_request {
  enum antenna_command command;
  int motion_value;
  bool relative;
  bool force;
};
#endif
