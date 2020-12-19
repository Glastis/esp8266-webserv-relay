/*
** Created by glastis
** Date: 17-Nov-20
** Contact: developers@glastis.com
*/

#include <ESP8266WiFi.h>

#include "relay.h"
#include "constants.h"

void                                relay_init(t_relay *relay)
{
    relay->activated = 0;
}

void                                relay_set_status(t_relay *relay, int status)
{
    relay->activated = status;
    digitalWrite(PIN_RELAY, status);
}

void                                relay_switch_status(t_relay *relay)
{
    relay->activated = !relay->activated;
    digitalWrite(PIN_RELAY, relay->activated);
}