#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

int main(int argc, char *argv[]) {

    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /* Create a linked list */
    struct node *node_0 = (struct node *)malloc(sizeof(struct node));
    node_0->data = values[0];
    node_0->next = NULL;
    printf("Created node %d\n", node_0->data);

    struct node *node_im1 = node_0;
    for (int i = 1; i < 10; i++) {
        struct node *node_i = (struct node *)malloc(sizeof(struct node));
        node_i->data = values[i];
        node_i->next = NULL;
        printf("Created node %d\n", node_i->data);
        if (i > 0) {
            node_im1->next = node_i;
        }
        node_im1 = node_i;
    }

    /* Print the linked list */
    struct node *current = node_0;
    while (current) {
        printf("Printing node %d\n", current->data);
        current = current->next;
    }

    /* Free the linked list, FIFO, first in, first out. */
    while (node_0) {
        struct node *next = node_0->next;
        printf("Cleaning up node %d\n", node_0->data);
        free(node_0);
        node_0 = next;
    }

    return EXIT_SUCCESS;
}
