#ifndef RADIX_TREE_IMPLEMENTATION_H
#define RADIX_TREE_IMPLEMENTATION_H

typedef struct radix_node{
    int* prefix;
    int prefix_length;
    struct radix_node* branch_A;
    struct radix_node* branch_B;

    cafe_t** cafe_list;
    int list_curr_size;
    int list_count;
} radix_node_t;


radix_node_t* insert_radix_node(cafe_t* cafe, radix_node_t* root);

void find_and_traverse_node (char* search_prefix, radix_node_t* root, FILE* output_file);
void free_radix_tree(radix_node_t* node);

#endif
