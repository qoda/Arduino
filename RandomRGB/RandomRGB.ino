/*
An RGB LED example which changes the colour randomly.
*/

// Instantiate the pins
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

// Instantiate the colour variables
int redVal = 0;
int greenVal = 0;
int blueVal = 0;

void setup () {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop () {

  // Give the colour values random values depending on the previous values
  redVal = random(0, 255);
  greenVal = random(0, 255);
  blueVal = random(0, 255);


  // Write the values to the digital pins
  analogWrite(redPin, redVal);
  analogWrite(greenPin, greenVal);
  analogWrite(bluePin, blueVal);

  Serial.print("Red: ");
  Serial.println(redVal);

  Serial.print("Green: ");
  Serial.println(greenVal);

  Serial.print("Blue: ");
  Serial.println(blueVal);

  delay(1000);
}
