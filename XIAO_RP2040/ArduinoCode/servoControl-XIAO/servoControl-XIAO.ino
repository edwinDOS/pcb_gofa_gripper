/*
This code is used to control the gripper of GOFA robot
The target arduino board is the Nano v3
Author: edwinDOS
*/

// Incluímos la librería para poder controlar el servo
#include <Servo.h>

Servo myservo;               // create servo object to control a servo
int ledPin = 13;             // LED connected to digital pin 13
int do1Pin = 9;              // robot output 1 connected to digital pin D9
int do2Pin = 8;              // robot output 2 connected to digital pin D8
int do1State = 0;            // variable to store the read value
int do2State = 0;            // variable to store the read value
bool gripperStatus = false;  //flag to identify the gripper status
int pos = 0;                 // variable to store the servo position

void setup() {
  myservo.attach(2);        // Iniciamos el servo para que empiece a trabajar con el pin D2 GPIO28 como salida PWM
  pinMode(ledPin, OUTPUT);  // sets the digital pin 13 as output
  pinMode(do1Pin, INPUT);   // sets the digital pin D9 as input
  pinMode(do2Pin, INPUT);   // sets the digital pin D8 as input
  myservo.write(180);       // moves servo to open position for initialization
  // initialize serial communication:
  //Serial.begin(9600); // Uncomment to debug by console
}

void loop() {

  do1State = digitalRead(do1Pin);  // read the input from the robot via DO1 signal
  do2State = digitalRead(do2Pin);  // read the input from the robot via DO2 signal
  digitalWrite(ledPin, do1State);  // sets the LED to the DI1's value

  //Serial.print("DO2: ");
  //Serial.println(do2State);

  if (do1State == 0 && gripperStatus == true) {
    for (pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);  // tell servo to go to position in variable 'pos'
      digitalWrite(ledPin, 1);
      delay(15);  // waits 15 ms for the servo to reach the position
    }
    gripperStatus = false;  //
  }

  if (do1State == 1 && gripperStatus == false) {
    for (pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
      myservo.write(pos);                  // tell servo to go to position in variable 'pos'
      digitalWrite(ledPin, 0);
      delay(15);  // waits 15 ms for the servo to reach the position
    }
    gripperStatus = true;  // Gripper closed
  }
}
