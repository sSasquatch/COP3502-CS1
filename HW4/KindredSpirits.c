

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

double difficultyRating(void)
{
	return 1;
}

double hoursSpent(void)
{
	return 2;
}

int isReflection(node *a, node *b)
{
	// check if both trees are null
	// if so then is reflection
	if (a == NULL && b == NULL)
		return 1;
	
	// check if a is null
	// if so then is not reflection
	if (a == NULL)
		return 0;
	
	// check is b is null
	// if so then is not reflection
	if (b == NULL)
		return 0;
	
	// check if the data at the root of a and b are equal or not
	// if so then is not reflection
	if (a->data != b->data)
		return 0;
	
	return isReflection(a->right, b->left) && isReflection(a->left, b->right);
}

node *makeReflection(node *root)
{
	node *reflection = calloc(1, sizeof(node));
	
	// check if root is null
	// if so then reflection is null
	if (root == NULL)
	{
		free(reflection);
		return NULL;
	}
	
	// check if root is leaf node
	// if so then reflection is same leaf node
	if (root->right == NULL && root->left == NULL)
	{
		reflection->data = root->data;
		return reflection;
	}
	
	reflection->data = root->data;
	reflection->right = makeReflection(root->left);
	reflection->left = makeReflection(root->right);
	
	return reflection;
}

// taken inspiration from notes to count the amount of nodes in a tree
int count_nodes(node *root)
{
	if (root == NULL)
		return 0;
	
	return 1 + count_nodes(root->right) + count_nodes(root->left);
}

// taken inspiration from notes for preorder traversal
void preorder(node *root, int *array, int *size)
{
	if (root == NULL)
		return;
	
	array[*size] = root->data;
	*size++;
	
	preorder(root->left, array, size);
	preorder(root->right, array, size);
}

// taken inspiration from notes for postorder traversal
void postorder(node *root, int *array, int *size)
{
	if (root == NULL)
		return;
	
	postorder(root->left, array, size);
	postorder(root->right, array, size);
	
	array[*size] = root->data;
	*size++;
}

int kindredSpirits(node *a, node *b)
{
	// get the size of each tree
	int size_a = count_nodes(a), size_b = count_nodes(b);
	
	// make arrays of each tree for the traversals with size 0
	int *pre_a, *pre_b, *post_a, *post_b;
	int size_pre_a = 0, size_pre_b = 0, size_post_a = 0, size_post_b = 0;
	
	int i, check1 = 1, check2 = 1;
	
	// initialize each array
	pre_a = calloc(size_a, sizeof(int));
	pre_b = calloc(size_b, sizeof(int));
	post_a = calloc(size_a, sizeof(int));
	post_b = calloc(size_b, sizeof(int));
	
	// check if both trees are null
	// if so then they are kindred spirits
	if (a == NULL && b == NULL)
	{
		free(pre_a);
		free(pre_b);
		free(post_a);
		free(post_b);
		return 1;
	}
	
	// check if a is null
	// if so then are not kindred spirits
	if (a == NULL)
	{
		free(pre_a);
		free(pre_b);
		free(post_a);
		free(post_b);
		return 0;
	}
	
	// check if b is null
	// if so then are not kindred spirits
	if (b == NULL)
	{
		free(pre_a);
		free(pre_b);
		free(post_a);
		free(post_b);
		return 0;
	}
	
	// get pree and post order for both trees
	preorder(a, pre_a, &size_pre_a);
	preorder(b, pre_b, &size_pre_b);
	postorder(a, post_a, &size_post_a);
	postorder(b, post_b, &size_post_b);
	
	// check if the size of a doesn't equal the size of b
	// if so then are not kindred spirits
	if (size_a != size_b)
		return 0;
	
	// loop through and compare the arrays of the pre/post order
	for (i = 0; i < size_a; i++)
	{
		if (pre_a[i] != post_b[i])
			check1 = 0;
		
		if (pre_b[i] != post_a[i])
			check2 = 0;
	}
	
	free(pre_a);
	free(pre_b);
	free(post_a);
	free(post_b);
	return check1 || check2;
}
