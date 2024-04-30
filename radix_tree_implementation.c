#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bit_operations.h"
#include "cafe.h"
#include "radix_tree_implementation.h"

#define INITIAL_SIZE 2
#define TRUE 1
#define FALSE 0

/*
 This function takes a cafe record and the root node of the radix tree.
 Then it stores the cafe record in its suitable position inside the radix tree.
 */
radix_node_t* insert_radix_node(cafe_t* cafe, radix_node_t* root) {

    radix_node_t* curr_pointer = root;
    radix_node_t* previous_pointer = curr_pointer;
    radix_node_t* temp_pointer = NULL;
    int* common_prefix = NULL;
    int common_prefix_length = 0;
    int* bits_cafe_name = (int *) string_to_binary(cafe -> trading_name); // the trading name converted to bits


    // inserting the first element
    if (root == NULL) {
        
        root = (radix_node_t* )malloc(sizeof(radix_node_t));
        root -> prefix = bits_cafe_name;
        root -> prefix_length = getLength(root->prefix);
        root -> branch_A = NULL;  // when next bit is 0
        root -> branch_B = NULL;  // when next bit is 1
        root -> list_curr_size = INITIAL_SIZE;
        root -> cafe_list = (cafe_t** )malloc(root->list_curr_size*sizeof(cafe_t*));
        root -> list_count = 0;
        root -> cafe_list[root->list_count] = cafe;
        root -> list_count++;

        return root;

    }


    // inserting a new node to existing radix tree
    
    while (curr_pointer != NULL) {
        
        common_prefix = find_common_prefix(curr_pointer->prefix, bits_cafe_name);

        if (common_prefix != NULL && prefix_match(curr_pointer->prefix, bits_cafe_name) == TRUE) {
            // prefix matches exactly
            // the new cafe is the same as the one stored
            
            if (curr_pointer->list_count >= curr_pointer->list_curr_size) { // checking the size of the array
                curr_pointer->list_curr_size *= 2;
                curr_pointer->cafe_list = (cafe_t** )realloc(curr_pointer->cafe_list, curr_pointer->list_curr_size*sizeof(cafe_t* ));
            }
            // storing the cafe name in the array of cafe_list
            curr_pointer->cafe_list[curr_pointer->list_count] = cafe;
            curr_pointer->list_count++;

            return root;
        
        } else if (common_prefix != NULL && prefix_match(curr_pointer->prefix, bits_cafe_name) == FALSE) {
            // prefix doesn't match exactly but both of them have some parts in common

            common_prefix_length = getLength(common_prefix);
            
            if (common_prefix_length < curr_pointer->prefix_length) {
                // the common part is less in length than the one currently stored

                //creating a temp_pointer to store this as new parent node
                temp_pointer = (radix_node_t* )malloc(sizeof(radix_node_t));
                temp_pointer -> prefix = common_prefix;
                temp_pointer -> prefix_length = common_prefix_length;

                if (getBit(bits_cafe_name, temp_pointer->prefix_length+1) == 0) {  /* +1 is to check the next bit
                                                                                    of the common_prefix_length of
                                                                                    the current cafe_bit entered*/

                    // assigning new cafe record to branch_A
                    temp_pointer->branch_A = (radix_node_t* )malloc(sizeof(radix_node_t));
                    temp_pointer->branch_A->prefix = bits_cafe_name;
                    temp_pointer->branch_A->prefix_length = getLength(bits_cafe_name);
                    temp_pointer->branch_A->branch_A = NULL;
                    temp_pointer->branch_A->branch_B = NULL;
                    temp_pointer->branch_A->list_curr_size = INITIAL_SIZE;
                    temp_pointer->branch_A->cafe_list = (cafe_t** )malloc(INITIAL_SIZE*sizeof(cafe_t*));
                    temp_pointer->branch_A->list_count = 0;
                    temp_pointer->branch_A->cafe_list[temp_pointer->branch_A->list_count] = cafe;
                    temp_pointer->branch_A->list_count++;

                    // assigning the current pointer to branch_B
                    temp_pointer->branch_B = curr_pointer;

                } else if (getBit(bits_cafe_name, temp_pointer->prefix_length+1) == 1) {

                    // assigning new cafe record to branch_B
                    temp_pointer->branch_B = (radix_node_t* )malloc(sizeof(radix_node_t));
                    temp_pointer->branch_B->prefix = bits_cafe_name;
                    temp_pointer->branch_B->prefix_length = getLength(bits_cafe_name);
                    temp_pointer->branch_B->branch_A = NULL;
                    temp_pointer->branch_B->branch_B = NULL;
                    temp_pointer->branch_B->list_curr_size = INITIAL_SIZE;
                    temp_pointer->branch_B->cafe_list = (cafe_t** )malloc(INITIAL_SIZE*sizeof(cafe_t*));
                    temp_pointer->branch_B->list_count = 0;
                    temp_pointer->branch_B->cafe_list[temp_pointer->branch_B->list_count] = cafe;
                    temp_pointer->branch_B->list_count++;

                    // assigning the current pointer to branch_A
                    temp_pointer->branch_A = curr_pointer;

                }

                temp_pointer -> list_curr_size = 0; // this node doesn't store any cafe
                temp_pointer -> cafe_list = NULL;
                temp_pointer -> list_count = 0;

                // deciding whether it was the root node changed
                if (curr_pointer == root) {
                    root = temp_pointer;
                    return root;
                } else {

                    // find whether it was attached to branch_A or branch_B
                    if (previous_pointer->branch_A == curr_pointer) {
                        previous_pointer->branch_A = temp_pointer;
                    } else if (previous_pointer->branch_B == curr_pointer) {
                        previous_pointer->branch_B = temp_pointer;
                    }
                    return root;

                }


            } else { // common_prefix > curr_pointer->prefix_length, current_pointer needs to get passed to the branches
                     // the case where it's equal, means the prefix match exactly with the common_prefix

                if (getBit(bits_cafe_name, curr_pointer->prefix_length+1) == 0) {
                    // curr_pointer will point towards branch_A
                    previous_pointer = curr_pointer;
                    curr_pointer = curr_pointer->branch_A;

                } else if (getBit(bits_cafe_name, curr_pointer->prefix_length+1) == 1) {
                    // curr_pointer will point towards branch_B
                    previous_pointer = curr_pointer;
                    curr_pointer = curr_pointer->branch_B;

                }
            }
        } /*else if (common_prefix == NULL) {
            // this cannot happen because all the characters have 0 in common in their binary form
            // as all ASCII are positive and all positive integers in binary ASCII start with 0.

        }*/
    }

    // curr_pointer points to NULL, so new node needs to be created
    curr_pointer = (radix_node_t* )malloc(sizeof(radix_node_t));
    curr_pointer -> prefix = bits_cafe_name;
    curr_pointer -> prefix_length = getLength(curr_pointer -> prefix);
    curr_pointer -> branch_A = NULL; 
    curr_pointer -> branch_B = NULL;
    curr_pointer -> list_curr_size = INITIAL_SIZE;
    curr_pointer -> cafe_list = (cafe_t** )malloc(curr_pointer->list_curr_size*sizeof(cafe_t*));
    curr_pointer -> list_count = 0;
    curr_pointer -> cafe_list[curr_pointer->list_count] = cafe;
    curr_pointer -> list_count++;
    
    if (getBit(bits_cafe_name, previous_pointer->prefix_length+1) == 0) {
        // curr_pointer gets assigned to branch_A
        previous_pointer->branch_A = curr_pointer;
    } else {
        // curr_pointer gets assigned to branch_B
        previous_pointer->branch_B = curr_pointer;
    }

    return root;
    
}

