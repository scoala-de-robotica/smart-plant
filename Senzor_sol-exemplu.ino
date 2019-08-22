void setup() {

  // Initiem interfata serial
  Serial.begin(9600);

}

// Declaram o variabila "hum" (humidity)
int hum = 0;

// Declaram o variabila "val"
int val = 0;

void loop() {

  // Afisam in consola serial mesajul "Moisture Sensor Value:"
  Serial.print("Moisture Sensor Value:");

  // Schimbam scala valorilor citite de senzor, din 0 - 1024 in 0 - 100
  hum = map(analogRead(0), 0, 1024, 0, 100);

  // Afisam valoarea citita de catre senzor in consola serial
  Serial.println(100 - hum);

  // atribuim variabilei "val", rezultatul scaderii
  val = 100 - hum;

  if (val < 20) {
    // Planta are nevoie de apa
    // se va uda timp de 3.5 secunde
  }

  if ((val > 30) && (val < 70) ) {
    // Planta mai vrea putina apa
    // se va uda timp de 1.5 secunde
  }

  if (val > 80) {
    // Planta nu mai are nevoie de apa
  }


  delay(1000);

}
