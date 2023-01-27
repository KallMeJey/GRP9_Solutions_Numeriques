#include <DHT.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#define brocheDeBranchementDHT 4    // La ligne de communication du DHT22 sera donc branchée sur la pin GPIO4 de l'Arduino
#define typeDeDHT DHT22             // Ici, le type de DHT utilisé est un DHT22

// Instanciation de la librairie DHT
DHT dht(brocheDeBranchementDHT, typeDeDHT);

const char* ssid = "Invite-ESIEA";
const char* password = "hQV86deaazEZQPu9a";
const char* mqttServer = "10.8.128.250";
const int mqttPort = 1883;
const char* topic = "ESIEA/grpEJMM";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup () {
  
  Serial.begin(9600);

  connectToWiFi();
  client.setServer(mqttServer, mqttPort);

  Serial.println("Programme de test du DHT22");
  Serial.println("==========================");
  Serial.println();

  // Initialisation du DHT22;
  dht.begin();
}
 
// =================
// Boucle principale
// =================
void loop () {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Lecture des données
  float tauxHumidite = dht.readHumidity();              // Lecture du taux d'humidité (en %)
  float temperatureEnCelsius = dht.readTemperature();   // Lecture de la température, exprimée en degrés Celsius

  // Vérification si données bien reçues
  if (isnan(tauxHumidite) || isnan(temperatureEnCelsius)) {
    Serial.println("Aucune valeur retournée par le DHT22. Est-il bien branché ?");
    delay(2000);
    return;         // Si aucune valeur n'a été reçue par l'Arduino, on attend 2 secondes, puis on redémarre la fonction loop()
  }



  // Calcul de la température ressentie
  float temperatureRessentieEnCelsius = dht.computeHeatIndex(temperatureEnCelsius, tauxHumidite, false); // Le "false" est là pour dire qu'on travaille en °C, et non en °F
  
  // Affichage des valeurs
  Serial.print("Humidité = "); Serial.print(tauxHumidite); Serial.println(" %");
  Serial.print("Température = "); Serial.print(temperatureEnCelsius); Serial.println(" °C");
  Serial.print("Température ressentie = "); Serial.print(temperatureRessentieEnCelsius); Serial.println(" °C");
  Serial.println();

  DynamicJsonDocument jsonTemp(1024);
  DynamicJsonDocument jsonHum(1024);
  jsonTemp["temperature"] = temperatureEnCelsius;
  jsonHum["humidity"] = tauxHumidite;
  String jsonStringTemp;
  String jsonStringHum;
  serializeJson(jsonTemp, jsonStringTemp);
  serializeJson(jsonHum, jsonStringHum);
  client.publish("ejmm/temperature", jsonStringTemp.c_str());
  client.publish("ejmm/humidity", jsonStringHum.c_str());
  
  
  // Temporisation de 2 secondes
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqttServer)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}