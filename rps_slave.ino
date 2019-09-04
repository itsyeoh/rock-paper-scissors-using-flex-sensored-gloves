//CS 362
//Team 33

//Ho Chon; hchon6
//Jason Yeoh; jyeoh2

//Rock-Paper-Scissor Flex Sensor Glove

//Why play rock-paper-scissor the normal way when you can upgrade it to have a better experience. 
//Using flex sensing technology and an inter-integrated Arduino circuit, it would increase the fun in playing a simple game. 
//The timer countdown can be used to prevent cheating and it would light up corresponding to a victory or loss. 
//The winner would even get its own victory tune, improving winning experience. 

int ledPin1 = 2; //green for p1
int ledPin2 = 3; //yellow for p1
int ledPin3 = 4; //red for p1
int ledPin4 = 5; //green for p2
int ledPin5 = 6; //yellow for p2
int ledPin6 = 7; //red for p2

//new game button
int ngPin = 8;
int ngState = 0;
int ng_val;
int send_ng_val = 1;

//game over button
int goPin = 9;
int goState = 0;
int go_val;
int send_go_val = 2;

int x = 0;

int buzzer = 10;

//Music definitions
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//main mario soundtrack
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  //  NOTE_D7, NOTE_B6, 0, 0,
  //
  //  NOTE_C7, 0, 0, NOTE_G6,
  //  0, 0, NOTE_E6, 0,
  //  0, NOTE_A6, 0, NOTE_B6,
  //  0, NOTE_AS6, NOTE_A6, 0,
  //
  //  NOTE_G6, NOTE_E7, NOTE_G7,
  //  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  //  0, NOTE_E7, 0, NOTE_C7,
  //  NOTE_D7, NOTE_B6, 0, 0
};

int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

#include <Wire.h>

void receiveEvent(int bytes) {
  x = Wire.read();    // read one character from the I2C
}

void setup() {
  Wire.begin(9); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  // pinMode(buzzer, OUTPUT);
  pinMode(ngPin, INPUT);
  pinMode(goPin, INPUT);

  //reads the button data to buttonstate
  ngState = digitalRead(ngPin);
  goState = digitalRead(goPin);

  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void loop() {
  ng_val = digitalRead(ngPin);
  //toggle new game button
  if (ng_val != ngState) {
    if (ngState == LOW) {
      resetLight();

      Wire.beginTransmission(8);   // transmit to device
      Wire.write(send_ng_val);              // sends x
      Wire.endTransmission();     // stop transmitting

      //3
      countDown();
      //2
      countDown();
      //1
      countDown();
    }
  }
  ngState = ng_val;

  go_val = digitalRead(goPin);
  //toggle game over button
  if (go_val != goState) {
    if (goState == LOW) {
      Wire.beginTransmission(8);   // transmit to device
      Wire.write(send_go_val);              // sends x
      Wire.endTransmission();     // stop transmitting
      delay(500);

      gameOver();
    }
  }
  goState = go_val;

  //set all leds to be off
  resetLight();
  delay(500);

  //If value received is 1, player 1 won
  if (x == 1) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin6, HIGH);
    tone(buzzer, 1500); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(3000);
    x = 0;
  }
  //If value received is 2, player 2 won
  if (x == 2) {
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    tone(buzzer, 1500); // Send 1KHz sound signal...
    delay(500);        // ...for 1/2 sec
    noTone(buzzer);     // Stop sound...
    delay(500);
    tone(buzzer, 1500); // Send 1KHz sound signal...
    delay(500);        // ...for 1/2 sec
    noTone(buzzer);     // Stop sound...
    delay(3000);
    x = 0;
  }
  //If value received is 3, result is tie
  if (x == 3) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin5, HIGH);
    delay(3000);
    x = 0;
  }
  else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
  }

}

//countdown timer by using led and buzzer
void countDown() {
  //red led
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin6, HIGH);
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(500);        // ...for 1/2 sec
  noTone(buzzer);     // Stop sound...
  delay(500);        // ...for 1/2 sec

  //yellow led
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin6, LOW);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin5, HIGH);
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(500);        // ...for 1/2 sec
  noTone(buzzer);     // Stop sound...
  delay(500);        // ...for 1/2 sec

  //green led
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin4, HIGH);
  tone(buzzer, 2000); // Send 1KHz sound signal...
  delay(500);        // ...for 1/2 sec
  noTone(buzzer);     // Stop sound...
  delay(500);        // ...for 1/2 sec

  //  tone(buzzer, 500); // Send 1KHz sound signal...
  //  delay(3500);        // ...for 1/2 sec
  //  noTone(buzzer);     // Stop sound...
  //  delay(500);

  int size = sizeof(melody) / sizeof(int);
  for (int i = 0; i < size; i++) {
    tone(buzzer, melody[i], 250);
    delay(100);
    noTone(buzzer);
  }

}

//game over function to play soundtrack
void gameOver() {
  int size = sizeof(underworld_melody) / sizeof(int);
  for (int i = 0; i < size; i++) {
    int noteDuration = 1000 / underworld_tempo[i];
    tone(buzzer, underworld_melody[i], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer);
  }

  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  delay(500);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
  delay(500);

  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(ledPin5, HIGH);
  digitalWrite(ledPin6, HIGH);
  delay(500);

  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
  delay(500);

}

void resetLight() {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin4, LOW);
  digitalWrite(ledPin5, LOW);
  digitalWrite(ledPin6, LOW);
}
