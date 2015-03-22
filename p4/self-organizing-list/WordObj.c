#include "WordObj.h"

//creates and returns a pointer to a new word object with the given string and
//frequency.
WordObjPtr createWordObj(const char *word, const unisgned long int frequency)
{
	struct word* newWordObj = (struct word*) malloc (sizeof(struct word));
	newWordObj->word = word;
	newWordObj->frequency = frequency;
	return newWordObj;
}

//Prints a word object as a string in the following format: word frequency
char * toString(const void * obj)
{
	if(obj == NULL) return;
	char *objstr = (*toString)(obj->word);
	printf("%s", objstr);
	free(objstr);
}

//Frees the word and then the word object itself
void freeWordObj(const void * obj)
{
	if(obj == NULL) return;
	(*freeWordObj)(obj->word);
	free(obj);
}

//Compares two word objects by comparing the words stored in the objects and
//returns a 1 (TRUE) if the first word is equal to the second and a 0 (FALSE). 
int equals(const void * obj1, const void * obj2)
{
	struct word * o1 = (struct word*) obj1;
	struct word * o2 = (struct word*) obj2;
	return o1->word == o2->word;
}
