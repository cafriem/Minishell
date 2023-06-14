#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void match(char *expected);
void pipeline();
void simple_command();
void io_list();
void cmd_suffix();
void io_redirect();

// Input string
char input[] = "ls -l | grep foo";

// Current position in the input string
int pos = 0;

// Utility function to match expected tokens
void match(char *expected)
{
	if (strncmp(&input[pos], expected, strlen(expected)) == 0)
		pos += strlen(expected);
	else
	{
		fprintf(stderr, "Error: Expected '%s' at position %d\n", expected, pos);
		exit(1);
	}
}

// Recursive descent parsing functions
void pipeline()
{
	simple_command();
	if (strncmp(&input[pos], "|", 1) == 0)
	{
		match("|");
		pipeline();
	}
}

void simple_command()
{
	io_list();
	if (strncmp(&input[pos], "<word>", 6) == 0)
	{
		match("<word>");
		cmd_suffix();
	}
}

void io_list()
{
	if (strncmp(&input[pos], "<io_redirect>", 13) == 0)
	{
		io_redirect();
		io_list();
	}
}

void cmd_suffix()
{
	if (strncmp(&input[pos], "<io_list>", 9) == 0)
	{
		io_list();
		cmd_suffix();
	}
	else if (strncmp(&input[pos], "<word>", 6) == 0)
	{
		match("<word>");
		cmd_suffix();
	}
}

void io_redirect() {
	if (strncmp(&input[pos], "<", 1) == 0)
	{
		match("<");
		match("<word>");
	}
	else if (strncmp(&input[pos], ">", 1) == 0)
	{
		match(">");
		match("<word>");
	}
	else if (strncmp(&input[pos], ">>", 2) == 0)
	{
		match(">>");
		match("<word>");
	}
	else if (strncmp(&input[pos], "<<", 2) == 0)
	{
		match("<<");
		match("<word>");
	}
}

int main()
{
	pipeline();

	if (pos == strlen(input))
		printf("Parsing successful.\n");
	else
		fprintf(stderr, "Error: Unexpected token at position %d\n", pos);
	return (0);
}

