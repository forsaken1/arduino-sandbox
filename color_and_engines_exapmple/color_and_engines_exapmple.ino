int IN3 = 6; // Input3 подключен к выводу 5 left motor 
int IN4 = 7; 
int ENB = 5; 

int IN1 = 2; // right motor 
int IN2 = 4;
int ENA = 3;

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

void init_engines() {
    pinMode (ENB, OUTPUT); 
    pinMode (IN3, OUTPUT); 
    pinMode (IN4, OUTPUT); 
    
    pinMode (ENA, OUTPUT); 
    pinMode (IN1, OUTPUT); 
    pinMode (IN2, OUTPUT);
}

void init_color_detector() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(OUT, INPUT);

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

void color() // процедура color
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
}

float get_distance() {
    int duration, cm;
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 
    return pulseIn(echo, HIGH)*0.034/2; 
}

void left_engine_run(int power, boolean front_direction) {
    if(front_direction) {
        digitalWrite (IN3, HIGH); 
        digitalWrite (IN4, LOW);
    } else {
        digitalWrite (IN4, HIGH); 
        digitalWrite (IN3, LOW);
    }
    analogWrite(ENB, power);
}

void right_engine_run(int power, boolean front_direction) {
    if(front_direction) {
        digitalWrite (IN1, HIGH);
        digitalWrite (IN2, LOW);
    } else {
        digitalWrite (IN2, HIGH);
        digitalWrite (IN1, LOW);
    }
    analogWrite(ENA, power);
}

void left_engine_stop() {
    digitalWrite(ENB, 0);
}

void right_engine_stop() {
    digitalWrite(ENA, 0);
}

void stop() {
    left_engine_stop();
    right_engine_stop();
}

void move(int power) {
    left_engine_run(power, true);
    right_engine_run(power, true);
}

void back(int power) {
    left_engine_run(power, false);
    right_engine_run(power, false);
}

void left(int power) {
    left_engine_run(power, true);
    right_engine_run(power, false);
}

void right(int power) {
    left_engine_run(power, false);
    right_engine_run(power, true);
}

void step(int power) {
    move(power);
    delay(10);
    stop();
    delay(10);
}

void step_right(int power) {
    right(power);
    delay(10);
    stop();
    delay(10);
}

void step_left(int power) {
    left(power);
    delay(10);
    stop();
    delay(10);
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
