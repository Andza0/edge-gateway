#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "parse.h"

int volatile running = 1;

void sig_handle(int signal){
    running = 0;
}


int main(void){

    signal(SIGINT, sig_handle);
    signal(SIGTERM, sig_handle);

    char cwd[50]; 
    if(getcwd(cwd, 50) == NULL){
        perror("Klaida su getcwd");
        return -1;
    }

    printf("cwd: %s\n", cwd);

    FILE *stream = fopen("/home/edge/edge-gateway/config/config.conf", "r");
    if(stream == NULL){
        perror("Nepavyko atidaryti failo ");
        return -1;
    }

    int ret;

    char name[50];
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