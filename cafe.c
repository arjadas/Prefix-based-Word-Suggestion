
/* This file has been taken from  Assignment 1, which was a group project
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "cafe.h"


#define MAX_STR_LEN 128
#define TRUE 1
#define FALSE 0

/*
Function that takes a csv file as input and returns a cafe struct with field data from the file
*/

cafe_t *cafeRead(FILE *f) {

    // declare cafe_t struct to csv data in
    cafe_t *c = NULL;
    c = (cafe_t *)malloc(sizeof(*c));
    assert(c);


    // Initialise the state variable to FALSE
    int in_quotes = FALSE;

    // Initialise variable tracking cafe field 
    int field_no = 0;

    // Declare string buffer for reading in csv
    char str[MAX_STR_LEN];
    int str_index = 0;
    char ch;


    // While fgetc is assigning a char other than EOF to ch
    while((ch = fgetc(f)) != EOF) {

        // If newline of csv reached
        if (ch == '\n') {
            // Replace newline character with null terminator
            str[str_index] = '\0';
            // Assign String to final field of cafe struct
            cafe_populator(c, str, field_no);
            // Return Cafe struct with appropriate contents
            return c;
        }

        // State Machine
        // if currently not in quotes
        if(in_quotes == FALSE) {
            
            // state switch
            if (ch == '"') {
                in_quotes = TRUE;   
            } 
            // if ch is a comma, end of string has been reached, initialise cafe_t field with data from csv
            else if (ch == ',') {
                str[str_index] = '\0';
                cafe_populator(c,str,field_no);

                // Increment to new field
                field_no++;
                
                // Reset buffer index
                str_index = 0;
            } else {
                // Otherwise, assign ch to buffer, increment index
                str[str_index++] = ch;
            }

        // If in quotes    
        } else {
            if (ch == '"') {
                in_quotes = FALSE;
    
            } else {
                // treat commas the same as other chars
                str[str_index++] = ch;
            }
        }
    }

    // If no chars have been assigned to ch (while loop wasn't entered)
    if (field_no == 0 && str_index == 0) {
        // free cafe struct memory
        free(c);
        // return nothing
        return NULL;
    }

    
    // Otherwise, assign null terminator to final index of final field, populate cafe struct appropriately
    str[str_index] = '\0';
    cafe_populator(c, str, field_no);

    // return cafe struct
    return c;
}

/*
Function that takes a cafe struct, string and integer variable as inputs, assigning the value stored by the string (as the corresponding data type)
to the field of the cafe struct indicated by the integer.
*/

void cafe_populator(cafe_t* cafe, char* field_data, int field_no) {

    // If field_no = x, assign field data, as the corresponding data type, to the appropriate cafe field
    if (field_no == 0) {
        cafe->census_year = string_to_int(field_data);
    } else if (field_no == 1) {
        cafe->block_id = string_to_int(field_data);
    } else if (field_no == 2) {
        cafe->property_id = string_to_int(field_data);
    } else if (field_no == 3) {
        cafe->base_property_id = string_to_int(field_data);
    } else if (field_no == 4) {
        cafe->building_address = strdup(field_data);
    } else if (field_no == 5) {
        cafe->clue_small_area = strdup(field_data);
    } else if (field_no == 6) {
        cafe->business_address = strdup(field_data);
    } else if (field_no == 7) {
        cafe->trading_name = strdup(field_data);
    } else if (field_no == 8) {
        cafe->industry_code = string_to_int(field_data);
    } else if (field_no == 9) {
        cafe->industry_desc = strdup(field_data);
    } else if (field_no == 10) {
        cafe->seating_type = strdup(field_data);
    } else if (field_no == 11) {
        cafe->no_of_seats = string_to_int(field_data);
    } else if (field_no == 12) {
        cafe->longitude = atof(field_data);
    } else if (field_no == 13) {
        cafe->latitude = atof(field_data);
    }
} 

/*
Function that converts the contents of a string (which only containsintegers) to an integer variable
*/
int string_to_int(char *str) {
    int integer = 0;
    // iterate over characters in the string
    while(*str) {
        // String is processed left to right, multiply str chars already stored in integer by 10 to allow the next digit (0-9) to be 
        // added as the new 'single' digit. Subtract 0 from char to convert to int.
        integer = (integer * 10) + (*str - '0');
        str++;
    }
    return integer; 
}


/*
Function that converts the contents of a string (which contains a decimal point number) to a double variable
*/
double string_to_double(char *str) {
    double number = 0.0;
    while(*str) {
        number = (number * 10.0) + (*str - '0');
        str++;
    }
    return number;
}

/*
Functions that prints the contents of a cafe struct, in a specifcied format, to a given FILE pointer
*/

void print_cafe(FILE *output_file, cafe_t* result_cafe) {

    fprintf(output_file, "--> census_year: %d || block_id: %d || property_id: %d || base_property_id: %d || building_address: %s || clue_small_area: %s || business_address: %s ||trading_name: %s || industry_code: %d || industry_description: %s || seating_type: %s || number_of_seats: %d || longitude: %.5lf || latitude: %.5lf ||\n",
    result_cafe->census_year,
    result_cafe->block_id,
    result_cafe->property_id,
    result_cafe->base_property_id,
    result_cafe->building_address,
    result_cafe->clue_small_area,
    result_cafe->business_address,
    result_cafe->trading_name,
    result_cafe->industry_code,
    result_cafe->industry_desc,
    result_cafe->seating_type,
    result_cafe->no_of_seats,
    result_cafe->longitude,
    result_cafe->latitude);

}



/*
Function that free the memory assigned to an individual cafe struct
*/

void free_cafe(cafe_t* c) {
    free(c->building_address);
    free(c->clue_small_area);
    free(c->business_address);
    free(c->trading_name);
    free(c->industry_desc);
    free(c->seating_type);
    free(c);
}

