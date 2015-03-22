
/**
 * wf.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

const int MAX_LINE_LENGTH = 2048;
const char * delimiters = " 0123456789\t;{}()[].#<>\n\r+-/%*\"^~&=!|:\\?,";

int main(int argc, char *argv[]) {
	if(argc != 2){
		printf("Usage: %s", argv[0]);
		exit(0);
	}
	
	FILE *fin;
	fin = fopen(argv[1], "r");
	if (!fin){
		perror(argv[1]);
		exit(errno);
	}

	//Read line-by line
	int totalCount = 0;
	char buffer[MAX_LINE_LENGTH];
	while(fgets(buffer, sizeof(buffer), fin)){
		//Break line into words
		char *nextWord;
		struct WordObj *word;
		nextWord = strtok(buffer, delimiters);
		while(nextWord != NULL){
			totalCount++;
			word = createWordObj(nextWord, totalCount);	
			nextWord = strtok(NULL, delimiters);
		}
	}
	return 0;
}
