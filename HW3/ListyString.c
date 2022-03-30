

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ListyString.h"

double difficultyRating(void)
{
	return 3;
}

double hoursSpent(void)
{
	return 11;
}

// taken inspiration from notes to create a node
ListyNode *create_node(char data)
{
	ListyNode *node = malloc(sizeof(ListyNode));
	
	node->data = data;
	node->next = NULL;
	
	return node;
}

// taken inspiration from notes to insert a node at the tail
ListyNode *insert_node(ListyNode *head, char data)
{
	ListyNode *temp;
	
	if (head == NULL)
		return create_node(data);
	
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	
	temp->next = create_node(data);
		
	return head;
}

ListyString *createListyString(char *str)
{
	int i;
	ListyString *listy = calloc(1, sizeof(ListyString));
	
	// check if the string is null or empty
	if (str == NULL || strlen(str) == 0)
		return listy;
	
	for (i = 0; i < strlen(str); i++)
	{
		listy->head = insert_node(listy->head, str[i]);
		
		// keeps track of length of list
		listy->length++;
	}
	
	return listy;
}

// taken inspiration from notes to destroy a list
ListyString *destroyListyString(ListyString *listy)
{
	ListyNode *temp, *current;
	
	// check if listy or listy->head is null
	if (listy == NULL || listy->head == NULL)
		return NULL;
	
	current = listy->head;
	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
	
	free(listy);
	return NULL;
}

ListyString *cloneListyString(ListyString *listy)
{
	int i;
	char *str;
	ListyNode *temp;
	ListyString *newListy;
	
	// check if listy is null
	if (listy == NULL)
		return NULL;
	
	// navigates list and turns it into a string
	str = malloc(sizeof(char) * listy->length);
	for (temp = listy->head; temp != NULL; temp = temp->next)
		str[i++] = temp->data;
	
	newListy = createListyString(str);
	temp = listy->head;
	
	return newListy;
}

void replaceChar(ListyString *listy, char key, char *str)
{
	int i;
	ListyNode *temp, *temp2, *previous, *storage;
	
	// checks if listy or listy->head is null
	if (listy == NULL || listy->head == NULL)
		return;
	
	// removes the key from the list
	if (str == NULL || strlen(str) == 0)
	{
		for (temp = listy->head; temp != NULL; temp = temp->next)
		{
			storage = malloc(sizeof(ListyNode));
			
			// removes the head if it has the key
			if (temp->data == key && temp == listy->head)
			{
				storage = listy->head;
				listy->head = temp->next;
				
				// keeps track of length of list
				listy->length--;
			}
			// removes the node if it is in the middle of two other nodes
			else if (temp->data == key && temp->next != NULL && previous != NULL)
			{
				storage = temp;
				previous->next = temp->next;
				temp = previous;
				
				// keeps track of length of list
				listy->length--;
			}
			// removes if te tail has the key
			else if (temp->data == key && temp->next == NULL)
			{
				storage = temp;
				temp = previous;
				previous->next = NULL;
				
				// keeps track of length of list
				listy->length--;
			}
			
			// keeps record of the previous node
			previous = temp;
			free(storage);
		}
		
		return;
	}
	
	// replaces key with the string
	for (temp = listy->head; temp != NULL; temp = temp->next)
	{
		if (temp->data == key)
		{
			temp->data = str[0];
			
			// add the rest of the string to the list
			for (i = 1; i < strlen(str); i++)
			{
				temp2 = temp->next;
				temp->next = create_node(str[i]);
				temp->next->next = temp2;
				temp = temp->next;
				
				// keeps track of length of list
				listy->length++;
			}
		}
	}
	
	return;
}

void reverseListyString(ListyString *listy)
{
	int i = 0;
	char *str;
	ListyNode *temp;
	
	// checks if listy or listy->head is null
	if (listy == NULL || listy->head == NULL)
		return;
	
	// navigates list and turns it into a string
	str = malloc(sizeof(char) * listy->length);
	for (temp = listy->head; temp != NULL; temp = temp->next)
		str[i++] = temp->data;
	
	temp = listy->head;
	
	for (i = listy->length - 1; i >= 0; i--)
	{
		temp->data = str[i];
		temp = temp->next;
	}
	
	free(str);
	return;
}

