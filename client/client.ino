#include "WiFi.h"
#include <WiFiUdp.h>

const char * ssid = "ESP32UDP";             // SSID
const char * password = "12345678";         // password

IPAddress ip(192, 168, 4, 2);               // IP Address
IPAddress gateway(192,168, 4, 1);           // Gateway Address
IPAddress subnet(255, 255, 255, 0);         // Subnet Address

IPAddress sv_ip(192, 168, 4, 1);            // Server IP Address

static const int Remote_Port = 9000;        // Destination port
static const int Org_Port = 9000;           // Source port

WiFiUDP UDP;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  // Try forever
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(1000);
  }

  Serial.println("Connected");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  UDP.begin(Org_Port);
  Serial.println("Client OK");

}

char a = 'A';
void loop()
{
  Serial.println("Send : " + String(a));

  UDP.beginPacket(sv_ip, Remote_Port);
  UDP.write(a);
  UDP.endPacket();

  a ++;
  if(a > 'F') a = 'A';

  delay(3000);
}
