#include "Functions.h"

Node* insertNode(Node *head, int data[], int i, int size);
void deleten(Node **head, int data);
void update(Node *head, int data);
Node* searchn(Node *head, int data);

void tree_level_order()
{
	// Declare the variable
	int d;
	// Read the variable from STDIN
	scanf_s("%d", &d);

	int n = (int)pow(2, d + 1) - 1;
	int *data;
	data = (int *)malloc(n*sizeof(int));

	for (int i = 0; i < n; i++)
		scanf_s("%d", &data[i]);

	Node *head = NULL;
	head = insertNode(head, data, 0, n);

	//	insertNode(head, data, 0);

	deleten(&head, data);

	void update(head, data);

	Node* search(head, data);



	// Output the variable to STDOUT
	//	printf("%d", a);

	// Note that you need to explicitly return 0 in main() function,
	// otherwise your solution won't get accepted
	return 0;
}

Node* insertNode(Node *head, int data[], int i, int size)
{
	if (data[i] < 0)
		return NULL;

	if (i < size)
	{
		Node* temp;
		temp = (Node *)malloc(sizeof(Node));

		if (!temp)   //mem full
			return NULL;

		temp->data = data[i];
		temp->left = temp->right = NULL;
		head = temp;

		// insert left child
		head->left = insertNode(head->left, data, 2 * i + 1, size);

		// insert right child
		head->right = insertNode(head->right, data, 2 * i + 2, size);
	}
	return head;
}
void deleten(Node **head, int data)
{

}

void update(Node *head, int data)
{

}

Node* searchn(Node *head, int data)
{

}

