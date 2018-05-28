const int buttonRedPin = 2;
const int buttonGreenPin = 3;
const int buttonBluePin = 4;

const int redPin = 5;
const int greenPin = 6;
const int bluePin = 7;

int buttonRedVal = 0;
int buttonGreenVal = 0;
int buttonBlueVal = 0;

void setup() {
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonRedPin, INPUT);
  pinMode(buttonGreenPin, INPUT);
  pinMode(buttonBluePin, INPUT);
}

void loop() {

  // Read the button values
  buttonRedVal = digitalRead(buttonRedPin);
  buttonGreenVal = digitalRead(buttonGreenPin);
  buttonBlueVal = digitalRead(buttonBluePin);

  // Check if the pushbutton is pressed. If it is, the buttonState is HIGH and
  // the corresponding LED should be lit.
  if (buttonRedVal == HIGH) {
    analogWrite(redPin, 255);
  } else {
    analogWrite(redPin, 0);
  }
  if (buttonGreenVal == HIGH) {
    analogWrite(greenPin, 255);
  } else {
    analogWrite(greenPin, 0);
  }
  if (buttonBlueVal == HIGH) {
    analogWrite(bluePin, 255);
  } else {
    analogWrite(bluePin, 0);
  }

  delay(100);

  Serial.print(buttonRedVal);
  Serial.print(" | ");
  Serial.print(buttonGreenVal);
  Serial.print(" | ");
  Serial.println(buttonBlueVal);
}
