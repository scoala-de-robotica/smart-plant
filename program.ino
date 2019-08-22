#include <DHT.h>
#define water_level D0
#define DHTPIN D6
#define DHTTYPE DHT11
#define relay D7
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(relay, OUTPUT);
  dht.begin();
  pinMode(water_level, INPUT_PULLUP);
  digitalWrite(water_level, LOW);
}

void loop() {
  int val = 0;
  int hum = 0;
  int level = digitalRead(water_level);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  //DHT11
  Serial.print("Exterior Temperature (C) = ");
  Serial.println(t);
  Serial.print("Exterior Humidity = ");
  Serial.println(h);
  delay(2000);
  
  // Notificare cand are nevoie de apa/cand are
  if (digitalRead(water_level) == HIGH) {
    
    Serial.println("am apa");
  }
  else {
    
    Serial.println("Nu am apa");
    
  }
  delay(2000);
  
// Umiditate sol
  Serial.print("Moisture Sensor Value:");
  hum = map(analogRead(0), 0, 1024, 0, 100);
  
  Serial.println(100 - hum);
  
  val = 100 - hum;

    if (val < 20) {
    // Planta are nevoie de apa
    digitalWrite(relay, HIGH);
    delay(500);
    digitalWrite(relay, LOW);
  }

  if ((val > 30) && (val < 70) ) {
    // Planta mai vrea putina apa
    // se va uda timp de 1.5 secunde
    digitalWrite(relay, HIGH);
    delay(300);
    digitalWrite(relay, LOW);
  }

  if (val > 80) {
    // Planta nu mai are nevoie de apa
    // Solul este suficient de ud
  }


}
