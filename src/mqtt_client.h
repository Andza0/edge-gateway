#ifndef mqtt_client_h_
#define mqtt_client_h_
#include <mosquitto.h>
#include "config.h"

typedef struct{
    struct mosquitto *mosq;
    bool connected;
}mqtt_client;

void mqtt_client_init();
int mqtt_configure(mqtt_client *client);
void mqtt_client_connect(mqtt_client client, mqtt_settings settings);
void mqtt_publish_temperature(mqtt_client client, mqtt_settings settings, char *temp);
void mqtt_client_cleanup();

#endif