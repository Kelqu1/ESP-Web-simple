#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "BTS_CIEL";
const char* password = "ERIR1234";
WebServer server(80); // Création d'un serveur WEB qui écoute sur le port 80
const int led = 2; // Led intégrée à l'ESP32

void PageHTML()
{
String page = "<!DOCTYPE html>";
page += "<html>";
page += "<head>";
page += " <title>Page Projet SNBot</title>";
page += "</head>";
page += "<body>";
page += " <h1> Commande Led </h1>";
page += " <p><a href='/on'><button>ON</button></a></p>";
page += " <p><a href='/off'><button>OFF</button></a></p>";
page += "</body>";
page += "</html>";
server.setContentLength(page.length());// Indique au navigateur la
// longueur de la page
server.send(200, "text/html", page);


}
void PageOn()
{
digitalWrite(led, HIGH);
server.sendHeader("Location","/"); // Retour à la page d’accueil
server.send(303); // Le serveur indique au navigateur qu’il l’envoie faire
//une redirection
}
void PageOff()
{
digitalWrite(led, LOW);
server.sendHeader("Location","/");
server.send(303);
}
void PageNotFound()
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
server.on("/", PageHTML);
server.on("/on", PageOn);

server.on("/off", PageOff);
server.onNotFound(PageNotFound);
server.begin();
Serial.println("Serveur web actif!");
}
void loop()
{
server.handleClient();// Attente de demande du client
}