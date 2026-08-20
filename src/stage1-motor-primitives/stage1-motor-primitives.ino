const int LEFT_EN  = 5;
const int LEFT_IN1 = 7;
const int LEFT_IN2 = 8;

const int RIGHT_EN  = 6;
const int RIGHT_IN3 = 9;
const int RIGHT_IN4 = 11;

// Signed speed per side: sign selects direction, magnitude sets duty.
// Direction logic differs between sides because the motors are mounted
// mirror-image — left forward is IN1 HIGH, right forward is IN4 HIGH.
void setSpeeds(int left, int right) {
  if (left > 0) {
    digitalWrite(LEFT_IN1, HIGH);
    digitalWrite(LEFT_IN2, LOW);
  } else if (left < 0) {
    digitalWrite(LEFT_IN1, LOW);
    digitalWrite(LEFT_IN2, HIGH);
  } else {
    // LOW/LOW coasts. HIGH/HIGH would brake — coasting chosen so the
    // chassis decelerates smoothly, at the cost of a longer stopping
    // distance.
    digitalWrite(LEFT_IN1, LOW);
    digitalWrite(LEFT_IN2, LOW);
  }

  analogWrite(LEFT_EN, constrain(abs(left), 0, 255));

  if (right > 0) {
    digitalWrite(RIGHT_IN3, LOW);
    digitalWrite(RIGHT_IN4, HIGH);
  } else if (right < 0) {
    digitalWrite(RIGHT_IN3, HIGH);
    digitalWrite(RIGHT_IN4, LOW);
  } else {
    digitalWrite(RIGHT_IN3, LOW);
    digitalWrite(RIGHT_IN4, LOW);
  }

  analogWrite(RIGHT_EN, constrain(abs(right), 0, 255));
}

void forward(int speed) {
  setSpeeds(speed, speed);
}

void backward(int speed) {
  setSpeeds(-speed, -speed);
}

void spinLeft(int speed) {
  setSpeeds(-speed, speed);
}

void spinRight(int speed) {
  setSpeeds(speed, -speed);
}

void halt() {
  setSpeeds(0, 0);
}

void setup() {
  pinMode(LEFT_EN, OUTPUT);
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_EN, OUTPUT);
  pinMode(RIGHT_IN3, OUTPUT);
  pinMode(RIGHT_IN4, OUTPUT);

  // Test sequence — run with the wheels clear of the ground.
  forward(200);
  delay(1000);
  halt();
  delay(500);
  spinRight(200);
  delay(1000);
  halt();
}

void loop() {
}
