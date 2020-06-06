#define ROLE_CONTROLLER 0
#define ROLE_ANTENNA 1
#define ROLE_SWITCH 2

#define SWITCH_MAX_OUTPUTS 4
#define SWITCH_MAX_ANTENNAS 12
#define RADIO_RATE RF24_250KBPS
#define RADIO_CHANNEL 113
#define RADIO_CRC RF24_CRC_16
byte addresses[][6] = {"2Node", "1Node", "3Node" };

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
