#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *softAPssid = "ESP8266_AP"; // ESP WIFI HOTSPOT SSID
const char *softAPpassword = "password"; // ESP WIFI HOTSPOT PASSWORD

const int trigPin = 4; // D2 pin (GPIO 4)
const int echoPin = 5; // D1 pin (GPIO 5)

ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration on ECHO pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  // Calculate person's height in feet and inches
  float baseToSensor = 176.5;  // Distance from sensor to base in centimeters
  float personHeight = baseToSensor - distance;

  // Convert height to feet and inches
  int feet = personHeight / 30.48;  // 1 meter = 30.48 inches
  int inches = (personHeight - feet * 30.48) / 2.54;  // 1 inch = 2.54 cm

  // HTML response
String html = "<html><body>";
html += "<h1>Height Measurement</h1>";
html += "<p>Person's Height: " + String(feet) + " feet " + String(inches) + " inches</p>";
html += "<button onclick='refreshPage()'>Refresh</button>";
html += "<script>";
html += "function refreshPage() {";
html += "  location.reload(true);";
html += "}";
html += "</script>";
html += "</body></html>";
  // Send the HTML response to the client
  server.send(200, "text/html", html);

  Serial.println("Person's Height: " + String(feet) + " feet " + String(inches) + " inches");
}


void calc_height() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the pulse duration on ECHO pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  float distance = duration * 0.034 / 2;

  // Calculate person's height in feet and inches
  float baseToSensor = 176.5;  // Distance from sensor to base in centimeters
  float personHeight = baseToSensor - distance;

  // Convert height to feet and inches
  int feet = personHeight / 30.48;  // 1 meter = 30.48 inches
  int inches = (personHeight - feet * 30.48) / 2.54;  // 1 inch = 2.54 cm

  // HTML response
String html = "<html><body>";
html += "<h1>Height Measurement</h1>";
html += "<p>Person's Height: " + String(feet) + " feet " + String(inches) + " inches</p>";
html += "<button onclick='refreshPage()'>Refresh</button>";
html += "<script>";
html += "function refreshPage() {";
html += "  location.reload(true);";
html += "}";
html += "</script>";
html += "</body></html>";
  // Send the HTML response to the client
//  server.send(200, "text/html", html);

  Serial.println("Person's Height: " + String(feet) + " feet " + String(inches) + " inches" + "  IN CM: [" + String(personHeight)+"]");
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up SoftAP
  WiFi.softAP(softAPssid, softAPpassword);

  Serial.println("SoftAP started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Setup the server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  if (Serial.available()) {
    char a = Serial.read();
    if (a == 'a') {
      calc_height();
    }
  }
}
