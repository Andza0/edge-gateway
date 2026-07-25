#ifndef config_h_
#define config_h_

typedef struct{
    int interval;
    char name[50];
} settings;

int read_config(char *file_name, settings *set);

#endif 