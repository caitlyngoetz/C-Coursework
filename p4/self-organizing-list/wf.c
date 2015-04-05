
/**
 * wf.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <List.h>
#include <Node.h>
#include "WordObj.h"

const int MAX_LINE_LENGTH = 2048;
const char * delimiters = " 0123456789\t;{}()[].#<>\n\r+-/%*\"^~&=!|:\\?,";


char * toLowercase(char * c){ 
	int i = 0;
	while(c[i]){
		c[i] = tolower(c[i]);
		i++;
	}
	return c;
}

int main(int argc, char *argv[]) {
struct list *list = createList(equals, toString, freeWordObj);
	if(argc != 3){
		printf("Usage: %s {--self-organized-list|--std-list} <textfile>\n", argv[0]);
		exit(0);
	}
		
	FILE *fin;
	fin = fopen(argv[2], "r");
	if (!fin){
		perror(argv[1]);
		exit(errno);
	}

	//Read line-by line
	char buffer[MAX_LINE_LENGTH];
	while(fgets(buffer, sizeof(buffer), fin)){
		//Break line into words
		char *lowerWord;
		lowerWord = strtok(buffer, delimiters);
		if(strcmp(argv[1], "--std-list") == 0){
			while(lowerWord){
			lowerWord =(char *) (toLowercase(lowerWord));
			WordObjPtr lowerPtr = createWordObj(lowerWord, 1);	
				if(search(list, lowerPtr) != NULL){
					//increment frequency
					struct node*temp = search(list, lowerPtr);
					WordObjPtr wordTemp = temp->obj;
					wordTemp->frequency++;
				}else{
					struct node *nodeWord = createNode(lowerPtr);
					addAtFront(list, nodeWord);
				}
				lowerWord = strtok(NULL, delimiters);
				//free word obj
			}
			

		}else if(strcmp(argv[1], "--self-organized-list") == 0){
			while(lowerWord){
			lowerWord =(char *) (toLowercase(lowerWord));
			WordObjPtr lowerPtr = createWordObj(lowerWord, 1);	
				if(search(list, lowerPtr) != NULL){
					//increment frequency
					struct node*temp = search(list, lowerPtr);
					WordObjPtr wordTemp = temp->obj;
					wordTemp->frequency++;
					removeNode(list, temp);
					addAtFront(list, temp);
				}else{
					struct node *nodeWord = createNode(lowerPtr);
					addAtFront(list, nodeWord);
				}
				lowerWord = strtok(NULL, delimiters);
			}

		}else{
			printf("Usage: %s {--self-organized-list|--std-list} <testfile>\n", argv[0]);
			exit(0);
		}

	}
	fclose(fin);
	struct node *current = list->head;
	while(current){
		char *temp = list->toString(current->obj);
		printf("%s\n", temp);
		free(temp);
		current = current->next;
	}
//free list
	
	return 0;
}
