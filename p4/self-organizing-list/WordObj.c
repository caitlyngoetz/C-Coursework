#include "WordObj.h"
#include <string.h>

//creates and returns a pointer to a new word object with the given string and
//frequency.
WordObjPtr createWordObj(char *word, const unsigned long int frequency)
{
	WordObjPtr newWordObj = (WordObjPtr) malloc (sizeof(WordObj));
	newWordObj->word = (char *) malloc(sizeof(char)*(strlen(word)+1));
	strcpy(newWordObj->word, word);
	newWordObj->frequency = frequency;
	return newWordObj;
}

//Prints a word object as a string in the following format: word frequency
char * toString(const void * obj)
{
	WordObjPtr myword = (WordObjPtr) obj;
        char *temp = (char *)malloc(sizeof(char)*MAX_WORD_LENGTH +2+sizeof(int));
        sprintf(temp, "%s %lu", myword->word, myword->frequency);
	return temp;	
}

//Frees the word and then the word object itself
void freeWordObj(void * obj)
{
	WordObjPtr myword = (WordObjPtr) obj;
	if(myword == NULL) return;
	free(myword->word);
	free(myword);
}

//Compares two word objects by comparing the words stored in the objects and
//returns a 1 (TRUE) if the first word is equal to the second and a 0 (FALSE). 
int equals(const void * obj1, const void * obj2)
{
	WordObjPtr o1 = (WordObjPtr) obj1;
	WordObjPtr o2 = (WordObjPtr) obj2;
	return strcmp(o1->word, o2->word);
}
