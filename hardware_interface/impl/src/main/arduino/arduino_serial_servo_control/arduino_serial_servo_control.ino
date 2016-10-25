#include <Servo.h>

const short THROTTLE_PIN_NR = 9;
const short STEERING_PIN_NR = 6; 
const short DEFAULT_DURATION_THROTTLE = 1500;
const short DEFAULT_DURATION_STEERING = 1500;
const long DEFAULT_SERIAL_COMMUNICATION_DATA_RATE = 57600;

Servo throttleServo;
Servo steeringServo;

void setup() {
  setupServos();
  setupSerial();

  throttleValue = DEFAULT_DURATION_THROTTLE;
  steeringValue = DEFAULT_DURATION_STEERING;
}

void setupServos() {
  // attach servo instances to PWM pins
  throttleServo.attach(THROTTLE_PIN_NR);
  steeringServo.attach(STEERING_PIN_NR);

  // small delay for attaching to kick in
  delay(10);

  // set Servo's to default values
  throttleServo.writeMicroseconds(DEFAULT_DURATION_THROTTLE);
  steeringServo.writeMicroseconds(DEFAULT_DURATION_STEERING);
}

void setupSerial() {
  Serial.begin(DEFAULT_SERIAL_COMMUNICATION_DATA_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("INITIALIZED COMMUNICATION");
}

void loop() {  
    // No standard loop code as all is done through Serial Events
}

void serialEvent() {
  while (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    Serial.read();

    String cmd = msg.substring(0, 3);

    int value;
    if (msg.length() > 3) {
      value = msg.substring(3).toInt();
    } else {
      value = 0;
    }

    executeCommand(cmd, value);
  }
}

void executeCommand(String cmd, int value) {
  if (cmd == "THR") {
    updateServo(throttleServo, value);
    returnCurrentState();
  } else if (cmd == "STE") {
    updateServo(steeringServo, value);
    returnCurrentState();
  } else if (cmd == "GET") {
    returnCurrentState();
  } else if (cmd == "INI") {
    valueStep = value;
  }
}

void updateServo(Servo servo, int value) {
  servo.writeMicroseconds(value);
}

void returnCurrentState() {
    String currentState = "";
    currentState.concat(throttleServo.read());
    currentState.concat(";");
    currentState.concat(steeringServo.read());
    Serial.println(currentState);
    Serial.flush();
}

