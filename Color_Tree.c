/*
Bob is very interested in the data structure of a tree. A tree is a directed graph in which a special node is singled out, called the "root" of the tree, and there is a unique path from the root to 
each of the other nodes.

Bob intends to color all the nodes of a tree with a pen. A tree has N nodes, these nodes are numbered 1, 2, ..., N. Suppose coloring a node takes 1 unit of time, and after finishing coloring one node, 
he is allowed to color another. Additionally, he is allowed to color a node only when its father node has been colored. Obviously, Bob is only allowed to color the root in the first try.

Each node has a "coloring cost factor", Ci. The coloring cost of each node depends both on Ci and the time at which Bob finishes the coloring of this node. At the beginning, the time is set to 0. 
If the finishing time of coloring node i is Fi, then the coloring cost of node i is Ci * Fi.
*/

#include "Functions.h"

#define N 5

typedef struct Node
{
	int id;	//node no.
	int p_id;	//who is parent of this, For root, parent shall be 0
	int cost;	//Coloring Cost Factor Ci
	int colored;	//True 1 = Colored ; False 0 = Not Colored yet
	int time;	//Time at which its colored, 0 means not colored yet, if we want to trace path i.e. Ti
}Node;

void push(int S[], int *top, int p_id);

void color_tree()
{
	Node A[N] = {
		{ 1, 0, 1, 1, 1},	//we made root node colored at very first point, so now Ti will be 2 for next Node
		{ 2, 1, 2, 0, 0 },
		{ 3, 1, 3, 0, 0 },
		{ 4, 1, 4, 0, 0 },
		{ 5, 1, 5, 0, 0 },
				};

	int t = 2; //As 1 is already processed for root node so next Ti is 2 and then +1 after each color to child node
	int total_cost = A[0].cost*A[0].time;	//root node cost is already taken up
	while (1)
	{
		int max = -1, index = 0;
		for (int i = 1; i < N; i++)
		{
			if (!A[i].colored)
			{
				if (A[i].cost > max)
				{
					max = A[i].cost;
					index = i;
				}
			}
		}
		if (!index)
			break;

		//create a stack of parent id's till we get a colored parent node
		int S[N - 2];	//root is already colored, child node we won't be storing in stack. so left nodes maximum side is N-2
		int top = 0;
		
		int max_index = index;	//storing index which has max value & is uncolored

		while (!A[A[index].p_id-1].colored)	//puhsing all indexes to stack till we get a colored node as we need to color all parents of this max cost node and will color it finally
		{
			push(S, &top, A[index].p_id-1);
			index = A[index].p_id - 1; 
		}

		if (!top)	//already parent is colored, so its time to color the child
		{
			A[index].colored = 1;
			A[index].time = t;
			total_cost += A[index].time*A[index].cost;
			t++;
			continue;
		}

		//control coming here, means their are few parent nodes which has not been colored yet, so color them first and then color max cost child node

		int p_id = 0;
		while (1)
		{
			p_id = pop(S, &top);
			if (!p_id)
				break;

			A[p_id].colored = 1;
			A[p_id].time = t;
			total_cost += A[p_id].time*A[p_id].cost;
			t++;
		}
		
		//All corresponding parents have been colored, now color the child with Max cost here and repeat loop for next max in remaining uncolored nodes

		A[max_index].colored = 1;
		A[max_index].time = t;
		total_cost += A[max_index].time*A[max_index].cost;
		t++;
	}

	printf("Min Cost to Color Tree : %d", total_cost);
	
}

void push(int S[], int *top, int p_id)
{
	if (*top >= N-2)
		return;

	S[*(top)++] = p_id;
}

int pop(int S[], int *top)
{
	if (*top < 0)
		return 0;

	return S[(*top)--];

}