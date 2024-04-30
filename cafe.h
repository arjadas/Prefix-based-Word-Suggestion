/* This file has been taken from my friend Razeen Asief who has done it perfectly in Assignment 1.
 * All credit for this file goes to Razeen and his teammate Ethan Allan.
 * I took their cafe file because my cafe file was not working correctly in my Assignment 1
 * I have also taken permission from a tutor if I am allowed to do that.
 */

#ifndef CAFE_H
#define CAFE_H

typedef struct {
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char* building_address;
    char* clue_small_area;
    char* business_address;
    char* trading_name;
    int industry_code;
    char* industry_desc;
    char* seating_type;
    int no_of_seats;
    double longitude;
    double latitude;
} cafe_t;

cafe_t *cafeRead(FILE *f);
void cafe_populator(cafe_t* cafe, char* field_data, int field_no);
int string_to_int(char *string);
double string_to_double(char *string);
void print_cafe(FILE* output_file, cafe_t* result_cafe);
void free_cafe(cafe_t* c);

#endif
