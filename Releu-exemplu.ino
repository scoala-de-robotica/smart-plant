// Conectam releul la pinul digital 7 (D7)
#define relay D7

void setup() {

  // Definim pinul D7 ca fii unul de OUTPUT
  pinMode(relay, OUTPUT);

  // Initiem interfata serial
  Serial.begin(9600);

}

void loop() {
  // Punem pompa in functiune
  digitalWrite(relay, HIGH);

  // Functioneaza timp de 5 secunde
  delay(5000);

  // Oprim pompa din functiune
  digitalWrite(relay, LOW);

  delay(10);

}
