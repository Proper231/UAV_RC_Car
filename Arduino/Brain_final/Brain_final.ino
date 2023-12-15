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
      delay(5000);
    } else if (receivedSignal.equals("YIELD_SIGNAL")) {
      moveStop();
      delay(1000);
    } else if (receivedSignal.equals("P_SIGNAL")) {
      moveRight();
      delay(1000);
    } else if (receivedSignal.equals("SA_SIGNAL")) {
      moveLeft();
      delay(1000);    
      }
   }
}

void moveForward() {
  // Move both motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void moveStop() {
  // Move both motors backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveLeft() {
  // Move left by turning off right motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
