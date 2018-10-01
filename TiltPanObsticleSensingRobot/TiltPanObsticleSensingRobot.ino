#include <Servo.h>

// instantiate servo pins
Servo servo_pan;
Servo servo_tilt;

// instantiate direction sensor pins
const int sensorTopPin = 1;
const int sensorLeftPin = 2;
const int sensorBottomPin = 3;
const int sensorRightPin = 4;

// instantiate the digital pin
const int irPin = 5;

int servoPosition = 0;
int powerState = 0;

void setup() {
  
  // setup the servo pins
  servo_pan.attach(5);
  servo_tilt.attach(6);
  
  // setup all the required pin modes
  pinMode(sensorTopPin, INPUT);
  pinMode(sensorLeftPin, INPUT);
  pinMode(sensorBottomPin, INPUT);
  pinMode(sensorRightPin, INPUT);
  pinMode(irPin, OUTPUT);
  
  // swith the IR leds on
  digitalWrite(irPin, HIGH);
  
  // move the servo to a start position
  servo_pan.write(90);
  servo_tilt.write(90);
  
  // output to serial
  Serial.begin(9600);
}

void loop() {
  
  // read ir analog values
  int sensorTopVal = analogRead(sensorTopPin);
  int sensorLeftVal = analogRead(sensorLeftPin);
  int sensorBottomVal = analogRead(sensorBottomPin);
  int sensorRightVal = analogRead(sensorRightPin);
  int sensorAvg = (sensorTopVal + sensorLeftVal + sensorBottomVal + sensorRightVal) / 4;
  int sensorMinTilt = min(sensorTopVal, sensorBottomVal);
  int sensorMinPan = min(sensorLeftVal, sensorRightVal);
  
  // debug data
  Serial.print("Average: ");
  Serial.println(sensorAvg);
  
  Serial.print("Tilt: ");
  Serial.println(sensorMinTilt);
  
  Serial.print("Pan: ");
  Serial.println(sensorMinPan);
  
  // test servos
  if (sensorTopVal == sensorMinTilt) {
    Serial.println("UP");
    servo_tilt.write(50);
  }
  else if (sensorBottomVal == sensorMinTilt) {
    Serial.println("Down");
    servo_tilt.write(120);
  }
  else if (sensorLeftVal == sensorMinPan) {
    Serial.println("LEFT");
    servo_pan.write(0);
  }
  else if (sensorRightVal == sensorMinPan) {
    Serial.println("RIGHT");
    servo_tilt.write(180);
  }
  
  delay(1000);
}
