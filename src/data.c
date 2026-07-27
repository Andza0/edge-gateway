#include <stdio.h>

float get_cpu_temp(){
    
    FILE* file = fopen("/sys/devices/virtual/thermal/thermal_zone0/temp", "r");
    if(file == NULL){
        return -1;
    }
    
    long temperature_mili;

    fscanf(file, "%ld", &temperature_mili);

    fclose(file);

    return (float)temperature_mili / 1000;
}