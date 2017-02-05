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

DHT_Unified dht(DHTPIN, DHTTYPE);

int brightness = 0;
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
        
      case 6:
        Serial.print(temperature);
        Serial.print(',');
        Serial.print(humidity);
        Serial.print(',');
        Serial.println(brightness);
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
    
    //
    // guziki!
    //

    
  }
}
