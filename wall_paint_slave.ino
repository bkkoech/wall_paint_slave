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

//Constants and Variables
int x_stepCount = 0;         // number of steps the x motors have taken
int z_stepCount = 0;
int x_pos = 0; //default x position in steps
int y_pos = 0; //default y position in degrees
int z_pos = 0; //default z position

// Initialize stepper object for x motion
Stepper xTopStepper(200,X_TOP_PIN_1,X_TOP_PIN_2,X_TOP_PIN_3,X_TOP_PIN_4);
Stepper xBtmStepper(200, X_BTM_PIN_1,X_BTM_PIN_2,X_BTM_PIN_3,X_BTM_PIN_4);

// Initialize stepper object for z motion
Stepper zStepper(200,Z_PIN_1,Z_PIN_2,Z_PIN_3,Z_PIN_4);

// function to move all 3 axes
void move_axes(int x_steps, int y_angle, int z_steps){

}


//x forward motion function
void move_x(int no_of_steps) {
  for (int i=1; i <= abs(no_of_steps); i++){
    xTopStepper.step(no_of_steps/abs(no_of_steps)); // move top x stepper
    xBtmStepper.step(-1*(no_of_steps/abs(no_of_steps))); // move bottom x stepper

  }
}

/*
//x forward motion function
void move_x_forward(int no_of_steps) {
  for (int i=0; i <= no_of_steps; i++){
    xTopStepper.step(1); // move top x stepper
    xBtmStepper.step(-1); // move bottom x stepper
    Serial.print(i);
    Serial.print("\n");
  }
}

//x reverse motion function
void move_x_reverse(int no_of_steps) {
  for (int i=1; i <= no_of_steps; i++){
    xTopStepper.step(-1); // move top x stepper
    xBtmStepper.step(1); // move bottom x stepper  
   }
}
*/

//z motion function
void move_z(int no_of_steps) {
  zStepper.step(-1*no_of_steps); // move top z stepper
}


// create servo object to control a servo
Servo yServo; 

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
  zStepper.setSpeed(60); //rpms
  // attaches the servo on pin 9 to the servo object
  yServo.attach(9); 
  set_angle(110); 
  
  
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

  for(int i=1; i<=300; i++){
    move_x(1);
    move_z(1);
  }
  for(int i=1; i<=300; i++){
    move_x(-1);
    move_z(-1);
    //set_angle((i/300)*180);
  }

  
 
 
 
}
