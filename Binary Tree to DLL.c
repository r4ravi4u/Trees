/*
Binary Tree to Doubly Linked List

Head of DLL = Left Most node of Bin Tree

DLL shall be formed in-place

DLL is like Inorder traversal of the tree

*/

#include "Functions.h"

/*void BToDLLUtilCircular(Node *root, Node **head_ref, Node** prev)
{
	if (!root)
	{
		(*prev)->right = *head_ref;
		(*head_ref)->left = *prev;
		return;
	}
		

	BToDLLUtilCircular(root->left, head_ref, prev);

	if (!(*prev))
		*head_ref = root;

	else
	{
		root->left = (*prev);
		(*prev)->right = root;
	}

	*prev = root;	//update prev now for next recusrive call

	BToDLLUtilCircular(root->right, head_ref, prev);

}*/

void BToDLLUtil(Node *root, Node **head_ref, Node** prev)
{
	if (!root)
		return;

	BToDLLUtil(root->left, head_ref, prev);

	if (!(*prev))
		*head_ref = root;

	else
	{
		root->left = (*prev);
		(*prev)->right = root;
	}

	*prev = root;	//update prev now for next recusrive call

	BToDLLUtil(root->right, head_ref, prev);
}

void BToDLL(Node *root, Node **head_ref)	//static version can't be used their are more than 1 TCs, so for next TC also prev value takes value from Last TC
{
	Node* prev = NULL;
	BToDLLUtil(root, head_ref, &prev);

	//BToDLLUtilCircular(root, head_ref, &prev);

	/*if (!root)
		return;

	BToDLL(root->left, head_ref);

	static Node* prev = NULL; //prev same value for all recursive calls

	if (!prev)
		*head_ref = root;

	else
	{
		root->left = prev;
		prev->right = root;
	}

	prev = root;	//update prev now for next recusrive call

	BToDLL(root->right, head_ref);*/

}