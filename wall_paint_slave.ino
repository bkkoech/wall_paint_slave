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
#define X_TOP_PIN_1 10
#define X_TOP_PIN_2 11
#define X_TOP_PIN_3 12
#define X_TOP_PIN_4 13
#define X_BTM_PIN_1 4
#define X_BTM_PIN_2 5
#define X_BTM_PIN_3 6
#define X_BTM_PIN_4 7
#define Z_PIN_1 A5
#define Z_PIN_2 A4
#define Z_PIN_3 2
#define Z_PIN_4 3


// Load libraries and modules
#include <Stepper.h>
#include <Servo.h>


Stepper xTopStepper(200,X_TOP_PIN_1,X_TOP_PIN_2,X_TOP_PIN_3,X_TOP_PIN_4);
Stepper xBtmStepper(200, X_BTM_PIN_1,X_BTM_PIN_2,X_BTM_PIN_3,X_BTM_PIN_4);

//Constants and Variables
int x_stepCount = 0;         // number of steps the x motors have taken
int x_pos = 0; //default x position
int y_pos = 0; //default y position
int z_pos = 0; //default z position

// Use step frequency instead of delays
// Based on FSM Code by by: David Abrams in ES52
const int STEP_FREQ = 100;      // set to frequency of each step in Hz (max 500Hz)
const int STEP_TIME = 1000/STEP_FREQ; // milliseconds per state cycle (do not change this variable)
unsigned long StepStart;

//Stepping function
//based on https://github.com/arduino-libraries/Stepper/blob/master/src/Stepper.cpp
 void Step(int no_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4){
  
  // Run this if no_steps is positive
  for(int i=0; i<=no_steps; i++){
    
    // get time we started this FSM cycle
    StepStart = millis();
    
      switch (i%4) {
        case 0:  // 1010
          digitalWrite(motor_pin_1, HIGH);
          digitalWrite(motor_pin_2, LOW);
          digitalWrite(motor_pin_3, HIGH);
          digitalWrite(motor_pin_4, LOW);
        break;
        case 1:  // 0110
          digitalWrite(motor_pin_1, LOW);
          digitalWrite(motor_pin_2, HIGH);
          digitalWrite(motor_pin_3, HIGH);
          digitalWrite(motor_pin_4, LOW);
        break;
        case 2:  //0101
          digitalWrite(motor_pin_1, LOW);
          digitalWrite(motor_pin_2, HIGH);
          digitalWrite(motor_pin_3, LOW);
          digitalWrite(motor_pin_4, HIGH);
        break;
        case 3:  //1001
          digitalWrite(motor_pin_1, HIGH);
          digitalWrite(motor_pin_2, LOW);
          digitalWrite(motor_pin_3, LOW);
          digitalWrite(motor_pin_4, HIGH);
        break;
      }
      
       // wait one FSM cycle  
       while (millis() < (StepStart + STEP_TIME)) {
       } 
                                                      
  }

    // Run this if no_steps is negative
    for(int i=no_steps; i<=0; i++){
    
    // get time we started this FSM cycle
    StepStart = millis();
    
      switch (abs(i%4)) {
        case 0:  // 1010
          digitalWrite(motor_pin_1, HIGH);
          digitalWrite(motor_pin_2, LOW);
          digitalWrite(motor_pin_3, HIGH);
          digitalWrite(motor_pin_4, LOW);
        break;
        case 1:  // 0110
          digitalWrite(motor_pin_1, LOW);
          digitalWrite(motor_pin_2, HIGH);
          digitalWrite(motor_pin_3, HIGH);
          digitalWrite(motor_pin_4, LOW);
        break;
        case 2:  //0101
          digitalWrite(motor_pin_1, LOW);
          digitalWrite(motor_pin_2, HIGH);
          digitalWrite(motor_pin_3, LOW);
          digitalWrite(motor_pin_4, HIGH);
        break;
        case 3:  //1001
          digitalWrite(motor_pin_1, HIGH);
          digitalWrite(motor_pin_2, LOW);
          digitalWrite(motor_pin_3, LOW);
          digitalWrite(motor_pin_4, HIGH);
        break;
      }
      // wait one FSM cycle  
      while (millis() < (StepStart + STEP_TIME)) {

    }
  }

 }


// create servo object to control a servo
Servo yServo;  


//x forward motion function
void move_x_forward(int no_of_steps) {
  for (int i=1; i <= no_of_steps; i++){
    xTopStepper.step(1); // move top x stepper
    xBtmStepper.step(-1); // move bottom x stepper
  }
}

//x reverse motion function
void move_x_reverse(int no_of_steps) {
  for (int i=1; i <= no_of_steps; i++){
    xTopStepper.step(-1); // move top x stepper
    xBtmStepper.step(1); // move bottom x stepper  
   }
}

//z motion function
void move_z(int no_of_steps) {
  Step(no_of_steps, Z_PIN_1, Z_PIN_2, Z_PIN_3, Z_PIN_4); // move top z stepper
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

  //speed
  xTopStepper.setSpeed(60); //rpms
  xBtmStepper.setSpeed(60); //rpms
  // attaches the servo on pin 9 to the servo object
  yServo.attach(9); 
  set_angle(90); 
  
  
  // initialize the serial port:
  Serial.begin(9600);

  //setup pinmode
  pinMode(X_TOP_PIN_1, OUTPUT);
  pinMode(X_TOP_PIN_2, OUTPUT);
  pinMode(X_TOP_PIN_3, OUTPUT);
  pinMode(X_TOP_PIN_4, OUTPUT);
  pinMode(X_BTM_PIN_1, OUTPUT);
  pinMode(X_BTM_PIN_2, OUTPUT);
  pinMode(X_BTM_PIN_3, OUTPUT);
  pinMode(X_BTM_PIN_4, OUTPUT);
  pinMode(Z_PIN_1, OUTPUT);
  pinMode(Z_PIN_2, OUTPUT);
  pinMode(Z_PIN_3, OUTPUT);
  pinMode(Z_PIN_4, OUTPUT);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  move_x_forward(200);
  move_x_reverse(200);
  move_z(-200);
  move_z(200);
  
  for(int i=0; i<= 180; i++){
    set_angle(i);
    delay(50);
  }
 
 
}
