#include "Servo.h"

#define LEFT_SERVO_PIN   7
#define RIGHT_SERVO_PIN  6
#define CW               0
#define STOP             90
#define CCW              180

#define LED              4

int OUT = 9; // color detector
int S0 = 11;
int S1 = 12;
int S2 = 8;
int S3 = 10;

byte red = 0;
byte green = 0;
byte blue = 0;

int echo = 12; // distance detector
int trig = 11; 

float distance;

Servo leftEngine, rightEngine;

void init_engines() {
    leftEngine.attach(LEFT_SERVO_PIN);
    rightEngine.attach(RIGHT_SERVO_PIN);
    stop();
}

void init_color_detector() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
}

void init_distance_detector() {
    pinMode(trig, OUTPUT); 
    pinMode(echo, INPUT);
    digitalWrite(trig, LOW); 
}

void setup() 
{ 
    init_engines();
    init_distance_detector();
    init_color_detector();
    Serial.begin(9600);
}

void color()
{
    // если 2 и 3 порты отключить, то получим значение красного цвета
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(OUT, LOW);

    // если 3 порт включить, а 2 отключить, то получим синий цвет
    digitalWrite(S3, HIGH);
    blue = pulseIn(OUT, LOW);

    // если 2 включить, а 3 отключить, то получим зеленый цвет
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    green = pulseIn(OUT, LOW);

    if(lost_blue()) {
      digitalWrite(LED, LOW);
    } else {
      digitalWrite(LED, HIGH);
    }
}

float get_distance() {
    int duration, cm;
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 
    return pulseIn(echo, HIGH)*0.034/2; 
}

void stop() {
    leftEngine.write(STOP + 5);
    rightEngine.write(STOP);
}

void move(int power) {
    leftEngine.write(CW);
    rightEngine.write(CCW);
}

void back(int power) {
    leftEngine.write(CCW);
    rightEngine.write(CW);
}

void left(int power) {
    leftEngine.write(CCW);
    rightEngine.write(CCW);
}

void right(int power) {
    leftEngine.write(CW);
    rightEngine.write(CW);
}

void step(int power) {
    move(power);
    delay(10);
    stop();
    delay(10);
}

void step_right(int power) {
    right(power);
    delay(1);
    stop();
    delay(1);
}

void step_left(int power) {
    left(power);
    delay(1);
    stop();
    delay(1);
}

bool lost_blue() {
    Serial.println(String(blue));
    return blue > 50;
}

void find_path(int power) {
    for(int i = 0; i < 3; i++) {
      step_right(power);
      if(!lost_blue()) { return; }
    }
    
    for(int i = 0; i < 6; i++) {
      step_left(power);
      if(!lost_blue()) { return; }
    }
    
    for(int i = 0; i < 3; i++) {
      step_right(power);
      if(!lost_blue()) { return; }
    }
}

void loop() 
{ 
    color();
    if(lost_blue()) {
        find_path(100);
    } else {
        step(80);
    }
}
