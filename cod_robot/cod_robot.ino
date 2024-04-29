#define LEFT_ENA 6 // ENA pin for the left motor
#define LEFT_IN1 A0 // IN1 pin for the left motor
#define LEFT_IN2 A1 // IN2 pin for the left motor
#define RIGHT_ENB 5 // ENB pin for the right motor
#define RIGHT_IN3 A2 // IN3 pin for the right motor
#define RIGHT_IN4 A3 // IN4 pin for the right motor

#define IR_LEFT A4 // Analog pin for the left infrared sensor
#define IR_CENTER A5 // Analog pin for the center infrared sensor
#define IR_RIGHT A6 // Analog pin for the right infrared sensor

#define TRIGGER_PIN 8 // Digital pin for ultrasonic sensor trigger
#define ECHO_PIN 7 // Digital pin for ultrasonic sensor echo

void setup() 
{
  pinMode(LEFT_ENA, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_ENB, OUTPUT);
  pinMode(RIGHT_IN3, OUTPUT);
  pinMode(RIGHT_IN4, OUTPUT);
  
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_CENTER, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop()
{
  int irLeftValue = analogRead(IR_LEFT);
  int irCenterValue = analogRead(IR_CENTER);
  int irRightValue = analogRead(IR_RIGHT);
  float distance = getDistance();

  // If the center sensor detects the line and there's no obstacle, move forward
  if (irCenterValue < 500 && distance > 10) {
    moveForward();
  }
  // If the left sensor detects the line but not the center, turn left
  else if (irLeftValue < 500) {
    turnLeft();
  }
  // If the right sensor detects the line but not the center, turn right
  else if (irRightValue < 500) {
    turnRight();
  }
  // If both sensors are off the line and there's no obstacle, stop
  else {
    stopMoving();
  }
}

void moveForward() 
{
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(LEFT_ENA, 255); // Full speed for left motor
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);
  analogWrite(RIGHT_ENB, 255); // Full speed for right motor
}

void turnLeft() 
{
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, HIGH);
  analogWrite(LEFT_ENA, 200); // Adjust speed as needed
  digitalWrite(RIGHT_IN3, HIGH);
  digitalWrite(RIGHT_IN4, LOW);
  analogWrite(RIGHT_ENB, 200); // Adjust speed as needed
}

void turnRight() 
{
  digitalWrite(LEFT_IN1, HIGH);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(LEFT_ENA, 200); // Adjust speed as needed
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, HIGH);
  analogWrite(RIGHT_ENB, 200); // Adjust speed as needed
}

void stopMoving() 
{
  digitalWrite(LEFT_IN1, LOW);
  digitalWrite(LEFT_IN2, LOW);
  analogWrite(LEFT_ENA, 0);
  digitalWrite(RIGHT_IN3, LOW);
  digitalWrite(RIGHT_IN4, LOW);
  analogWrite(RIGHT_ENB, 0);
}

float getDistance() 
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}