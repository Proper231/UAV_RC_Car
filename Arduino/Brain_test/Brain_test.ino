// Define motor control pins
const int in1 = 6;   // Input 1 for Motor A
const int in2 = 5;   // Input 2 for Motor A
const int in3 = 7;   // Input 1 for Motor B
const int in4 = 4;   // Input 2 for Motor B

// Function prototypes
void moveForward();
void moveBackward();
void moveLeft();
void moveRight();
void moveStop();

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize motor control
  moveForward();
  delay(5000);
}

void loop() {
  if (Serial.available() > 0) {
    String receivedSignal = Serial.readStringUntil('\n');

    // Check the received signal and perform corresponding actions
    if (receivedSignal.equals("STOP_SIGNAL")) {
      moveStop();
      delay(3000);
    } else if (receivedSignal.equals("YIELD_SIGNAL")) {
      moveStop();
      delay(1000);
    } else if (receivedSignal.equals("P_SIGNAL")) {
      moveRight();
    } else if (receivedSignal.equals("SA_SIGNAL")) {
      moveLeft();   
      }
   }
}

void moveForward() {
  // Move both motors forward
  motorControlA(HIGH, LOW);
  motorControlB(HIGH, LOW);
}

void moveStop() {
  // Move both motors backward
  motorControlA(LOW, LOW);
  motorControlB(LOW, LOW);
}

void moveLeft() {
  // Move left by turning off right motor
  motorControlA(LOW, HIGH);
  motorControlB(HIGH, LOW);
  delay(2000);
}

void moveRight() {
  motorControlA(HIGH, LOW);
  motorControlB(LOW, HIGH);
  delay(2000);
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
