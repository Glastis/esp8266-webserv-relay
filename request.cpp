/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "request.h"

static void                 reply_headers(WiFiClient &client, const char *type, const char *status)
{
    client.print(REQUEST_RESPONSE_HEADER_HTTP_VERSION);
    client.println(status);
    client.println(type);
    client.println("");
}

void                        reply(WiFiClient &client, const char *file, const char *type, const char *status)
{
    reply_headers(client, type, status);
    client.println(file);
}

void                        reply_html(WiFiClient &client, const char *html, const char *status)
{
    reply_headers(client, REQUEST_RESPONSE_HEADER_CONTENT_TYPE_HTML, status);
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println(html);
    client.println("</html>");
}

void                        reply_json(WiFiClient &client, const char *json, const char *status)
{
    reply(client, json, REQUEST_RESPONSE_HEADER_CONTENT_TYPE_JSON, status);
}