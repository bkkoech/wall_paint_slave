/*
Pseudo code:


Fuctions to write:
plus_x(steps) - takes int steps returns void
minus_x(steps) - "
plus_y(steps) - "
minus_y(steps) - "
engage_sharpie() - 
disengage_sharpie() -
Calibrate() 




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
#define Y_PIN_1 A5
#define Y_PIN_2 A4
#define Y_PIN_3 2
#define Y_PIN_4 3
#define BUTTONS_PIN A0
#define SENSOR_PIN A1


// Load libraries and modules
#include <Stepper.h>
#include <Servo.h>
//#include <string.h>


//Constants and Variables
int x_stepCount = 0; // number of steps it takes to cover the entire x length
int y_stepCount = 0; // number of steps it takes to cover the entire y length
int x_pos = 0; //default x position in steps
int y_pos = 0; //default y position in steps
int z_pos = 0; //default z position in degrees
int x_btn_left_R = 1001 ;
int x_btn_right_R = 434;
int y_btn_top_R = 146;
int y_btn_bottom_R = 252;
int R_offset = 60;
bool DEBUG = true;
int MODE = 5;

// String data
String receivedData = "";
String parsed_g= "";
String parsed_x = "";
String parsed_y = "";
String parsed_z = "";



// Initialize stepper object for x motion
Stepper xTopStepper(200,X_TOP_PIN_1,X_TOP_PIN_2,X_TOP_PIN_3,X_TOP_PIN_4);
Stepper xBtmStepper(200, X_BTM_PIN_1,X_BTM_PIN_2,X_BTM_PIN_3,X_BTM_PIN_4);

// Initialize stepper object for y motion
Stepper yStepper(200,Y_PIN_1,Y_PIN_2,Y_PIN_3,Y_PIN_4);


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

//y motion function
void move_y(int no_of_steps) {
  yStepper.step(-1*no_of_steps); // move top y stepper
}


// create servo object to control a servo
Servo zServo; 

// y motion function
void set_angle(int angle){
  zServo.write(angle);  // set servo angle
}


// function to move all 3 axes simultaneosly
// takes x steps to move, z angle to set servo to and y steps to move
void move_axes(int x_steps, int y_steps, int z_angle){
  int xsteps = abs(x_steps);
  int zangle = z_angle;
  int ysteps = abs(y_steps);
  while(xsteps!=0 || zangle!=0 || ysteps!=0){
     if(xsteps!=0){
      move_x(x_steps/abs(x_steps));
      xsteps -= 1;
     }
     if(zangle!=0){
      set_angle(zangle);
      zangle -= z_angle;
     }
     if(ysteps!=0){
      move_y(y_steps/abs(y_steps));
      ysteps -= 1;
     }
  }
  
}



void go_to_coordinates(int x, int y, int z_angle){
  // find difference between current position and next position
  int x_diff = x - x_pos;
  int y_diff = y - y_pos;

  

  //move to new postion and set x_pos, y_pos and z_pos
  move_axes(x_diff, y_diff, z_angle);
  x_pos = x;
  y_pos = y;
  z_pos = z_angle;
}

// calibration function
bool calibrate(){
  /* Step 1: Calibrate
   * Move hub towards -x until switch is triggered at the end 
   * Move hub towards -y until switch is triggered at the top
   * Move +x while counting steps, store number of steps. No. of Steps = width.
   * Move -y while counting steps, store number of steps. No. of Steps = height. 
   * Move hub to origin, x = 0, y = 0 
   */
   bool calibrated = false;
   int sensorVal = 0; // varaible to hold analog value of buttons
   bool left_trig = false;
   bool right_trig = false;
   bool bottom_trig = false;
   bool top_trig = false;
   
   while(!left_trig){
    // move x to left until switch is trigerred
    sensorVal = analogRead(BUTTONS_PIN);
    if (x_btn_left_R-R_offset < sensorVal && sensorVal < x_btn_left_R+R_offset){
      left_trig = true; // stop moving
    }
    else{
      move_x(-1);
    }
    
   }

   
   while(!right_trig){
    // move x to right until switch is trigerred
    sensorVal = analogRead(BUTTONS_PIN);
    if (x_btn_right_R-R_offset < sensorVal && sensorVal < x_btn_right_R+R_offset){
      right_trig = true; //stop moving
      move_x(-x_stepCount);//go back to origin
      x_pos = 0; //reset x coordinate to 0
      
    }
    else{
      move_x(1);
      x_stepCount +=1; // start counting steps
    }
    
   }
   while(!bottom_trig){
    // move y to bottom until switch is trigerred
    sensorVal = analogRead(BUTTONS_PIN);
    if (y_btn_bottom_R-R_offset < sensorVal && sensorVal < y_btn_bottom_R+R_offset){
      bottom_trig = true; // stop moving
    }
    else{
      move_y(-1);
    }
    
   }

   while(!top_trig){
    // move y to top until switch is trigerred
    sensorVal = analogRead(BUTTONS_PIN);
    if (y_btn_top_R-R_offset < sensorVal && sensorVal < y_btn_top_R+R_offset){
      top_trig = true; //stop moving
      move_y(-y_stepCount);//go back to origin
      y_pos = 0; //reset y coordinate to 0
      
    }
    else{
      move_y(1);
      y_stepCount +=1; // start counting steps
    }
    
   }

   calibrated = true;
   return calibrated;
}




