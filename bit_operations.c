#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BIT_SIZE 8
#define END_POINT -1
#define TRUE 1
#define FALSE 0

/*
 This function takes in a string and returns its binary in an array of int format.
 */
int* string_to_binary(char *string) {
    
    int i = 0, j = 0;
    
    int *binary_array = (int *)malloc((BIT_SIZE*strlen(string)+1)*sizeof(int)); // extra 1 bit to store -1, meaning end of array
    
    for (i = 0; i < strlen(string); i++) {
        
        int c = string[i];
        
        for (j = (i+1)*BIT_SIZE - 1; j>= i*BIT_SIZE; j--) { 
            binary_array[j] = (c % 2);
            c = (c / 2);  
        }
    }
    
    binary_array[BIT_SIZE*strlen(string)] = END_POINT;  // to mark the end of the array
    
    return binary_array;
}

/*
 This function takes in a bit array and returns the bit of the requested position.
 */
int getBit(int *key, int n) {
    return key[n-1];
}

/*
 This function takes in a bit array and returns its length.
 */
 int getLength(int *key) {
    int count = 0;
    if (key == NULL){
        return count;
    }
    while (key[count] != END_POINT) { // loops until end_point is reached
        count++;
    }
    return count;
}

/*
 This function takes in two prefixes and returns the common prefix between them. It returns NULL if there's no common prefix.
 */
int *find_common_prefix(int *prefix1_binary, int *prefix2_binary) {

    int *common_prefix = NULL;
    int count = 0;

    while((prefix1_binary[count] == prefix2_binary[count]) && 
        (prefix1_binary[count] != END_POINT) && (prefix2_binary[count] != END_POINT)) {  //loops until the bits are equal and no endpoint is reached
        count++;
    }

    if (count == 0) {
        // no common prefix found
        return NULL;
    }

    common_prefix = (int *)malloc((count+1)*sizeof(int)); // an extra room for storing the endpoint

    // putting the values inside common_prefix
    for (int i = 0; i < count; i++) {
        common_prefix[i] = prefix1_binary[i];
    }
    common_prefix[count] = END_POINT;

    return common_prefix;
}

/*
 This function takes in two prefixes and determines whether they match exactly or not.
 */
int prefix_match(int* prefix1, int* prefix2) {

    int i = 0;

    while (prefix1[i] == prefix2[i]) {  // any unmatching including one of them being END_POINT breaks loop
        
        // checks whether matching occurrs due to both being END_POINT 
        if (prefix1[i] == END_POINT && prefix2[i] == END_POINT) {
            return TRUE;
        }
        i++;
    }

    return FALSE;
}

/*
 This function takes in two prefixes and addresses of the bit and character comparisons variables to update them.
 */
void compare_bits_and_characters(int* key1, int* key2, int* b_c, int* c_c) {

    int count = 0;

    while (key1[count] == key2[count]) { // any unmatching including one of them being END_POINT breaks loop
        
        count++;

        // checks whether matching occurrs due to both being END_POINT 
        if (key1[count] == END_POINT && key2[count] == END_POINT) {
            //count--;
            break;
        }
        
    }

    *b_c += count;
    *c_c += count / BIT_SIZE;

}

