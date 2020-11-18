# ESP8266 Web server

Simple web server with url routing, used to activate/deactivate relays.

## How to

Have arduino IDE, makes sure esp8266 board is installed.

Rename `wifi_pass.h.example` to `wifi_pass.h` and replaces values to match with your wifi access point credentials.

## I want to use the webserver part but I don't care about the relay part

Have a look in `router.cpp` and `router.h`, you can quickly edit it to add your routes.

In `router.h`, add your routes to `route_list[]` array.
In `router.cpp`, define it. 