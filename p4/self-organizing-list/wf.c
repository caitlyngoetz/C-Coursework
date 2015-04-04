
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
	//printf("\ninto main\n");
	if(argc != 3){
		printf("Usage: %s {--self-organized-list|--std-list} <textfile>\n", argv[0]);
		exit(0);
	}
	//printf("after first if\n");
	
	FILE *fin;
	fin = fopen(argv[2], "r");
	if (!fin){
		perror(argv[1]);
		exit(errno);
	}

	//printf("read in file\n");	

	//Read line-by line
	char buffer[MAX_LINE_LENGTH];
	while(fgets(buffer, sizeof(buffer), fin)){
		//Break line into words
	//	printf("into first while loop\n");
		char * nextWord;
		nextWord = strtok(buffer, delimiters);
		int frequency = 0;
		if(strcmp(argv[1], "--std-list") == 0){
	//		printf("into std list\n");
			while(nextWord != NULL){
	//			printf("into while loop\n");
				char * lowerWord =(char *) (toLowercase(nextWord));
				printf("here:  %s\n", lowerWord);
				if(search(list, lowerWord) != NULL){
					//increment frequency
					struct node* temp = search(list, lowerWord);
					WordObjPtr theWord = (WordObjPtr) temp->obj;
					frequency = theWord->frequency++;
					WordObjPtr word = createWordObj(lowerWord, frequency);
					struct node * nodeWord = createNode(word);
					addAtFront(list, nodeWord);
	//				printf("found\n");
				}else{
	//				printf("%s\n", nextWord);
					frequency = 1;
					WordObjPtr word = createWordObj(lowerWord, frequency);
					struct node * nodeWord = createNode(word);
					addAtFront(list, nodeWord);
	//				printf("new\n");
				}
				nextWord = strtok(NULL, delimiters);
	//			printf("grabbed new word\n");
				frequency = 0;
			}
			//perror("out of loop");
			struct node * current = list->head;
			while(current){
				WordObjPtr myword= (WordObjPtr) current->obj;
				printf("test: %s %lu\n", myword->word, myword->frequency); 
				char * temp = toString(current->obj);
				printf("%s\n", temp);
				free(temp);
				current = current->next;
			}
			free(current);

		}else if(strcmp(argv[1], "--self-organized-list") == 0){
			while(nextWord != NULL){
				char * lowerWord = toLowercase(nextWord);
				if(search(list, lowerWord) != NULL){
					//increment frequency
					struct node * temp = search(list, lowerWord);
					WordObjPtr theWord = (WordObjPtr) temp->obj;
					frequency = theWord->frequency++;
					
					WordObjPtr word = createWordObj(lowerWord, frequency);
                                        struct node * nodeWord = createNode(word);
                                        addAtFront(list, nodeWord);
				}else{
					frequency = 1;
					WordObjPtr word = createWordObj(lowerWord, frequency);
                                        struct node * nodeWord = createNode(word);
                                        addAtFront(list, nodeWord);
				}
			nextWord = strtok(NULL, delimiters);
			frequency = 0;
			}
		}
		else{
			printf("Usage: %s {--self-organized-list|--std-list} <testfile>\n", argv[0]);
			exit(0);
		}

	}

	return 0;
}
