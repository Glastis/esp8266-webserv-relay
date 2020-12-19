/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#include <ESP8266WiFi.h>

#include "request.h"
#include "constants.h"
#include "utilities.h"

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
    const char              *arr[] = { "<script src=\"", HTML_EXTERNAL_JS_URL, "\"></script>" };

    reply_arr(client, (char **)arr);
}

static void                 reply_headers(WiFiClient &client, const char *type, const char *status)
{
    client.print(REQUEST_RESPONSE_HEADER_HTTP_VERSION);
    client.println(status);
    client.println(type);
    client.println("");
}

static void                 get_http_param_extract_value(const char *param, char *output)
{
    unsigned int            i;
    unsigned int            o;

    i = 0;
    while ( param[i] &&
            param[i] != '=' &&
            param[i] != '\r' &&
            param[i] != '\n' &&
            param[i] != '\t')
    {
        ++i;
    }
    if (param[i] == '=' && param[i + 1])
    {
        ++i;
        o = 0;
        while (param[i] && param[i] != '&' && o < REQUEST_HTTP_PARAMS_MAX_SIZE)
        {
            output[o] = param[i];
            ++o;
            ++i;
        }
        return;
    }
    output[0] = '1';
    output[1] = '\0';
}

int                         get_http_param(const char *params, const char *key, char *value_output)
{
    unsigned int            i;

    i = 0;
    while (params[i])
    {
        if (comp_str_beg(key, &params[i]))
        {
            get_http_param_extract_value(&params[i], value_output);
            return TRUE;
        }
        ++i;
    }
    return FALSE;
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