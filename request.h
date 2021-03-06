/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#ifndef ESP_RELAIS_WIFI_REQUEST_H
#define ESP_RELAIS_WIFI_REQUEST_H

#define REQUEST_RESPONSE_HEADER_HTTP_VERSION            "HTTP/1.1"
#define REQUEST_RESPONSE_HEADER_CONTENT_TYPE_HTML       "Content-Type: text/html"
#define REQUEST_RESPONSE_HEADER_CONTENT_TYPE_JSON       "Content-Type: application/json"

#define REQUEST_RESPONSE_HEADER_OK                      "200 OK"
#define REQUEST_RESPONSE_HEADER_BAD_REQUEST             "400 Bad Request"
#define REQUEST_RESPONSE_HEADER_NOT_FOUND               "404 Not Found"
#define REQUEST_RESPONSE_HEADER_SERVER_ERROR            "500 Internal Server Error"

#define REQUEST_JSON_DEFAULT_CONTENT                    "{}"

#define REQUEST_HTTP_PARAMS_MAX_SIZE                    100u

void                        reply(WiFiClient &client, const char *file, const char *type, const char *status);
void                        reply_html(WiFiClient &client, const char *html, const char *status);
void                        reply_html_arr(WiFiClient &client, char **body, const char *status);
void                        reply_json(WiFiClient &client, const char *json, const char *status);
void                        reply_html_begin(WiFiClient &client, const char *status);
void                        reply_html_end(WiFiClient &client);
void                        send_button(WiFiClient &client, const char *href, const char *name);
void                        get_http_params(char *request, char *params);
int                         get_http_param(const char *params, const char *key, char *value_output);

#endif //ESP_RELAIS_WIFI_REQUEST_H
