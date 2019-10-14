/*
root
left to right - level 1
right to left - level 2
left to right - level 3
...
& so on

Will take 2 stacks. S1 and S2
S1 : Root
Pop all from S1 -> Push First R then L :  S2
Pop all from S2 -> Push First L and then R : S1
..
& so on

Repeat above process till S1 && S2 both become empty

*/

#include "Functions.h"

typedef struct sNode
{
	Node *node;
	struct sNode *next;
}sNode;

void pushNode(sNode **top, Node *node)
{
	sNode *temp = (sNode *)malloc(sizeof(sNode));
	temp->node = node;
	temp->next = NULL;

	if (!(*top))	//first element needs to be inserted
	{
		*top = temp;
		return;
	}

	temp->next = *top;
	*top = temp;
}

Node* popNode(sNode **top)
{
	if (!(*top))
		return NULL;

	struct Node* node = (*top)->node;
	struct sNode *temp = *top;
	(*top) = (*top)->next;

	free(temp);
	temp = NULL;

	return node;
}

int isEmptyS(sNode *top)
{
	if (!top)
		return 1;

	return 0;
}

void printSpiral(Node *root)
{
	//S1 and S2 as a linked list
	sNode *top1 = NULL, *top2 = NULL;

	/*
	pushNode(&top1, root);
	pushNode(&top1, root->left);
	pushNode(&top1, root->right);
	
	Node *node = popNode(&top1);
	node = popNode(&top1);
	node = popNode(&top1);
	*/

	pushNode(&top1, root);
	int flag = 1;	//1 means pop from S1 and push into S2 RL style ; 2 means pop from S2 and push into S1 LR style
	while (!isEmptyS(top1) || !isEmptyS(top2))
	{
		if (flag == 1) //pop from S1 and push into S2 RL style
		{
			while (!isEmptyS(top1))
			{
				Node *node = popNode(&top1);
				printf("%d ", node->data);

				if (node->right)
					pushNode(&top2, node->right);

				if (node->left)
					pushNode(&top2, node->left);
			}
			flag = 2;
		}
		else //pop from S2 and push into S1 LR style
		{
			while (!isEmptyS(top2))
			{
				Node *node = popNode(&top2);
				printf("%d ", node->data);

				if (node->left)
					pushNode(&top1, node->left);

				if (node->right)
					pushNode(&top1, node->right);
			}
			flag = 1;
		}
	}
	printf("\n");
}