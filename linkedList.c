#include <stdio.h>
#include <stdlib.h>

struct node{
	struct node *next;
	struct node *prev;
};



int main(){
	struct node *head = malloc(sizeof(struct node)*1);
	struct node *tail = malloc(sizeof(struct node)*1);


	return 0;
}