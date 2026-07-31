#include <stdio.h>
#include <mosquitto.h>
#include "mqtt_client.h"
#include "parse.h"
#include "config.h"
#include <string.h>

void mqtt_client_init(){
    mosquitto_lib_init();
}

int mqtt_configure(mqtt_client *client){
    struct mosquitto *mosq = mosquitto_new(NULL, 1, NULL);
    if(mosq == NULL){
        return -1;
    }
    client->mosq = mosq;
    return 1;
}

void mqtt_client_connect(mqtt_client client, mqtt_settings settings){
    mosquitto_connect(client.mosq, settings.host, settings.port, 60);
}

void mqtt_publish_temperature(mqtt_client client, mqtt_settings settings, char *temp){
    mosquitto_publish(client.mosq, NULL, settings.topic, strlen(temp), temp, 0, 0);
}

void mqtt_client_cleanup(){  
    mosquitto_lib_cleanup();
}