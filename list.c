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
    struct node *pointer = head;
    struct node temp_node;
    while (pointer != NULL) {
        temp_node = *pointer;
        if (strcasestr(temp_node.name, name) != NULL) { // match found
            printf("A match: %s\n",temp_node.name);
        }
        pointer = temp_node.next;
    }
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
    struct node *pointer = *head;
    struct node temp_node;
    struct node **ptr_before = head;
    
    while (pointer != NULL) {   

        temp_node = *pointer;
        printf("Currently comparing: %s\n",temp_node.name);
        if (strcasecmp(temp_node.name, name) != NULL) { // match found
            *ptr_before = temp_node.next;
            free(pointer);
            return 1;
        }
        *ptr_before = pointer;
        pointer = temp_node.next;
    }
    return 0;
}

void list_append(const char *name, struct node **head) {
    struct node *new_node = malloc(sizeof(struct node));
    strcpy(new_node -> name, name);
    new_node -> next = *head;
    *head = new_node;
}

void list_reverse(struct node **head) {
    // your code here
    struct node *temp = *head;
    struct node *previous = NULL;     
    struct node *next = NULL;
    
    while (temp != NULL) {
        //printf("Current name: %s\n",temp->name);
        next = temp -> next; // save the next node
        temp -> next = previous; // change node.next to previous node
        previous = temp;    // change previous to current node
        temp = next;        // go to next node
    }
    *head = previous; // update head
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

    if (head) {
        printf("Now we'll delete the first element\n");
        list_delete(head->name, &head);
    }

    list_clear(head);

    return 0;
}
#endif
