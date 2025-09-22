#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Pino do LED integrado
#define LED_PIN 2

// Configurações Wi-Fi
const char* ssid = "MARTINS WIFI-2.4";
const char* password = "20025450";

// Configurações MQTT
const char* mqtt_server = "192.168.15.146";
const int mqtt_port = 1883;
const char* mqtt_user = "aluno";
const char* mqtt_password = "2509";

// Tópicos MQTT
const char* topic_rp1_lum = "bitdoglab1/luminosidade";
const char* topic_rp1_hum = "bitdoglab1/umidade/solo";
const char* topic_rp1_temp = "bitdoglab1/temperatura";
const char* topic_rp1_hum_air = "bitdoglab1/umidade/ar";

// Inicializa cliente MQTT
WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado!");
      // Inscrever-se nos tópicos para receber dados da RP2040
      client.subscribe(topic_rp1_lum);
      client.subscribe(topic_rp1_hum);
      client.subscribe(topic_rp1_temp);
      client.subscribe(topic_rp1_hum_air);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

// Callback MQTT
void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  message.trim(); // remove espaços em branco e \r\n no início e fim
  // Decodifica e envia para serial no padrão $TOPIC:valor
  if (String(topic) == topic_rp1_lum) {
    Serial.printf("%s\n", message.c_str());}
  // } else if (String(topic) == topic_rp1_hum) {
  //   Serial.printf("%s", message.c_str());
  // } else if (String(topic) == topic_rp1_temp) {
  //   Serial.printf("%s", message.c_str());
  // } else if (String(topic) == topic_rp1_hum_air) {
  //   Serial.printf("%s", message.c_str());
  // }

}


void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Conecta ao Wi-Fi
  Serial.print("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println(" Conectado!");
  Serial.print("IP da ESP32: ");
  Serial.println(WiFi.localIP());

  // Configura cliente MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(100); // Pequeno delay para não sobrecarregar o loop
}

