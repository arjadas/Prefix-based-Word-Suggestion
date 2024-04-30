#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include "cafe.h"
#include "array_implementation.h"

#define INIT_CAFE_SIZE 10
#define MAX_STR_LEN 128

int main(int argc, char* argv[]) {

    // checking the number of arguements
    if(argc != 4){
        printf("Incorrect input");
        exit(EXIT_FAILURE);
    }

    // processing the arguements to the program
    FILE* input_file = fopen(argv[2], "r");
    FILE* output_file = fopen(argv[3], "w");
    assert(input_file && output_file);

    char* prefix = (char *) malloc(MAX_STR_LEN*sizeof(char));  // prefix can't be geater than field

    int curr_size_array = INIT_CAFE_SIZE;
    int total_cafe = 0;

    // creating an array to store the pointers to cafe records
    cafe_t** cafe_array = (cafe_t** )malloc(curr_size_array * sizeof(cafe_t*));
    cafe_t* cafe = NULL;

    // skipping the header
    while(fgetc(input_file)!='\n');

    // inserting cafe records from csv into the array
    while ((cafe = (cafe_t* )cafeRead(input_file)) != NULL) {
        if (total_cafe >= curr_size_array) { // checking size of array
            curr_size_array *= 2;
            cafe_array = (cafe_t** )realloc(cafe_array,curr_size_array*sizeof(cafe_t*));
        }
        cafe_array[total_cafe] = cafe;
        total_cafe++;
    }

    // performing insertion sort
    insertion_sort(cafe_array, total_cafe);

    // taking input
    while (scanf(" %[^\n]", prefix) != EOF) {  // loop runs untill ctrl+d is pressed
            
        // finding all the names with matching prefix
        find_and_traverse(prefix, cafe_array, total_cafe, output_file);

    }

    // freeing the memory allocations
    for (int i = 0; i < total_cafe; i++) {
        free_cafe(cafe_array[i]);
    }
    free(cafe_array);
    free(prefix);

    // closing the file pointers
    fclose(input_file);
    fclose(output_file);

    return 0;
}
