#include<stdio.h> 
#include<stdlib.h> 
#include<stdbool.h>
#include <string.h>

typedef struct node
{
  int data;
  struct node * left;
  struct node * right;
  struct node * parent;
} node;
 
typedef struct tree
{
  struct node * root;
  int count;
} tree;

void init(tree * t)
{
    struct tree * new_t = malloc(sizeof new_t);
    new_t->root = NULL;
    new_t->count = 0;
    t = new_t;
}

int find(tree* t, int data, node* n)
{
  struct node * n2;
  n2 = t->root;
  if (t->root == NULL){
    return 1;
  }
  while (1){
    if (n2 == NULL) {
      return 1;
    } else if (n2->data == data){

      n->data = n2->data;
      n->left = n2->left;
      n->right = n2->right;
      n->parent = n2->parent;

      return 0;
    } else if (data > n2->data){
      n2 = n2->right;
    } else {
      n2 = n2->left;
    }
  }

  return 1;
}

int insert(tree* t, int data)
{
  struct node * n, ** nn, * last_n = NULL;
  struct node * e_n;
  e_n = malloc(sizeof * e_n);
  int err = find(t, data, e_n);
  if (err == 0){
    return 1;
  }
  nn = &t->root;
  n = t->root;
  while (1){
    if (n == NULL) {
      n = *nn = malloc(sizeof * n);
      if (n != NULL){
        n->data = data;
        n->left = NULL;
        n->right = NULL;
        n->parent = last_n;
        t->count++;
        return 0;
      } else {
        return 2; 
      }
    }
    last_n = n;
    if (data > n->data){
      nn = &n->right;
      n = n->right;
    } else {
      nn = &n->left;
      n = n->left;
    }
  }
  return 0;
}

int deepness(struct node * n, int deep){
  if (n == NULL){
    return deep;
  }
  int d1 = deepness(n->left, deep + 1);
  int d2 = deepness(n->right, deep + 1);
  return (d1 > d2) ? d1 : d2;
}

void printNode(struct node * n, int current, int deep, int first){
  if (current == deep){
      if (first > 0){
        printf(" ");
      }   
    if (n == NULL){
      printf("_");
    } else{
      printf("%d", n->data);
    } 
  } else if (n != NULL){
    printNode(n->left, current + 1, deep, first);
    printNode(n->right, current + 1, deep, first + 1);
  } else {
    printNode(n, current + 1, deep, first);
    printNode(n, current + 1, deep, first + 1);
  }
}

void print_depth_first(struct node * n)
{
  int m = deepness(n, 0);
  for (int i = 1; i <= m; i++){
    printNode(n, 1, i, 0);
    if(i!=m){
      printf(" ");	
    }
    else{
      printf("\n");
    }
  }
}   


void print_direct(node* n){
	node** nodes = malloc(sizeof(node)*100);
	int last_pos=99;
	printf("%d", n->data);
	nodes[last_pos]=n->right;
	last_pos--;
	nodes[last_pos]=n->left;
	last_pos--;
	while(last_pos!=99){
		last_pos++;
		node* tmp=nodes[last_pos];
		printf(" %d", tmp->data);
		if(tmp->right!=NULL){
			nodes[last_pos]=tmp->right;
			last_pos--;
		}
		if(tmp->left!=NULL){
			nodes[last_pos]=tmp->left;
			last_pos--;
		}
	}
	printf("\n");
}

bool end=false;
void print_reverse(node* n){
	if (n!=NULL) {
		bool is_end=false;
		if(!end){
			is_end=true;
			end=true;
		}
        print_reverse(n->left);
        print_reverse(n->right);
        if(is_end)
        	printf("%d\n", n->data);
        else
        	printf("%d ", n->data);
    }
}

void printTree(struct tree * t)
{
    print_direct(t->root);
}

int main(){

  struct tree * t = malloc(sizeof t);
  init(t);
  for (int i = 0; i < 7; i++){
    int a;
    scanf("%d", &a);
    insert(t, a);
  }
  printTree(t);
  return 0;
}
