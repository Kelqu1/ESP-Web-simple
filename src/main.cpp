#include <WiFi.h>
#include <WebServer.h>

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

page += " <meta name='viewport' content='width=device-width, initial-scale=1'>";

page += "<style>";
page += " html {";
page += " font-family: Helvetica;";
page += " margin: 0px auto;";
page += " text-align: center;";
page += " }";
page += " h1 {";
page += " color: #0F3376;";
page += " padding: 2vh;";
page += " }";
page += " .button {";
page += " background-color: #4CAF50; /* Vert */";
page += " border: none;";
page += " border-radius: 6px; /* Angle arrondi */";
page += " color: white;";
page += " padding: 15px 32px;";
page += " text-align: center;";
page += " text-decoration: none;";
page += " font-size: 30px;";
page += " }";

page += " .button2 {";
page += " background-color: #f44336; /* Rouge */";
page += " }";
page += "</style>";
page += "</head>";
page += "<body>";
page += " <h1>Projet SNbot</h1>";
page += " <p><a href='/on'><button class='button'>ON</button></a></p>";
page += " <p><a href='/off'><button class='button button2'>OFF</button></a></p>";
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