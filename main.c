#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned char array[100000] = {0};
unsigned char *ptr = array;
unsigned int jump_array[2][1000] = {-1};
int jump_number = 0;

void compile_jumps(char data[])
{
	int i = 0;
	int forward_counter = 0;
	int backward_counter = 0;
	while(i < sizeof(data))
	{
		switch(data[i])
		{
			case '[':
				jump_array[0][forward_counter] = i;
				forward_counter++;
				break;
			case ']':
				jump_array[1][backward_counter] = i;
				backward_counter++;
				break;
		}
		i++;
	}
}

void compile(char data[])
{
	// Validate that there is data.
	if(sizeof(data) <= 0)
	{
		return;
	}
	
	loop_through(data, 0, 100000);
}

void loop_through(char data[], int pos, int end_point)
{
	int i = pos;
	
	for(i; i <= end_point; i++)
	{
		//debug_print_values();
		check_character(data, i);
	}
}

void check_character(char data[], int i)
{
	int pos;
	if(i == jump_array[0][jump_number])
	{
		jump_number++;
		int* location;
		*location = &ptr;
					
		while(*location != 0)
		{
			loop_through(data, i + 1, jump_array[1][jump_number - 1]);
		}
	}
	else
	{
		switch(data[i])
		{
			case '>':
				ptr++;
				break;
			case '<':
				ptr--;
				break;
			case '+':
				*ptr++;
				break;
			case '-':
				*ptr--;
				break;
			case '.':
				putchar(*ptr);
				break;
			case ',':
				*ptr = getchar();
				break;
		}
	}
}

int main(int argc, char **argv)
{
	// Should print "Hello world!"
	compile("+[-[>>[+[---<]-[>>>]]]<<<-]<-.---.>..<.>>>>-.>+.<<<<<.<.>>.>-.");
	return 0;
}
