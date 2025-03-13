#include <EEPROM.h>
#define EEPROM_SIZE 512

//NETWORK
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

//OLED
#include <GyverOLED.h>
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
#define OLED_SDA 0
#define OLED_SCL 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//DS18B20
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
float temp;

#define GPIO_MODE 3  // Пин выбора режима

struct Config {
  char WFAP[32];
  char WFAP_PWD[16];
  char WFSSID[32];
  char WF_PWD[16];
  char MQTT[32];
  char MQTT_PORT[16];
  char MQTT_USER[32];
  char MQTT_PWD[16];
  char MQTT_TOPIC[32];
  char MQTT_TOPIC_NAME[64];
  char MQTT_CLIENT_STATUS[32];
  char mqttClientID[20];
  char CFG[16];
} cfg;

ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  pinMode(GPIO_MODE, INPUT_PULLUP);
  loadConfig();
  oled.init(OLED_SDA,OLED_SCL);  
  oled.clear();   
  oled.update();
  
  if (digitalRead(GPIO_MODE) == HIGH) {
    setupConfigMode();
  } else {
    setupSensorMode();
  } 
}

void setupSensorMode() { 
  drawScreen("Режим датчика");
  sensor.begin(); //sensor.setResolution(12);
  if(digitalRead(ONE_WIRE_BUS))
  drawScreen("Датчик обнаружен");
else
  drawScreen("Датчик не обнаружен"); 

  getTemperature(); drawScreen("Поехали...");
  WiFi.begin(cfg.WFSSID, cfg.WF_PWD);
  while (WiFi.status() != WL_CONNECTED) { 
    getTemperature();
    drawScreen("Подключение к WiFi.."); 
    delay(500);
  }
  drawScreen("Подклчено к " + String(cfg.WFSSID));
  
  mqttClient.setServer(cfg.MQTT, String(cfg.MQTT_PORT).toInt());
  reconnect(); 
}

void reconnect() {
    while (!mqttClient.connected()) {
        drawScreen("Подключение к MQTT...");
        // Подключение с LWT
        if (mqttClient.connect(cfg.mqttClientID, cfg.MQTT_USER, cfg.MQTT_PWD, cfg.MQTT_CLIENT_STATUS, 0, true, "offline")) {
            drawScreen("Подключено к MQTT");
            mqttClient.publish(cfg.MQTT_CLIENT_STATUS, "online", true);  // Сообщаем, что устройство в сети
        } else {
           drawScreen("Ошибка, код: " + String(mqttClient.state()));
            delay(2000);
               }
    }
}



void setupConfigMode() {
  WiFi.softAP(cfg.WFAP, cfg.WFAP_PWD);
  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();
  drawSetupScreen("КОНФИГУРИРОВАНИЕ");
}

void sendTemperature() {
  if (!mqttClient.connected()) reconnect();
  getTemperature();
  drawScreen(cfg.MQTT_TOPIC_NAME);
  mqttClient.publish(cfg.MQTT_TOPIC, String(temp).c_str());
}

void loop() {
  if (digitalRead(GPIO_MODE) == HIGH) {
    server.handleClient();
  } else {
    sendTemperature();}
}