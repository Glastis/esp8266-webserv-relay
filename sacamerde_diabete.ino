#include <EEPROM.h>
#include "main.h"
#include "screen.h"
#include "wifi.h"
#include "input.h"
#include "menu.h"
#include "time.h"
#include "file.h"

char                                        results_glob[MENU_MAIN_LEN][MAX_CHAR_PER_LINE];
OLED                                        display(PIN_SCL, PIN_SDA);
t_coord                                     coord;

void                                        setup()
{
    init_coord(&coord);
    display.begin();
    write(&coord, "  Booting...");
    Serial.begin(SERIAL_BAUDRATE);
    wifi_init();
    input_init();
    EEPROM.begin(EEPROM_MAX_SIZE_USED);
}

static void                                 check_time(unsigned int *job)
{
    char                                    buff_time[TIME_LEN];
    unsigned int                            i;

    i = 0;
    if (request_time(buff_time))
    {
        return;
    }
    while (i < MENU_MAIN_LEN)
    {
        if (job[i] && comp_time(buff_time, &results_glob[i][RESULT_LEFT_PADDING + strlen(JOB_DONE) + 1]))
        {
            memset(results_glob[i], ' ', MAX_CHAR_PER_LINE - 1);
            memcpy(&results_glob[i][RESULT_LEFT_PADDING], JOB_LEFT, strlen(JOB_LEFT));
            results_glob[i][MAX_CHAR_PER_LINE - 1] = '\0';
            job[i] = 0;
            write_time(&results_glob[i][RESULT_LEFT_PADDING + strlen(JOB_DONE) + 1], i);
        }
        ++i;
    }
}

static void                                 fill_time(char *buffer, unsigned int pos)
{
    if (request_time(buffer))
    {
        buffer[0] = 'E';
        buffer[1] = 'R';
        buffer[2] = 'R';
        buffer[3] = 'O';
        buffer[4] = 'R';
        buffer[5] = '\0';
    }
    write_time(buffer, pos);
}

static void                                 set_result_ok(unsigned int *job, char *result, unsigned int pos)
{
    char                                    buffer[BUFF_TIME_SIZE];

    fill_time(buffer, pos);
    memset(result, ' ', MAX_CHAR_PER_LINE - 1);
    memcpy(&result[RESULT_LEFT_PADDING], JOB_DONE, strlen(JOB_DONE));
    memcpy(&result[RESULT_LEFT_PADDING + strlen(JOB_DONE) + 1], buffer, strlen(buffer));
    result[MAX_CHAR_PER_LINE - 1] = '\0';
    job[0] = 1;
}

static void                                 init_loop(unsigned int *job)
{
    unsigned int                            i;

    i = 0;
    while (i < MENU_MAIN_LEN)
    {
        memset(results_glob[i], ' ', MAX_CHAR_PER_LINE - 1);
        if ((job[i] = read_time(&results_glob[i][RESULT_LEFT_PADDING + strlen(JOB_DONE) + 1], i)))
        {
            memcpy(&results_glob[i][RESULT_LEFT_PADDING], JOB_DONE, strlen(JOB_DONE));
        }
        else
        {
            memcpy(&results_glob[i][RESULT_LEFT_PADDING], JOB_LEFT, strlen(JOB_LEFT));
        }
        results_glob[i][MAX_CHAR_PER_LINE - 1] = '\0';
        ++i;
    }
}

void                                        shutdown()
{
    clear_screen(&coord);
    ESP.deepSleep(2000000);
}

void                                        loop()
{
    t_menu                                  menu;
    e_input                                 pressed;
    unsigned int                            job_done[MENU_MAIN_LEN];

    init_loop(job_done);
    init_menu(&menu, MENU_MAIN);
    check_time(job_done);
    show_menu(&coord, &menu);
    while (true)
    {
        pressed = input_wait();
        if (pressed == BUTTON_OK)
        {
            set_result_ok(&job_done[menu.state], results_glob[menu.state], menu.state);
            show_menu(&coord, &menu);
        }
        else if (pressed == BUTTON_LEFT)
        {
            menu_mod(&menu, -1);
        }
        else if (pressed == BUTTON_RIGHT)
        {
            menu_mod(&menu, 1);
        }
        else if (pressed == BUTTON_TIMEOUT)
        {
            shutdown();
        }
        delay(MAIN_DELAY);
    }
}
