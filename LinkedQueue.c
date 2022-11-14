#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct node {
    elem x;
    struct node* next;
} node;

typedef struct queue {
    node* front;
    node* rear;
} queue;

// aloca fila
queue *create_queue(elem x) {
    queue *this = (queue *)malloc(sizeof(queue));
    node *new = (node *)malloc(sizeof(node));
    new -> x = x;
    new -> next = NULL;
    this -> front = new;
    this -> rear = new;
    
    return this;
}

// deleta queue
void destroy_queue(queue *this) {
    node *tmp;
    while (this -> front != NULL) {
        tmp = this -> front;
        this -> front = this -> front -> next;
        free(tmp);
    }
}

// coloca elemento na fila
void enqueue(queue *this, elem x) {
    node *new = (node*)malloc(sizeof(node));
    new -> x = x;
    new -> next = NULL;
    this -> rear -> next = new;
    this -> rear = new;
}

// ve se esta vazia
int is_empty(queue *this) {
    return (this -> front == NULL) ? 1 : 0;
}

// tira elemento da fila
elem dequeue(queue *this) {
    if (is_empty(this)) {
        printf("fila vazia\n");
        return 0;
    }
    
    node *current = this -> front;
    this -> front = this -> front -> next;
    elem x = current -> x;
    free(current);
    return x;
}

// mostra a fila
void print_queue(queue *this) {
    node *tmp = this -> front;
    
    if (tmp == NULL) {
        printf("fila vazia\n");
        return;
    }
    
    while (tmp != NULL) {
        printf("%d\n", tmp -> x);
        tmp = tmp -> next;
    }
}

int main() {
    queue *q = create_queue(1);
    enqueue(q,2);
    enqueue(q,5);
    dequeue(q);
    dequeue(q);
    dequeue(q);
    print_queue(q);
    destroy_queue(q);

    return 0;
}
