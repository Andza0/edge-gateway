#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <getopt.h>
#include "parse.h"

int volatile running = 1;

void sig_handle(int signal){
    running = 0;
}


int main(int argc, char **argv){

    char *config_file = "/etc/edge-gateway/config.conf";

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

    FILE *stream = fopen(config_file, "r");
    if(stream == NULL){
        perror("Nepavyko atidaryti failo ");
        return -1;
    }
    
    int ret;

    char name[50];
    rewind(stream);
    ret = find_var(stream, "name", name, 50);
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

    int interval = atoi(intervalc);



    while(running){
        printf("%s: ON\n", name);
        sleep(interval);
        fflush(stdout);
    }
    
    printf("\n%s: OFF\n", name);

    return 0;
}