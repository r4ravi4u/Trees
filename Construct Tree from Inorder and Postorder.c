/*
1 <=T<= 30
1 <= Size of arrays <= 100
1 <= Values in arrays <= 1000

Let us see the process of constructing tree from in[] = {4, 8, 2, 5, 1, 6, 3, 7} and post[] = {8, 4, 5, 2, 6, 7, 3, 1}

1) We first find the last node in post[]. The last node is “1”, we know this value is root as root always appear in the end of postorder traversal.

2) We search “1” in in[] to find left and right subtrees of root. Everything on left of “1” in in[] is in left subtree and everything on right is in right subtree.

		1
	/		\
[4,8,2,5]   [6,3,7]

3) We recur the above process for following two.

….b) Recur for in[] = {6,3,7} and post[] = {6,7,3}
…….Make the created tree as right child of root.

….a) Recur for in[] = {4,8,2,5} and post[] = {8,4,5,2}.
…….Make the created tree as left child of root.

*/
#include "Functions.h"
#define MAX 1000

Node *buildTreeUtil(int in[], int post[], int start, int end, int* postIndex)
{
	if (start > end)
		return NULL;

	struct Node* root = newNode(post[*postIndex]);	//root of the tree and for subtrees when recursion happens
	(*postIndex)--;

	if (start == end)	//when we reached to a leaf node
		return root;

	//Searching node->data in Inorder array so as to build right and left subtree recursively
	int inIndex;
	for (int i = 0; i <= end; i++)
	{
		if (in[i] == root->data)
		{
			inIndex = i; //i is the index in Inorder array
			break;	
		}
			
	}
	//Left side of inIndex is left subtree and right side is right subtree, Willl build Right side first as Postorder index decrements from right side and its like Left Right Root

	root->right = buildTreeUtil(in, post, inIndex + 1, end, postIndex);
	root->left = buildTreeUtil(in, post, start, inIndex - 1, postIndex);

	return root;

}

Node *buildTree(int in[], int post[], int n)
{
	if (n < 1)
		return NULL;

	if (n == 1)
	{
		return newNode(in[0]);	//or post[0]
	}

	int postIndex = n - 1;	//Postorder array index as last element of postorder is always root and we need to find this element in inorder array
	//in Inorder array before pIndex all are left subtree and after pIndex all are right subtree
	return buildTreeUtil(in, post, 0, n - 1, &postIndex);

}

void ConstructTreeFromInPost()
{
	FILE *fp = fopen("Test.txt", "r");

	rewind(fp);

	int T;

	fscanf(fp, "%d", &T);

	while (T--)
	{
		int N;	//array size of in & post
		fscanf(fp, "%d", &N);
		
		int in[MAX], post[MAX];
		for (int i = 0; i < N;i++)
			fscanf(fp, "%d", &in[i]);

		for (int i = 0; i < N; i++)
			fscanf(fp, "%d", &post[i]);	

		Node* root = buildTree(in, post, N);
		preOrder(root);
		
		//After all work done and we are moving to next TC, lets delete this Tree completely to sustain memory crash
		deleteTree(&root);

	}

	fclose(fp);
}