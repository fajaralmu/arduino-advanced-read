// 
// 
// 

#include "InputParses.h"

boolean match(int value, int* comparators, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (value == comparators[i])
			return 1;
	}
	return 0;
}

char* concatenate(char* str1, char* str2)
{
	unsigned int c = strlen(str1) + strlen(str2) + 1;
	char* result = (char*)malloc(c);
	strcpy(result, str1);
	strcat(result, str2);
	free(result);
	return result;
}

