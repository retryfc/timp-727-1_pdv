#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
} node;

typedef struct list {
    struct node* head;
    struct node* tail;
} list;

void init(list* l)
{
    l->head = NULL;
    l->tail = NULL;
}

int push_back(list* l, int value)
{
    node* temp = malloc(sizeof(node));
    temp->value = value;
    temp->next = NULL;
    if(l->head == NULL) {
        l->head = temp;
        l->tail = temp;
        return 0;
    }
    else {
        l->tail->next = temp;
        l->tail = temp;
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
    temp2->next = temp->next;
    temp->next = temp2;
    return 0;
}

int push_front(list* l, int value)
{
    node* temp = malloc(sizeof(node));
    temp->value = value;
    if(l->tail == NULL) {
        l->head = temp;
        l->tail = temp;
        return 0;
    }
    else {
        temp->next = l->head;
        l->head = temp;
        return 0;
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

int isEmpty(list* l)
{
    if((l->head == NULL) && (l->tail == NULL))
        return 0;
    return 1;
}

int delete(list* l, int value)
{
    node* temp1;
    node* temp2;
    temp1 = l->head;
    while(temp1->value != value) {
        temp2 = temp1;
        temp1 = temp1->next;
    }
    if(temp1 == NULL)
        return 1;
    temp2->next = temp1->next;
    free(temp1);
    return 0;
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
    print(out);

    scanf("%d", &n);
    push_front(out, n);
    print(out);

    scanf("%d %d", &n, &y);
    insertAfter(out, n-1, y);
    print(out);

    scanf("%d", &n);
    delete(out, n);
    print(out);

    clear(out);

    return 0;
}
