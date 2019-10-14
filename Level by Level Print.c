/*
1 <=T<= 20
1 <= N, Number of edges<= 1000
1 <= data, Data of a node<= 100 with L R mentioned

1 queue and 1 delimiter $ will be stored after each level and then left and right has been inserted

Before $ we need to remove from front and then add $ at rear, when previous $ has been printed
*/

#include "Functions.h"
#include <math.h>

typedef struct qNode
{
	Node *node;
	struct qNode* next;
}qNode;

void qPrint(qNode *rear, qNode *front)
{
	while (front)
	{
		if ((char)front->node->data == '$')
			printf("%c ", (char)front->node->data);
		else
			printf("%d ", front->node->data);

		front = front->next;
	}
}

int isEmptyQ(qNode *rear, qNode *front)
{
	if (!rear && !front)
		return 1;

	return 0;
}

void qInsert(qNode **rear, qNode **front, Node *node)
{
	qNode *temp = (qNode *)malloc(sizeof(qNode));
	temp->node = node;
	temp->next = NULL;
	
	if (isEmptyQ(*rear, *front))
	{
		*rear = *front = temp;
		return;
	}

	(*rear)->next = temp;
	(*rear) = temp;
}

Node* qDelete(qNode **rear, qNode **front)
{
	if (isEmptyQ(*rear, *front))
		return NULL;

	struct Node *node = (*front)->node;

	qNode *temp = *front;
	(*front) = (*front)->next;

	free(temp);
	temp = NULL;

	if (!(*front))
		*rear = NULL;

	return node;

}

void levelOrder(Node *node)	//here node = root of the tree
{
	if (!node)
		return;

	//To maintaim queue of optimised size, 1 way is to get height of the tree, h(tree) = no. of $ in the answer, or else we can have queue of length 2*(N+1) where N is edges, hence nodes are N+1
	//As we can have at max 2*(N+1) $ in case all nodes are on same end, skewed tree

	//Height of the tree
	/*int h = height(node);

	int *q = (int *)malloc(sizeof(int)*(pow(2, h) - 1));	//at max 2^h - 1 nodes for a complete binary tree
	if (!q)
		return;

	*/

	//This above method can be costly in terms of time, as we are traversing tree for height first and then will make a queue based on it to save little space
	//Better to make a Queue Linked list so as to accomodate nodes as they come up : We can free up memory or Queue node as we remove the element from it
	//Addition at Rear & Deletion from front

	struct qNode *front = NULL, *rear = NULL;	//Queue empty condition
	Node* node1 = (Node *)malloc(sizeof(Node));	//Dummy Node
	node1->data = 0;
	node1->left = node1->right = NULL;
		
	//On insert : Rear will move, On delete : Front will move

	qInsert(&rear, &front, node);	//For root node insert
	qInsert(&rear, &front, node1);

/*	qInsert(&rear, &front, node->left);	//For root node insert
	qDelete(&rear, &front);
	qDelete(&rear, &front);
	qInsert(&rear, &front, node->right);	//For root node insert
//	qInsert(&rear, &front, '$');
		
	qDelete(&rear, &front);

	qPrint(rear, front); */


	while (!isEmptyQ(rear, front))
	{
		Node* temp = qDelete(&rear, &front);
		if (temp->data != 0)
		{
			printf("%d ", temp->data);
			
			if(temp->left)
				qInsert(&rear, &front, temp->left);

			if (temp->right)
				qInsert(&rear, &front, temp->right);
		}
		else
		{
			printf("$ ");
			if(isEmptyQ(rear, front))
				break;
			
			qInsert(&rear, &front, node1);
		}
	}
	printf("\n");

	if (node1)
	{
		free(node1);
		node1 = NULL;
	}
}

Node* newNode(int data)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (!node)
		return NULL;

	node->data = data;
	node->left = node->right = NULL;

	return node;
}

int AddNode(Node *root, int parent, Node *c, char side)	//root shall be constant that is why we haven't taken double pointer, we not going to alter root in any case
{
	if (!root)
		return 0;

	if (root->data == parent)
	{
		if (side == 'L')
			root->left = c;
		else
			root->right = c;
	
		return 1;
	}
	if (AddNode(root->left, parent, c, side))
		return 1;

	else if (AddNode(root->right, parent, c, side))
		return 1;

	return 0;

}

void preOrder(Node* root)
{
	if (!root)
		return;

	printf("%d ", root->data);
	preOrder(root->left);
	preOrder(root->right);
}

void deleteTree(Node** root)
{
	if (!(*root))
		return;

	deleteTree(&(*root)->left);
	deleteTree(&(*root)->right);

	free((*root));
	(*root) = NULL;
}

void LevelByLevelPrint()
{
	FILE *fp = fopen("Test.txt", "r");

	rewind(fp);

	int T;

	fscanf(fp, "%d", &T);

	while (T--)
	{
		int N;
		fscanf(fp, "%d", &N);
		//N = no. of edges, hence nodes shall be N+1
		//in next line 1st element is root, second is its child and char (L or R) denotes left or right child

		Node* root = NULL;
		
		while (N--)
		{
			int parent, child;
			char side[2];	//For 1 char L or R and 1 for \n, as are taking input via %s

			fscanf(fp, "%d", &parent);
			if (!root)
			{
				root = newNode(parent);
				if (!root)
					return;

			}
			fscanf(fp, "%d", &child);
			Node* c = newNode(child);
			if (!child)
				return;

			//fscanf(fp, "%s", &side);	//L = left; R = right
			//fscanf(fp, "%c", &side);
			fscanf(fp, "%s", side);
			//side = fgetc(fp);

			AddNode(root, parent, c, side[0]);	//to add child node to parent node at mentioned side

		}

		//preOrder(root);
		//printf("\n");

		//level order print with $ in between
		// levelOrder(root);

		//printSpiral(root);

		//Node* node = LCA(root, 8, 7);

		//int size = largestBst(root);

		// printBoundary(root);

		// Node * target = root->left;
		// printkdistanceNode(root, target, 2);

		/*Node *head_ref = NULL;
		BToDLL(root, &head_ref);	//Binary Tree to Doubly Linked List DLL

		while (head_ref)
		{
			printf("%d ", head_ref->data);
			head_ref = head_ref->right;
		}*/

		//After all work done and we are moving to next TC, lets delete this Tree completely to sustain memory crash
		deleteTree(&root);

	}

	fclose(fp);

}