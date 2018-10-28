#include "Servo.h"

#define ON_OFF_BUTTON    4
#define LED              5
#define RIGHT_SERVO_PIN  6
#define LEFT_SERVO_PIN   7
#define S2               8
#define COLOR            9
#define S3               10
#define S0               11
#define S1               12

#define CW               0
#define STOP             90
#define CCW              180

#define ECHO             12
#define TRIG             11

#define DELAY            50

byte red = 0;
byte green = 0;
byte blue = 0;

float distance;
bool on = true;
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
    pinMode(COLOR, INPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
}

void init_distance_detector() {
    pinMode(TRIG, OUTPUT); 
    pinMode(ECHO, INPUT);
    digitalWrite(TRIG, LOW); 
}

void setup() 
{ 
    init_engines();
    init_distance_detector();
    init_color_detector();
    pinMode(ON_OFF_BUTTON, INPUT);
    Serial.begin(9600);
}

void color()
{
    // если 2 и 3 порты отключить, то получим значение красного цвета
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    red = pulseIn(COLOR, LOW);

    // если 3 порт включить, а 2 отключить, то получим синий цвет
    digitalWrite(S3, HIGH);
    blue = pulseIn(COLOR, LOW);

    // если 2 включить, а 3 отключить, то получим зеленый цвет
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    green = pulseIn(COLOR, LOW);

    led();
}

void led() {
    if(lost_blue()) {
      digitalWrite(LED, LOW);
    } else {
      digitalWrite(LED, HIGH);
    }
}

void on_off_button() {
    if(digitalRead(ON_OFF_BUTTON) == 1) {
      on = !on;
      delay(1000);
    }
}

float get_distance() {
    int duration, cm;
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    return pulseIn(ECHO, HIGH)*0.034/2;
}

void stop() {
    leftEngine.write(STOP + 5);
    rightEngine.write(STOP);
}

void move() {
    leftEngine.write(CW);
    rightEngine.write(CCW);
}

void back() {
    leftEngine.write(CCW);
    rightEngine.write(CW);
}

void left() {
    leftEngine.write(CCW);
    rightEngine.write(CCW);
}

void right() {
    leftEngine.write(CW);
    rightEngine.write(CW);
}

void step() {
    move();
    delay(DELAY * 2);
    stop();
    delay(DELAY * 2);
}

void step_right() {
    right();
    delay(DELAY);
    stop();
    delay(DELAY);
}

void step_left() {
    left();
    delay(DELAY);
    stop();
    delay(DELAY);
}

bool lost_blue() {
    return blue > 50;
}

void find_path() {
    for(int i = 0; i < 3; i++) {
      step_right();
      if(!lost_blue()) { return; }
    }
    
    for(int i = 0; i < 6; i++) {
      step_left();
      if(!lost_blue()) { return; }
    }
    
    for(int i = 0; i < 3; i++) {
      step_right();
      if(!lost_blue()) { return; }
    }
}

void loop() 
{
    on_off_button();
    color();
    if(!on) return;
    if(lost_blue()) {
        find_path();
    } else {
        step();
    }
}
