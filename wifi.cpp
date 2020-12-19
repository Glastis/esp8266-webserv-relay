/*
** Created by Glastis on 03/02/19.
*/

#include <ESP8266WiFi.h>

#include "print.h"
#include "wifi.h"
#include "wifi_pass.h"

void                                        wifi_print_status()
{
    debug_println("------------");
    debug_print("Wifi status: ");
    debug_println(wifi_status_to_string());
    if (WiFi.status() == WL_CONNECTED)
    {
        debug_print("IP Address: ");
        Serial.println(WiFi.localIP());
    }
    debug_println("------------");
}

const char                                  *wifi_status_to_string()
{
    return (WiFi.status() == WL_CONNECTED) ? WIFI_CONNECTED_STR : WIFI_DISCONNECTED_STR;
}

void                                        wifi_check()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        wifi_print_status();
    }
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(WIFI_CONNECT_DELAY);
    }
}

void                                        wifi_init()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    wifi_check();
}
