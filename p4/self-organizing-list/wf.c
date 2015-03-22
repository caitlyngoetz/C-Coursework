
/**
 * wf.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

const int MAX_LINE_LENGTH = 2048;
const char * delimiters = " 0123456789\t;{}()[].#<>\n\r+-/%*\"^~&=!|:\\?,";

int main(int argc, char *argv[]) {
	if(argc != 2){
		printf("Usage: %s", argv[0]);
		exit(0);
	}
	char *nextToken;
	char *save;
	char *s;
	char **token;
	int numTokens;

	s = (char *) malloc(sizeof(char) * MAX_LINE_LENGTH);
		
	return 0;
}
