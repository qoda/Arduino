// PIR Sensor controlled LED
const int ledPin = 13;
const int pirPin = 2;

int pirState = LOW;
int val = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  Serial.begin(9600);
}

void loop(){
    val = digitalRead(pirPin);
    if (val == HIGH) {
        digitalWrite(ledPin, HIGH);
        if (pirState == LOW) {
            Serial.println("Motion detected!");
            pirState = HIGH;
        }
    }
    else {
        digitalWrite(ledPin, LOW);
        if (pirState == HIGH){
            Serial.println("Motion ended!");
            pirState = LOW;
        }
    }
}
