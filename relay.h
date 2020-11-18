/*
** Created by glastis
** Date: 17-Nov-20
** Contact: developers@glastis.com
*/

#ifndef ESP_RELAIS_WIFI_RELAY_H
#define ESP_RELAIS_WIFI_RELAY_H

struct                              s_relay
{
    int                             activated;
};

typedef struct s_relay              t_relay;

void                                relay_init(t_relay *relay);

#endif //ESP_RELAIS_WIFI_RELAY_H