/*
 This function takes in the prefix to be found, the root of the radix tree and the output file to where the information
 is to be stored. Then, it traverses through the radix tree finds all the matching information and stores it to the output file.
 */
void find_and_traverse_node(char* search_prefix, radix_node_t* root, FILE* output_file) {

    int bits_compared = 0, characters_compared = 0, strings_compared = 0;

    radix_node_t* curr_pointer = root;

    int* bits_search_prefix = (int *) string_to_binary(search_prefix); // the prefix gets converted to bits

    while (curr_pointer != NULL) {
        
        compare_bits_and_characters(bits_search_prefix, curr_pointer->prefix, &bits_compared, &characters_compared);

        if (prefix_match(bits_search_prefix, curr_pointer->prefix) == TRUE) {
            // prefix searched and the trading name has a common prefix
            strings_compared++;

            // outputting to stdout
            printf("%s --> b%d c%d s%d\n", search_prefix, bits_compared, characters_compared, strings_compared);
            
            // outputting into the output_file
            fprintf(output_file, "%s\n", curr_pointer->cafe_list[0]->trading_name);
            for (int i = 0; i < curr_pointer->list_count; i++) {
                print_cafe(output_file, curr_pointer->cafe_list[i]);
            }
            break;

        // else, choosing which branch to go next    
        } else if (getBit(bits_search_prefix, curr_pointer->prefix_length+1) == 0) {
            curr_pointer = curr_pointer->branch_A;
        } else if (getBit(bits_search_prefix, curr_pointer->prefix_length+1) == 1) {
            curr_pointer = curr_pointer->branch_B;
        }
    }
}

/*
 This function takes in the root of the radix tree and frees all the dynamically allocated memories.
 */
void free_radix_tree(radix_node_t* node) {
    
    if (node == NULL) {
        return;
    }

    // recursively freeing the child nodes
    free_radix_tree(node->branch_A);
    free_radix_tree(node->branch_B);

    // freeing prefix array if allocated
    if (node->prefix != NULL) {
        free(node->prefix);
    }

    // freeing cafe_list if allocated
    if (node->cafe_list != NULL) {
        for (int i = 0; i < node->list_count; i++) {
            free(node->cafe_list[i]);
        }
        free(node->cafe_list);
    }

    // freeing the node itself
    free(node);
}

