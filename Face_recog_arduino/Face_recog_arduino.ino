#include <ESP8266WiFi.h>

const char* ssid = "SSID";    //  Your Wi-Fi Name
const char* password = "PASSWORD";   // Wi-Fi Password

int LED = 13;   // led connected to GPIO2 (D7)(pin no 13 as per arduino)
WiFiServer server(80);
void setup(){
  Serial.begin(9600);
  Serial.print("Turning off wifi");
  WiFi.mode(WIFI_OFF);//Default Baudrate
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected"); 
  server.begin();  // Starts the Server
  Serial.println("Server started");
  Serial.print("IP Address of network: "); // will IP address on Serial Monitor
  Serial.println(WiFi.localIP());
  Serial.print("Copy and paste the following URL: http://"); // Will print IP address in URL format
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop(){
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }
  Serial.println("Waiting for new client");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value = HIGH;
  if(request.indexOf("/LED=ON") != -1)
  {
    digitalWrite(LED, HIGH); // Turn LED ON
    value = HIGH;
  }
  if(request.indexOf("/LED=OFF") != -1)
  {
    digitalWrite(LED, LOW); // Turn LED OFF
    value = LOW;
  }
//*------------------HTML Page Code---------------------*//

  client.println("HTTP/1.1 200 OK"); //
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>"); 
  client.println("<html>"); 
  client.print("<body style='background: #00979C'>"); 
  client.println("<h1 align ='center'>"); 
  client.println("<font-color='red'>");
  client.println("<h2>ESP 8266 LED ON/OFF Code By Sibadyuti De</h2>"); 
  client.println("</font>"); 
  client.println("</h1>"); 
  client.println("<bg color ='#00ff00'>"); 
  client.println("</bg>"); 
  client.println("<p align ='center'>"); 
  client.print("CONTROL LED: ");  
  if(value == HIGH) {
    client.print("ON");
  }
  else {
    client.print("OFF");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>ON</button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>OFF</button></a><br />");
  client.println("</html>");
//*------------------HTML Page Code end---------------------*//
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
