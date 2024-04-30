#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "cafe.h"
#include "array_implementation.h"

#define NOT_FOUND -1
#define BITS_IN_CHARACTER 8

/*
 This function takes an array of pointers to cafe records and the array length, 
 sorts the array using insertion sort algorithm.
 */
void insertion_sort(cafe_t** array, int n) {

    cafe_t* temp;
    int i = 0, j = 0;

    for (i = 1; i < n; i++) {

        for (j = i-1; j >= 0; j--) {

            if (strcmp(array[j]->trading_name, array[j+1]->trading_name) > 0) {
                // swapping the consecutive two items in the array if they aren't in ascending order
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
        temp = NULL; // resetting temp pointer
    }
}

/*
 This function takes a prefix, the sorted array of pointers to cafe records, the array length, and 
 the name of the file to which the output is intended to store. It searches the prefix in the array
 and stores the matching records in the output file. it also displays the bits, characters and strings
 compared to the standard output terminal.
 */
void find_and_traverse(char* prefix, cafe_t** array, int n, FILE *output_file) {

    int characters_compared = 0;
    int strings_compared = 0;

    // finds the index of the matching prefix in the array 
    int index = get_matching_index(prefix, array, n, &characters_compared, &strings_compared);

    if (index != NOT_FOUND) {
        // an index is found

        // this aims to find the starting index of the matching prefix
        int start_index = find_start_index(index, prefix, array, &characters_compared, &strings_compared);
        // this aims to find the end index of the matching prefix
        int end_index = find_end_index(index, n,prefix, array, &characters_compared, &strings_compared);

        // outputting the required information to their respective places
        output_information(prefix, array, start_index, end_index, output_file);
        display_comparisons(prefix, characters_compared, strings_compared);

    } else {
        // no matching prefix is found
        // only outputting the items compared to the terminal, nothing is stored in the output file 
        display_comparisons(prefix, characters_compared, strings_compared);
    }

}

/*
 This function takes in the prefix, array of pointers to cafe records and stores the cafe 
 information of the matching prefix in the output file
 */
void output_information(char* prefix, cafe_t** array, int start_index, int end_index, FILE* output_file) {

    fprintf(output_file, "%s\n", prefix);

    for (int i = start_index; i <= end_index; i++) {

        print_cafe(output_file, array[i]);

    }
}

/*
 This function takes in the prefix, number of characters and strings compared, and prints them
 on the standard output terminal
 */
void display_comparisons(char* prefix, int characters_compared, int strings_compared) {

    characters_compared++; // this is for checking the last byte (null byte) for the characters compared
    int bits_compared = characters_compared * BITS_IN_CHARACTER;

    printf("%s --> b%d c%d s%d\n", prefix, bits_compared, characters_compared, strings_compared);
    
}

/*
 This function takes in the prefix, array of pointers to cafe records and tries to find the index
 of the matching prefix using a binary search approach. Returns -1 (NOT_FOUND) in case no matching
 prefix is found.
 */
int get_matching_index(char *prefix, cafe_t** array, int n, int *c_c, int *s_c) {

    int low_index = 0;
    int high_index = n-1;
    int mid_index = (low_index + high_index) / 2;
    int comparison_output;
    int l = strlen(prefix);

    while (low_index <= high_index) {

        mid_index = (low_index + high_index) / 2;
        comparison_output = strncmp(array[mid_index]->trading_name, prefix, l);

        *s_c += 1; // one string is being compared

        if (comparison_output == 0) {
            *c_c += l; // updating the number of characters compared
            return mid_index;
        } else if (comparison_output > 0) {
            *c_c += characters_compared(array[mid_index]->trading_name, prefix);
            high_index = mid_index - 1;
        } else if (comparison_output < 0){
            *c_c += characters_compared(array[mid_index]->trading_name, prefix);
            low_index = mid_index + 1;
        }
    }

    // no matching index is found
    return NOT_FOUND;

}

/*
 This function takes in the prefix, and the string to compare how many characters were compared
 to find the matching index.
 */
int characters_compared(char* str1, char* prefix) {

    int count = 0;
    int i = 0;

    while (i<strlen(prefix) && (str1[i] == prefix[i])) {

        count++;
        i++;
    }
    
    return (count + 1); // the last bit compared wasn't incremented inside the loop.
}

/*
 This function takes in the prefix, and the array to find the very first matching prefix index in the array.
 */
int find_start_index(int index, char* prefix, cafe_t** array, int *c_c, int *s_c) {

    int l = strlen(prefix);

    if (index == 0) {
        // returning the index if it's already the first element of the array
        return index;
    }

    while(index > 0 && strncmp(array[index - 1]->trading_name, prefix, l) == 0) {
        index -= 1;
        *c_c += l;
        *s_c += 1;
    }

    // the last non-matching prefix comparison which wasn't counted inside the loop
    *c_c += characters_compared(array[index-1]->trading_name, prefix);
    *s_c += 1;

    return index;
}

/*
 This function takes in the prefix, and the array to find the very end matching prefix index in the array.
 */
int find_end_index(int index, int n, char* prefix, cafe_t** array, int *c_c, int *s_c) {

    int l = strlen(prefix);

    if (index == (n-1)) {
        // returning the index if it's already the last element of the array
        return index;
    }

    while(index < n-1 && strncmp(array[index + 1]->trading_name, prefix, l) == 0) {
        index += 1;
        *c_c += l;
        *s_c += 1;
    }

    // the last non-matching prefix comparison which wasn't counted inside the loop
    *c_c += characters_compared(array[index+1]->trading_name, prefix);
    *s_c += 1;

    return index;
}
