/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

#include "router.h"
#include "request.h"
#include "relay.h"

void                        route_landing(WiFiClient &client, const char *route, void *params, const char *http_params)
{
    t_relay                 *relay;

    relay = (t_relay *)params;
    reply_html_begin(client, REQUEST_RESPONSE_HEADER_OK);
    client.println(R"(<div class="col-md-8 col-md-offset-2">)");
    client.println(R"(<div class="panel panel-default">)");
    client.println(R"(<div class="panel-heading">Login</div>)");
    client.println(R"(<div class="panel-body">)");
    client.print(R"(<p>Light status : )");
    client.print(relay->activated ? "ON" : "OFF");
    client.println(R"(</p>)");
    client.println(R"(<br><br>)");
    send_button(client, "/api/relay?on", "Start");
    send_button(client, "/api/relay?off", "Stop");
    client.println(R"(<br>)");
    client.println(R"(</div>)"); //<div class="panel-body">
    client.println(R"(</div>)"); //<div class="panel panel-default">
    client.println(R"(</div>)"); //<div class="col-md-8 col-md-offset-2">
    reply_html_end(client);
}

void                        route_api_relay_set_status(WiFiClient &client, const char *route, void *params, const char *http_params)
{

}

void                        get_http_params(char *request, char *params)
{
    unsigned int            i;
    unsigned int            x;

    i = 0;
    x = 0;
    params[x] = '\0';
    while (request[i] && request[i] != '?')
    {
        ++i;
    }
    if (request[i])
    {
        request[i] = '\0';
        ++i;
        while (request[i])
        {
            params[x] = request[i];
            ++x;
            ++i;
        }
    }
}

void                        router(WiFiClient &client, void *params)
{
    unsigned int            i;
    String                  request = client.readStringUntil('\r');
    char                    route[ROUTER_ROUTE_SIZE];
    char                    parameters[ROUTER_PARAMETERS_SIZE];

    client.flush();
    i = 0;
    while (i < sizeof(route_list) - 1)
    {
        if (request.indexOf(route_list[i].uri) != -1)
        {
            memcpy(route, request.c_str(), request.length());
            get_http_params(route, parameters);
            route_list[i].action(client, request.c_str(), params, parameters);
            return;
        }
    }
    reply_html(client, "Page not found", REQUEST_RESPONSE_HEADER_NOT_FOUND);
}