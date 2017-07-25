#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h> 

const char *APssid = "myESP";
const char *APpassword = "password"; //the password should be 8 char or more

ESP8266WebServer server(80); 


//setting the addresses
IPAddress APip(192,168,8,1);
IPAddress APgateway(192, 168, 8, 1);
IPAddress APsubnet(255, 255, 255, 0);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected to ESP8266 AP with webserver</h1>");
} 


void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
//  WiFi.mode(WIFI_AP);          //switching to AP mode ? why not need?
  WiFi.softAP(APssid, APpassword);
  WiFi.softAPConfig(APip,APgateway,APsubnet);   // tricky: config should be after begin
//  WiFi.begin();
//  WiFi.config(ip,gateway,subnet);   // tricky: config should be after begin

  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.begin();

  Serial.print("AP SSID: ");
  Serial.println(APssid);
  Serial.print("AP login password: ");
  Serial.println(APpassword);
  
  Serial.println("HTTP server started");
  Serial.print("at AP IP address: ");
  Serial.println(myIP);
 
  
  
}

void loop() {
  server.handleClient(); 
}

/*
 * copy from  
 * http://runtimeprojects.com/2016/10/esp8266-tutorial-part-4-how-to-turn-your-esp8266-into-an-access-point/
 * By admin, 27th October 2016
 * 
 */

 /*
  * copy from esp8266 wifi example 
  * WiFiAccessPoint.ino
  * 
  * 
  */
