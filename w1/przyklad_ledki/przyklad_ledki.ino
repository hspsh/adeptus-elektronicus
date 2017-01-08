#include <avr/io.h>
#define BUTTON1_PIN 8
#define BUTTON2_PIN 7

#define LED_TO_GROUD_PIN 11
#define LED_TO_POWER_PIN 10
#define DOUBLE_LED_PIN   9

#define SOFT_COUNTER_MAX 256

enum MODES {
  GROUND_LED = 0,
  POWER_LED = 1,
  DOUBLE_LED = 2,
  ALL_LEDS = 3,
  MODES_MAX = 4
};

boolean pwmMode;
unsigned int mode;
unsigned long lastUpdateTime;

void setupButtons(){
  pinMode(BUTTON1_PIN,  INPUT_PULLUP);     
  pinMode(BUTTON2_PIN,  INPUT_PULLUP);
}


void setupLeds(){                
  pinMode(LED_TO_GROUD_PIN, OUTPUT);     
  pinMode(LED_TO_POWER_PIN, OUTPUT);     
  pinMode(DOUBLE_LED_PIN,  OUTPUT); 
  TCCR0B = TCCR0B & B11111000 | B00000010;    // set timer 0 divisor to     8 for PWM frequency of  7812.50 Hz
  TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
}

void setup() {
  setupButtons();
  setupLeds();
  Serial.begin(115200);
  mode = ALL_LEDS;
  pwmMode = true;
  
}



void readButtons(){
  //
  // zmien tryb pracy jesli uzytkownik wcisnal jakis guzik. Funkcja zawiera naiwny mechanizm debounce.
  //
  unsigned long lastButtonPress = 0;
  if (millis() - lastButtonPress > 500) {
    
    if(digitalRead(BUTTON1_PIN)) {
      pwmMode != pwmMode;
    } else if (digitalRead(BUTTON2_PIN) ) {
      mode = (mode + 1) % MODES_MAX;
    }  
    
  }
}

void updateGroundLed() {
  static unsigned long lastUpdate = 0;
  static unsigned int dutyCycle = 128;
  if(millis() - lastUpdate < 100)
    return;
    
  if (!pwmMode){
     dutyCycle = dutyCycle > 127? 255 : 0; 
  }
  pinMode(LED_TO_POWER_PIN, OUTPUT);
  analogWrite(LED_TO_POWER_PIN, dutyCycle);
  dutyCycle = (dutyCycle - 3) % 255;
  lastUpdate = millis();
}

void updatePowerLed() {
  static unsigned long lastUpdate = 0;
  static unsigned int dutyCycle = 255;
  if((millis() - lastUpdate) < 100)
    return;
    
  if (!pwmMode){
     dutyCycle = dutyCycle > 127? 255 : 0; 
  }
  pinMode(LED_TO_GROUD_PIN, OUTPUT);
  analogWrite(LED_TO_GROUD_PIN, dutyCycle);
  dutyCycle = (dutyCycle - 1 ) & 0xff;
  lastUpdate = millis();
}

void updateDoubleLed() {
  static unsigned int whichLed = 0;
  static unsigned int dutyCycle1 = 0;
  static unsigned int dutyCycle2 = SOFT_COUNTER_MAX/2;
  static unsigned int counter = 0;
 

  if(counter > SOFT_COUNTER_MAX){
    counter = 0;
    whichLed ^= 0x01;
    if(whichLed==0) {
      dutyCycle1 = (dutyCycle1 + 1) % SOFT_COUNTER_MAX; 
    } else {
      dutyCycle2 = (dutyCycle2 + 5) % SOFT_COUNTER_MAX; 
    }
  }
  
  if (pwmMode && dutyCycle1 > SOFT_COUNTER_MAX/2) {
    dutyCycle1 = SOFT_COUNTER_MAX; 
  }  if (pwmMode && dutyCycle2 > SOFT_COUNTER_MAX/2) {
    dutyCycle2 = SOFT_COUNTER_MAX; 
  }
  
  
  if(whichLed==0){
    if(dutyCycle1 > counter) {
      pinMode(DOUBLE_LED_PIN, OUTPUT);
      digitalWrite(DOUBLE_LED_PIN, HIGH);
    } else {
      pinMode(DOUBLE_LED_PIN, INPUT);
      digitalWrite(DOUBLE_LED_PIN, LOW);
    }
  } else {
    if(dutyCycle2 > counter) {
      pinMode(DOUBLE_LED_PIN, OUTPUT);
      digitalWrite(DOUBLE_LED_PIN, LOW);
    } else {
      pinMode(DOUBLE_LED_PIN, INPUT);
      digitalWrite(DOUBLE_LED_PIN, LOW);
    }
  }
  
  
  counter += 1;
}

void updateLeds() {
  //
  // w zaleznosci od wybranego trybu zaktualizuj stan tylko wygranych ledow
  //
  if(mode == GROUND_LED || mode == ALL_LEDS){
    updateGroundLed();
  } else {
    //
    // wygas diode
    //
    digitalWrite(LED_TO_GROUD_PIN, LOW);
  }
  
  if(mode == POWER_LED || mode == ALL_LEDS){
    updatePowerLed();
  } else {
    //
    // wygas diode
    //
    digitalWrite(POWER_LED, HIGH);
  }
  
  if(mode == DOUBLE_LED || mode == ALL_LEDS){
    updateDoubleLed();
  } else {
    //
    // wygas diode - przestaw pin w stan HI-Z
    //
    pinMode(LED_TO_GROUD_PIN, INPUT);
    digitalWrite(LED_TO_GROUD_PIN, LOW);
  }
}

// the loop routine runs over and over again forever:
void loop() {
  readButtons();
  updateLeds();
}
