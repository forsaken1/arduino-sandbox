#include "IRremote.h"
#include "Servo.h"

#define SERIAL_SPEED 9600
#define DELAY        100
#define IR_PIN       11
#define SERVO_PIN    9
#define CW           0
#define STOP         90
#define CCW          180
#define KEY_UP       0xFFFF8877
#define KEY_DOWN     0xFFFF9867
#define KEY_STOP     0xFFFFA857
#define KEY_PRESS    0xFFFFFFFF

Servo myServo;
IRrecv irrecv(IR_PIN);
decode_results results;

void setup()
{
    Serial.begin(SERIAL_SPEED);
    irrecv.enableIRIn();
    myServo.attach(SERVO_PIN);
    myServo.write(STOP);
}

void loop() {
    if (irrecv.decode(&results))
    {
        int res = results.value;
        Serial.println(res, HEX);

        if(res == KEY_UP)
        {
            myServo.write(CCW);
        }
        else if(res == KEY_DOWN)
        {
            myServo.write(CW);
        }
        else if(res == KEY_STOP)
        {
            myServo.write(STOP);
        }

        irrecv.resume();
        delay(DELAY);
    }
}
