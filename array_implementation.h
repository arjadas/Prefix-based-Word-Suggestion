#ifndef ARRAY_IMPLEMENTATION_H
#define ARRAY_IMPLEMENTATION_H

#include "cafe.h"

void insertion_sort(cafe_t** array, int n);
void find_and_traverse(char* prefix, cafe_t** array, int n, FILE* output_file);
void output_information(char* prefix, cafe_t** array, int start_index, int end_index, FILE* output_file);
void display_comparisons(char* prefix, int characters_compared, int strings_compared);
int get_matching_index(char *prefix, cafe_t** array, int n, int *c_c, int *s_c);
int characters_compared(char* str1, char* prefix);
int find_start_index(int index, char* prefix, cafe_t** array, int *c_c, int *s_c);
int find_end_index(int index, int n, char* prefix, cafe_t** array, int *c_c, int *s_c);

#endif
