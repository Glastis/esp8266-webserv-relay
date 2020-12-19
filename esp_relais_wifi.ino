#include <ESP8266WiFi.h>

#include "main.h"
#include "router.h"
#include "wifi.h"
#include "relay.h"
#include "constants.h"

WiFiServer                  server(80);
t_relay                     relay;

static void                 print_ip(unsigned int every_useconds, unsigned int repeat)
{
    while (repeat > 0)
    {
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        delay(every_useconds);
        --repeat;
    }
}

void                        setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, LOW);
    wifi_init();
    relay_init(&relay);
    print_ip(500, 20);
}

void                        loop()
{
    WiFiClient              client = server.available();

    if (!client)
    {
        return;
    }
    while (!client.available())
    {
        delay(DELAY_WAITING_CLIENT);
    }
    router(client, &relay);
}
