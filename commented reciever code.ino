// Nehan Mohammed/Sushaan Kathirgamar                 Hand Gesture-Contrlled Car Reciever          Jan 19/24
//This Arduino code interfaces with a HC05 Bluetooth transmitter to receive speed index values created from hand gestures.
//It controls the movement of a car by initializing motor controls based on the transmitted data.

int data = 0;

// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B
int enB = 3;
int in3 = 5;
int in4 = 4;\\

void setup() {
  Serial.begin(38400); // Set the Bluetooth module communication rate
  delay(100);

  // Motor pin configurations
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize motor pins
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read(); // Read data from the serial port
  }

  // Motor control based on received data
  if (data == 1) { // Forward Motion
    moveForward();
  } else if (data == 2) { // Backward Motion
    moveBackward();
  } else if (data == 4) { // Turning Left Motion
    turnLeft();
  } else if (data == 3) { // Turning Right Motion
    turnRight();
  } else { // STOP
    stopMotion();
  }

  delay(10);
}

// Functions for different motions

void moveForward() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveBackward() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnLeft() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotion() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
