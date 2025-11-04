#include <DHT.h>

#define DHTPIN 2       // Pino do sensor DHT11
#define DHTTYPE DHT11  // Tipo do sensor
DHT dht(DHTPIN, DHTTYPE);

#define LED_VERDE 3
#define LED_VERMELHO 4
#define LED_AMARELO 5

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
}

void loop() {
  float temperatura = dht.readTemperature();

  if (isnan(temperatura)) {
    Serial.println("Erro");
    delay(500);
    return;
  }

  // Envia a temperatura via serial
  Serial.println(temperatura);

  // Lógica de controle automático
  if (temperatura > 30.0) {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARELO, HIGH); // Ventilador ligado
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW); // Ventilador desligado
  }

  delay(500); // Atualiza a cada 0,5s
}
