#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include "SevSeg.h"

void TaskColorSensorsMotor( void *pvParameters );

void TaskLDR( void *pvParameters );

void TaskAnalogSevSeg( void *pvParameters );

  int out=2;  //RIGHT COLOR SENSOR
  int out2=7; //LEFT COLOR SENSOR
  

  int data=0;        //This is where we're going to stock our values


void setup() {

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  pinMode(out,INPUT);
  pinMode(out2,INPUT);
  

  xTaskCreate(
    TaskColorSensorsMotor
    ,  "SensorsMotor"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL );

//---------------------------------------------------------------------------------
    xTaskCreate(
    TaskLDR
    ,  "LDR"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );
//---------------------------------------------------------------------------------
  xTaskCreate(
    TaskAnalogSevSeg
    ,  "AnalogSevSeg"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  2  // priority
    ,  NULL );

    

  
  

}

void loop() {
  

}


void TaskColorSensorsMotor(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  
  int s0=3;
  int s1=4;
  int s2=5;
  int s3=6;
  //int out=2;  //RIGHT COLOR SENSOR
  //int out2=7; //LEFT COLOR SENSOR

  int IN1 = 9; //Motor
  int IN2 = 10;
  int IN3 = 11;
  int IN4 = 12;


  int red1;
  int green1;
  int blue1;

  int red2;
  int green2;
  int blue2;

  

  //int data=0;        //This is where we're going to stock our values

  bool right = false;
  bool left = false;


  int led2 = 50;           // the PWM pin the LED is attached to

  pinMode(led2, OUTPUT); 
 

  

   pinMode(s0,OUTPUT);    //pin modes for the two color sensors
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   //pinMode(out,INPUT);
   //pinMode(out2,INPUT);

   pinMode(IN1, OUTPUT);  //IN1 and IN2 are for the right motor
   pinMode(IN2, OUTPUT);
   pinMode(IN3, OUTPUT); //IN3 and IN4 are for the left motor
   pinMode(IN4, OUTPUT);

   

   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%

  
  for (;;) // A Task shall never return or exit.
  {

    right = false;
    left = false;

    digitalWrite(led2, LOW);

    // Rotate the Motor A clockwise
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    // Rotate the Motor B clockwise
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    
   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red1 value= ");
   red1=pulseIn(out,LOW);
   GetData();                   //Executing GetData function to get the value

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue1 value= ");
   blue1=pulseIn(out,LOW);
   GetData();

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green1 value= ");
   green1=pulseIn(out,LOW);
   GetData();

 
   Serial.println();

   if(red1<250 && green1<250 && blue1<100){
    Serial.println();
    Serial.print("Right Lane Detected");
    right = true;
    //Turn Left
   }

   digitalWrite(s2,LOW);        //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
   digitalWrite(s3,LOW);
   Serial.print("Red2 value= ");
   red2=pulseIn(out2,LOW);
   GetData2();                   //Executing GetData function to get the value

   digitalWrite(s2,LOW);
   digitalWrite(s3,HIGH);
   Serial.print("Blue2 value= ");
   blue2=pulseIn(out2,LOW);
   GetData2();

   digitalWrite(s2,HIGH);
   digitalWrite(s3,HIGH);
   Serial.print("Green2 value= ");
   green2=pulseIn(out2,LOW);
   GetData2();

 
   Serial.println();

   if(red2<250 && green2<250 && blue2<200){
    Serial.println();
    Serial.print("Left Lane Detected");
    left = true;
    //Turn Right
   }

   if(!(right && left)){
    digitalWrite(led2, HIGH);
    if(right){
    //go left
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
     delay(50);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
  }
  if(left){
    //go right
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, HIGH);
     delay(50);
     digitalWrite(IN1, HIGH);
     digitalWrite(IN2, LOW);
  }
}
   
    
    vTaskDelay( 100 / portTICK_PERIOD_MS ); // wait for 100ms
  }
}

//-------------------------------------------------------------------------------------

void TaskLDR(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  
  int led = 8;           // the PWM pin the LED is attached to
  int ldr = A0;            // Pin 8 is the analog output of the LDR
  int brightness;    // LDR analog output // set to a certain pin as input from LDR

  pinMode(led, OUTPUT); //pin modes for the LDR
  pinMode(ldr, INPUT);

  for (;;) // A Task shall never return or exit.
  {

    brightness=2; ////LDR
    brightness = brightness + analogRead(ldr);
    analogWrite(led, brightness);
    
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for 500 ms
  }
}

//-------------------------------------------------------------------------------------

void TaskAnalogSevSeg(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  SevSeg sevseg; 

  const int SW_pin = 53; // digital pin connected to switch output
  const int X_pin = A5; // analog pin connected to X output
  const int Y_pin = A4; // analog pin connected to Y output
  

  pinMode(53,INPUT);
  digitalWrite(SW_pin, HIGH);

  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {22, 24, 42, 44, 46, 26, 28, 40};
  bool resistorsOnSegments = true;


  byte hardwareConfig = COMMON_ANODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(50);

  sevseg.setChars("p");
  sevseg.refreshDisplay();
    
  for (;;) // A Task shall never return or exit.
  {

    Serial.print("Switch:  ");
          Serial.print(digitalRead(SW_pin));
          Serial.print(" | ");
          Serial.print("X-axis: ");
          Serial.print(analogRead(X_pin));
          Serial.print(" | ");
          Serial.print("Y-axis: ");
          Serial.print(analogRead(Y_pin));
          Serial.println(" | ");


          if(digitalRead(SW_pin)==0){
            sevseg.setChars("p");
            sevseg.refreshDisplay();
            Serial.print("Park");
          }

           if(  ( analogRead(X_pin)) <400 && ( analogRead(X_pin))>0 ){
            sevseg.setChars("d");
            sevseg.refreshDisplay();
            Serial.print("Drive");
          }

           if(  ( analogRead(X_pin))<1000 && (analogRead(X_pin))>600 ){
            sevseg.setChars("r");
            sevseg.refreshDisplay();
            Serial.print("Reverse");
          }

          if(  ( analogRead(Y_pin))<300 && (analogRead(Y_pin))>0 ){
            sevseg.setChars("n");
            sevseg.refreshDisplay();
            Serial.print("Neutral");
          }

          if(  ( analogRead(Y_pin))<1000 && (analogRead(Y_pin))>800 ){
            sevseg.setChars("n");
            sevseg.refreshDisplay();
            Serial.print("Neutral");
          }

    
    
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for 500 ms
  }
}

//-------------------------------------------------------------------------------------

void GetData(){
   data=pulseIn(out,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
}
void GetData2(){
   data=pulseIn(out2,LOW);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
   Serial.print(data);          //it's a time duration measured, which is related to frequency as the sensor gives a frequency depending on the color
   Serial.print("\t");          //The higher the frequency the lower the duration
   delay(20);
}
//------------------------------------------------------------------------------------
void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer

   if(x==1){
     
    Serial.print("PLAY");
    Serial.print("\n");
  }

  if(x==2){
     
    Serial.print("PAUSE");
    Serial.print("\n");
  }

  if(x==3){
     
    Serial.print("NEXT");
    Serial.print("\n");
  }

  if(x==4){
     
    Serial.print("PREVIOUS");
    Serial.print("\n");
  }
}
