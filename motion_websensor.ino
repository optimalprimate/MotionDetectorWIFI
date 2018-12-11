#include <ESP8266WiFi.h>

const char* ssid     = "ssid";
const char* password = "password";

const char *host = "maker.ifttt.com";
const char *privateKey = "ifttt key";

int pir_pin = D4; 
int pir_stat = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(pir_pin, INPUT);
  
  digitalWrite(pir_pin, LOW); 
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println();
  int pir_stat = digitalRead(pir_pin);
  Serial.print(pir_stat); 
  if (pir_stat == 1) {
    
  
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  Serial.println("sending data to server");

  String url = "/trigger/";
  url += "motion_detected";
  url += "/with/key/";
  url += privateKey;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
 
delay(30000);
  Serial.println();
  Serial.println("closing connection");
  client.stop();
    }
}
