// Anthony Pionessa
// an089926

#include <stdio.h>
#include "SneakyRooks.h"

double difficultyRating(void)
{
	return 2;
}

double hoursSpent(void)
{
	return 3;
}

int findColumn(char *rookString)
{
	int i = 0, column = 0;
	
	if (strlen(rookString) == 0)
		return 0;
	
	// loop through the string until you hit a non-alpha character
	// while you loop, you calculate the column number
	while (rookString[i] >= 'a' && rookString[i] <= 'z')
	{
		column *= 26;
		column += (rookString[i] - 'a' + 1);
		i++;
	}
	
	return column;
}

int findRow(char *rookString)
{
	int i = 0, row = 0;
	
	if (strlen(rookString) == 0)
		return 0;
	
	// loop through the string until you get to the numbers
	while (rookString[i] >= 'a' && rookString[i] <= 'z')
	{
		i++;
	}
	
	// loop through the rest of the string and calculate the row number
	while (rookString[i] >= '1' && rookString[i] <= '9')
	{
		row *= 10;
		row += (rookString[i] - '0');
		i++;
	}
	
	return row;
}

int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
	int *columnNumbers, *rowNumbers;
	int i, column, row;
	
	// check if there is only one rook
	// if so then it is safe
	if (numRooks == 1)
		return 1;
	
	columnNumbers = calloc(boardSize, sizeof(int));
	rowNumbers = calloc(boardSize, sizeof(int));
	
	for (i = 0; i < numRooks; i++)
	{
		// find the column and row number of the current string
		column = findColumn(rookStrings[i]);
		row = findRow(rookStrings[i]);
		
		// increment that column and row number in the arrays
		columnNumbers[column - 1]++;
		rowNumbers[row ]++;
		
		// if the number at the indexes in the arrays is greater than one
		// that means that index has been used before and the rook is not safe
		if (columnNumbers[column - 1] > 1 || rowNumbers[row] > 1)
		{
			free(columnNumbers);
			free(rowNumbers);
			return 0;
		}
	}
	
	free(columnNumbers);
	free(rowNumbers);
	return 1;
}

void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
	int column, row;
	
	// call the functions to get the column and row numbers
	rookCoordinate->col = findColumn(rookString);
	rookCoordinate->row = findRow(rookString);
	
	return;
}