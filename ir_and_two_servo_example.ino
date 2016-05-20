#include "IRremote.h"
#include "Servo.h"

#define SERIAL_SPEED     9600
#define DELAY            100
#define IR_PIN           11
#define LEFT_SERVO_PIN   8
#define RIGHT_SERVO_PIN  9
#define CW               0
#define STOP             90
#define CCW              180
#define KEY_UP           0xFFFF8877
#define KEY_DOWN         0xFFFF9867
#define KEY_LEFT         0x28D7
#define KEY_RIGHT        0x6897
#define KEY_STOP         0xFFFFA857
#define KEY_PRESS        0xFFFFFFFF

Servo leftEngine, rightEngine;
IRrecv irrecv(IR_PIN);
decode_results results;
 
void setup()
{
    Serial.begin(SERIAL_SPEED);
    irrecv.enableIRIn();
    leftEngine.attach(LEFT_SERVO_PIN);
    rightEngine.attach(RIGHT_SERVO_PIN);
    leftEngine.write(STOP + 5);
    rightEngine.write(STOP);
}
 
void loop() {
    if (irrecv.decode(&results))
    {
        int res = results.value;
        Serial.println(res, HEX);
        
        if(res == KEY_UP)
        {
            leftEngine.write(CW);
            rightEngine.write(CCW);
        }
        else if(res == KEY_DOWN)
        {
            leftEngine.write(CCW);
            rightEngine.write(CW);
        }
        else if(res == KEY_STOP)
        {
            leftEngine.write(STOP + 5);
            rightEngine.write(STOP);
        }
        else if(res == KEY_LEFT)
        {
            leftEngine.write(CCW);
            rightEngine.write(CCW);
        }
        else if(res == KEY_RIGHT)
        {
            leftEngine.write(CW);
            rightEngine.write(CW);
        }
 
        irrecv.resume();
        delay(DELAY);
    }
}