#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct node {
    elem x;
    struct node *next;
} node;

typedef node* list;

// aloca uma nova lista
list create_list(elem x) {
    node* this = (node *)malloc(sizeof(node));
    this -> x = x;
    this -> next = NULL;
    
    return this;
}

// desaloca a memoria ocupada pela lista
void destroy_list(list this) {
    list tmp;
    while (this != NULL) {
        tmp = this;
        this = this -> next;
        tmp -> x = 0;
        free(tmp);
    }
}

// retorna o tamanho da lista
int list_size(list this) {
    int size = 0;
    while (this != NULL) {
        this = this -> next;
        size++;
    }
    
    return size;
}

// coloca elemento no comeco da lista
void append_first(list this, elem x) {
    node *old_head = create_list(this -> x);
    old_head -> next = this -> next;
    this -> x = x;
    this -> next = old_head;
}

// coloca elemento no final da lista
void append_last(list this, elem x) {
    node *tail = create_list(x);
    while (this -> next != NULL) {
        this = this -> next;
    }
    this -> next = tail;
}

// coloca elemento apos primeira aparicao de x na lista
void insert_after(list this, elem x, elem after_elem) {
    node *new = create_list(x);
    while (this -> x != after_elem) {
        this = this -> next;
        if (this == NULL) {
            printf("Element not found\n");
            return;
        }
    }
}

// remove elemento da lista
void remove_element(list this, elem x)  {
    if (this == NULL) {
        printf("Lista Vazia\n");
        return;
    }
    
    node *tmp;
    // primeiro elemento da lista
    if (this -> x == x) {
        tmp = this -> next;
        this -> x = tmp -> x;
        this -> next = tmp -> next;
        
        tmp -> x = 0;
        free(tmp);
        return;
    }
        
    // procura elemento
    while (this -> x != x) {
        tmp = this;
        this = this -> next;
        
        // elemento nao esta na lista
        if (this == NULL) {
            printf("Element not found\n");
            return;
        }
    }
    
    // ultimo elemento da lista
    if (this -> next == NULL) {
        tmp -> next = NULL;
        this -> x = 0;
        free(this);
        return;
    }
    
    // caso contrario
    this -> x = 0;
    tmp -> next = this -> next;
    free(this);
}

// imprime os valores da lista
void print_list(list this) {
    if (this == NULL) {
        printf("Lista Vazia\n");
        return;
    }
    
    while (this != NULL) {
        printf("%d\n", this -> x);
        this = this -> next;
    }
}

int main()
{
    list l = create_list(2);
    append_first(l,3);
    append_first(l,4);
    append_first(l,5);
    append_first(l,6);
    append_first(l,7);
    remove_element(l,7);
    remove_element(l,4);
    remove_element(l,2);
    
    print_list(l);
    destroy_list(l);

    return 0;
}
