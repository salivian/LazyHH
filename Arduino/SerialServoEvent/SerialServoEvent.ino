String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.print("get ");
    Serial.print(inputString);
    if(inputString == "F\n"){
      ServoForward();
    }
    
    if(inputString == "B\n"){
      ServoBackward();
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void ServoForward(){
  Serial.println("move Forward");
  myservo.writeMicroseconds(1000);
  delay(1000);
  myservo.writeMicroseconds(1500);
  
/*  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    Serial.println(pos);
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
    myservo.writeMicroseconds(1500);
  } 
*/
}
  
void ServoBackward(){
  Serial.println("move backward");
  myservo.writeMicroseconds(2000);
  delay(1000);
  myservo.writeMicroseconds(1500);
/*
  Serial.println("move Backward");
  for(pos = 180; pos >=1; pos -= 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  */
}
  
/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}

