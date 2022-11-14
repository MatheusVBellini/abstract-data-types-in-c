#include <stdio.h>
#include <stdlib.h>

/* LIST BINARY TREE */
typedef int elem;

typedef struct node {
    elem value;
    struct node *left, *right;
} node;

typedef struct ListBinaryTree {
    node *head;
} ListBinaryTree;

// allocate tree
node *create_node(elem x) {
    node *new = malloc(sizeof(node));
    new -> value = x;
    new -> left = NULL;
    new -> right = NULL;

    return new;
}
ListBinaryTree *create_lbt(elem x) {
    ListBinaryTree *this = malloc(sizeof(ListBinaryTree));
    this -> head = create_node(x);

    return this;
}

// desallocate tree
void destroy_node(node *this) {
    if (this == NULL)
        return;
    destroy_node(this -> left);
    destroy_node(this -> right);
    free(this);
}
void destroy_lbt(ListBinaryTree *this) {
    destroy_node(this -> head);
}

// search tree
node *_search_tree_lbt(node *this, elem x) {
    if (this == NULL)
        return NULL;
    if (x == this -> value)
        return this;
    return (x < this -> value) ? _search_tree_lbt(this -> left, x) : _search_tree_lbt(this -> right, x);
}
node *search_tree_lbt(ListBinaryTree *this, elem x) {
    return _search_tree_lbt(this -> head, x);
}

// check if node is a leaf node
int is_external(node *this) {
    if (this -> left == NULL && this -> right == NULL)
        return 1;
    return 0;
}

// return root of binary tree
node *root(ListBinaryTree *this) {
    return this -> head;
}

// return children of node
node **children(node *this) {
    node **children = malloc(2 * sizeof(node*));
    children[0] = this -> left;
    children[1] = this -> right;

    return children;
}

// return parent of node
node *search_parent(node *root, elem x) {
    if (root -> value == x) {
        printf("node is root\n");
        return NULL;
    }

    while (root -> left -> value == x || root -> right -> value == x) {
        root = (x < root -> value) ? root -> left : root -> right;
        if (root == NULL) {
            return NULL;
        }
    }

    return root;
}

node *parent(ListBinaryTree *this, node *child) {
    return search_parent(this->head,child->value);
}

// insert new value in tree
void _insert_lbt(node **this, elem x) {
    if (*this == NULL) {
        *this = create_node(x);
        return;
    }

    (x <= (*this) -> value) ? _insert_lbt(&((*this) -> left), x) : _insert_lbt(&((*this) -> right), x);
}
void insert_lbt(ListBinaryTree *this, elem x) {
    if (this == NULL) {
        printf("Arvore nao alocada\n");
        return;
    }

    _insert_lbt(&(this -> head), x);
}

// remove value from tree
void _remove_lbt(node **this, elem x) {
    node *current = *this;
    node *previous = NULL;

    while (current != NULL && current -> value != x) {
        previous = current;
        current = (x <= current -> value) ? current -> left : current -> right;
    }

    // x is not in the tree
    if (current == NULL)
        return;

    // if node is external or has only one child
    if (current -> left == NULL || current -> right == NULL) {
        node *new;
        if (current -> left == NULL) {
            new = current -> right;
        } else {
            new = current -> left;
        }

        // node to be deleted is root
        if (previous == NULL) {
            node *tmp = *this;
            *this = new;
            tmp -> value = 0;
            tmp -> left = NULL;
            tmp -> right = NULL;
            free(tmp);
            return ;
        }

        // current is substitued to new
        if (current == previous -> left)
            previous -> left = new;
        else
            previous -> right = new;

        free(current);
        return;
    }

    // if node has two children
    node *tmp1 = current -> right, *tmp2 = NULL;
    while (tmp1 -> left != NULL) {
        tmp2 = tmp1;
        tmp1 = tmp1 -> left;
    }

    if (tmp2 != NULL)
        tmp2 = tmp1 -> right;
    else
        current -> right = tmp1 -> right;

    current -> value = tmp1 -> value;
    free(tmp1);
}
void remove_lbt(ListBinaryTree *this, elem x) {
    _remove_lbt(&(this -> head), x);
}

// get tree height
int _tree_height(node *this) {
    if (this == NULL) {
        return 0;
    }

    int left_height = _tree_height(this -> left);
    int right_height = _tree_height(this -> right);

    return (left_height >= right_height) ? left_height + 1 : right_height + 1;
}
int tree_height(ListBinaryTree *this) {
    return _tree_height(this -> head);
}

// level order traversal
void print_level_lbt(node *this, int level) {
    if (this == NULL)
        return;
    if (level == 0)
        printf("%d\n", this -> value);
    else if (level > 0) {
        print_level_lbt(this -> left, level - 1);
        print_level_lbt(this -> right, level - 1);
    }
}
void _level_order_traversal_lbt(node *this, int height) {
    for (int i = 0; i < height; i ++) {
        print_level_lbt(this, i);
    }
}
void level_order_traversal_lbt(ListBinaryTree *this) {
    _level_order_traversal_lbt(this -> head, tree_height(this));
}

// in order traversal
void _in_order_traversal_lbt(node *this) {
    if (this == NULL)
        return;
    _in_order_traversal_lbt(this -> left);
    printf("%d\n", this -> value);
    _in_order_traversal_lbt(this -> right);
}
void in_order_traversal_lbt(ListBinaryTree *this) {
    _in_order_traversal_lbt(this -> head);
}

// pre order traversal
void _pre_order_traversal_lbt(node *this) {
    if (this == NULL)
        return;
    printf("%d\n", this -> value);
    _pre_order_traversal_lbt(this -> left);
    _pre_order_traversal_lbt(this -> right);
}
void pre_order_traversal_lbt(ListBinaryTree *this) {
    _pre_order_traversal_lbt(this -> head);
}

// post order traversal
void _post_order_traversal_lbt(node *this) {
    if (this == NULL)
        return;
    _post_order_traversal_lbt(this -> left);
    _post_order_traversal_lbt(this -> right);
    printf("%d\n", this -> value);
}
void post_order_traversal_lbt(ListBinaryTree *this) {
    _post_order_traversal_lbt(this -> head);
}

/* ---------------- */

int main() {
    ListBinaryTree *t = create_lbt(2);
    insert_lbt(t,3);
    insert_lbt(t,1);
    insert_lbt(t,4);
    insert_lbt(t,0);
    insert_lbt(t,10);
    /*
            2
          /  \
         1    3
        /    / \
       0    4  10
    */


    pre_order_traversal_lbt(t);
    printf("\n");
    remove_lbt(t,2);

    node *n = search_tree_lbt(t, 11);
    printf("%d\n", n == NULL);

    return 0;
}
