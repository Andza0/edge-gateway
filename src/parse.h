#ifndef parse_h_
#define parse_h_

int get_var(FILE *stream, char *key, int key_sz, char *value, int val_sz);
int find_var(FILE *stream, char *target_key, char *val, int val_sz);

#endif