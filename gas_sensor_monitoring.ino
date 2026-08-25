#include <ThingSpeak.h>

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// WiFi credentials
const char* ssid = "vivo T3x 5G";
const char* password = "09876543";

// ThingSpeak
unsigned long channelID = 3469498;
const char* writeAPIKey = "5HZ3XIGO8FZFDQYA";

WiFiClient client;

// Gas sensor
#define GAS_SENSOR A0

void setup()
{
  Serial.begin(115200);

  pinMode(GAS_SENSOR, INPUT);

  Serial.println();
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

void loop()
{
  // Read gas sensor
  int gasValue = analogRead(GAS_SENSOR);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Send data to ThingSpeak
  ThingSpeak.setField(1, gasValue);

  int response = ThingSpeak.writeFields(3469498, "5HZ3XIGO8FZFDQYA");

  if (response == 200)
  {
    Serial.println("Data successfully sent to ThingSpeak!");
  }
  else
  {
    Serial.print("ThingSpeak Error: ");
    Serial.println(response);
  }

  // ThingSpeak requires at least 15 seconds between updates
  delay(20000);
}