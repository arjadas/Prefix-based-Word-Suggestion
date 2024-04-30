#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

#include "cafe.h"
#include "bit_operations.h"
#include "radix_tree_implementation.h"

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

    radix_node_t* root = NULL;
    cafe_t* cafe = NULL;

    char* prefix = (char *) malloc(MAX_STR_LEN*sizeof(char));  // prefix can't be geater than field

    // skipping the header
    while(fgetc(input_file)!='\n');
    
    // inserting cafe records from csv into the radix tree
    while ((cafe = (cafe_t* )cafeRead(input_file)) != NULL) {
        root = insert_radix_node(cafe, root);
    }
    
    // taking input
    while (scanf(" %[^\n]", prefix) != EOF) {  // loop runs untill ctrl+d is pressed
            
        //finding all the nodes with matching prefix
        find_and_traverse_node(prefix, root, output_file);
    }
    
    // freeing all memory allocations
    free_radix_tree(root);
    free(prefix);

    // closing the file pointers
    fclose(input_file);
    fclose(output_file);

    return 0;
}
