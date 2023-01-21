#include <WiFiUdp.h>
#include "WiFi.h"

const char * ssid = "ESP32UDP";             // SSID
const char * password = "12345678";         // password

static const int Remote_Port = 9000;        // Destination port
static const int Org_Port = 9000;           // Source port

WiFiUDP UDP;

void setup()
{
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  delay(1000);

  Serial.print("AP IP address: ");            //    192.168.4.1
  Serial.println(WiFi.softAPIP());

  UDP.begin(Org_Port);
  Serial.println("Server OK");

}

void loop()
{
  char rv_data[2] = {0,0};

  if (UDP.parsePacket() > 0)
    {
      UDP.read(rv_data , 1);
      Serial.print("Recieve : ");
      Serial.println(rv_data);
      UDP.flush();
    }
}
