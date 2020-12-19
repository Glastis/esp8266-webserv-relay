/*
** Created by glastis
** Date: 19-Dec-20
** Contact: developers@glastis.com
*/

#include <ESP8266WiFi.h>

#include "constants.h"
#include "print.h"
#include "utilities.h"

#ifdef DEBUG

void                   debug_print(const char *str)
{
    Serial.print(str);
}

void                   debug_println(const char *str)
{
    Serial.println(str);
}

void                   debug_print(int nb)
{
    Serial.print(nb);
}

void                   debug_println(int nb)
{
    Serial.println(nb);
}

void                   debug_print(unsigned int nb)
{
    Serial.print(nb);
}

void                   debug_println(unsigned int nb)
{
    Serial.println(nb);
}

#else

void                    debug_print(const char *str) { UNUSED(str); }
void                    debug_println(const char *str) { UNUSED(str); }
void                    debug_print(int nb) { UNUSED(nb); }
void                    debug_println(int nb) { UNUSED(nb); }
void                    debug_print(unsigned int nb) { UNUSED(nb); }
void                    debug_println(unsigned int nb) { UNUSED(nb); }

#endif