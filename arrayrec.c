#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>


struct record {
    char name[128];
    unsigned char age;
    unsigned char shoe_size;
}; 

int search_by_name(struct record records[], int num_records, 
                   const char *str, int start_index) {
    struct record temp;
    for (int i = start_index; i < num_records; i++) {
        temp = records[i];
        if (strcasestr(temp.name,str) != NULL) {
            return i;
        }
    } 
    return -1;
}

int *get_matches(struct record records[], int num_records,
                 const char *str) {
    // your code here
    int *match=malloc((num_records+1) * sizeof(int));
    int index = 1; // where to put matching index. reserve 0 for array length
    int start_index = 0;  // index used for searching   
    while (start_index < num_records) {
        int temp = search_by_name(records, num_records, str, start_index);
        if (temp == -1) { //no (more )matches found, ends    
            break;
        } else {
            match[index] = temp;
            index++;
            start_index = temp + 1; // start from the one after the match
        }
    
    }

    match[0] = index-1;
    return match;
}


#ifndef AUTOTEST
int main(int argc, char **argv) {
    printf ("*** testing search_by_name\n");

    struct record records[] = { {"Alice",18,6}, {"Bob",17,7},{"Claudia",18,49}, {"bobby", 0, 0} };

    int rv = search_by_name(records, 4, "alice", 0);
    assert(rv == 0);

    rv = search_by_name(records, 4, "audi", 1);
    assert(rv == 2);

    rv = search_by_name(records, 4, "alice", 1);
    assert(rv == -1);

    printf ("*** testing get_matches\n");

    int *matches = NULL; 
    matches = get_matches(records, 4, "bob");
    assert(matches[0] == 2);
    assert(matches[1] == 1);
    assert(matches[2] == 3);
    free(matches); // this shouldn't crash :-)
    
    matches = NULL;
    matches = get_matches(records, 4, "robert");
    assert(matches[0] == 0);
    free(matches);
    
    printf ("*** if you got here, then the tests passed\n");
    return 0;
}
#endif
