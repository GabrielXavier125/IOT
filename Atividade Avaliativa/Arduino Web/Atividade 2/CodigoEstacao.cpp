#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

// Pinos dos LEDs
const int led1Pin = 7;  // LED Verde
const int led2Pin = 8;  // LED Vermelho  
const int led3Pin = 9;  // LED Amarelo

DHT dht(DHTPIN, DHTTYPE);

// Variáveis para controle de tempo
unsigned long ultimaLeituraSensor = 0;
const unsigned long intervaloLeitura = 5000; // 5 segundos

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Configura pinos dos LEDs
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  
  // LEDs iniciam desligados
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  digitalWrite(led3Pin, LOW);
  
  Serial.println("✅ Sistema IoT Pronto - Resposta Rápida!");
}

void loop() {
  // LEITURA DO SENSOR (não bloqueante)
  unsigned long tempoAtual = millis();
  
  if (tempoAtual - ultimaLeituraSensor >= intervaloLeitura) {
    // Leitura do sensor DHT
    float temperatura = dht.readTemperature();
    float umidade = dht.readHumidity();
    
    // Envia dados do sensor se forem válidos
    if (!isnan(temperatura) && !isnan(umidade)) {
      Serial.print("T:");
      Serial.print(temperatura);
      Serial.print("|U:");
      Serial.print(umidade);
      Serial.println();
    } else {
      Serial.println("ERRO: Falha na leitura do sensor");
    }
    
    ultimaLeituraSensor = tempoAtual;
  }
  
  // LEITURA DOS COMANDOS DOS LEDs (prioridade máxima)
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch (command) {
      case 'A': 
        digitalWrite(led1Pin, HIGH);
        Serial.println("LED1:ON");
        break;
      case 'a': 
        digitalWrite(led1Pin, LOW);
        Serial.println("LED1:OFF");
        break;
      case 'B': 
        digitalWrite(led2Pin, HIGH);
        Serial.println("LED2:ON");
        break;
      case 'b': 
        digitalWrite(led2Pin, LOW);
        Serial.println("LED2:OFF");
        break;
      case 'C': 
        digitalWrite(led3Pin, HIGH);
        Serial.println("LED3:ON");
        break;
      case 'c': 
        digitalWrite(led3Pin, LOW);
        Serial.println("LED3:OFF");
        break;
    }
  }
  
  // Pequeno delay não-bloqueante
  delay(10);
}