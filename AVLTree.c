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

int height(Node *this) {
    if (this == NULL) {
        return 0;
    }
    return this->height;
}

int get_balance(Node *this) {
    if (this == NULL) {
        return 0;
    }

    return height(this->left) - height(this->right);
}

int is_balanced(Node *this) {
	return (abs(get_balance(this)) >= 1) ? 1 : 0;
}

Node *next_in_order(Node *this) {
    Node *current = this;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node *previous_in_order(Node *this) {
	Node *current = this;
	while (current->right != NULL) {
		current = current->right;
	}
	return current;
}

// constructor
Node *new_node(elem x) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->x = x;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;

    return new;
}

// AVL rotations
Node *right_rotate(Node *this) {
    Node *x = this->left;
    Node *y = x->right;

    x->right = this;
    this->left = y;

    this->height = max(height(this->left), height(this->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *left_rotate(Node *this) {
    Node *x = this->right;
    Node *y = x->left;

    x->left = this;
    this->right = y;

    this->height = max(height(this->left), height(this->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// insertion
Node *insert(Node *this, elem x) {
    // binary search tree insertion
    if (this == NULL) {
        return new_node(x);
    }

    if (x < this->x) {
        this->left = insert(this->left, x);
    } else if (x > this->x) {
        this->right = insert(this->right, x);
    } else {
        return this;
    }

    this->height = max(height(this->left), height(this->right)) + 1;

    // check balance
    int balance = get_balance(this);

    if (balance > 1) {
        if (x > this->left->x)
			this->left = left_rotate(this->left);
		return right_rotate(this);
    }

    if (balance < -1) {
		if (x < this->right->x) {
			this->right = right_rotate(this->right);
		}
        return left_rotate(this);
    }

    return this;
}


// removal 
Node *remove_node(Node *this, elem x) {
    if (this == NULL) {
        return this;
    }
	
    if (x < this->x) {									// x smaller, go left
        this->left = remove_node(this->left, x);
    } else if (x > this->x) {							// x greater, go right
        this->right = remove_node(this->right, x);
    } else {											// x equal, remove
        if (this->left == NULL) {						// substitute with right node
            Node *tmp = this->right;

            if (tmp == NULL) {
                tmp = this;
                this = NULL;
            } else {
                *this = *tmp;
            }
            free(tmp);
        } else if (this->right == NULL) {				// substitute with left node
            Node *tmp = this->left;

            if (tmp == NULL) {
                tmp = this;
                this = NULL;
            } else {
                *this = *tmp;
            }
            free(tmp);
		} else {										// substitute with next in order
            Node *tmp = next_in_order(this->right);
            this->x = tmp->x;
            this->right = remove_node(this->right, tmp->x);
        }
    }

    if (this == NULL) {
        return this;
    }

    this->height = max(height(this->left), height(this->right)) + 1;

    int balance = get_balance(this);

    if (balance > 1) {
		if (get_balance(this->left) < 0)
	        this->left = left_rotate(this->left);
        return right_rotate(this);
    }

    if (balance < -1) {
		if (get_balance(this->right) > 0)
			this->right = right_rotate(this->right);
        return left_rotate(this);
    }

    return this;
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
    Node *this = NULL;

    this = insert(this, 4);
    this = insert(this, 3);
    this = insert(this, 1);
    this = insert(this, 10);
    this = insert(this, 11);
    this = insert(this, 0);
    this = insert(this, 2);
    this = insert(this, 5);

    level_order_traversal(this);

	printf("\n\n\n");

	remove_node(this,4);
    level_order_traversal(this);
	printf("\n\n\n");

	remove_node(this,3);
    level_order_traversal(this);
	printf("\n\n\n");

	remove_node(this,7);
    level_order_traversal(this);
	printf("\n\n\n");

	remove_node(this,1);
    level_order_traversal(this);
	printf("\n\n\n");

	remove_node(this,2);
    level_order_traversal(this);
	printf("\n\n\n");


    return 0;
}
