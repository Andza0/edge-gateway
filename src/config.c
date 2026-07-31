#include "config.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int read_config(char *file_name, settings *settings){
    FILE *stream = fopen(file_name, "r");
    if(stream == NULL){
        perror("Nepavyko atidaryti failo ");
        return -1;
    }
    
    int ret;

    ret = read_general_settings(stream, &settings->general_settings);
    if(ret != 1){
        printf("Klaida nuskaitant pagrindinius nustatymus\n");
        return -1;
        fclose(stream);
    }

    ret = read_mqtt_settings(stream, &settings->mqtt_settings);


    fclose(stream);    
    return 1;
}

int read_general_settings(FILE *stream, general_settings *settings){
    int ret;

    rewind(stream);
    ret = find_var(stream, "name", settings->name, 50);
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

    char *end;
    long interval = strtol(intervalc, &end, 0);
    if(intervalc == end){
        printf("Neteisingas intervalo nurodymas, turi buti sveikasis skaicius\n");
        return -1;
    }

    settings->interval = (int)interval;

    return 1;
}

int read_mqtt_settings(FILE *stream, mqtt_settings *settings){
    int ret;

    rewind(stream);
    ret = find_var(stream, "mqtt_host", settings->host, 50);
    if(ret == -1){
        printf("Nepavyko nuskaityti host\n");
    }

    rewind(stream);
    char portc[50];
    ret = find_var(stream, "mqtt_port", portc, 50);
    if(ret == -1){
        printf("Nepavyko nuskaityti port\n");
        return -1;
    }

    char *end;
    long port = strtol(portc, &end, 0);
    if(portc == end){
        printf("Neteisingas port nurodymas, turi buti sveikasis skaicius\n");
        return -1;
    }

    settings->port = port;

    rewind(stream);
    ret = find_var(stream, "mqtt_topic", settings->topic, 100);
    if(ret == -1){
        printf("Nepavyko nuskaityti topic\n");
        return -1;
    }

    return 1;
}