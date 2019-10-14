/*
1<=T<=1000
1<=no of edges<=100
1<=data of node<=100
1<=target<=100

Down side and ancestor side both we need to check

*/

#include "Functions.h"

/* Recursive function to print all the nodes at distance k in the
tree (or subtree) rooted with given root. See  */
void printkdistanceNodeDown(Node *root, int k)
{
	if (k < 0 || !root)
		return;

	if (!k)
	{
		printf("%d ", root->data);
		return;
	}

	printkdistanceNodeDown(root->left, k - 1);
	printkdistanceNodeDown(root->right, k - 1);
}



int printkdistanceNode(Node* root, Node* target, int k)
{
	if (!root)
		return -1;

	if (root == target)	//we need this check for the nodes to be printed below target node as k distance hence return is also 0
	{
		printkdistanceNodeDown(target, k);
		return 0;
	}

	//check if target is at left side
	int dl = printkdistanceNode(root->left, target, k);
	if (dl != -1)
	{
		if (k == dl + 1)	//we found the node to be printed
			printf("%d ", root->data);

		else
			printkdistanceNodeDown(root->right, k - dl - 2);

		return dl + 1;
	}

	//check if target is at right side
	int dr = printkdistanceNode(root->right, target, k);
	if (dr != -1)
	{
		if (k == dr + 1)	//we found the node to be printed
			printf("%d ", root->data);

		else
			printkdistanceNodeDown(root->left, k - dr - 2);

		return dr + 1;
	}

	return -1;

}