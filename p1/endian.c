/* C-examples/intro/helloworld.c */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

void printBits(unsigned int x);
unsigned int swapBytes(unsigned int);
unsigned int btoi(char[]);

int main(int argc, char *argv[])
{
    if (argc != 3) {
	printf
	    ("Usage: endian -i|-b <x>\n-i x: positive integer less than 4294967295");
	printf
	    ("\n-b x: binary representation of positive integer less than 4294967295");
	printf("\n\t(string of 1s and 0s)\n");
	return 0;
    }
    //Parse int argurment
    unsigned int temp = (unsigned int) atoi(argv[2]);
    if ((temp > UINT_MAX) || (temp < 0)
	|| ((temp == 0) && (strcmp(argv[2], "0") != 0))) {
	printf
	    ("Usage: endian -i|-b <x>\n-i x: positive integer less than 4294967295");
	printf
	    ("\n-b x: binary representation of positive integer less than 4294967295");
	printf("\n\t(string of 1s and 0s)\n");
	return 0;
    }

    if (argv[1][1] == 'i') {
	unsigned int decimal = temp;
	printf("%-30s %-40s %-30s\n", "Decimal", "Binary", "Hexidecimal");
	printf
	    ("------------------------------------------------------------------------------------\n");
	printf("x   %-27u", decimal);
	printBits(decimal);
	printf("%-9s", "");
	printf("0x%08x", decimal);
	printf("\n");

	unsigned int newdecimal = swapBytes(decimal);
	printf("x'  %-27u", newdecimal);
	printBits(newdecimal);
	printf("%-9s", "");
	printf("0x%08x", newdecimal);
	printf("\n");
    } else if (strcmp(argv[1], "-b") == 0) {
	int i;
	for (i = 0; i < strlen(argv[2]); i++) {

	    unsigned int number = (unsigned int) argv[2][i] - 48;

	    if ((number != 0) && (number != 1)) {
		printf
		    ("Usage: endian -i|-b <x>\n-i x: positive integer less than 4294967295");
		printf
		    ("\n-b x: binary representation of positive integer less than 4294967295");
		printf("\n\t(string of 1s and 0s)\n");
		return 0;
	    }
	}

	unsigned int bdecimal = (unsigned int) btoi(argv[2]);
	printf("%-30s %-40s %-30s\n", "Decimal", "Binary", "Hexidecimal");
	printf
	    ("------------------------------------------------------------------------------------\n");
	printf("x  %-27u", bdecimal);
	printBits(bdecimal);
	printf("%-9s", "");
	printf("0x%08x", bdecimal);
	printf("\n");

	unsigned int newbdecimal = swapBytes(bdecimal);
	printf("x' %-27u", newbdecimal);
	printBits(newbdecimal);
	printf("%-9s", "");
	printf("0x%08x", newbdecimal);
	printf("\n");

    }
    return 0;
}

void printBits(unsigned int x)
{
    int i;
    for (i = sizeof(unsigned int) * CHAR_BIT - 1; i >= 0; i--) {
	if ((1U << i) & x) {
	    printf("1");
	} else {
	    printf("0");
	}
    }
}

unsigned int getByte(unsigned int y, const int set)
{
    unsigned int mask = (~(~0 << CHAR_BIT));
    y >>= set * CHAR_BIT;

    return y & mask;
}

unsigned int swapBytes(unsigned int x)
{
    unsigned int result = 0;
    unsigned int i;
    unsigned int value;
    unsigned int mask = 0X00FF;
    for (i = 0; i < sizeof(unsigned int); i++) {
	result = result << 8;
	value = x & mask;
	result = result | (value >> (i * 8));
	mask = mask << 8;
    }
    return result;
}

unsigned int btoi(char b[])
{
    int i;
    unsigned int result = 0;
    for (i = 0; b[i + 1] != '\0'; i++) {
	if (b[i] == '1')
	    result |= 1;
	result = result << 1;
    }
    if (b[i] == '1')
	result |= 1;
    return result;
}
