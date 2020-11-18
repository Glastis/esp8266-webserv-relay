/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "request.h"
#include "constants.h"

static void                 reply_arr(WiFiClient &client, char **arr)
{
    unsigned int            i;

    i = 0;
    while (arr[i])
    {
        client.print(arr[i]);
        ++i;
    }
    client.println("");
}

static void                 reply_html_content_write_flag_simple(WiFiClient &client, const char *flag, const char *flag_content)
{
    client.print("<");
    client.print(flag);
    client.print(">");
    client.print(flag_content);
    client.print("</");
    client.print(flag);
    client.println(">");
}

static void                 reply_html_content_header_meta(WiFiClient &client, const char *meta_name, const char *meta_value)
{
    client.print(R"(<meta name=")");
    client.print(meta_name);
    client.print(R"(" content=")");
    client.print(meta_value);
    client.println(R"(">)");
}

static void                 reply_html_content_header(WiFiClient &client)
{
    client.println("<head>");
    reply_html_content_write_flag_simple(client, "title", WEB_TITLE);

    client.println(R"(<link href="https://glastis.com/css/app.css" rel="stylesheet">)");
    client.println(R"(<meta charset="UTF-8">)");
    reply_html_content_header_meta(client, "viewport", "width=device-width, initial-scale=1");
    reply_html_content_header_meta(client, "description", WEB_DESCRIPTION);
    reply_html_content_header_meta(client, "keywords", WEB_KEYWORDS);
    client.println("</head>");
}

static void                 reply_html_content_scripts(WiFiClient &client)
{
    char                    *arr[] = { "<script src=\"", HTML_EXTERNAL_JS_URL, "\"></script>" };

    reply_arr(client, arr);
}

static void                 reply_headers(WiFiClient &client, const char *type, const char *status)
{
    client.print(REQUEST_RESPONSE_HEADER_HTTP_VERSION);
    client.println(status);
    client.println(type);
    client.println("");
}

void                        send_button(WiFiClient &client, const char *href, const char *name)
{
    client.print(R"(<div class="btn-link"><a href=")");
    client.print(href);
    client.print(R"(">)");
    client.print(name);
    client.println(R"(</a></div>)");
}

void                        reply(WiFiClient &client, const char *file, const char *type, const char *status)
{
    reply_headers(client, type, status);
    client.println(file);
}

void                        reply_html_begin(WiFiClient &client, const char *status)
{
    reply_headers(client, REQUEST_RESPONSE_HEADER_CONTENT_TYPE_HTML, status);
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    reply_html_content_header(client);
    client.println("<body>");
}

void                        reply_html_end(WiFiClient &client)
{
    reply_html_content_scripts(client);
    client.println("</body>");
    client.println("</html>");
}

void                        reply_html(WiFiClient &client, const char *body, char **body_arr, const char *status)
{
    reply_html_begin(client, status);
    if (body)
    {
        client.println(body);
    }
    else
    {
        reply_arr(client, body_arr);
    }
    reply_html_end(client);
}

void                        reply_json(WiFiClient &client, const char *json, const char *status)
{
    reply(client, json, REQUEST_RESPONSE_HEADER_CONTENT_TYPE_JSON, status);
}