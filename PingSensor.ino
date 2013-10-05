/* HC-SR04 Ultrasonic Ping Sensor
  
   This sketch is used with an Ultrasonic Ping Sensor, model HC-SR04.
   It detects the distance by sending out a pulse and listening for the echo.
   The distance is calculated using the speed of sound.
    
   Circuit:
    * +V connection of the HC-SR04 attached to +5V
    * trig connection of the HC-SR04 attached to Digital 3
    * echo connection of the HC-SR04 attached to Digital 4 
    * GND connection of the HC-SR04 attached to ground
  
   Coded on October 4, 2013
   by: Justin Chang
   http://www.justinkjchang.com

  This code is public from http://github.com/justinkjchang

 */

// initialize variables
int pingPin = 12; // Out trigger
int echoPin = 11; // In echo
int toggle = 0; // for noise reduction
int prevDistance = 0;
int currDistance = 0;
int limit = 200; //limit as 2m

void setup() {
  // initialize serial communication:
  Serial.begin(57600);
}

void loop()
{
  // variables for duration of ping
long duration, inches, cm;
  
  // LOW pulse to ensure a clean HIGH pulse
  // module trigered by HIGH pulse of >= 2 microseconds
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  // echoPin reads for a pulse, duration time is the time from the
  // sending of the ping to when the echo off the object is received
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

 // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  // used for noise reduction & distance jumps
  // check difference betwen current distance and previous distance
  if (toggle == 0){
    prevDistance = cm;
    toggle = 1;
  } else {
    currDistance = cm;
    toggle = 0;
  }
  
//  if (currDistance > (prevDistance + 50) || currDistance == prevDistance){
//    
//  } else {
//    Serial.println((limit - prevDistance));
//  }

  // reverse distance using a limit to reverse graph function
  if (currDistance < (prevDistance * 3) || currDistance > (prevDistance / 3)){
    Serial.println((limit - prevDistance) * 2);
  }

  delay(5);
  //Serial.print("cm ");
  //Serial.println();
}

long microsecondsToCentimeters(long microseconds)
{
  // speed of sound is 340 m/s or 29 us/cm
  // to find distance, divide the distance travelled by half since the ping
  // is sent out and then comes back
  return microseconds / 29 / 2;
}
