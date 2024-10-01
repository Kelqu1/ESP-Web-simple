#include <WiFi.h>
#include <WebServer.h>
// Potentiomètre relié à GPIO 34 (Analog ADC1_CH6)
const int potPin = 34;

const char* ssid = "BTS_CIEL";
const char* password = "ERIR1234";
WebServer server(80);
const int led = 2;
bool etatLed = 0;
char texteEtatLed[2][10] = {"ÉTEINTE!","ALLUMÉE!"};
void handleRoot()
{
String page = "<!DOCTYPE html>";
page += "<html lang='fr'>";
page += "<head>";
page += " <title>Serveur ESP32</title>";

page += " <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8' />";

page += " <link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";
page += "</head>";

page += "<body>";
page += " <div class='w3-card w3-blue w3-padding-small w3-jumbo w3-center'>";
page += " <p>Valeur Potentiomètre : "; page += String(analogRead(potPin)); + "</p>";
page += " </div>";
page += " <div class='w3-bar'>";
page += " <a href='/on' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>ON</a>";
page += " <a href='/off' class='w3-bar-item w3-button w3-border w3-jumbo' style='width:50%; height:50%;'>OFF</a>";
page += " </div>";
page += " <div class='w3-center w3-padding-16'>";
page += " <p>Serveur hébergé sur un ESP32</p>";
page += " <i>Projet SNBot</i>";
page += " </div>";
page += "</body>";
page += "</html>";
server.setContentLength(page.length());
server.send(200, "text/html", page);
}
void handleOn()
{
etatLed = 1;
digitalWrite(led, HIGH);
server.sendHeader("Location","/");
server.send(303);
}
void handleOff()
{
etatLed = 0;
digitalWrite(led, LOW);
server.sendHeader("Location","/");
server.send(303);
}
void handleNotFound()
{
server.send(404, "text/plain", "404: Not found");
}

void setup()
{
Serial.begin(9600);
delay(1000);
Serial.println("\n");
pinMode(led, OUTPUT);
digitalWrite(led, LOW);
WiFi.persistent(false);
WiFi.begin(ssid, password);
Serial.print("Tentative de connexion...");
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(100);
}
Serial.println("\n");
Serial.println("Connexion etablie!");
Serial.print("Adresse IP: ");
Serial.println(WiFi.localIP());
server.on("/", handleRoot);
server.on("/on", handleOn);
server.on("/off", handleOff);
server.onNotFound(handleNotFound);
server.begin();
Serial.println("Serveur web actif!");
}
void loop()
{
server.handleClient();
}