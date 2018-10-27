int IN3 = 5; // Input3 подключен к выводу 5 left motor 
int IN4 = 4; 
int ENB = 3; 

int IN1 = 11; // right motor 
int IN2 = 10;
int ENA = 9;

int OUT = 2;
int S2 = 7;
int S3 = 6;

byte red = 0;
byte green = 0;
byte blue = 0;

void setup() 
{ 
  pinMode (ENB, OUTPUT); 
  pinMode (IN3, OUTPUT); 
  pinMode (IN4, OUTPUT); 
  
  pinMode (ENA, OUTPUT); 
  pinMode (IN1, OUTPUT); 
  pinMode (IN2, OUTPUT);

  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  Serial.begin(9600);
}

void color() // процедура color
{
  // если 2 и 3 порты отключить, то получим значение красного цвета
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  // если 3 порт включить, а 2 отключить, то получим синий цвет
  digitalWrite(S3, HIGH);
  blue = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH);

  // если 2 включить, а 3 отключить, то получим зеленый цвет
  digitalWrite(S2, HIGH);
  green = pulseIn(OUT, digitalRead(OUT) == HIGH ? LOW : HIGH); 
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
  left_engine_run(power, false);
  right_engine_run(power, true);
}

void right(int power) {
  left_engine_run(power, true);
  right_engine_run(power, false);
}

void loop() 
{ 
//  right(50);
//  delay(1000);
//  left(50);
//  delay(1000);
//  stop();
  color();
  Serial.print(" RED :" + String(red));
  Serial.print(" GREEN : " + String(green));
  Serial.println(" BLUE : " + String(blue));
  delay(500);
}