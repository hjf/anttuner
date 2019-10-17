#define ROLE_CONTROLLER 0
#define ROLE_ANTENNA 1
#define ROLE_SWITCH 2

byte addresses[][6] = {"1Node", "2Node", "3Node" };

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
