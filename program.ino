// Librarie folosita pentru DHT11
#include <DHT.h>

#define soilMoistureSensor 0 // Pin senzor de umiditate in sol
#define relay D7 // Pin releu pompa
#define waterLevelSensor D6 // Pin senzor de nivel al apei
#define DHTPIN D5 // Pin senzor de temperatura si umiditate

// Defineste tipul senzorului folosit ("DHT11")
#define DHTTYPE DHT11

// Initiere senzor DHT11
DHT dht(DHTPIN, DHTTYPE);

//## Variabile
int pragUmiditateSol = 40;
float timpUdarePlanta = 1500;

void setup() {
  //## Setari Senzor umiditate si temperatura
  // Pornire senzorul
  dht.begin();
  //##


  //## Setari senzor nivel apa
  //Defineste pin-ul waterLevelSensor ca fiind unul de intrare, de tip PULL UP
  pinMode(waterLevelSensor, INPUT_PULLUP);
  //##

  //## Setari NodeMCU
  // Initiere interfata serial
  Serial.begin(9600);
  // Setare pin inclus ca pin de iesire
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //##
}

void loop() {
  int umiditateSol = citesteUmiditateSol();
  bool nivelApaInVas = citesteNivelApaInVas();
  float umiditateExterior = citesteUmiditateExterior();
  float temperaturaExterior = citesteTempExterior();

  Serial.print("|Status sistem: ");
  Serial.print("Pregatit");

  Serial.print("|Umiditate in sol: ");
  Serial.print(umiditateSol);

  Serial.print("|Nivel apa in vas: ");
  if (nivelApaInVas == HIGH) {
    Serial.print("Da");
  } else {
    Serial.print("Nu");
  }

  Serial.print("|Umiditate in exterior: ");
  Serial.print(umiditateExterior);
  Serial.print(" %");

  Serial.print("|Temperatura in exterior: ");
  Serial.print(temperaturaExterior);
  Serial.print(" °C");

  Serial.print("|Prag de udare: ");
  Serial.print(pragUmiditateSol);

  Serial.print("|Timp de udare: ");
  Serial.print(timpUdarePlanta / 1000);
  Serial.println(" sec.");

  //Daca umiditate din sol este sub pragul acceptat
  if (umiditateSol < pragUmiditateSol) {
    Serial.println();
    Serial.println("Umiditate redusa. Initializez procesul de udare a plantei.");
    //Verifica daca in vas este apa
    if (nivelApaInVas) {
      Serial.println("Este prezenta apa in vas. Pornire pompa");
      // Stinge ledul se status de pe NodeMcu
      digitalWrite(LED_BUILTIN, HIGH);
      //Porneste pompa pentru intervalul de timp de udare
      startPompa(timpUdarePlanta);
      Serial.println("Asteapta 1 minut.");
      // Asteapta 1 minut ca apa sa se propage in sol
      for (int i = 0; i < 180; i++) {
        int umiditateSol = citesteUmiditateSol();
        bool nivelApaInVas = citesteNivelApaInVas();
        float umiditateExterior = citesteUmiditateExterior();
        float temperaturaExterior = citesteTempExterior();

        Serial.print("|Status sistem: ");
        Serial.print("In asteptare ");
        Serial.print((180000 - (i * 1000)) / 1000);
        Serial.print(" secunde");

        Serial.print("|Umiditate in sol: ");
        Serial.print(umiditateSol);

        Serial.print("|Nivel apa in vas: ");
        if (nivelApaInVas == HIGH) {
          Serial.print("Da");
        } else {
          Serial.print("Nu");
        }

        Serial.print("|Umiditate in exterior: ");
        Serial.print(umiditateExterior);
        Serial.print(" %");


        Serial.print("|Temperatura in exterior: ");
        Serial.print(temperaturaExterior);
        Serial.println(" °C");
        delay(1000);
      }
    }
    else {
      Serial.println("Nu pot uda planta, pentru ca nu este apa in vas");
      //Altfel porneste ledul de pe NodeMcu in semn de alerta ca in vas nu mai este apa
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  // Reia procesul odata la 5 secunde
  delay(5000);
}

void startPompa(int timp) {

    //## Setari RELEU
  // Defineste pinul relay ca fiind unul de iesire
  pinMode(relay, OUTPUT);
  // pentru ca este un releu activ doar daca simte semnal pe pinul de semnal, atunci aplica tensiune maxima pe pin relay

  //##
  
  // Pune pompa in functiune
  digitalWrite(relay, LOW);

  // Functioneaza cat timp primeste ca parametru
  delay(timp);
  pinMode(relay, INPUT);
}

int citesteUmiditateSol() {
  // Citeste valoare areturnata de pin-ul analog A0 si transpune-o in intervalul 0, 100, deoarece ea este citita in intervalul 0, 1024
  return map(analogRead(soilMoistureSensor), 0, 1024, 100, 0);
}

bool citesteNivelApaInVas() {
  // Citeste valoarea returnata de pin-ul senzorului
  int nivelApaInVas = digitalRead(waterLevelSensor);

  //Returneaza daca valoare citita este HIGH sau LOW
  return (nivelApaInVas == HIGH);

}

float citesteTempExterior() {
  return dht.readTemperature();
}

float citesteUmiditateExterior() {
  return dht.readHumidity();
}
