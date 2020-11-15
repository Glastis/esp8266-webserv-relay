#include <Arduino.h>
#include <ESP8266Wifi.h>

#include "main.h"
#include "router.h"
#include "wifi.h"

WiFiServer server(80);

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    wifi_init();
}

void loop()
{
    WiFiClient client = server.available();

    if (!client)
    {
        return;
    }
    while (!client.available())
    {
        delay(DELAY_WAITING_CLIENT);
    }

    router(client);
    client.flush();
    if (request.indexOf("/LED=ON") != -1)
    {
        digitalWrite(output, HIGH);
        value = HIGH;
    }
    if (request.indexOf("/LED=OFF") != -1)
    {
        digitalWrite(output, LOW);
        value = LOW;
    }

    // Display GPIO status
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.print("GPIO status: ");

    if (value == HIGH)
    {
        client.print("ON");
    }
    else
    {
        client.print("OFF");
    }

    client.println("<br><br>");
    client.println("Switch manually GPIO state");
    client.println("<br><br>");
    client.println("Turn <a href=\"/LED=ON\">ON</a><br>");
    client.println("Turn <a href=\"/LED=OFF\">OFF</a><br>");
    client.println("</html>");

    Serial.println("");
}
