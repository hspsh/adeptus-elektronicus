#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define MEASUREMENTS_INTERVAL 100
#define BRIGHTNESS_PIN A0
#define RED_LED 11
#define BLUE_LED 10
#define GREEN_LED 9
#define DHTPIN 13
#define DHTTYPE           DHT11
#define BUZZER 2

#define LED1 A0
#define LED2 7
#define LED3 5
#define LED4 A2

#define SW1 8
#define SW2 6
#define SW3 4
//#define SW4 22

#define NOISE_INPUT A7

DHT_Unified dht(DHTPIN, DHTTYPE);

int brightness = 0;
int noise = 0;
float temperature = 0;
float humidity = 0;
unsigned long int lastMeasurement = 0;

void setup( void ) {
  sensor_t sensor;
  pinMode(BRIGHTNESS_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  Serial.begin(115200);
  dht.begin();

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
//  pinMode(SW1, INPUT_PULLUP);
//  pinMode(SW2, INPUT_PULLUP);
//  pinMode(SW3, INPUT_PULLUP);
//  pinMode(SW4, INPUT_PULLUP);
}

int lastMeasurementType = 0;

void loop( void ) {
  if (millis() - lastMeasurement > MEASUREMENTS_INTERVAL) {

    
    lastMeasurement = millis();
    switch(lastMeasurementType){
      case 0:
        brightness = analogRead(BRIGHTNESS_PIN);
        break;
      
      case 1:
      case 3:
      case 5:
      case 7:
      case 9:
        //
        // empty 
        //
        break;
        
      case 2:
          sensors_event_t event;
          dht.temperature().getEvent(&event);
          
          if (isnan(event.temperature)) {
            temperature = -1;
          }
          else {
            temperature = event.temperature;
          }
    
          dht.humidity().getEvent(&event);
          if (isnan(event.relative_humidity)) {
            humidity = -1;
          }
          else {
            humidity = event.relative_humidity;
          }
        break;


      case 4:
        noise = analogRead(NOISE_INPUT);
        break;
        
      case 6:
        Serial.print(temperature);
        Serial.print(',');
        Serial.print(humidity);
        Serial.print(',');
        Serial.print(brightness);
        Serial.print(',');
        Serial.println(noise);
        // jasnosc ma wartosc od 0 do 1024, przemapuj na 0-255 dla pwm
        analogWrite(RED_LED, brightness / 4);
        // temperatura ma wartosc od 0 do 50, z grubsza przemapuj na 0-255 dla pwm
        analogWrite(BLUE_LED, temperature * 4);
        // wilgotnosc ma wartosc od 20 do 95 %, z grubsza przmapuj na 0-255 dla pwm
        analogWrite(GREEN_LED, humidity * 2);
    
        digitalWrite(BUZZER, HIGH);
        delayMicroseconds(100);
        digitalWrite(BUZZER, LOW);
        break;
    }
    
    if(lastMeasurementType==9){
      lastMeasurementType=0;
    } else {
      lastMeasurementType++;
    }
    /*
    if(lastMeasurementType==1){
      digitalWrite(LED1, HIGH);
    }else if(lastMeasurementType==4){
      digitalWrite(LED2, HIGH);
    }else if(lastMeasurementType==6){
      digitalWrite(LED3, HIGH);
    }else if(lastMeasurementType==9){
      digitalWrite(LED4, HIGH);
    } else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, LOW);
      
    }*/

    
  }
}
