#include <stdio.h>
#include "mqtt_client.h"
#include "parse.h"
#include "config.h"

int mqtt_client_init(){
    mosquitto_lib_init();
}

int mqtt_configure(mqtt_client *client){
    struct mosquitto mosq = mosquitto_new(NULL, 1, NULL);
    if(mosq == NULL){
        return -1;
    }
    client->mosq = mosq;
}

/*
int mqtt_client_connect(){

}

int mqtt_publish_temperature(char *temp){

}

int mqtt_client_cleanup(){

}
*/