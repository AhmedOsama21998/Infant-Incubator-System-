//ESP8266
#include <ESP8266WiFi.h>
#include <dht.h> // inlcude the library of DHT11
#define dht_apin 5  // define the analog pin that we need to connect
dht DHT; // giving out dht sensor a name
#include <ArduinoJson.h>
WiFiServer server(1300);

void setup() {

   Serial.begin(9600);
   delay(10);
// WiFi Definitions
  Serial.print("Configuring access point...");
   /* You can remove the password parameter if you want the AP to be open. */
   WiFi.softAP("esp","12345678");
   delay(10000);
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);

   Serial.println("\nStarting server...");
  // start the server:
  server.begin();

}

void loop() 
{
      float  T;float H;
StaticJsonDocument<1000> doc;
DHT.read11(dht_apin); //function to read the values from the pin A0
 H=DHT.humidity;
 T=DHT.temperature;
float h = analogRead(A0);
float G =h/1023*100;
doc["H"]=H;
 doc["T"]=T;
 doc["G"]=G;
delay(1000);
serializeJsonPretty(doc, Serial);
  // Check of client has connected
  WiFiClient client = server.available();
  if(!client) 
    {
      return;
    }

  // Read the request line

 while(client.connected())
    {
            float  T;float H;
StaticJsonDocument<1000> doc;
DHT.read11(dht_apin); //function to read the values from the pin A0
 H=DHT.humidity;
 T=DHT.temperature;
  doc["H"]=H;
 doc["T"]=T;
 doc["G"]=G;
delay(1000);
serializeJsonPretty(doc, Serial);
client.print(T);
client.print(H);
  
    }
client.stop();

  // The client will actually be disconnected when the function returns and the client object is destroyed
}
