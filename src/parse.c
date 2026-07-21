#include <stdio.h>
#include <string.h>

int get_var(FILE *stream, char *key, int key_sz, char *value, int val_sz){
    char buf[100];
    char* ret = fgets(buf, 100, stream);

    if(ret == NULL){
        return -1;
    }

    char *k = strtok(buf, "=");
    char *v = strtok(NULL, "=");

    strncpy(key, k, key_sz - 1);
    key[strcspn(key, "\n")] = '\0';

    strncpy(value, v, val_sz);
    value[strcspn(value, "\n")] = '\0';

    return 1;
}

int find_var(FILE *stream, char *target_key, char *val, int val_sz)
{
    char key[50];
    char value[50];

    while(1){
        int ret = get_var(stream, key, 50, value, 50);

        if(ret == -1){
            return -1;
        }

        if(strcmp(target_key, key) == 0){
            strncpy(val, value, val_sz - 1);
            val[val_sz - 1] = '\0';
            return 1;
        }
    }

    return 0;
    
}