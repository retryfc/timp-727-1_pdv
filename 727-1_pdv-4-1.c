#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    struct node *child_left;
    struct node *child_right;
    struct node *parent;
    int data;
} node;

typedef struct tree {
    struct node *root; 
    int count; 
} tree;

void init(tree *t) {
    t->root = NULL;
    t->count = 0;
}

int find(struct tree *t, int value, struct node *n) {
    struct node *current_node = t->root;
    if (t->root == NULL) {
        return 1;
    }
    while (1) {
        if (current_node == NULL) {
            return 1;
        } else if (current_node->data == value) {
            n->data = current_node->data;
            n->child_left = current_node->child_left;
            n->child_right = current_node->child_right;
            n->parent = current_node->parent;
            return 0;
        } else if (value > current_node->data) {
            current_node = current_node->child_right;
        } else {
            current_node = current_node->child_left;
        }
    }
    return 1;
}

int insert(tree *t, int value) {
    struct node *new_node;
    new_node = (struct node*) malloc (sizeof(struct node));
    int err = find(t, value, new_node);
    free(new_node);
    if (err == 0) {
        return 1;
    }

    struct node* current_node = t->root;
    struct node* current_parent = NULL;
    int is_left = 0;

    while (1) {
        if (current_node == NULL) {
            struct node* result = (struct node*) malloc (sizeof(struct node));
            result->child_left = NULL;
            result->child_right = NULL;
            result->parent = current_parent;
            result->data = value;
            t->count += 1;

            if (t->root == NULL) {
                t->root = result;
            } else if (result->parent != NULL) {
                if (is_left == 1) {
                    result->parent->child_left = result;
                } else {
                    result->parent->child_right = result;
                }
            }

            return 0;
        }

        if (current_node->data > value) {
            current_parent = current_node;
            current_node = current_node->child_left;
            is_left = 1;
        } else {
            current_parent = current_node;
            current_node = current_node->child_right;
            is_left = 0;
        }
    }

    return 0;
}

int remove_from_tree(tree *t, int value) {
    node *n = t->root;
    if (t->root == NULL) {
        return 1;
    }
    while (1) {
        if (n == NULL) {
            break;
            return 1;
        } else if (n->data == value) {
            break;
        } else if (value > n->data) {
            n = n->child_right;
        } else {
            n = n->child_left;
        }
    }

    if ((n->child_left == NULL) && (n->child_right == NULL)) {
        if (n->parent->child_right->data == n->data) {
            n->parent->child_right = NULL;
        } else {
            n->parent->child_left = NULL;
        }
    } else if (n->child_right == NULL) {
        *n = *n->child_left;
    } else if (n->child_left == NULL) {
        *n = *n->child_right;
    } else {

        node *search = n->child_right;
        int min_value;
        node *min;
        while (1) {
            if (search == NULL) {
                break;
            } else {
                min = search;
                min_value = search->data;
                search = search->child_left;
            }
        }
        n->data = min->data;
        n = min;
        if ((n->child_left == NULL) && (n->child_right == NULL)) {
            if (n->parent->child_right->data == n->data) {
                n->parent->child_right = NULL;
            } else {
                n->parent->child_left = NULL;
            }
        } else if (n->child_right == NULL) {
            *n = *n->child_left;
        } else {
            *n = *n->child_right;
        }
    }
    t->count--;
    return 0;
}

int deepness(struct node *n) {
    if (n == NULL) {
        return 0;
    } else {
        int depth_left = deepness(n->child_left);
        int depth_right = deepness(n->child_right);
        return (depth_left > depth_right) ? depth_left + 1 : depth_right + 1;
    }
}

void printNode(struct node *n, int current, int deep, int first) {
    if (current == deep) {
        if (first > 0) {
            printf(" ");
        }
        if (n == NULL) {
            printf("_");
        } else {
            printf("%d", n->data);
        }
    } else if (n != NULL) {
        printNode(n->child_left, current + 1, deep, first);
        printNode(n->child_right, current + 1, deep, first + 1);
    } else {
        printNode(n, current + 1, deep, first);
        printNode(n, current + 1, deep, first + 1);
    }
}

void print(struct node *n) {
    int max_deepness = deepness(n);
    for (int i = 1; i <= max_deepness; i++) {
        printNode(n, 1, i, 0);
        printf("\n");
    }
}

