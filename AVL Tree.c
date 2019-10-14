/*
AVL Tree is BST only with constraint : 
| Height of Left Subtree - Height of Right Subtree | <= 1

if its > +- 1, then we need to check for rotations : 

Lets say height as h 
															LEFT LEFT : Right Rotate
h(left) > h(right) : Left
So check Left child - 
h(child left) > h(child right) = left

		3
	2
1

After L-L Rotation, it become (For 3)

	2
1		3

															LEFT RIGHT : 
h(left) > h(right) : Left
So check Left child -
h(child right) > h(child left) = right 

		3
	1
		2

After L-R Rotation (2 steps), it become (For 3)

		3																2
	2					Now do L-L rotation like above ->			1		3
1																	



															RIGHT RIGHT
h(right) > h(left) : Right
So check Right child -
h(child right) > h(child left) = Right

	1																		2
		2							After RR Rotation->					1		3
			3

															RIGHT LEFT
h(right) > h(left) : Right
So check Right child -
h(child left) > h(child right) = Left

		1										1													2		
			3					->					2							Do RR Now ->	1		3	
		2												3
*/

#include "Functions.h"

Node* newTreeNode(int data)
{
	Node *temp = (Node *)malloc(sizeof(Node));
	if (!temp)
		return NULL;

	temp->data = data;
	temp->left = temp->right = NULL;

	return temp;
}

int height(Node *node)
{
	if (!node)
		return 0;

	int max1 = height(node->left);
	int max2 = height(node->right);
	return 1 + (max1 > max2 ? max1 : max2);
}

Node* RotateRight(Node* root)
{
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	return temp;
}

Node* RotateLeft(Node* root)
{
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	return temp;
}

Node* insertToAVL(Node* node, int data)
{
	if (!node)
	{
		Node *temp = newTreeNode(data);
		node = temp;
		return node;
	}
	if (data < node->data)
		node->left = insertToAVL(node->left, data);
	else if (data > node->data)
		node->right = insertToAVL(node->right, data);

	int balance = height(node->left) - height(node->right);

	if (balance > 1)	//L for sure -> either LL or LR
	{
		//check child height now
		if (height(node->left->left) > height(node->left->right))	//LL
		{
			//Rotate Right (node)
			return RotateRight(node);
		}

		else //LR
		{
			//Rotate Left (node left child) & then Rotate Right (node)
			node->left = RotateLeft(node->left);
			return RotateRight(node);
		}
	}
	else if (balance < -1)	//R for sure -> either RR or RL
	{
		//check child height now
		if (height(node->right->right) > height(node->right->left))	//RR
		{
			//Rotate Right (node)
			return RotateLeft(node);
		}

		else //RL
		{
			//Rotate Right (node right child) & then Rotate Left (node)
			node->right = RotateRight(node->right);
			return RotateLeft(node);
		}
	}
	return node;
}

void inOrder(Node *root)
{
	if (!root)
		return;

	inOrder(root->left);
	printf("%d\t", root->data);

	/*
	static int max = 0;
	if (max <= 0)
		max = root->data;
	else
	{
		if (max > root->data)
			printf("%d : %d\n", max, root->data);

		max = root->data;
	}*/

	inOrder(root->right);
}

int isBalanced(struct Node *root)
{
	int lh; /* for height of left subtree */
	int rh; /* for height of right subtree */

	/* If tree is empty then return true */
	if (root == NULL)
		return 1;

	/* Get the height of left and right sub trees */
	lh = height(root->left);
	rh = height(root->right);

	if (abs(lh - rh) <= 1 &&
		isBalanced(root->left) &&
		isBalanced(root->right))
		return 1;

	/* If we reach here then tree is not height-balanced */
	return 0;
}


void AVL()
{
	FILE *fp = fopen("Test.txt", "r");

	//rewind(fp);

	int T;

	fscanf(fp, "%d", &T);

	while (T--)
	{
		int N;
		fscanf(fp, "%d", &N);
		//N = no. of nodes
		//in next line nodes are given that needs to be inserted and it shall form an AVL tree at any stage

		Node* root = NULL;

		while (N--)
		{
			int data;
			fscanf(fp, "%d", &data);
			root = insertToAVL(root, data);
			
		}
		int i = isBalanced(root);
		inOrder(root);
		deleteTree(&root);

	}

	fclose(fp);

}