#include <Arduino.h>
#include <ESP8266Wifi.h>

#include "main.h"
#include "router.h"
#include "wifi.h"
#include "relay.h"

WiFiServer      server(80);
t_relay         relay;

void relay_init();

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);
    wifi_init();
    relay_init(&relay);
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
    router(client, &relay);
}
