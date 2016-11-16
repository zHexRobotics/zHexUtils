#include <Servo.h>
/**************************/
const int SERVO_PIN = 2;

/**************************/
Servo myservo;
/*************************/


void setup() {
    Serial.begin(57600);
    myservo.attach(SERVO_PIN);
    myservo.writeMicroseconds(1000);
}

void loop() {
    while(Serial.available() > 0)
    {
        int pos = Serial.parseInt();
        if (pos >= 500)
        {
            myservo.writeMicroseconds(pos);
        } 
    }
}
