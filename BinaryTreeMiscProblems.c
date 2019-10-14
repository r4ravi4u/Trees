#include "Functions.h"

struct info
{
	int size; // Size of subtree
	int max; // Min value in right subtree
	int min; // Max value in left subtree
	int ans; // Size of largest BST which
	// is subtree of current node
	bool isBST; // If subtree is BST
};

void tree()
{
	struct Node *head = NULL;

	int arr[arrSize]; //array for storing vertical SUMs separate
	memset(arr, 0, arrSize*sizeof(arr[0]));

	insert(&head, 20);
	insert(&head, 18);

	delete(&head, 20);

/*	insert(&head, 15);
	insert(&head, 11);
	insert(&head, 20);
	insert(&head, 9);
	insert(&head, 13);
	insert(&head, 18);
	insert(&head, 22);
	insert(&head, 6);
	insert(&head, 10);
	/*insert(&head, 12);
	insert(&head, 14);
	insert(&head, 16);
	insert(&head, 19);
	insert(&head, 21);
	insert(&head, 23);*/

	/*insert_alt(head, 15);
	insert_alt(head, 11);
	insert_alt(head, 20);*/
	
//	int max = largestBst(head);

//	printf("%d", height_spiral_tree(head));

	//	q(head,0); //level order traversal for max width of a tree

	//Leaf node of the tree insert to DLL from left to right
//	Node *head_ref = NULL;
//	head = convertToDLL(head, &head_ref);	//head is root of the tree, head_ref is head of the DLL

	//print(head);
	//printf("\n\n");

	//	verticalSum(head, (arrSize-1)/2, arr); //start from root hence neither l nor r
//	verticalSum(head, 0, arr);

//	printSum(arr);

	/*	delete(&head, 11);
	print(head);
	printf("\n\n");

	delete(&head, 15);
	print(head);
	printf("\n\n");

	delete(&head, 22); print(head); printf("\n\n");

	delete(&head, 6); print(head); printf("\n\n");

	insert(&head, 6);

	delete(&head, 21); print(head); printf("\n\n");

	//print(head); */

//	level_order(head);

//	int h = height_tree(head);
}

void largestBstBT(struct Node *root, struct info *ret)
{
	if (!root)
		return;

	if (!root->left && !root->right)
	{
		ret->size = 1;
		ret->min = ret->max = root->data;
		ret->ans = 1;
		ret->isBST = true;
		return;
	}

	struct info left, right;
	left.size = right.size = 0;
	left.max = right.max = INT_MAX;
	left.min = right.min = INT_MIN;
	left.ans = right.ans = 0;
	left.isBST = right.isBST = true;

	largestBstBT(root->left, &left);
	largestBstBT(root->right, &right);

	ret->size = 1 + left.size + right.size;

	//if whole tree as of now is BST
	if (left.isBST && right.isBST && left.max < root->data && right.min > root->data)
	{
		ret->min = min(left.min, min(right.min, root->data));
		ret->max = max(right.max, max(left.max, root->data));

		ret->ans = ret->size;
		ret->isBST = true;
		return;
	}

	//else return max of left and right subtree
	ret->ans = max(left.ans, right.ans);
	ret->isBST = false;
	return;
}

int largestBst(Node *root)
{
	struct info start;
	start.size = 0;
	start.max = INT_MAX;
	start.min = INT_MIN;
	start.ans = 0;
	start.isBST = true;	

	largestBstBT(root, &start);

	return start.ans;

}

void insert_alt(struct Node* head, int data)
{
	struct Node *temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	if (temp == NULL) //memory full
		return;

	temp->data = data;
	temp->left = temp->right = NULL;

	if (head == NULL) //insert first node
	{
		head = temp;
		return;
	}

	if (!head->left)
		head->left = temp;
	else
		head->right = temp;

	return;

}

int height_spiral_tree(struct Node* node)
{
	if (!node)
		return 0;

	if (node->left && node->left->right == node && node->right && node->right->left == node)
		return 1;

	int l_h = height_spiral_tree(node->left);
	int r_h = height_spiral_tree(node->right);

	return (l_h > r_h) ? l_h + 1 : r_h + 1;
}

