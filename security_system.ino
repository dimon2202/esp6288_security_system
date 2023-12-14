// Програма з оповіщеннями у бот 
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "Kyivstar_XXXX";
const char* password = "XXXXXXXXX";

#define BOTtoken "XXXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
#define CHAT_ID "XXXXXXXX"


WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int sensorValue;
const int laserPin = 2;
const int ledPin = 5;
const int buzzerPin = 4;

void setup() {
  Serial.begin(115200);
  client.setInsecure();
  
  pinMode(laserPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(A0, INPUT);  // Assuming your light sensor is connected to A0

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi соединение установлено");
  Serial.print("IP адрес: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "СИСТЕМУ ОХОРОНИ АКТИВОВАНО", "");
}

void loop() {

  digitalWrite(laserPin, HIGH);

  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  
  

  if (sensorValue > 800) {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);


  } else {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

        // Оповіщення про порушення сигналу світла
    bot.sendMessage(CHAT_ID, "Система зафіксувала порушення!", "");
  }

  delay(200);
}


