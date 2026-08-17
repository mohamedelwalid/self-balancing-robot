float angle = 0;
float motorSpeed = 0;
int motorDelta = 0;

void setup() {
  Serial.begin(115200);
  setupSensor();
  setupPID();
  setupMotor();
}

void loop() {
  sensorTask();
  pidTask();
  motorTask();
}
