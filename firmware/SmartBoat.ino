#include <SoftwareSerial.h>

// ===== BLUETOOTH =====
SoftwareSerial BT(10, 11); // RX, TX

// ===== MOTOR TRÁI =====
const int ENA = 3;
const int IN1 = 5;
const int IN2 = 6;

// ===== MOTOR PHẢI =====
const int ENB = 9;
const int IN3 = 7;
const int IN4 = 8;

// ===== THAM SỐ =====
int runSpeed  = 160;   // tốc độ chạy ổn định
int kickSpeed = 200;   // tốc độ ban đầu
int kickTime  = 100;   // ms

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();
  BT.begin(9600);
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();

    switch (cmd) {
      case 'F': forward();   break;
      case 'B': backward();  break;
      case 'L': turnLeft();  break;
      case 'R': turnRight(); break;
      case 'S': stopMotor(); break;
    }
  }
}

// ===== HÀM =====

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  kickStart();
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  kickStart();
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, kickSpeed);
  delay(kickTime);
  analogWrite(ENB, runSpeed);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, kickSpeed);
  analogWrite(ENB, 0);
  delay(kickTime);
  analogWrite(ENA, runSpeed);
}

void kickStart() {
  analogWrite(ENA, kickSpeed);
  analogWrite(ENB, kickSpeed);
  delay(kickTime);

  analogWrite(ENA, runSpeed);
  analogWrite(ENB, runSpeed);
}

void stopMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
