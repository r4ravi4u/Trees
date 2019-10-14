/*
1 <=T<= 30
1 <=Number of nodes<= 100
1 <=Data of a node<= 1000

Postorder traversal of the tree & at each lebel compute following 4 items that each node returns to it successor
4 items every node returns  : 
isBST : T or F : if leaf than T, else if self data > max of left side && data < min of right side then T else F
size : if leaf than 1 else (left+right+1 for self)
min : if leaf self data else max of left side
max = if leaf self data else min of right side
*/

#include "Functions.h"

#define INT_MAX 9999
#define INT_MIN -9999

typedef struct Info
{
	int isBST;
	int size;
	int min;
	int max;

	//max and min limits only needs to be filled in case isBST is 1 i.e. subtree is a Binary Tree
}Info;

Info largest(Node *root)
{
	if (!root)
	{
		Info inf;
		inf.isBST = 1;
		inf.size = 0;
		inf.min = INT_MAX;
		inf.max = INT_MIN;
		return inf;
	}
	
	//Postorder Traversal Left Right Root
	Info Left = largest(root->left);
	Info Right = largest(root->right);

	Info Self;
	if (Left.isBST == 0 || Right.isBST == 0 || Left.max > root->data || Right.min <= root->data)	//means Root is not BST
	{
		Self.isBST = 0;
		Self.size = Left.size > Right.size ? Left.size : Right.size;
		//no need to set max and min as its of no use as this subtree is not BST
		return Self;
	}

	//If counter reaches here, it means subtree is a BST and we need to update Self values properly
	Self.isBST = 1;
	Self.size = 1 + Left.size + Right.size;
	Self.min = root->left ? Left.min : root->data;
	Self.max = root->right ? Right.max : root->data;

	return Self;
}

int largestBst(Node *root)
{
	Info inf = largest(root);
	return inf.size;
}