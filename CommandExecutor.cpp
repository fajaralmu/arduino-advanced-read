// 
// 
// 

#include "CommandExecutor.h"

char* printCharacters(int inputs[], int size)
{
	char* string = "";
	for (int i = 0; i < size; i++)
	{
		char input = (char) inputs[i];
		char ch[] = { input };
		string = concatenate(string, ch);
	}
	return string;
}

char* executeCommand(CmdMode mode, int arguments[], int size)
{

	switch (mode)
	{
	case NONE:
		return "No result";
	case PRINT_CHAR:
		return "Print char";
	case PRINT_NUMBER:
		return "Print number";
	default:
		break;
	}
}

int concat(int a, int b)
{

	char s1[20];
	char s2[20];

	// Convert both the integers to string
	sprintf(s1, "%d", a);
	sprintf(s2, "%d", b);

	// Concatenate both strings
	strcat(s1, s2);

	// Convert the concatenated string
	// to integer
	int c = atoi(s1);

	// return the formed integer
	return c;
}

char* printNumbers(int inputs[], int size)
{
	char* string = "";
	for (int i = 0; i < size; i++)
	{
		char input = inputs[i] + '0';
		char ch[] = { input };
		string = concatenate(string, ch);
	}
	return string;
}

