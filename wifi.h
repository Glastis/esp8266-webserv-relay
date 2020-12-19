/*
** Created by Glastis on 03/02/19.
*/

#ifndef SACAMERDE_DIABETE_WIFI_H
#define SACAMERDE_DIABETE_WIFI_H

#define WIFI_CONNECT_DELAY                  500u

#define WIFI_CONNECTED_STR                  "connected"
#define WIFI_DISCONNECTED_STR               "disconnected"

void                                        wifi_check();
void                                        wifi_init();
const char                                  *wifi_status_to_string();
void                                        wifi_print_status();

#endif /* !SACAMERDE_DIABETE_WIFI_H */
