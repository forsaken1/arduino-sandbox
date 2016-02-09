#include <Servo.h>

#define SERVO_PIN  9
#define CW   0
#define STOP 93 # for ds04 nfc servo
#define CCW  180

Servo myServo;
char c;

void setup()
{
    Serial.begin(57600);
    myServo.attach(SERVO_PIN);
    myServo.write(STOP);
}

void loop()
{
    while (Serial.available() > 0) {
        c = Serial.read();
        switch (c) {
            case 'c':
                myServo.write(CW);
                break;
            case 'w':
                myServo.write(CCW);
                break;
            case 's':
                myServo.write(STOP);
                break;
        }
    }
}
