//Step Angle 1.8 * 200 = 360 degree i.e Full revolution
#define STEPS_PER_REVOLUTION 200
#define STEP_ANGLE 1.8
#define BAUD_RATE 9600

#define DATA_LEN 100


// Define the GPIOs for Stepper Motor connection
#define STEPPER_1 2
#define STEPPER_2 3
#define STEPPER_3 6
#define STEPPER_4 7
#define STEPPER_DIRECTION 2

//JSON Keys
#define KEY_ANGEL "angel"
#define KEY_COMMAND_TYPE "command_type"
#define KEY_STEP_ANGEL "step_angel"
#define KEY_SPEED "speed"
#define KEY_DIRECTION "direction"
