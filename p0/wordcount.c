#include <stdio.h>

#define IN 1
#define OUT 0

int main(int argc, char *argv[])
{
	long charactercount;
	int c, linecount, wordcount, numbercount,  state;
	int zero, one, two, three, four, five, six, seven, eight, nine;
	zero = one = two = three = four = five = six = seven = eight = nine = 0;

	state = OUT;
	linecount = wordcount = charactercount = numbercount = 0;
	while((c = getchar()) != EOF) {
		charactercount++;
		if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4'){  //counts numbers 0-4 
			numbercount++;}
		if(c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){  //counts numbers 5-9
			numbercount++;}
		if(c == '\n'){  //counts new lines
			linecount++;}
		if (c == ' ' || c == '\n' || c == '\t') {//checks for end of lines
			state = OUT;}
		else if (state == OUT) {  //counts number of lines
			state = IN;
			wordcount++;
		}
		if(c == '0'){  //counts number of zeros
			zero++;}
		if(c == '1') { //counts number of ones
			one++;}
		if(c == '2')  {//counts numbers of twos
			two++;}
		if(c == '3')  {//counts number of threes
			three++;}
		if(c == '4')  {//counts number of fours
			four++;}
		if(c == '5')  {//counts number of fives
			five++;}
		if(c == '6')  {//counts number of sixes
			six++;}
		if(c == '7') { //counts number of sevens
			seven++;}
		if(c == '8')  {//counts number of eights
			eight++;}
		if(c == '9')  {//counts number of nines
			nine++;}
	}
	//Prints out results
	printf("Number of characters:  %ld\n", charactercount);
	printf("Number of words: %d\n", wordcount);
	printf("Number of lines: %d\n", linecount);
	printf("Total amount of digits: %d\n", numbercount);
	printf("Number of zeros: %d\n", zero);
	printf("Number of ones: %d\n", one);
	printf("Number of twos: %d\n", two);
	printf("Number of threes: %d\n", three);
	printf("Number of fours: %d\n", four);
	printf("Number of fives: %d\n", five);
	printf("Number of sixes: %d\n", six);
	printf("Number of sevens: %d\n", seven);
	printf("Number of eights: %d\n", eight);
	printf("Number of nines: %d\n", nine);
        return 0;
}

