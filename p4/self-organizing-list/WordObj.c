#include "WordObj.h"

//creates and returns a pointer to a new word object with the given string and
//frequency.
WordObjPtr createWordObj(const char *word, const unsigned long int frequency)
{
	WordObjPtr newWordObj = (WordObjPtr) malloc (sizeof(WordObj));
	newWordObj->word = (char *) malloc(sizeof(char)*(strlen(word)+1));
	newWordObj->frequency = frequency;
	return newWordObj;
}

//Prints a word object as a string in the following format: word frequency
char * toString(const void * obj)
{
	WordObjPtr myword = (WordObjPtr) obj;
        char *temp;
        int max_data = strlen(myword->word)+1;
       	max_data += MAX_WORD_LENGTH;
	max_data += MAX_FREQ_DIGITS;
        temp = (char *)malloc(sizeof(char)*max_data);
        snprintf(temp, max_data, "[%ld] %s", myword->frequency, myword->word);
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
	return o1->word == o2->word;
}
