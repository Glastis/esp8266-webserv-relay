/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#ifndef ESP_RELAIS_WIFI_ROUTER_H
#define ESP_RELAIS_WIFI_ROUTER_H

#include "request.h"

#define ROUTER_PARAMETERS_SIZE              100u
#define ROUTER_ROUTE_SIZE                   (REQUEST_HTTP_PARAMS_MAX_SIZE)

struct                                      s_route
{
    const char                              *uri;
    void                                    (*action)(WiFiClient &client, const char *route, void *param, const char *http_params);
};

typedef struct s_route                      t_route;

void                                        router(WiFiClient &client, void *params);
void                                        route_landing(WiFiClient &client, const char *route, void *params, const char *http_params);
void                                        route_api_relay_set_status(WiFiClient &client, const char *route, void *params, const char *http_params);

static t_route                                     route_list[] = {
        { "/", route_landing },
        { "/api/relay", route_api_relay_set_status },
};

#endif //ESP_RELAIS_WIFI_ROUTER_H
