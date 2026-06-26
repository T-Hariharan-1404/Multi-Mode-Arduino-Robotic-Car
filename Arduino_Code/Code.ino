#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3); // RX, TX

// Motor pins
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENA 9
#define ENB 10

// Ultrasonic pins
#define TRIG 8
#define ECHO 12

int speedPWM = 100;   // slow speed (0–255)
int stopDistance = 25; // stop if obstacle < 50 cm

void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  stopCar();
  Serial.println("🚗 Car Initializing...");
  delay(1000);

  // === PRE-START OBSTACLE CHECK ===
  while (isObstacleClose()) {
    stopCar();
    Serial.println("⚠ Obstacle detected in front! Please clear the path...");
    delay(1000);
  }

  Serial.println("✅ Path clear! Car Ready.");
  Serial.println("Type 'f', 'b', 'l', 'r' or say 'forward', 'left', etc.");
}

void loop() {
  // Continuous check — if obstacle appears anytime, stop
  if (isObstacleClose()) {
    stopCar();
    Serial.println("⛔ Obstacle detected! Waiting...");
    while (isObstacleClose()) delay(200);  // wait till path is clear
    Serial.println("✅ Path clear! Ready again.");
  }

  if (BT.available()) {
    String input = BT.readStringUntil('\n');
    input.trim();
    input.toLowerCase();
    input.replace("\r", ""); // clean up input

    Serial.print("📥 Command: ");
    Serial.println(input);

    if (input.length() == 1)
      executeLetterCommand(input[0]);
    else
      parseSequence(input);
  }
}

// === OBSTACLE CHECK ===
bool isObstacleClose() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  int distance = duration * 0.034 / 2; // cm

  if (distance > 0) {
    Serial.print("📏 Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  return (distance > 0 && distance < stopDistance);
}

// === EXECUTION ===
void executeLetterCommand(char cmd) {
  if (isObstacleClose() && (cmd == 'f' || cmd == 'r' || cmd == 'l')) {
    stopCar(); Serial.println("⛔ Obstacle ahead!"); return;
  }

  switch (tolower(cmd)) {
    case 'f': forward(); break;
    case 'b': backward(); break;
    case 'l': left(); break;
    case 'r': right(); break;
    case 's': stopCar(); break;
    default: stopCar(); break;
  }
}

// === VOICE SEQUENCE ===
void parseSequence(String str) {
  int idx = 0;
  while (idx < str.length()) {
    while (idx < str.length() && str[idx] == ' ') idx++;
    String word = "";
    while (idx < str.length() && str[idx] != ' ') word += str[idx++];

    if (isObstacleClose() && (word == "forward" || word == "right" || word == "left")) {
      stopCar(); Serial.println("⛔ Obstacle ahead!"); return;
    }

    executeWord(word);
  }
}

void executeWord(String w) {
  if (w == "forward") { forward(); delay(1500); }
  else if (w == "backward") { backward(); delay(1500); }
  else if (w == "left") { left(); delay(600); }
  else if (w == "right") { right(); delay(600); }
  else if (w == "stop") stopCar();
  stopCar();
}

// === MOVEMENT ===
void forward() {
  analogWrite(ENA, speedPWM); analogWrite(ENB, speedPWM);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  Serial.println("🚗 Forward");
}
void backward() {
  analogWrite(ENA, speedPWM); analogWrite(ENB, speedPWM);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  Serial.println("↩ Backward");
}
void left() {
  analogWrite(ENA, speedPWM); analogWrite(ENB, speedPWM);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  Serial.println("↪ Left");
}
void right() {
  analogWrite(ENA, speedPWM); analogWrite(ENB, speedPWM);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  Serial.println("↩ Right");
}
void stopCar() {
  analogWrite(ENA, 0); analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  Serial.println("■ Stop");
}