#include <Arduino.h>

const int ain1Pin = 4;
const int ain2Pin = 18; 
const int bin1Pin = 5; 
const int bin2Pin = 6;
const int pwmaPin = 19; 
const int pwmbPin = 7; 

const int minimumMotorPwm = 20;

void setupMotor() {
  pinMode(ain1Pin, OUTPUT);
  pinMode(ain2Pin, OUTPUT);
  pinMode(bin1Pin, OUTPUT);
  pinMode(bin2Pin, OUTPUT);
  pinMode(pwmaPin, OUTPUT);
  pinMode(pwmbPin, OUTPUT);

  analogWrite(pwmaPin, 0);
  analogWrite(pwmbPin, 0);
}

void setMotorSpeed(float speed, int in1Pin, int in2Pin, int pwmPin) {
  const bool reverse = speed < 0;
  const float magnitude = constrain(abs(speed), 0, 255);

  if (magnitude == 0) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(pwmPin, 0);
    return;
  }

  digitalWrite(in1Pin, reverse ? LOW : HIGH);
  digitalWrite(in2Pin, reverse ? HIGH : LOW);

  const int calibratedPwm =
      minimumMotorPwm +
      static_cast<int>(magnitude * (255 - minimumMotorPwm) / 255.0f);
  analogWrite(pwmPin, calibratedPwm);
}

void motorTask() {
  setMotorSpeed(motorSpeed + motorDelta, ain1Pin, ain2Pin, pwmaPin);
  setMotorSpeed(motorSpeed - motorDelta, bin1Pin, bin2Pin, pwmbPin);
  Serial.print("Motor A: ");
  Serial.print(motorSpeed + motorDelta);
  Serial.print(" | Motor B: ");
  Serial.println(motorSpeed - motorDelta);
}
