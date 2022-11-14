#include <stdio.h>
#include <stdlib.h>

typedef int elem;

typedef struct Node {
    elem x;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// tree utilities
elem max(elem a, elem b) {
    return (a > b) ? a : b;
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int is_balanced(Node* root)
{
    if (root == NULL)
        return 0;
    int lh = is_balanced(root->left);
    if (lh == -1)
        return -1;
    int rh = is_balanced(root->right);
    if (rh == -1)
        return -1;
 
    if (abs(lh - rh) > 1)
        return -1;
    else
        return max(lh, rh) + 1;
}

int get_balance(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

Node *min_value_node(Node *root) {
    Node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// constructor
Node *new_node(elem x) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->x = x;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;

    return new;
}

// AVL rotations
Node *right_rotate(Node *root) {
    Node *x = root->left;
    Node *y = x->right;

    x->right = root;
    root->left = y;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *left_rotate(Node *root) {
    Node *x = root->right;
    Node *y = x->left;

    x->left = root;
    root->right = y;

    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// insertion
Node *insert(Node *root, elem x) {
    // binary search tree insertion
    if (root == NULL) {
        return new_node(x);
    }

    if (x < root->x) {
        root->left = insert(root->left, x);
    } else if (x > root->x) {
        root->right = insert(root->right, x);
    } else {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    // check balance
    int balance = get_balance(root);

    if (balance > 1 && x < root->left->x) {
        return right_rotate(root);
    }

    if (balance < -1 && x > root->right->x) {
        return left_rotate(root);
    }

    if (balance > 1 && x > root->left->x) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && x < root->right->x) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}


// removal 
Node *remove_node(Node *root, elem x) {
    if (root == NULL) {
        return root;
    }

    if (x < root->x) {
        root->left = remove_node(root->left, x);
    } else if (x > root->x) {
        root->right = remove_node(root->right, x);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *tmp = (root->left) ? root->left : root->right;

            if (tmp == NULL) {
                tmp = root;
                root = NULL;
            } else {
                *root = *tmp;
            }
            free(tmp);
        } else {
            Node *tmp = min_value_node(root->right);
            root->x = tmp->x;
            root->right = remove_node(root->right, tmp->x);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && get_balance(root->left) >= 0) {
        return right_rotate(root);
    }

    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0) {
        return left_rotate(root);
    }

    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// traversal
// level order traversal
void print_level(Node *node, int level) {
    if (node == NULL)
        return;
    if (level == 0)
        printf("%d\n", node->x);
    else if (level > 0) {
        print_level(node->left, level - 1);
        print_level(node->right, level - 1);
    }
}
void level_order_traversal(Node *node) {
    for (int i = 0; i < node->height; i ++) {
        print_level(node, i);
    }
}

// in order traversal
void in_order_traversal(Node *node) {
    if (node == NULL)
        return;
    in_order_traversal(node->left);
    printf("%d\n", node->x);
    in_order_traversal(node->right);
}

// pre order traversal
void pre_order_traversal(Node *node) {
    if (node == NULL)
        return;
    printf("%d\n", node->x);
    pre_order_traversal(node->left);
    pre_order_traversal(node->right);
}

// post order traversal
void post_order_traversal(Node *node) {
    if (node == NULL)
        return;
    post_order_traversal(node->left);
    post_order_traversal(node->right);
    printf("%d\n", node->x);
}

int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    root = remove_node(root, 20);

    pre_order_traversal(root);
    printf("\n\n%d\n\n", is_balanced(root));

    return 0;
}
