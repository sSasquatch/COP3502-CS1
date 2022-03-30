/*

an089926
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Glowworm.h"

double difficultyRating(void)
{
	return 3.0;
}

double hoursSpent(void)
{
	return 12.0;
}

void printGlowworm(int tail, int head, int maxLength, int death)
{
	int i;

	//Print out if Glowworm had not died.
	if(death == 0)
	{
		//Print Glowworm with no wrapping.
		if(head>=tail)
		{
			for(i=0; i<tail; i++)
				printf(" ");
			
			printf("~");
			
			for(i=tail; i<(head-2); i++)
				printf("o");
				
			printf("OG");
		}
		//Print Glowworm with wrapping.
		else if(head<tail)
		{
			for(i=0; i<(head-1); i++)
				printf("o");
			
			if(head==0)
				printf("G");
			else
				printf("OG");
			
			for(i=head; i<(tail-1); i++)
					printf(" ");
			
			printf("~");
			
			if(head==0)
			{
				for(i=(tail+1); i<(maxLength-1); i++)
					printf("o");
			}
			else
			{
				for(i=(tail+1); i<maxLength; i++)
					printf("o");
			}
			
			if(head==0)
				printf("O");
		}
	}
	//Print out if Glowworm died.
	else if(death == 1)
	{
		//Print Glowworm with no wrapping.
		if(head>=tail)
		{
			for(i=0; i<tail; i++)
				printf(" ");
			
			printf("~");
			
			for(i=tail; i<(head-2); i++)
				printf("o");
				
			printf("Xx");
		}
		//Print Glowworm with wrapping.
		else if(head<tail)
		{
			for(i=0; i<(head-1); i++)
				printf("o");
			
			if(head==0)
				printf("x");
			else
				printf("Xx");
			
			for(i=head; i<(tail-1); i++)
					printf(" ");
			
			printf("~");
			
			if(head==0)
			{
				for(i=(tail+1); i<(maxLength-1); i++)
					printf("o");
			}
			else
			{
				for(i=(tail+1); i<maxLength; i++)
					printf("o");
			}
			
			if(head==0)
				printf("X");
		}
	}
	
	//Print the ledge.
	printf("\n");
	for(i=0; i<maxLength; i++)
	{
		printf("=");
		if(i == (maxLength-1))
			printf("\n\n");
	}
	return;
}

// You'll need to set this up to accept command line parameters.
int main(int argc, char **argv)
{
	int i, max_glowworm_length;
	int tail = 0, head = 2, worm_length = 3, death = 0;
	
	max_glowworm_length = atoi(argv[1]);
	
	//Print out the input string.
	printf("%s\n\n", argv[2]);
	
	//Print out the starting Glowworm.
	printf("Glowworm appears! Hooray!\n");
	printf("~OG\n");
	for(i=0; i<max_glowworm_length; i++)
	{
		printf("=");
		if(i == (max_glowworm_length-1))
			printf("\n\n");
	}
	
	for(i=0; i<strlen(argv[2]); i++)
	{
		//Check if Glowworm grows.
		if(argv[2][i]=='o' || argv[2][i]=='O' || argv[2][i]=='@')
		{
			if(worm_length < max_glowworm_length)
			{
				printf("Glowworm grows:\n");
				worm_length=worm_length+1;
				head=head+1;
        
				if((tail+head)>max_glowworm_length)
					head = head-max_glowworm_length;
       
				if(head<0)
					head = head+max_glowworm_length;
			}
			else
				printf("Glowworm chills:\n");
			
			printGlowworm(tail, head, max_glowworm_length, death);
		}
		//Check if Glowworm shrinks.
		else if(argv[2][i]=='s' || argv[2][i]=='S')
		{
			if(worm_length > 3)
			{
				printf("Glowworm shrinks:\n");
				worm_length=worm_length-1;
				head=head-1;
				
				if(head<0)
					head = head+max_glowworm_length;
			}
			else
				printf("Glowworm chills:\n");
			
			printGlowworm(tail, head, max_glowworm_length, death);
		}
		//Check if Glowworm moves forward.
		else if(argv[2][i]=='-' || argv[2][i]=='=')
		{
			printf("Glowworm inches forward:\n");
			tail=tail+1;
			head=head+1;

			if(tail>=max_glowworm_length)
				tail = tail-max_glowworm_length;
			
			if((tail+head)>max_glowworm_length)
				head = head-max_glowworm_length;
       
			if(head<0)
				head = head+max_glowworm_length;
               
			if(tail<0)
				tail=tail+max_glowworm_length;  
			
			printGlowworm(tail, head, max_glowworm_length, death);
		}
		//Check if Glowworm dies.
		else if(argv[2][i]=='x' || argv[2][i]=='X' || argv[2][i]=='%')
		{
			printf("Glowworm meets its demise. SAD.\n");
			death = 1;
			
			printGlowworm(tail, head, max_glowworm_length, death);
			break;
		}
		//All other inputs.
		else 
		{
			printf("Glowworm chills:\n");
			
			printGlowworm(tail, head, max_glowworm_length, death);
		}
	}
	
	return 0;
}
