#include <Servo.h> 
String read_buffer; //String captured from serial port
Servo myservo;  // create servo object to control a servo 
int n; //value to write to servo

void setup() {
  Serial.begin(9600);
  myservo.writeMicroseconds(1500); //set initial servo position if desired
  myservo.attach(9, 500, 2500);  //the pin for the servo control, and range if desired
  Serial.println("Ready"); // so I can keep track of what is loaded
}

void loop() {
  if (Serial.available() > 0) {
    read_buffer = Serial.readStringUntil('\n');
    // Takes the corresponding action according to the first char of the String.
    take_action(read_buffer.charAt(0));
    read_buffer = "";
    Serial.flush();
  }
  delay(2);
}

void take_action(char action) {
    switch (action) {
      case 'l':
        // Turn left.
        move_servo(30);
        delay(1000);
        move_servo(90);
        Serial.println("1");
        break;
      case 'r':
        // Turn right.
        move_servo(150);
        delay(1000);
        move_servo(90);
        Serial.println("1");
        break;
      case 'c':
        // Turn right.
        Serial.println("center");
        move_servo(90);
        break;  
      // attach or detach servo if desired
      case 'd' : 
        while (digitalRead(7)) {} //delay loop until pin 7 is low
        myservo.detach(); //detach servo
        //Serial.println("servo detached");
        goto bailout; //jump over writing to servo
        break;
      case 'a':
        myservo.attach(7); //reattach servo to pin 7
        //Serial.println("servo attached");
        goto bailout;
        break;
    }

bailout: //reenter code loop
    //Serial.print("Last servo command position: ");    
    //Serial.println(myservo.read());
    //Serial.println();
    read_buffer=""; //empty for next input
}

void move_servo(int n) {
  // auto select appropriate value
  if(n >= 500){
    //Serial.print("writing Microseconds: ");
    //Serial.println(n);
    myservo.writeMicroseconds(n);
  } else {   
    //Serial.print("writing Angle: ");
    //Serial.println(n);
    myservo.write(n); 
  }
}
