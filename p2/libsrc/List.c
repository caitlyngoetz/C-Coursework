#include <stdio.h>
#include <stdlib.h>
#include "List.h"

struct list * createList(int (*equals)(const void *,const void *),
			 char * (*toString)(const void *),
			 void (*freeObject)(void *))
{
	struct list *list;
	list = (struct list *) malloc(sizeof(struct list));
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	list->equals = equals;
	list->toString = toString;
	list->freeObject = freeObject;
	return list;
}

void freeList(struct list *list)
{
	if(list == NULL) return;
	struct node *node = list->head;
	while(node){
		struct node *temp = node->next;
		freeNode(node);
		node = temp;
	}
	free(list);
	list = NULL;
}
//TODO: complete this method
int getSize(const struct list *list)
{
	return 0;
}
//TODO:  complete this method 
int isEmpty(const struct list *list)
{
	return list->size == 0;
}

void addAtFront(struct list *list, struct node *node)
{
	if (list == NULL) return;
	if (node == NULL) return;
	list->size++;
	node->next = list->head;
	node->prev = NULL;
	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->head->prev = node;
		list->head = node;
	}
}
//TODO: complete this method
void addAtRear(struct list *list, struct node *node)
{
	if(list == NULL) return;
	if(node == NULL) return;
	list->size++;
	node->next = NULL;
	node->prev = list->tail;
	if(list->head == NULL){
		list->head = node;
		list->tail = node;
	}else{
		list->tail->next = node;
		list->tail = node;
	}
}
//TODO: complete this method
struct node* removeFront(struct list *list)
{
	if(list == NULL) return;
	
	struct node *temp = list-> head;

	if(list->size == 1){
		list->head=list->tail=NULL;
	}else{
		head = list->head->next;
		list
		//TODO
}
//TODO: complete this method
struct node* removeRear(struct list *list)
{
	return NULL;
}
//TODO: complete this method
struct node* removeNode(struct list *list, struct node *node)
{
	return NULL;
}

struct node* search(const struct list *list, const void *obj)
{
	if(list == NULL) return NULL;
	struct node *node = list->head;
	while(node != NULL){
		if(equals(node->object, object)){
			return node;
		}	
		node = node->next;
	}
	return NULL;
}
//TODO: complete this method
void reverseList(struct list *list)
{
}

void printList(const struct list *list)
{
	if (!list) return; //list was null!!
	int count = 0;
	char *output;
	struct node *temp = list->head;
	while (temp) {
		output = list->toString(temp->obj);
		printf(" %s -->",output);
		free(output);
		temp = temp->next;
		count++;
		if ((count % 6) == 0)
			printf("\n");
	}
	printf(" NULL \n");
}
