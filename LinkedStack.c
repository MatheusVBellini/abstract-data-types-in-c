#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct node {
    elem x;
    struct node* next;
} node;

typedef struct stack {
    node* sbp; // stack base pointer
    node* stp; // stack top pointer
} stack;

// aloca stack
stack *create_stack(elem x) {
    stack *this = (stack *)malloc(sizeof(stack));
    node *new = (node *)malloc(sizeof(node));
    new -> x = x;
    new -> next = NULL;
    this -> stp = new;
    this -> sbp = new;
    
    return this;
}

// deleta stack
void destroy_stack(stack *this) {
    node *tmp;
    while (this -> stp != NULL) {
        tmp = this -> stp;
        this -> stp = this -> stp -> next;
        free(tmp);
    }
}

// coloca elemento na stack
void push(stack *this, elem x) {
    node *new = (node*)malloc(sizeof(node));
    new -> x = x;
    new -> next = this -> stp;
    this -> stp = new;
}

// ve se esta vazia
int is_empty(stack *this) {
    return (this -> stp == NULL) ? 1 : 0;
}

// tira elemento da stack
elem pop(stack *this) {
    if (is_empty(this)) {
        printf("stack vazia\n");
        return 0;
    }
    
    node *current = this -> stp;
    this -> stp = this -> stp -> next;
    elem x = current -> x;
    free(current);
    return x;
}

// mostra a stack
void print_stack(stack *this) {
    node *tmp = this -> stp;
    
    if (tmp == NULL) {
        printf("stack vazia\n");
        return;
    }
    
    while (tmp != NULL) {
        printf("%d\n", tmp -> x);
        tmp = tmp -> next;
    }
}

int main() {
    stack *q = create_stack(1);
    push(q,2);
    push(q,5);
    pop(q);
    pop(q);
    pop(q);
    print_stack(q);
    destroy_stack(q);

    return 0;
}

