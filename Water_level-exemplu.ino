// Senzorul de nivel al apei este conectat in portul digital 3 (D3)

#define water_level 0

void setup() {

  // Initiem interfata serial
  Serial.begin(9600);

  // delcaram senzorul ca fiind de tip INPUT_PULLUP
  pinMode(0, INPUT_PULLUP);

}

void loop() {

  // Afisam in consola serial valorile citite de senzorul de nivel al apei
  Serial.println(digitalRead(water_level));

  // In funtie de valoare citita, se scrie in consola daca se afla sau nu apa in rezervor
  if (digitalRead(water_level) == HIGH) {
    
    Serial.println("am apa");
  }
  
  else {
    
    Serial.println("Nu am apa");
    
  }
  
  delay(2000);

}
