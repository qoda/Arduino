#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz

#define  R     0       // Rest

int piezoOut = 9;

void setup() {
  pinMode(piezoOut, OUTPUT);
}

int melody[] = {  };
int beats[] = {  };
int MAX_COUNT = sizeof(melody) / 2; 

long tempo = 10000;
int pause = 250;
int rest_count = 20;

int tone_ = 0;
int beat = 0;
long duration  = 0;

void loop() {
  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, c, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, g, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, g, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, c, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

   tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);
  
  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, e, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, d, 1000);
  delay(500);

  tone(piezoOut, R, 500);
  tone(piezoOut, c, 1000);
  delay(500);

  delay(10000);
}
