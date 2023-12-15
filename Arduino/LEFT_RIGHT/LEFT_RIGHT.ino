// Define motor control pins
const int in1 = 4;   // Input 1 for Motor A
const int in2 = 5;   // Input 2 for Motor A
const int in3 = 6;   // Input 1 for Motor B
const int in4 = 7;   // Input 2 for Motor B

void setup() {
  // Set up motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Move motor A forward and motor B backward for 2 seconds
  motorControlA(HIGH, LOW);
  motorControlB(LOW, HIGH);
  delay(2000);

  // Stop both motors for 1 second
  motorControlA(LOW, LOW);
  motorControlB(LOW, LOW);
  delay(1000);

  // Move motor A backward and motor B forward for 2 seconds
  motorControlA(LOW, HIGH);
  motorControlB(HIGH, LOW);
  delay(2000);

  // Stop both motors for 1 second
  motorControlA(LOW, LOW);
  motorControlB(LOW, LOW);
  delay(1000);
}

void motorControlA(int direction1, int direction2) {
  // Set the direction of Motor A
  digitalWrite(in1, direction1);
  digitalWrite(in2, direction2);
}

void motorControlB(int direction1, int direction2) {
  // Set the direction of Motor B
  digitalWrite(in3, direction1);
  digitalWrite(in4, direction2);
}