Node *convertToDLL(Node *root, Node **head_ref)	//function returns root of the tree, head_ref is DLL (Double Linked List) head pointer
{
	if (!root)
		return root;

	convertToDLL(root->left, head_ref);

	if (!(root->left) && !(root->right))
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		temp->data = root->data;
		temp->right = NULL;

		if (!(*head_ref))
		{
			temp->left = *head_ref;
			*head_ref = temp;
		}			
		else
		{
			Node *temp_dll = *head_ref;
			while (temp_dll->right)
			{
				temp_dll = temp_dll->right;
			}
			temp_dll->right = temp;
			temp->left = temp_dll;
		}

	}

	convertToDLL(root->right, head_ref);

	return root;
}

void level_order(struct Node* root)
{
	if (!root)
		return;

	struct NodeLevel *head, *tail;
	head = tail = NULL;

	insert_q(&head, &tail, root);
	
	while (head && tail)
	{
		int n = q_size(head, tail);
		if (!n)
			break;
		while (n--)
		{
			struct Node *temp = remove_q(&head, &tail);
			if (temp)
			{
				printf("%d ", temp->data);

				if (temp->left)
					insert_q(&head, &tail, temp->left);

				if (temp->right)
					insert_q(&head, &tail, temp->right);

				free(temp);
			}
		}
		printf("$ ");			
	}
}

int q_size(NodeLevel *head, NodeLevel *tail)
{
	
	if (!head || !tail)
		return 0;

	if (head == tail && head)
		return 1;

	int i = 1;
	while (head != tail)
	{
		i++;
		head = head->next;
	}
	return i;		
}

void insert_q(NodeLevel **head, NodeLevel **tail, struct Node* data)	//insert from tail end
{
	NodeLevel *temp;
	temp = (NodeLevel*)malloc(sizeof(NodeLevel));

	if (!temp) //mem full
		return;

	temp->data = data;
	temp->next = NULL;

	if (!(*head) && !(*tail)) //1st element insertion
	{
		*head = *tail = temp;
		temp = NULL;
		return;
	}

	(*tail)->next = temp;
	*tail = temp;
	temp = NULL;

}

struct Node* remove_q(NodeLevel **head, NodeLevel **tail)	//delete from head end
{
	NodeLevel *temp;

	if (!(*head))	//empty list
		return NULL;

	temp = *head;
	if (*head == *tail)
		*tail = temp->next;

	*head = temp->next;
	
	return temp->data;


}

int height_tree(struct Node* head)
{
	if (!head)
		return 0;

	int l_h = height_tree(head->left);
	int r_h = height_tree(head->right);

	return (l_h > r_h) ? l_h + 1 : r_h + 1;
}

void verticalSum(struct Node* head, int index, int arr[])
{
	if (head == NULL)
		return; //base condition		

	/*	arr[index] += head->data;

	verticalSum(head->left, index - 1, arr);

	verticalSum(head->right, index + 1, arr); */ //for Vertical Sum List

	//Here below code for level order trasversal for max width

	arr[index]++;

	verticalSum(head->left, index + 1, arr);

	verticalSum(head->right, index + 1, arr);

}

void printSum(int arr[])	//for max width & vertical SUM
{
	int index = 0;
	int level = -1, max = 0;

	while (index < arrSize)
	{
		printf("arr[%d] = %d\n", index, arr[index]);
		if (arr[index] > max)
		{
			level = index;
			max = arr[index];
		}
		index++;
	}

	////for Vertical Sum List :	printf("Highesh Level : Its SUM :: %d : %d", level, arr[level]); 

	//Here below code for level order trasversal for max width 

	printf("Highesh Width at Level : Actual Width :: %d : %d", level, arr[level]);

}

void insert(struct Node** head, int data)
{
	struct Node *temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	if (temp == NULL) //memory full
		return;

	temp->data = data;
	temp->left = temp->right = NULL;

	if (*head == NULL) //insert first node
	{
		*head = temp;
		return;
	}

	struct Node *link;
	link = *head;

	if (data <= link->data)
		traverse(&link, 'l', data);
	else
		traverse(&link, 'r', data);

}

