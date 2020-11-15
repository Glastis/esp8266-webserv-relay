/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#include <Arduino.h>
#include <WiFiClient.h>

#include "router.h"
#include "request.h"

void                        route_landing(WiFiClient &client, const char *route)
{

}

void                        route_api_relay_set_status(WiFiClient &client, const char *route)
{

}

void                        router(WiFiClient &client)
{
    unsigned int            i;
    String request = client.readStringUntil('\r');

    i = 0;
    while (i < sizeof(route_list) - 1)
    {
        if (request.indexOf(route_list[i].uri) != -1)
        {
            route_list[i].action(client, request.c_str());
            return;
        }
    }
    reply_html(client, "Page not found", REQUEST_RESPONSE_HEADER_NOT_FOUND);
}