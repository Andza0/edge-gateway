#include <stdio.h>
#include <mosquitto.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


int running = 1;
void signal_handle(int signal){
    running = 0;
}

int main(void){


    signal(SIGINT, signal_handle);
    //https://mosquitto.org/api/files/mosquitto-h.html
    mosquitto_lib_init();

    struct mosquitto *mosq = mosquitto_new(NULL, 1, NULL);

    char *last_msg = "Nutruko darbas\n";
    mosquitto_will_set(mosq, "will", strlen(last_msg), last_msg, 0, 0);

    const char *host = "localhost";
    const int port = 1883;
    const int retain = 60;
    mosquitto_connect(mosq, host, port, retain);

    while(running){
        char *payload = "33.3C*\n";
        mosquitto_publish(mosq, NULL, "edge-gateway/telemetry", strlen(payload), payload, 0, 0);
        sleep(3);
    }    




    mosquitto_lib_cleanup();


    return 0;
}