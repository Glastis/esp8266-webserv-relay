#include <ESP8266WiFi.h>

#include "main.h"
#include "router.h"
#include "wifi.h"
#include "relay.h"
#include "constants.h"
#include "print.h"

WiFiServer                  server(80);
t_relay                     relay;

static void                 print_ip(unsigned int every_useconds, unsigned int repeat)
{
    while (repeat > 0)
    {
        wifi_print_status();
        delay(every_useconds);
        --repeat;
    }
}

void                        setup()
{
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, LOW);
    wifi_init();
    relay_init(&relay);
#ifdef DEBUG
    Serial.begin(SERIAL_BAUDRATE);
    print_ip(500, 20);
#endif
}

void                        loop()
{
    WiFiClient              client = server.available();

    wifi_check();
    debug_println("Waiting for a client");
    if (!client)
    {
        delay(DELAY_WAITING_CLIENT);
        return;
    }
    while (!client.available())
    {
        debug_println("Waiting client to be available");
        delay(DELAY_WAITING_CLIENT);
    }
    debug_println("Client available, passing to router");
    router(client, &relay);
}