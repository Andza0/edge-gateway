#ifndef mqtt_client_h_
#define mqtt_client_h_
#include <mosquitto.h>

typedef struct{
    struct mosquitto *mosq;
    bool connected;
}mqtt_client;

int mqtt_client_init();
int mqtt_configure(mqtt_client *client);
int mqtt_client_connect();
int mqtt_publish_temperature(char *temp);
int mqtt_client_cleanup();

#endif