#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

typedef struct list {
    struct node *head;
    struct node *tail;
} list;

void init(list* l)
{
    l->head = NULL;
    l->tail = NULL;
}

void clear(list* l)
{
    node* temp = l->head;
    node* temp1;

    while(temp != NULL) {
        temp1 = temp->next;
        free(temp);
        temp = temp1;
    }
    l->head = NULL;
    l->tail = NULL;
}

int isEmpty(list* l)
{
    if(l->head == NULL && l->tail == NULL)
        return 0;
    return 1;
}

int find(list* l, int value)
{
    node*  temp;
    temp = l->head;
    while(temp != NULL) {
        if(temp->value == value)
            return 1;
        temp = temp->next;
    }
    return 0;
}

int push_back(list* l, int value)
{
    node* temp = malloc(sizeof(node));
    temp->value = value;
    temp->prev = NULL;
    temp->next = NULL;
    if(!isEmpty(l)) {
        l->head = temp;
        l->tail = temp;
        return 0;
    }
    else {
        temp->prev = l->tail;
        l->tail->next = temp;
        l->tail = temp;
        return 0;
    }
    return 1;
}

int push_front(list* l, int value)
{
    node* temp = malloc(sizeof(node));
    temp->value = value;
    temp->prev = NULL;
    temp->next = NULL;
    if(!isEmpty(l)) {
        l->head = temp;
        l->tail = temp;
        return 0;
    }
    else {
        temp->next = l->head;
        l->head->prev = temp;
        l->head = temp;
        return 0;
    }
    return 1;
}

int insertAfter(list* l, int num, int value)
{
    node* temp = l->head;
    for(int i=0; i<num; ++i) {
        temp = temp->next;
        if(temp == NULL)
            return 1;
    }
    node* temp2 = malloc(sizeof(node));
    temp2->value = value;
    if(temp == l->tail) {
        temp->next = temp2;
        temp2->prev = temp;
        temp2->next = NULL;
    }
    else {
        temp2->next = temp->next;
        temp2->prev = temp;

        temp->next = temp2;
        temp = temp->next;
        temp = temp->next;
        temp->prev = temp2;
        return 0;
    }
}

int insertBefore(list* l, int num, int value)
{
    node* temp = l->head;

    for(int i=0; i<num; ++i) {
        temp = temp->next;
        if(temp == NULL)
            return 1;
    }
    node* temp2 = malloc(sizeof(node));
    temp2->value = value;
    if(temp == l->head) {
        temp->prev = temp2;
        temp2->next = temp;
        temp2->prev = NULL;
        l->head = temp2;
    }
    else {
        temp2->prev = temp->prev;
        temp2->next = temp;
        temp->prev = temp2;
        temp = temp->prev;
        temp = temp->prev;
        temp->next = temp2;
        return 0;
    }
}

int removeFirst(list* l, int value)
{
    node* temp1 = l->head;
    node* temp2;
    while(temp1 != NULL) {
        temp2 = temp1;
        if(temp1->value == value) {
            if(temp1 == l->head) {
                temp1 = temp1->next;
                temp1->prev = NULL;
                free(temp2);
            }
            else if(temp1 == l->tail) {
                temp1 = temp1->prev;
                temp1->next = NULL;
                free(temp2);
                l->tail = temp1;
            }
            else {
                temp1 = temp2->next;
                temp1->prev = temp2->prev;
                temp1 = temp2->prev;
                temp1->next = temp2->next;
                free(temp2);
            }
            return 0;
        }
        temp1 = temp1->next;
    }
    return 1;
}

int removeLast(list* l, int value)
{
    node* temp1 = l->tail;
    node* temp2;
    while(temp1 != NULL) {
        temp2 = temp1;
        if(temp1->value == value) {
            if(temp1 == l->tail) {
                temp1 = temp1->prev;
                temp1->next = NULL;
                free(temp2);
            }
            else if(temp1 == l->head) {
                temp1 = temp1->next;
                temp1->prev = NULL;
                free(temp2);
                l->head = temp1;
            }
            else {
                temp1 = temp2->next;
                temp1->prev = temp2->prev;
                temp1 = temp2->prev;
                temp1->next = temp2->next;
                free(temp2);
            }
            return 0;
        }
        temp1 = temp1->prev;
    }
    return 1;
}

void print(list* l)
{
    node*  temp;
    temp = l->head;
    while(temp != NULL) {
        printf("%d", temp->value);
        temp = temp->next;
        if(temp != NULL)
            printf(" ");
    }
    printf("\n");
}

void print_invers(list* l)
{
    node*  temp;
    temp = l->tail;
    while(temp != NULL) {
        printf("%d", temp->value);
        temp = temp->prev;
        if(temp != NULL)
            printf(" ");
    }
    printf("\n");
}

int main()
{
    int N, n, y;
    list* out;
    init(out);
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d", &n);
        push_back(out, n);
    }
    print(out);

    for(int i=1; i<=3; ++i) {
        scanf("%d", &y);
        printf("%d", find(out, y));
    }
    printf("\n");

    scanf("%d", &n);
    push_back(out, n);
    print_invers(out);

    scanf("%d", &n);
    push_front(out, n);
    print(out);

    scanf("%d %d", &n, &y);
    insertAfter(out, n-1, y);
    print_invers(out);

    scanf("%d %d", &n, &y);
    insertBefore(out, n-1, y);
    print(out);

    scanf("%d", &n);
    removeFirst(out, n);
    print_invers(out);

    scanf("%d", &n);
    removeLast(out, n);
    print(out);

    clear(out);
    return 0;
}