ListyString *listyCat(ListyString *listy, char *str)
{
	int i;
	
	// check if listy and the string are null
	if (listy == NULL && str == NULL)
		return NULL;
	
	// check if listy is null but the string exists
	// if so create the listy and put the string in it
	if (listy == NULL && str != NULL)
	{
		listy = createListyString(str);
		return listy;
	}
	
	// check if listy exists and the string is null or empty
	if (listy != NULL && (str == NULL || strlen(str) == 0))
		return listy;
	
	for (i = 0; i < strlen(str); i++)
	{
		listy->head = insert_node(listy->head, str[i]);
		
		// keeps track of length of list
		listy->length++;
	}
	
	return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
	int i;
	ListyNode *temp1, *temp2;
	
	// check if both listy are null
	if (listy1 == NULL && listy2 == NULL)
		return 0;
	
	// check if one or the other listy are null
	if (listy1 == NULL || listy2 == NULL)
		return 1;
	
	// check if both listy->heads are null
	if (listy1->head == NULL && listy2->head == NULL)
		return 0;
	
	// check if both listy have the same length
	// if they dont, they can not be equivalent
	if (listy1->length == listy2->length)
	{
		temp1 = listy1->head;
		temp2 = listy2->head;
		
		for (i = 0; i < listy1->length; i++)
		{
			if (temp1->data == temp2->data)
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
				
				continue;
			}
			else if (temp1->data != temp2->data)
			{
				return 1;
			}
		}
		
		return 0;
	}
	
	return 1;
}

int listyLength(ListyString *listy)
{
	// check if listy is null
	if (listy == NULL)
		return -1;
	
	// check if listy->head is null
	if (listy->head == NULL)
		return 0;
	
	return listy->length;
}

void printListyString(ListyString *listy)
{
	ListyNode *temp;
	
	// check if listy or listy->head is null 
	if (listy == NULL || listy->head == NULL)
		printf("(empty string)");
	else
	{
		//print out the list
		for (temp = listy->head; temp != NULL; temp = temp->next)
			printf("%c", temp->data);
	}
	
	printf("\n");
	return;
}

int processInputFile(char *filename)
{
	char key, next_char;
	char *str, *str2;
	FILE *ifp;
	ListyString *listy = NULL;
	
	// check if the file exists
	if (access(filename, F_OK) == -1)
		return 1;
	
	// open file
	ifp = fopen(filename, "r");
	
	// read string and make linked list
	str = malloc(sizeof(char) * 1024);
	fscanf(ifp, "%s", str);
	listy = createListyString(str);
	
	while (!feof(ifp))
	{
		fscanf(ifp, "%c", &next_char);
		
		// replaces the key with a string
		if (next_char == '@')
		{
			// allocate the string that is gonna be put into the list
			str2 = malloc(sizeof(char) * 1024);
			
			// read the key and string following the command
			fscanf(ifp, " %c ", &key);
			fscanf(ifp, "%s", str2);
			
			replaceChar(listy, key, str2);
			
			free(str2);
		}
		// concatenate the string to the end of the list
		else if (next_char == '+')
		{
			str2 = malloc(sizeof(char) * 1024);
			
			// read the string following the command
			fscanf(ifp, " %s", str2);
			
			listy = listyCat(listy, str2);
			
			free(str2);
		}
		//delete all of the key from the list
		else if (next_char == '-')
		{
			// read the key following the command
			fscanf(ifp, " %c ", &key);
			
			replaceChar(listy, key, NULL);
		}
		// reverse the list
		else if (next_char == '~')
		{
			reverseListyString(listy);
		}
		// print the number of characters in the list
		else if (next_char == '?')
		{
			printf("%d\n", listy->length);
		}
		// print the list
		else if (next_char == '!')
		{
			printListyString(listy);
		}
	}		
	
	free(str);
	fclose(ifp);
	return 0;
}

int main(int argc, char **argv)
{
	processInputFile(argv[1]);
	return 0;
}
