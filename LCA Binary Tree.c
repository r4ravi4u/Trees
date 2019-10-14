/*
1 <=T<= 30
1 <=Number of nodes<= 100
1 <=Data of a node<= 1000

check each node on left and then on right

if root data == n1 or == n2
means that is LCA
*/

#include"Functions.h"


Node* LCA(Node* root, int n1, int n2)
{
	if (!root)
		return NULL;

	if (root->data == n1 || root->data == n2)
		return root;

	struct Node *left = LCA(root->left, n1, n2);
	struct Node *right = LCA(root->right, n1, n2);

	if (left && right)
		return root;

	if (!left && !right)
		return NULL;

	return (left != NULL ? left : right);
}