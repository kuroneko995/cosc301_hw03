#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char name[128];
    struct node *next; 
};

void list_clear(struct node *list) {
    while (list != NULL) {
        struct node *tmp = list;
        list = list->next;
        free(tmp);
    }
}

void list_print_matches(const char *name, const struct node *head) {
    // your code here
    
}

void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %s\n", i++, list->name);
        list = list->next;
    }
}

int list_delete(const char *name, struct node **head) {
    // your code here

}

void list_append(const char *name, struct node **head) {
    // your code here

}

struct node *list_reverse(struct node *head) {
    // your code here

}

void list_sort(struct node **head) {
    // your code here

}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    char buffer[128];

    struct node *head = NULL;

    printf("Next string to add: ");
    fflush(stdout);
    while (fgets(buffer, 128, stdin) != NULL) {
        // fgets includes the newline character at
        // the end of a string as the last character.
        // let's squash it.
        int slen = strlen(buffer);
        buffer[slen-1] = '\0';

        list_append(buffer, &head);
        printf("Adding %s\n", buffer);

        printf("Next string to add (or ctrl+d to exit): ");
        fflush(stdout);
    }

    printf("\nHere is the list before sorting:\n");
    list_print(head);

    printf("\nAnd here is the list after sorting:\n");
    list_sort(&head);
    list_print(head);

    printf("\nAnd here is the list after reversing:\n");
    list_reverse(&head);
    list_print(head);

    printf("Printing matches for the string \"a\"\n");
    list_print_matches("a", head);
    list_clear(head);

    if (head) {
        printf("Now we'll delete the first element\n");
        list_delete(head->name, &head);
    }

    return 0;
}
#endif
