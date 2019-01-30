/*
Pseudo code:


Fuctions to write:
plus_x(steps) - takes int steps returns void
minus_x(steps) - "
plus_z(steps) - "
minus_z(steps) - "
engage_sharpie() - 
disengage_sharpie() -
Calibrate() 


Step 1: Calibrate
* Move hub towards -x until switch is triggered at the end
* Move hub towards +z until switch is triggered at the top
* Move +x while counting steps, store number of steps. No. of Steps = width.
* Move -z while counting steps, store number of steps. No. of Steps = height. 
* Move hub to origin, x = 0, y = 0 



 Created 22 Jan 2019
 by Billy Koech
*/


//Declaration of pin numbers
/*
#define X_TP_STEPPER_WIRE_A 1
#define X_TP_STEPPER_WIRE_B 2
#define X_TP_STEPPER_WIRE_C 3
#define X_TP_STEPPER_WIRE_D 4
#define X_BTM_STEPPER_WIRE_A 5
#define X_BTM_STEPPER_WIRE_B 6
#define X_BTM_STEPPER_WIRE_C 7
#define X_BTM_STEPPER_WIRE_D 8
#define Z_STEPPER_WIRE_A 10
#define Z_STEPPER_WIRE_B 11
#define Z_STEPPER_WIRE_C 12
#define Z_STEPPER_WIRE_D 13
*/


// Load libraries and modules
#include <Stepper.h>
#include <Servo.h>

//Constants and Variables
const int stepsPerRevolution = 200;  // number of steps per revolution for your motor
int x_stepCount = 0;         // number of steps the x motors have taken
int x_pos = 0; //default x position
int y_pos = 0; //default y position
int z_pos = 0; //default z position

// initialize the stepper library on pins 1 throught  8 for x.
Stepper xTopStepper(stepsPerRevolution, 10, 11, 12, 13);
Stepper xBottomStepper(stepsPerRevolution, 4, 5, 6, 7);

// initialize the stepper library on pins 10 throught  13 for z.
Stepper zStepper(stepsPerRevolution, 0, 1, 2, 3);


// create servo object to control a servo
Servo yServo;  


//x forward motion function
void move_x_forward(int no_of_steps) {
  for (int i=1; i <= no_of_steps; i++){
    xTopStepper.step(1); // move top x stepper
    xBottomStepper.step(-1); // move bottom x stepper
  }
}

//x reverse motion function
void move_x_reverse(int no_of_steps) {
  for (int i=1; i <= no_of_steps; i++){
    xTopStepper.step(-1); // move top x stepper
    xBottomStepper.step(1); // move bottom x stepper
  }
}

//z motion function
void move_z(int no_of_steps) {
  zStepper.step(no_of_steps); // move top z stepper
}

// y motion function
void set_angle(int angle){
  yServo.write(angle);  // set servo angle
}

void go_to_coordinates(int x, int z){
  // find difference between current position and next position
  int x_diff = x - x_pos;
  int z_diff = z - z_pos;

  //move to new postion and set x_pos and y_pos
  //move_x(x_diff);
  //move_z(z_diff);
}

void calibrate(){
 
}


void setup() {
  // set the speed at 60 rpm:
  xTopStepper.setSpeed(60);
  xBottomStepper.setSpeed(60);
  zStepper.setSpeed(60);

  // attaches the servo on pin 9 to the servo object
  yServo.attach(9); 
  set_angle(180); 
  
  
  // initialize the serial port:
  Serial.begin(9600);

  //setup pinmode

}

void loop() {
  // put your main code here, to run repeatedly:
 move_x_forward(400);
 move_x_reverse(400);

}
