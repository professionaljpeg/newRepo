#include <Adafruit_CircuitPlayground.h>

float midi[127];
int a440 = 440;
int buttonPinL = 4;
int buttonPinR = 5;
volatile bool buttonFlagL = 0;
volatile bool buttonFlagR = 0;

int theRobots[28][2] = {
  {50, 65},
  {50, 65},
  {48, 65},
  {48, 65},
  {50, 65},
  {50, 65},
  {48, 65},
  {48, 65},
  {50, 65},
  {50, 65},
  {127, 130},
  {53, 65},
  {53, 65},
  {127, 130},
  {50, 65},
  {50, 65},
  {48, 65},
  {48, 65},
  {50, 65},
  {50, 65},
  {48, 65},
  {48, 65},
  {50, 65},
  {50, 65},
  {38, 65},
  {38, 65},
  {38, 65},
  {38, 65},
};

int abLydian[24][2] = {
  {56, 500},
  {56, 250},
  {56, 125},
  {58, 500},
  {58, 250},
  {58, 500},
  {60, 500},
  {60, 250},
  {60, 125},
  {62, 500},
  {62, 250},
  {62, 125},
  {63, 500},
  {63, 250},
  {63, 125},
  {65, 500},
  {65, 250},
  {65, 125},
  {67, 500},
  {67, 250},
  {67, 125},
  {68, 500},
  {68, 250},
  {68, 125},

};

int pitches[8] = {56, 58, 60, 62, 63, 65, 67, 68};
int rhythms[3] = {500, 250, 125};

void setup() {
  // put your setup code here, to run once.
  Serial.begin(9600);
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(buttonPinL), buttonISR_L, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPinR), buttonISR_R, FALLING);
  generateMIDI();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (buttonFlagL == 1) {
    for (int i = 0; i < sizeof(theRobots)/sizeof(int); i++) {
        CircuitPlayground.playTone(midi[theRobots[i][0]],theRobots[i][1]);
        Serial.println(theRobots[i][0]);
        delay(1);
    }
    buttonFlagL = 0;
  } 
  
  if (buttonFlagR == 1) {
    for (int i = 0; i < 8; i++) {
      int randPitchIndex = random(0,7);
      int randRhythmIndex = random(0,2);
      int randPitch = pitches[randPitchIndex];
      int randRhythm = rhythms[randRhythmIndex];
      CircuitPlayground.playTone(midi[abLydian[randPitch][0]], abLydian[randRhythm][1]);
      Serial.println(abLydian[randPitch][0]);
       Serial.println("meow");
      delay(1);
    }
    buttonFlagR = 0;
  }
  delay(500);
}

void buttonISR_L() {
  buttonFlagL = 1;
}

void buttonISR_R() {
  buttonFlagR = 1;
}

void generateMIDI()
{
  for (int x = 0; x < 127; ++x)
  {
    midi[x] = (a440 / 32.0) * pow(2.0, ((x - 9.0) / 12.0));
    Serial.println(midi[x]);
  }
}
