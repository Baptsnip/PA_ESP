#include <ESP8266WiFi.h> // Remplacez par <WiFi.h> si vous utilisez un ESP32

// Configuration du point d'accès
const char* ssid = "ESP_AP"; // Nom du réseau Wi-Fi
const char* password = "12345678"; // Mot de passe du réseau (minimum 8 caractères)
// Variable à définir (booléenne) pour le choix de l'IP statique ou DHCP
bool useStaticIP = true;  // Par exemple, définissez à `true` pour utiliser une IP statique

WiFiServer server(1234); // Port TCP du serveur


void setup() {
  Serial.begin(115200);

  // Configuration en mode point d'accès
  WiFi.softAP(ssid, password);
  Serial.println("Point d'accès configuré");
  Serial.print("Nom du réseau: ");
  Serial.println(ssid);
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.softAPIP());

  // Démarrage du serveur
  server.begin();
  Serial.println("Serveur TCP démarré");
}

void loop() {
  // Vérifie si un client se connecte
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connecté");
    while (client.connected()) {
      // Lecture des données envoyées par le client
      if (client.available()) {
        String data = client.readStringUntil('\n');
        data.trim(); // Retire les espaces et retours à la ligne
        Serial.print("Reçu: ");
        Serial.println(data);

        // Vérifie si la commande est $DD
        if (data.startsWith("$DD")) {
          String packet = "Aucun paquet spécifique en attente";
          client.println(packet);
          Serial.print("Requête Telnet $DD: ");
          Serial.println(packet);
        } 
        // Vérifie si c'est une commande G-code
        else if (data.startsWith("G") || data.startsWith("M")) {
          Serial.print("Commande G-code reçue: ");
          Serial.println(data);
          client.println("Commande G-code acceptée: " + data);
        } else {
          // Réponse pour les commandes non reconnues
          client.println("Commande inconnue: " + data);
        }
      }
    }
    client.stop(); // Déconnecte le client
    Serial.println("Client déconnecté");
  }
}