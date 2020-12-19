/*
** Created by Glastis on 03/02/19.
*/

#include <ESP8266WiFi.h>

#include "wifi.h"
#include "wifi_pass.h"

void                                        wifi_check()
{
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