void traverse(struct Node** link, char direction, int data)
{
	struct Node *temp;
	temp = (struct Node*)malloc(sizeof(struct Node));

	if (temp == NULL) //memory full
		return;

	temp->data = data;
	temp->left = temp->right = NULL;

	if (direction == 'l')
	{
		if ((*link)->left == NULL)
		{
			(*link)->left = temp;
			return;
		}

		*link = (*link)->left;
		if (data <= (*link)->data)
			traverse(link, 'l', data);
		else
			traverse(link, 'r', data);
	}
	if (direction == 'r')
	{
		if ((*link)->right == NULL)
		{
			(*link)->right = temp;
			return;
		}
		*link = (*link)->right;
		if (data <= (*link)->data)
			traverse(link, 'l', data);
		else
			traverse(link, 'r', data);
	}

}

void print(struct Node* head)
{
	if (head == NULL)
		return; //base condition

	print(head->left);
	printf("%d\t", head->data);
	print(head->right);

	//printf("\n");
}

struct Node* search(struct Node* head, int data)
{
	/*if (head == NULL)
	{
	printf("Not Found !! \n");
	return head;
	}

	if (data == head->data)
	{
	printf("Found : %d", head->data);
	return head;
	}*/

	if (head == NULL)
	{
		printf("Not Found !! \n");
		return head;
	}

	if (data == head->data) //root head node
	{
		//printf("Found : %d\n", head->data);
		return head;
	}

	if (head->left && data == head->left->data) //left child has the search data
	{
		//printf("Found : %d\n", head->left->data);
		return head;
	}
	if (head->right && data == head->right->data) //left child has the search data
	{
		//printf("Found : %d\n", head->right->data);
		return head;
	}

	if (data <= head->data)
		search(head->left, data);
	else
		search(head->right, data);
}

void delete(struct Node** head, int data)
{
	struct Node* temp, *temp1;
	temp1 = (struct Node*)malloc(sizeof(struct Node));

	if (temp1 == NULL) //memory full
		return;

	temp = *head;

	temp = search(temp, data);

	if (temp)
	{
		//printf("\tDelete : %d\n", temp->data);

		if (temp == *head && data == temp->data) //root node i.e head node needs to be adjusted
		{
			temp1 = temp;
						
			if (!temp->right)
			{
				*head = temp->left;
				free(temp1);
				return;
			}
	
			temp = temp->right;

				while (temp && temp->left) //traverse bottom down to left
				{
					temp = temp->left;
				}
				
			temp->left = temp1->left;
			*head = temp1->right;
			free(temp1);
			return;
		}
		if (temp->left && data == temp->left->data) //left subtree had the node to delete
		{
			temp1 = temp->left;
			if (!(temp1->left || temp1->right)) //leaf node i.e. no child either side
			{
				temp->left = temp1->left;
				free(temp1);
				return;
			}
			if (!(temp1->right)) //right has no child
			{
				temp->left = temp1->left;
				free(temp1);
				return;
			}
			if (!(temp1->left)) //left has no child
			{
				temp->left = temp1->right;
				free(temp1);
				return;
			}
			if (temp1->left && temp1->right) //both side child
			{
				temp->left = temp1->right;
				while (temp->left)
				{
					temp = temp->left;
				}
				temp->left = temp1->left;
				free(temp1);
				return;
			}
		}
		if (temp->right && data == temp->right->data) //left subtree had the node to delete
		{
			temp1 = temp->right;
			if (!(temp1->left || temp1->right)) //leaf node i.e. no child either side
			{
				temp->right = temp1->left;
				free(temp1);
				return;
			}
			if (!(temp1->right)) //right has no child
			{
				temp->right = temp1->left;
				free(temp1);
				return;
			}
			if (!(temp1->left)) //left has no child
			{
				temp->right = temp1->right;
				free(temp1);
				return;
			}
			if (temp1->left && temp1->right) //both side child
			{
				temp->right = temp1->left;
				while (temp->right)
				{
					temp = temp->right;
				}
				temp->right = temp1->right;
				free(temp1);
				return;
			}
		}

	}

}
