#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//easy implementation of a queue with doubly linked list (each node has a previous, and a next)


struct node{
	int val;
	struct node *next;
	struct node *prev;
};

struct queue{
	int size;
	struct node *head;
	struct node *tail;
};


//initialize the queue
void initQueue(struct queue *myQueue){
	myQueue->head = malloc(sizeof(struct node));
	myQueue->tail = malloc(sizeof(struct node));

	//setting up intiial size of queue (0)
	myQueue->size = 0;
	//set up initial next
	myQueue->head->next = myQueue->tail;
	myQueue->tail->next = NULL;

	//set up initial prev
	myQueue->head->prev = NULL;
	myQueue->tail->prev = myQueue->head;

	return;
}

//should stick a new node with value x at the end of the queue
void enqueue(int x, struct queue *myQueue){
	struct node *newNode = malloc(sizeof(struct node));
	newNode->val = x;

	if(myQueue->head->next == myQueue->tail){	//if this is the first item to be added
		myQueue->head->next = newNode;
		newNode->next = myQueue->tail;
		newNode->prev = myQueue->head;
		myQueue->tail->prev = newNode;
	}
	else{
		newNode->next = myQueue->tail;
		newNode->prev = myQueue->tail->prev;
		myQueue->tail->prev->next = newNode;
		myQueue->tail->prev = newNode;
	}

	myQueue->size++;
}

//will print and pop off the first element of the queue
int dequeue(struct queue *myQueue){
	struct node *temp = myQueue->head->next;

	if(myQueue->size>0){
		printf("Popping %d off the queue...\n", myQueue->head->next->val);
		myQueue->head->next = myQueue->head->next->next;
		temp->next->prev = myQueue->head;
		free(temp);
		myQueue->size--;
	}
}

//test function to print the queue
void testPrint(struct queue *myQueue){
	struct node *current = myQueue->head->next;
	while(current!=myQueue->tail){
		printf("%d\n", current->val);
		current=current->next;
	}
	
}

//destroys the queue with good memory management
void destroyQueue(struct queue *myQueue){
	struct node *current = myQueue->head->next;
	while(current != myQueue->tail){
		myQueue->head->next = current->next;
		free(current);
		current = myQueue->head->next;
	}
	free(myQueue->head);
	free(myQueue->tail);
}


int main(){
	struct queue *myQueue;
	initQueue(myQueue);

	//first populate our queue
	int i;
	for(i=0; i<5; i++){
		enqueue(i, myQueue);
	}
	//test the size of the queue
	assert(myQueue->size == 5);

	//test print the queue:
	testPrint(myQueue);

	//test dequeue
	for(i=0; i<5; i++){
		dequeue(myQueue);
	}
	//test the size is 0
	assert(myQueue->size == 0);

	//testing big numbers
	for(i=0; i<50; i++){
		enqueue(i, myQueue);
	}
	
	//properly dispose of dynamic memory
	destroyQueue(myQueue);

	return 0;
}