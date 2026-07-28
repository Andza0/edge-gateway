#ifndef config_h_
#define config_h_
#include <stdio.h>

typedef struct {
    int interval;
    char name[50];
} general_settings;

typedef struct {
    char localhost[50];
    int port;
    char topic[100];
} mqtt_settings;

typedef struct{
    general_settings general_settings;
    mqtt_settings mqtt_settings;
} settings;

int read_config(char *file_name, settings *settings);
int read_mqtt_settings(FILE * stream, mqtt_settings *settings);
int read_general_settings(FILE *stream, general_settings *settings);

#endif 