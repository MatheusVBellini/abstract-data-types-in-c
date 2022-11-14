#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100
typedef int elem;

typedef struct {
    elem values[STACK_SIZE];
    int count;
} Stack;

typedef Stack* stack;

// aloca lista na memoria
stack create_stack(elem x) {
    stack this = (stack) malloc(sizeof(Stack));
    this -> values[0] = x;
    this -> count = 1;
    
    return this;
}

// desaloca lista da memoria
void destroy_stack(stack this) {
    for (int i = 0; i < this -> count; i++) {
        this -> values[i] = 0;
    }
    this -> count = 0;
    free(this);
}

// diz se a stack esta vazia
int is_empty(stack this) {
    return (this -> count == 0) ? 1 : 0;
}

// coloca elemento na stack
int push(stack this, elem x) {
    if (this -> count == STACK_SIZE) {
        printf("Stack overflow\n");
        return 1; // stack overflow
    }
    
    this -> values[this -> count] = x;
    this -> count++;
    
    return 0; // successfully pushed
}

// tira elemento da stack
int pop(stack this) {
    if (this -> count == 0) {
        printf("Stack already empty\n");
        return 0;
    }
    
    this -> count--;
    elem x = this -> values[this -> count];
    this -> values[this -> count] = 0;
    
    return x;
}

// mostra a stack na tela
void print_stack(stack this) {
    for (int i = this -> count - 1; i >= 0; i--) {
        printf("%d\n", this -> values[i]);
    }
}

int main() {
    stack q = create_stack(1);
    push(q,2);
    push(q,3);
    push(q,4);
    push(q,5);
    push(q,6);
    
    pop(q);
    pop(q);
    pop(q);
    pop(q);
    pop(q);
    pop(q);
    pop(q);
    
    print_stack(q);
    destroy_stack(q);

    return 0;
}