void printTree(struct tree *t) {
    print(t->root);
}

void dump(struct node *n) {
    if (n != NULL) {
        printf("%d ", n->data);
        dump(n->child_left);
        dump(n->child_right);
    }
}

int removeMin(node *n) {
    if (n->child_left == NULL) {
        n = n->child_right;
    }
    while (1) {
        if (n->child_left == NULL) {
            if ((n->child_left == NULL) && (n->child_right == NULL)) {
                if (n->parent->child_right->data == n->data) {
                    n->parent->child_right = NULL;
                } else {
                    n->parent->child_left = NULL;
                }
            } else if (n->child_right == NULL) {
                *n = *n->child_left;
            } else {
                *n = *n->child_right;
            }
            return n->data;
        } else {
            n = n->child_left;
        }
    }
}

int rotateRight(tree *t, node *current_node) {
    node *candidate = current_node->child_left;
    if ((candidate != NULL) && (current_node != NULL)) {
        current_node->child_left = candidate->child_right;
        if (candidate->child_right != NULL) {
            candidate->child_right->parent = current_node;
        }
        candidate->parent = current_node->parent;
        if (current_node->parent != NULL) {
            if (current_node->parent->child_left == current_node) {
                current_node->parent->child_left = candidate;
            } else {
                current_node->parent->child_right = candidate;
            }
        }
        t->root = candidate;
        candidate->child_right = current_node;
        current_node->parent = candidate;
        return 0;
    } else {
        return 1;
    }
}

int rotateLeft(tree *t, node *current_node) {
    node *candidate = current_node->child_right;
    if ((candidate != NULL) && (current_node != NULL)) {
        current_node->child_right = candidate->child_left;
        if (candidate->child_left != NULL) {
            candidate->child_left->parent = current_node;
        }
        candidate->parent = current_node->parent;
        if (current_node->parent != NULL) {
            if (current_node->parent->child_right == current_node) {
                current_node->parent->child_right = candidate;
            } else {
                current_node->parent->child_left = candidate;
            } 
        }
        t->root = candidate;
        candidate->child_left = current_node;
        current_node->parent = candidate;
        return 0;
    } else {
        return 1;
    }
}

void delete_node(struct node* node) {
    if (node == NULL) {
        return;
    } else {
        delete_node(node->child_right);
        delete_node(node->child_left);
        free(node);
        return;
    }
}

void clear(tree* t) {
    delete_node(t->root);
    init(t);
}

int main() {
    struct tree *t = malloc(sizeof t);
    init(t);
    for (int i = 0; i < 4; i++) {
        int value;
        scanf("%d", &value);
        insert(t, value);
    }
    printTree(t);

    for (int i = 0; i < 3; i++) {
        int value;
        scanf("%d", &value);
        insert(t, value);
    }
    printTree(t);


    int m1;
    scanf("%d", &m1);
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    find(t, m1, new_node);
    if (new_node->parent != NULL) {
        printf("%d ", new_node->parent->data);
    } else {
        printf("_ ");
    }
    if (new_node->child_left != NULL) {
        printf("%d ", new_node->child_left->data);
    } else {
        printf("_ ");
    }
    if (new_node->child_right != NULL) {
        printf("%d\n", new_node->child_right->data);
    } else {
        printf("_\n");
    }

    int m2;
    scanf("%d", &m2);
    
    int err = find(t, m2, new_node);
    if (err == 1) {
        printf("-\n");
    } else {
        if (new_node->parent != NULL) {
            printf("%d ", new_node->parent->data);
        } else {
            printf("_ ");
        }
        if (new_node->child_left != NULL) {
            printf("%d ", new_node->child_left->data);
        } else {
            printf("_ ");
        }
        if (new_node->child_right != NULL) {
            printf("%d\n", new_node->child_right->data);
        } else {
            printf("_\n");
        }
    }

    int m3;
    scanf("%d", &m3);


    remove_from_tree(t, m3);
    printTree(t);
    while (rotateLeft(t, t->root) != 1);
    printTree(t);

    while (rotateRight(t, t->root) != 1);
    printTree(t);

    printf("%d\n", t->count);
    printf("-\n");

    clear(t);
    delete_node(t->root);

    free(t);
    free(new_node);

    return 0;

}

