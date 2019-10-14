#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void insert(struct Node **head, int data);
void print(struct Node* head);

struct Node
{
	int data;
	struct Node* next;
};

void main(void)
{
	struct Node *head;
	head = NULL;

	insert(&head, 5);
	insert(&head, 3);
	insert(&head, 7);
	insert(&head, 4);
	insert(&head, 6);
	insert(&head, 15);
	insert(&head, 1);
	insert(&head, 9);
	insert(&head, -1);
	insert(&head, 0);
	insert(&head, 11);
	insert(&head, 2);
	insert(&head, 10);
	insert(&head, 12);

	print(head);

	_getch();
}

void insert(struct Node **head, int data)
{
	struct Node *temp, *link; //temp for new node ; link for traverse and find exact position
	int i;
	temp = (struct Node*)malloc(sizeof(struct Node));
	if (temp == NULL)
		return;

	temp->data = data;

	if (*head == NULL)
	{
		temp->next = NULL;
		*head = temp;
		return;
	}

	link = *head;

	if (link->data > temp->data) //shortest element at head
	{
		temp->next = link;
		*head = temp;
		return;
	}
	//head not to be altered, only node needs to be insert now
	//link = link->next;

	while (link != NULL)
	{
		if (link->data < temp->data && link->next == NULL) //highest element came at this point
		{
			link->next = temp;
			temp->next = NULL;
			return;
		}
		if (link->data < temp->data && link->next->data > temp->data) //node in between 2 already existing nodes
		{
			temp->next = link->next;
			link->next = temp;
			return;
		}
		link = link->next;
	}

}

void print(struct Node* head)
{
	struct Node *temp;
	temp = head;

	while (temp != NULL)
	{
		printf("%d\t", temp->data);
		temp = temp->next;

	}
}