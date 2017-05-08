/*
 * Kod sluzacy do prezentacji projektu 1 ze spotkania 4 adeptus elektronicus.
 * 
 * Program sluzy do sterowania prostym zamkiem elektromagnetycznym podlaczonym za 
 * posrednictwem odpoweidniego ukladu do pinu `LOCK_PIN`. Stan wysoki na wyjsciu 
 * wlacza zamek, stan niski wylacza. Sterowanie zamkiem odbywa sie za posrednictwem
 * przyciskow `OPEN_BUTTON` oraz `CLOSE_BUTTON`. Oba przyciski powinny zwierac 
 * wejscie do masy.
 * 
 * UWAGA pin ze wzgledu na ograniczona przestrzen na plytce prototypowej zastosowano
 * trik - pin `SHORT_TO_GROUND` sluzy tylko i wylacznie do doprowadzenia masy do 
 * przyciski  jednego z przyciskow. W przypadku reprodykcji projektu pin ten moze 
 * zostac wykorzystany do czegos innego.
 * 
 */

#define OPEN_BUTTON 4
#define CLOSE_BUTTON 8
#define SHORT_TO_GROUND 5
#define LOCK_PIN 9
#define LED_PIN 13



void setup() {
  pinMode(OPEN_BUTTON, INPUT);
  digitalWrite(OPEN_BUTTON, HIGH);
  pinMode(CLOSE_BUTTON, INPUT);
  digitalWrite(CLOSE_BUTTON, HIGH);
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);
  pinMode(SHORT_TO_GROUND, OUTPUT);
  digitalWrite(SHORT_TO_GROUND, LOW);
}

void loop() {
  if(!digitalRead(OPEN_BUTTON)){
    digitalWrite(LOCK_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
  } else if (!digitalRead(CLOSE_BUTTON)) {
    digitalWrite(LOCK_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

}
