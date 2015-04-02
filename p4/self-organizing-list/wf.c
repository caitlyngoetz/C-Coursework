
/**
 * wf.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "List.h"
#include "Node.h"
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
	if(argc != 3){
		printf("Usage: %s", argv[0]);
		exit(0);
	}
	
	FILE *fin;
	fin = fopen(argv[2], "r");
	if (!fin){
		perror(argv[1]);
		exit(errno);
	}

	//Read line-by line
	int totalCount = 0;
	char buffer[MAX_LINE_LENGTH];
	while(fgets(buffer, sizeof(buffer), fin)){
		//Break line into words
		char * nextWord;
		nextWord = strtok(buffer, delimiters);
		char * lowerWord = toLower(nextWord);
		while(nextWord != NULL){
			totalCount++;
			int i;
			for(i=0; i<list->size; i++){
				if(search(list, lowerWord)){
					//increment probes
					list->obj->frequency += 1;
					totalCount++;
			}
			else{
			struct word * word = createWordObj(lowerWord, totalCount);
			struct node * nodeWord = createNode(word);
			addAtFront(list, nodeWord);
			//increment probes
			nextWord = strtok(buffer, delimiters);
			lowerWord = toLower(nextWord);
			}
		}
	}
	return 0;
}
