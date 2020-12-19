/*
** Created by glastis
** Date: 09-Dec-20
** Contact: developers@glastis.com
*/

#include "utilities.h"

int                         comp_str_beg(const char *str1, const char *str2)
{
    unsigned int            i;

    i = 0;
    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
        {
            return FALSE;
        }
        ++i;
    }
    return TRUE;
}