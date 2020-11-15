/*
** Created by glastis
** Date: 15-Nov-20
** Contact: developers@glastis.com
*/

#ifndef ESP_RELAIS_WIFI_ROUTER_H
#define ESP_RELAIS_WIFI_ROUTER_H

struct                      s_route
{
    char                    *uri;
    void                    (*action)(WiFiClient &client, const char *route);
};

typedef struct s_route      t_route;

void                        router(WiFiClient &client);
void                        route_landing(WiFiClient &client, const char *route);
void                        route_api_relay_set_status(WiFiClient &client, const char *route);

t_route                     route_list[] = {
        {"/", route_landing},
        {"/api/relay", route_api_relay_set_status},
};

#endif //ESP_RELAIS_WIFI_ROUTER_H
