

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

double difficultyRating(void)
{
	return 3;
}

double hoursSpent(void)
{
	return 20;
}

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	
	// check if num_fragments and fragment_length are valid
	if (num_fragments <= 0 || fragment_length <= 0)
		return NULL;
	
	// allocate and initialize the LPA
	LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));
	party->num_fragments = num_fragments;
	party->fragment_length = fragment_length;
	party->num_active_fragments = 0;
	party->size = 0;
	
	// initialize the LPA
	party->fragments = malloc(sizeof(int *) * num_fragments);
	for (i = 0; i < num_fragments; i++)
		party->fragments[i] = NULL;
	
	// initialize the LPA
	party->fragment_sizes = malloc(sizeof(int) * num_fragments);
	for (i = 0; i < num_fragments; i++)
		party->fragment_sizes[i] = 0; 
	
	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", \
		num_fragments * fragment_length, num_fragments);
	
	// check if any malloc() failed
	if (party->fragments == NULL || party->fragment_sizes == NULL)
	{
		destroyLonelyPartyArray(party);
		return NULL;
	}
	
	return party;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i;
	
	// check if party is NULL
	if (party == NULL)
		return NULL;
	
	// free the dynamically allocated memory in the LPA
	for (i = 0; i < party->num_fragments; i++)
		free(party->fragments[i]);
	free(party->fragments);
	free(party->fragment_sizes);
	free(party);

	printf("-> The LonelyPartyArray has returned to the void.\n");
	return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
	int i;
	
	// check if party is NULL
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}
		
	// check if the index is valid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", \
			index, index / (party->fragment_length), index % (party->fragment_length));
		return LPA_FAILURE;
	}
	
	// check if the index fragment exists
	if (party->fragments[index / party->fragment_length] == NULL)
	{
		party->fragments[index / party->fragment_length] = malloc(sizeof(int) * party->fragment_length);
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", index / party->fragment_length, \
			party->fragment_length, index / party->fragment_length * party->fragment_length, \
			index / party->fragment_length * party->fragment_length + party->fragment_length - 1);
		for (i = 0; i < party->fragment_length; i++)
			party->fragments[index / party->fragment_length][i] = UNUSED;
		
		party->fragments[index / party->fragment_length][index % party->fragment_length] = key;
		party->fragment_sizes[index / party->fragment_length]++;
		party->num_active_fragments++;
		party->size++;
	}
	
	//check if there is a value at the index
	if (party->fragments[index / party->fragment_length][index % party->fragment_length] == UNUSED)
	{
		party->fragments[index / party->fragment_length][index % party->fragment_length] = key;
		party->fragment_sizes[index / party->fragment_length]++;
		party->size++;
	}
	else
	{
		party->fragments[index / party->fragment_length][index % party->fragment_length] = key;
	}
	
	return LPA_SUCCESS;
}

int get(LonelyPartyArray *party, int index)
{
	// check if party is NULL
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}
	
	// check if the index is valid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", \
			index, index / (party->fragment_length), index % (party->fragment_length));
		return LPA_FAILURE;
	}
	
	// check if the index fragment exists
	if (party->fragments[index / party->fragment_length] == NULL)
		return UNUSED;
	
	return party->fragments[index / party->fragment_length][index % party->fragment_length];
}

int delete(LonelyPartyArray *party, int index)
{
	// check if party is NULL
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}
		
	// check if the index is valid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", \
			index, index / (party->fragment_length), index % (party->fragment_length));
		return LPA_FAILURE;
	}
	
	// check if the index fragment exists
	if (party->fragments[index / party->fragment_length] == NULL)
		return LPA_FAILURE;
	
	//check if there is a value at the index
	if (party->fragments[index / party->fragment_length][index % party->fragment_length] == UNUSED)
		return LPA_FAILURE;
	
	party->fragments[index / party->fragment_length][index % party->fragment_length] = UNUSED;
	party->fragment_sizes[index / party->fragment_length]--;
	party->size--;
	
	// deallocate the fragment is the index deleted was the last in it
	if (party->fragment_sizes[index / party->fragment_length] == 0)
	{
		free(party->fragments[index / party->fragment_length]);
		party->fragments[index / party->fragment_length] = NULL;
		printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", index / party->fragment_length, \
			party->fragment_length, index / party->fragment_length * party->fragment_length, \
			index / party->fragment_length * party->fragment_length + party->fragment_length - 1);
		party->num_active_fragments--;
	}
	
	return LPA_SUCCESS;
}

int containsKey(LonelyPartyArray *party, int key)
{
	int i, j;
	
	// cycle through the LPA looking for the key
	for (i = 0; i < party->num_fragments; i++)
	{
		if (party->fragments[i] == NULL)
			continue;
		
		for (j = 0; j < party->fragment_length; j++)
		{
			if (party->fragments[i][j] == key)
				return 1;
		}
	}
	
	return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
	// check if party is NULL
	if (party == NULL)
		return 0;
	
	// check if the index is valid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
		return 0;
	
	// check if the index fragment exists
	if (party->fragments[index / party->fragment_length] == NULL)
		return 0;
	
	//check if there is a value at the index
	if (party->fragments[index / party->fragment_length][index % party->fragment_length] == UNUSED)
		return 0;
	
	return 1;
}

int printIfValid(LonelyPartyArray *party, int index)
{
	// check if party is NULL
	if (party == NULL)
		return LPA_FAILURE;
	
	// check if the index is valid
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
		return LPA_FAILURE;
	
	// check if the index fragment exists
	if (party->fragments[index / party->fragment_length] == NULL)
		return LPA_FAILURE;
	
	//check if there is a value at the index
	if (party->fragments[index / party->fragment_length][index % party->fragment_length] == UNUSED)
		return LPA_FAILURE;
	else
	{
		printf("%d\n", party->fragments[index / party->fragment_length][index % party->fragment_length]);
		return LPA_SUCCESS;
	}
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i, j;
	
	// check if party is NULL
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().\n");
		return party;
	}
	
	// cycle through and initialize back to right after creation
	for (i = 0; i < party->num_fragments; i++)
	{
		party->fragment_sizes[i] = 0;
		if (party->fragments[i] != NULL)
		{
			for (j = 0; j < party->fragment_length; j++)
				party->fragments[i][j] = UNUSED;
			free(party->fragments[i]);
			party->fragments[i] = NULL;
		}
		
	}
	
	party->num_active_fragments = 0;
	party->size = 0;
	
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", \
		party->num_fragments * party->fragment_length, party->num_fragments);
	
	return party;
}

int getSize(LonelyPartyArray *party)
{
	// check if party is NULL
	if (party == NULL)
		return -1;
	
	return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
	// check if party is NULL
	if (party == NULL)
		return -1;
	
	return party->num_fragments * party->fragment_length;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	// check if party is NULL
	if (party == NULL)
		return -1;
	
	return party->num_active_fragments * party->fragment_length;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	// check if party is NULL
	if (party == NULL)
		return 0;
	
	return (long long unsigned int)(party->num_fragments * party->fragment_length) * sizeof(int);
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	long long unsigned int result = (sizeof(LPA*) + sizeof(LPA) + \
		((long long unsigned int)sizeof(party->fragments[0]) * party->num_fragments) + \
		((long long unsigned int)sizeof(party->fragment_sizes[0]) * party->num_fragments) + \
		((long long unsigned int)party->num_active_fragments * party->fragment_length * \
			sizeof(party->fragments[0][0])));
		
	// check if party is NULL
	if (party == NULL)
		return 0;
	
	return result;
}
