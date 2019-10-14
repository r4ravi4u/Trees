/*
Print Left Boundary Top-Down

Print Leaves - So that during left and right boundaries. leaf shall not print 2 times
a) Left Subtree - Left to Right
b) Right Subtree - Left to Right

Print Right Boundary - Bottom-Up
*/

#include "Functions.h"

void printRightBoundary(Node *root)
{
	if (!root)
		return;

	if (root->right)
	{
		printRightBoundary(root->right);
		printf("%d ", root->data);
	}
	else if (root->left)
	{
		printRightBoundary(root->left);
		printf("%d ", root->data);
	}
}

void printLeaf(Node *root)
{
	if (!root)
		return;

	printLeaf(root->left);

	if (!(root->left) && !(root->right))	//means its a leaf node, then only print else not
		printf("%d ", root->data);

	printLeaf(root->right);
}

void printLeftBoundary(Node *root)
{
	if (!root)
		return;

	if (root->left)
	{
		printf("%d ", root->data);
		printLeftBoundary(root->left);
	}
	else if (root->right)
	{
		printf("%d ", root->data);
		printLeftBoundary(root->right);
	}
}

void printBoundary(Node *root)
{
	if (!root)
		return;

	printf("%d ", root->data);
	
	if (root->left)
	{
		printLeftBoundary(root->left);
		printLeaf(root->left);
	}
		

	if (root->right)
	{
		printLeaf(root->right);
		printRightBoundary(root->right);
	}
	printf("\n");
		
}