#include "config.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int read_config(char *file_name, settings *set){
    FILE *stream = fopen(file_name, "r");
    if(stream == NULL){
        perror("Nepavyko atidaryti failo ");
        return -1;
    }
    
    int ret;

    rewind(stream);
    ret = find_var(stream, "name", set->name, 50);
    if(ret == -1){
        printf("find_var grazino klaida(name).\n");
        return -1;
    }

    char intervalc[50];
    rewind(stream);
    ret = find_var(stream, "interval", intervalc, 50);
    if(ret == -1){
        printf("find_var grazino klaida(interval).\n");
        return -1;
    }

    fclose(stream);

    char *end;
    long interval = strtol(intervalc, &end, 0);

    set->interval = (int)interval;

    return 1;
}