/*
** Created by glastis
** Date: 17-Nov-20
** Contact: developers@glastis.com
*/

#ifndef ESP_RELAIS_WIFI_RELAY_H
#define ESP_RELAIS_WIFI_RELAY_H

#define RELAY_HTTP_PARAMETER_STATUS_KEY         "s"
#define RELAY_HTTP_PARAMETER_STATUS_VALUE_ON    "1"
#define RELAY_HTTP_PARAMETER_STATUS_VALUE_OFF   "0"
#define RELAY_HTTP_PARAMETER_STATUS_MISSING     "{\"error\": \"missing 's' parameter\"}"
#define RELAY_HTTP_PARAMETER_STATUS_BAD_VALUE   "{\"error\": \"'s' parameter value should be 1 or 0\"}"

struct                              s_relay
{
    int                             activated;
};

typedef struct s_relay              t_relay;

void                                relay_init(t_relay *relay);
void                                relay_switch_status(t_relay *relay);
void                                relay_set_status(t_relay *relay, int status);

#endif //ESP_RELAIS_WIFI_RELAY_H
