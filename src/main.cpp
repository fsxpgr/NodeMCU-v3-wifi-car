#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Eliftech_2.4G";
const char *password = "Golang-Node.js";
String page = "";

ESP8266WebServer server(80);

#define D1 05
#define D2 04
#define D5 14
#define D6 12
#define D7 13
#define D8 15

void forward()
{
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
}
void stop()
{
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
}
void right()
{
    digitalWrite(D5, LOW);
    digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
}
void left()
{
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
}
void back()
{
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
}

void setup()
{
    Serial.begin(9600);
    page = "<div style=\"background-color:aqua\">    <h1 style=\"text-align:center;\">Controll panel </h1>    <a href=\"f\" style=\"display: inline-block;width: 99%;        height: 60px; text-align:center;  border: 4px double black; font-size: 41px;    background-color: springgreen;\">        FORVARD    </a>    <a href=\"l\" style=\"display: inline-block; width: 47%;    float: left;    text-align:center;     height: 60px;border: 4px double black; font-size: 41px;    background-color: springgreen;\">        LEFT    </a>    <a href=\"r\" style=\"display: inline-block;  width: 47%;    float: right;   text-align:center;      height: 60px;border: 4px double black; font-size: 41px;    background-color: springgreen;\">        RIGHT    </a>    <a style=\"display:inline-block; width: 99%;   text-align:center;  height: 60px; border: 4px double black; font-size: 41px;    background-color: springgreen;\" href=\"b\">        BACK    </a>    <a style=\"display:inline-block; width: 99%;    text-align:center;     height: 60px;border: 4px double black; font-size: 41px;    background-color: indianred;\" href=\"s\">        STOP    </a></div>";
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", []() {
        forward();
        server.send(200, "text/html", page);
    });

    server.on("/f", []() {
        forward();
        server.send(200, "text/html", page);
    });

    server.on("/b", []() {
        back();
        server.send(200, "text/html", page);
    });

    server.on("/r", []() {
        right();
        server.send(200, "text/html", page);
    });

    server.on("/l", []() {
        left();
        server.send(200, "text/html", page);
    });

    server.on("/s", []() {
        stop();
        server.send(200, "text/html", page);
    });

    server.begin();

    Serial.println("Web server started!");
}

void loop(void)
{
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    server.handleClient();
}
