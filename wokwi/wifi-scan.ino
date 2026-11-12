// ===== INCLUDES =====
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ===== SENSOR DE TEMPERATURA =====
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// ===== ATUADORES =====
#define LED_PIN 2
#define BUZZER_PIN 4   // novo atuador sonoro

// ===== REDE =====
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ===== BROKER MQTT =====
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

// ===== TÓPICOS =====
const char* topico_temperatura = "parquecoco/ponto1/temperatura";
const char* topico_alerta = "parquecoco/ponto1/alerta";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.print("Conectando ao WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  client.setServer(mqtt_server, mqtt_port);
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("ESP32ParqueCoco")) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura base do DHT22 + variação dinâmica simulada
  float base = dht.readTemperature();
  if (isnan(base)) {
    Serial.println("Falha ao ler o sensor DHT22!");
    delay(2000);
    return;
  }
  float temperatura = base + random(-30, 180) / 10.0;

  // Gás simulado
  int gas = random(100, 3500);

  String payload = "{\"ponto\": \"1\", \"temperatura\": " + String(temperatura) +
                    ", \"gas\": " + String(gas) + "}";

  client.publish(topico_temperatura, payload.c_str());
  Serial.println("Publicado: " + payload);

  // Condição de risco: aciona LED + buzzer + publica alerta
  if (temperatura > 40 || gas > 3000) {
    client.publish(topico_alerta, "Possivel foco de incendio - verificar ponto 1");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);   // emite som de 1000 Hz
    Serial.println("ALERTA: possivel foco de incendio!");
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);       // desliga o som
  }

  delay(5000);
}