// fuction to listen for commands from master(Raspberry Pi)
void listenToPi() {

  // Serial.print("Listening for serial data... \n");
  // Wait for data to be available
  while (Serial.available() > 0) {

    // store received data as a string 
    // get new byte
    char inChar = (char)Serial.read();
    //add it to the receivedData
    receivedData += inChar;

    //break loop if incoming character is a new line
    if(inChar == '\n'){
      //if data received then break
      break;
      }
  }

  

  //return value
  // return receivedData;
}


 void parseSerialData(String data){

  // variable to keep track of comma position
  int commas = 0;

  //reset variables
  parsed_g= "";
  parsed_x = "";
  parsed_y = "";
  parsed_z = "";

  //iterate over data
  for(int i=0; i<=200; i++){

    //parse data
    if (data[i] == '\0'){ //end of data
      break; // exit
    }else if(data[i] != ',' && commas == 0){
      //get g part of g code
      parsed_g += data[i];
    }else if(data[i] !=',' && commas == 1){
      // get x value
      parsed_x += data[i];
    }else if (data[i] !=',' && commas == 2){
      // get y value
      parsed_y += data[i];
    }else if (data[i] !=',' && commas == 3){
      //get z value
      parsed_z += data[i];
    }

    //comma incrementation
    if(data[i] == ','){
      commas += 1;
    }else{
      // do nothing
    }
    
  }
  
  if (parsed_g == "G00"){
    Serial.print(" move ");  
  }else if(parsed_g == "go_to_coordinates"){
    //call go to coordinates and invoke with arguments
    
  }else if(parsed_g == "calibrate"){
    // call calibrate
    
  }else{ // run this if none match
    Serial.print("Data input into parse: ");
    Serial.print(data);
    Serial.print(" <-- -->");
    Serial.print("sysError: g function does not exist");
    Serial.print("\n");
    
  }

  
 }

 long getDistance(){
  // based on PING example by arduino
  
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, mm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(SENSOR_PIN, OUTPUT);
  digitalWrite(SENSOR_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(SENSOR_PIN, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(SENSOR_PIN, INPUT);
  duration = pulseIn(SENSOR_PIN, HIGH);

  // convert the time into a distance
  // speed of sound = 2.9 microseconds per mm
  mm = duration/2.9/2;

  return mm;
 }

void setup() {

  //speed
  xTopStepper.setSpeed(100); //rpms
  xBtmStepper.setSpeed(100); //rpms
  yStepper.setSpeed(100); //rpms
  
  // attaches the servo on pin 9 to the servo object
  zServo.attach(9); 
  set_angle(110); 

  // reserve 200 bytes for the receivedData:
  receivedData.reserve(200);

  //reserve
  parsed_g.reserve(5);
  parsed_x.reserve(5);
  parsed_y.reserve(5);
  parsed_z.reserve(5);
  
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
  pinMode(Y_PIN_1, OUTPUT);
  pinMode(Y_PIN_2, OUTPUT);
  pinMode(Y_PIN_3, OUTPUT);
  pinMode(Y_PIN_4, OUTPUT);

  Serial.print("Initalized");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (DEBUG){ 
    switch (MODE){
      case 1 : //"move_back_and_forth"
        //confirm that this section is being executed
        Serial.print("Running move_back_and_forth \n");
        // code for going back and forth using move_axes 
        move_axes(200, 200, 90);
        move_axes(-200, -200,180);
        Serial.print(analogRead(A0));
        Serial.print("\n");
  
        break;
       
      
      case 2: //"commands_over_serial" 
        //confirm that this section is being executed
        Serial.print("Running commands_over_serial \n");
        
        //code for testing if data received over serial
        // retrieve data
        listenToPi();
        
        if(receivedData != ""){
          Serial.print("Recieved Data: ");
          Serial.print(receivedData);
          Serial.print("\n");
      
          if (receivedData == "1"){
            move_axes(-200, 0, 0);
          }else if(receivedData == "2"){
            move_axes(200, 0, 0);
          }else if(receivedData == "3"){
            move_axes(0, 200, 0);
          }else if(receivedData == "4"){
            move_axes(0, -200, 0);
          }else if(receivedData == "5"){
            move_axes(0, 0, 90);
          }else if(receivedData == "6"){
            move_axes(0, 0, 180);
          }else{
            move_axes(5, 5, 90);
            move_axes(-5, -5,180);
          }
          //reset received data
          receivedData = "";
        }
        
        break;

      case 3: //"back_and_forth_move_func"
        //confirm that this section is being executed
        Serial.print("Running back_and_forth_move_func \n");
        // code for going back and forth using move
        for(int i=1; i<=300; i++){
          move_x(1);
          move_y(1);
        }
        for(int i=1; i<=300; i++){
          move_x(-1);
          move_y(-1);
          //set_angle((i/300)*180);
        }
        break;
      
      case 4: //"echo"
        //confirm that this section is being executed
        // Serial.print("Running echo \n");
        //code for testing echo
        listenToPi(); // retrieve data
        
        if(receivedData != ""){
          Serial.print(receivedData);
          // Serial.print("\n");
          //parseSerialData(receivedData.c_str());
          receivedData = "";
        }else{
          // do nothing
        }
        break;

      case 5:// test for receiving and parsing g-code
        
        listenToPi(); // retrieve data
        
        if(receivedData != ""){
          Serial.print(receivedData);
          //Serial.print("\n");
          //convert string to pointer and parse
          //parseSerialData(receivedData);
          
          receivedData = "";
        }else{
          // do nothing
        }
        break;
      
      default:
        Serial.print("Default case \n");

    }
  }else{
    // do nothing
  }
}
