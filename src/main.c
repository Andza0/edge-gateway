#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <getopt.h>
#include <stdlib.h>
#include "config.h"
#include "data.h"
#include "mqtt_client.h"

int volatile running = 1;
settings set;
char *config_file = "/etc/edge-gateway/config.conf";

void sig_handle(int signal){
    running = 0;
}

void sig_config_reload(int signal){
    read_config(config_file, &set);
}

int main(int argc, char **argv){

    int option;
    struct option long_options[] = {
        {"config", required_argument, NULL, 'c'}
    };

    while((option = getopt_long(argc, argv, "c:", long_options, NULL)) != -1){
        switch (option){
            case 'c':
                config_file = optarg;
                break;
            default:
                break;
        }
        
    }
    
    signal(SIGINT, sig_handle);
    signal(SIGTERM, sig_handle);
    signal(SIGHUP, sig_config_reload);

    if(read_config(config_file, &set) == -1){
        printf("Konfiguracijos nuskaitymo klaida\n");
        return -1;
    }

    mqtt_client mosq;
    mosq.mosq = NULL;
    mosq.connected = 0;
    
    int ret;
    ret = mqtt_configure(&mosq);
    if(ret == -1){
        printf("Nepavyko mqtt konfiguracija\n");
        return -1;
    }

    while(running){
        float temp = get_cpu_temp();
        printf("%s: %.2f C*\n", set.general_settings.name, temp);
        sleep(set.general_settings.interval);
        fflush(stdout);
    }
    
    printf("\n%s: OFF\n", set.general_settings.name);

    return 0;
}