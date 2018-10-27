int IN3 = 5; // Input3 подключен к выводу 5 left motor 
int IN4 = 4; 
int ENB = 3; 

int IN1 = 11; // right motor 
int IN2 = 10; 
int ENA = 9; 

void setup() 
{ 
    pinMode (ENB, OUTPUT); 
    pinMode (IN3, OUTPUT); 
    pinMode (IN4, OUTPUT); 
    
    pinMode (ENA, OUTPUT); 
    pinMode (IN1, OUTPUT); 
    pinMode (IN2, OUTPUT); 
}

void left_engine_run(int power, boolean front_direction) {
    if(front_direction) {
        digitalWrite (IN3, LOW); 
        digitalWrite (IN4, HIGH);
    } else {
        digitalWrite (IN4, LOW); 
        digitalWrite (IN3, HIGH);
    }
    analogWrite(ENB, power);
}

void right_engine_run(int power, boolean front_direction) {
    if(front_direction) {
        digitalWrite (IN1, LOW);
        digitalWrite (IN2, HIGH);
    } else {
        digitalWrite (IN2, LOW);
        digitalWrite (IN1, HIGH);
    }
    analogWrite(ENA, power);
}

void left_engine_stop() {
    analogWrite(ENB, 0);
}

void right_engine_stop() {
    analogWrite(ENA, 0);
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
    left_engine_run(power, false);
    right_engine_run(power, true);
}

void right(int power) {
    left_engine_run(power, true);
    right_engine_run(power, false);
}

void loop() 
{ 
    right(50);
    delay(1000);
    left(50);
    stop();
}
