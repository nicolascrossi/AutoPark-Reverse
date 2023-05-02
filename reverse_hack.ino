
// Author: Son Nguyen
// Gmail Address: spn1@rice.edu
// Date: 03/08/23

// Motor Controller Used: http://www.icstation.com/motor-driver-board-module-speed-controller-regulator-module-p-12328.html
#include <Encoder.h>                // Optimized Encoder Library



//interupts
#define FORWARD_PIN 2
#define BACKWARD_PIN 3
#define COMMAND_PIN 4
#define REQUEST_PIN 5



// Define the connections for steering motor controllers
#define S_INB_PIN 9
#define S_INA_PIN 10
#define S_PWM_PIN 11

#define GEAR_RATIO 1.5
#define NUM_REV 1.5
#define TICKS_PER_ROT 96
#define ALL_LEFT (int)(-NUM_REV*TICKS_PER_ROT*GEAR_RATIO)
#define ALL_RIGHT (int)(NUM_REV*TICKS_PER_ROT*GEAR_RATIO)


//130
#define MIN_SPEED 60
#define MIN_SPEED_EX1 230
#define MIN_SPEED_EX2 240
#define MAX_SPEED 255
int juwan;

#define FORWARD_STATE  1
#define BACKWARD_STATE  2

int state;


// Motor Controller Used: http://www.icstation.com/motor-driver-board-module-speed-controller-regulator-module-p-12328.html

void setup() {
  juwan = 0;
 pinMode(FORWARD_PIN, INPUT);
 pinMode(BACKWARD_PIN, INPUT);
 pinMode(COMMAND_PIN, INPUT); // lOW IS FORWARD
 pinMode(REQUEST_PIN, OUTPUT);
   // Set up the pin Modes
  pinMode(S_PWM_PIN, OUTPUT);
  pinMode(S_INA_PIN, OUTPUT);
  pinMode(S_INB_PIN, OUTPUT);

  // Set them all to 0s
  //analogWrite(S_PWM_PIN, 0); 
  digitalWrite(S_INA_PIN, LOW);
  digitalWrite(S_INB_PIN, LOW);
  state = FORWARD_STATE;

}

void drive_left(int s_speed){
  digitalWrite(S_INA_PIN, HIGH);
  digitalWrite(S_INB_PIN, LOW);
  analogWrite(S_PWM_PIN, s_speed);
}

void drive_right(int s_speed){
  digitalWrite(S_INA_PIN, LOW);
  digitalWrite(S_INB_PIN, HIGH);
  analogWrite(S_PWM_PIN, s_speed);
}

void drive_stop(){
  digitalWrite(S_INA_PIN, LOW);
  digitalWrite(S_INB_PIN, LOW);
  analogWrite(S_PWM_PIN, 0);
}

void loop() { 


   //Determine the state you are currently in 
   if ((digitalRead(COMMAND_PIN)== HIGH) && (digitalRead(BACKWARD_PIN)== HIGH)){
   digitalWrite(REQUEST_PIN,HIGH);
   state = BACKWARD_STATE;}
   if ((digitalRead(COMMAND_PIN)== LOW)  && (digitalRead(FORWARD_PIN)== HIGH)){
   digitalWrite(REQUEST_PIN,HIGH);
   state = FORWARD_STATE;}

   //if command isnt met AND your not already in that state
   if ((digitalRead(COMMAND_PIN)== HIGH) && (digitalRead(BACKWARD_PIN)== LOW) && (state != BACKWARD_STATE)){ //Backward and defualt
   drive_right(MIN_SPEED);//reverse 
   digitalWrite(REQUEST_PIN,LOW);
   }

   else if ((digitalRead(COMMAND_PIN)== LOW)&&(digitalRead(FORWARD_PIN)== LOW) && (state != FORWARD_STATE)) { //forward and defualt
   drive_left(MIN_SPEED);//forward
   digitalWrite(REQUEST_PIN,LOW);
   }
   else{   drive_stop();
   digitalWrite(REQUEST_PIN,HIGH);
   }//      drive_stop(); //    delay(1000);
}



void forward()//This function is called whenever a magnet/interrupt is detected by the arduino 
{    
  
     //drive_stop(); 
     //delay(250);
     drive_left(MIN_SPEED);//forward
     ///delay(1000);
    // drive_stop();
  }
void backward()//This function is called whenever a magnet/interrupt is detected by the arduino
{
    //drive_stop(); 
    //delay(250);
    drive_right(MIN_SPEED);//reverse 
    //delay(1000);
    //drive_stop();
  } 
