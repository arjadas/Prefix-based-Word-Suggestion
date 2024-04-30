#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

int* string_to_binary(char *string);
int getBit(int *key, int n);
int getLength(int *key);
int *find_common_prefix(int *prefix1_binary, int *prefix2_binary);
int prefix_match(int* prefix1, int* prefix2);

void compare_bits_and_characters(int* key1, int* key2, int* b_c, int* c_c);

#endif
