
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

struct list *list;

char * toLower(char * c){ 
	int i;
	for(i = 0; i < strlen(c)-1; i++){
		if(c[i]>=65 && c[i]<=90)
			c[i]=c[i]+32;
	}
	return c;
}

int main(int argc, char *argv[]) {
	printf("\ninto main\n");
	if(argc != 3){
		printf("Usage: %s {--self-organized-list|--std-list} <textfile>\n", argv[0]);
		exit(0);
	}
	printf("after first if\n");
	
	FILE *fin;
	fin = fopen(argv[2], "r");
	if (!fin){
		perror(argv[1]);
		exit(errno);
	}

	printf("read in file\n");	

	//Read line-by line
	char buffer[MAX_LINE_LENGTH];
	while(fgets(buffer, sizeof(buffer), fin)){
		//Break line into words
		printf("into first while loop\n");
		char * nextWord;
		nextWord = strtok(buffer, delimiters);
		int frequency = 0;
		if(strcmp(argv[1], "--std-list") == 0){
			printf("into std list\n");
			while(nextWord != NULL){
				printf("into while loop\n");
				char * lowerWord = toLower(nextWord);
				if(search(list, lowerWord) != NULL){
					printf("found\n");
					//increment frequency
					struct node* temp = search(list, lowerWord);
					WordObjPtr theWord = (WordObjPtr) temp->obj;
					frequency = theWord->frequency++;
					WordObjPtr word = createWordObj(lowerWord, frequency);
					struct node * nodeWord = createNode(word);
					addAtFront(list, nodeWord);	
				}else{
					printf("new\n");
					frequency = 1;
					WordObjPtr word = createWordObj(lowerWord, frequency);
					struct node * nodeWord = createNode(word);
					addAtFront(list, nodeWord);
				}
				
				frequency = 0;
			}
		}
		if(strcmp(argv[1], "--self-organized-list") == 0){
			while(nextWord != '\0'){
				char * lowerWord = toLower(nextWord);
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
			nextWord = strtok(buffer, delimiters);
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
