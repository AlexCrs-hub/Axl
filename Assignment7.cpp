// Assignment7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// The build operation runs in O(n) time. The select and delete management operations both have the complexity O(logn).
/*The build operation uses a divide and conquer strategy.
It takes the given sorted array, finds the middle element and sets it as root.
Then it goes recursively on the remaining two sub-arrays the same way, only with the mention that the left sub-array will constitute the left sub-tree and the right sub-array, the right sub-tree.
The select operation selects the ith smallest element in the tree. The search is being done using the rank of the nodes.If i is smaller than the rank, then the search continues on the left subtree.
If it is greater than the rank it continues on the right subtree.
The delete operation works by first comparing the key with the root's key. If it is smaller, it continues on the left. If it is greater, it continues ont the right.
When the node is found, we verify if the node has any children. If the node has both a left and a right children, we search for his successor, by searching for the smallest element on the right subtree.
We exchange their data and delete the successor.*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "Profiler.h"
#define STEP_SIZE 100
#define MAX_SIZE 10000
#define NR_TESTS 5

Profiler p("Dynamic Order Statistics");

typedef struct node {
	int data;
	int size;
	struct node* left;
	struct node* right;
}NodeT;

NodeT* createNode(int key,Operation opA)
{
	NodeT* newNode = (NodeT*)malloc(sizeof(NodeT));
	if (newNode)
	{
		newNode->data = key;
		newNode->size = 0;
		newNode->left = NULL;
		newNode->right = NULL;
		opA.count(4);
	}
	return newNode;
}

NodeT* BuildTree(int *arr,int i, int j, Operation opB,Operation opBC)
{
	if (i <= j)
	{
		int mid = (i + j) / 2;
		NodeT* root = createNode(arr[mid],opB);
		opB.count(2);
		root->left = BuildTree(arr,i, mid - 1,opB,opBC);
		root->right = BuildTree(arr,mid + 1, j,opB,opBC);
		opBC.count();
		if (root->left == NULL && root->right == NULL)
		{
			root->size = 1;
		}
		else
		{	
			opBC.count();
			if (root->left != NULL)
			{	
				opB.count();
				root->size += root->left->size;
			}
			opBC.count();
			if (root->right != NULL)
			{	
				opB.count();
				root->size += root->right->size;
			}
			opB.count();
			root->size += 1;
		}
		return root;
	}
	return NULL;
}

NodeT* OS_SELECT(NodeT *x, int i,int n,Operation opA,Operation opC)
{	
	int r;
	if (x->left == NULL)
	{
		r = 1;
	}
	opC.count(2);
	if (x->left != NULL)
	{
	     r = x->left->size + 1;
    }
	if (i == r)
	{
		return x;
	}
	else if (i < r)
	{
		opC.count();
		return OS_SELECT(x->left, i,n,opA,opC);
	}
	else
	{	
		opC.count();
		return OS_SELECT(x->right, i - r,n,opA,opC);
	}
	return NULL;
}

NodeT* minValueNode(NodeT* root,Operation opC,Operation opA)
{
	NodeT* current = root;
	opA.count();
	opC.count(2);
	while (current && current->left != NULL)
	{	
		opA.count();
		current = current->left;
	}
	return current;
}

NodeT* OS_DELETE(NodeT *x, int data,int n,Operation opA,Operation opC)
{	
	opC.count();
	if (x == NULL)
	{
		return x;
	}
	opC.count();
	if (data < x->data)
	{
		x->left = OS_DELETE(x->left, data,n,opA,opC);
		opA.count();
	}
	else if (data > x->data)
	{
		opC.count();
		x->right = OS_DELETE(x->right, data,n,opA,opC);
		opA.count();
	}
	else
	{
		opC.count();
		if (x->left == NULL)
		{	
			opA.count();
			NodeT* aux = x->right;
			free(x);
			return aux;
		}
		else if (x->right == NULL)
		{	
			opA.count();
			NodeT* aux = x->left;
			free(x);
			return aux;
		}
		opC.count();
		NodeT* aux = minValueNode(x->right,opC,opA);
		x->data = aux->data;
		x->right = OS_DELETE(x->right, aux->data, n, opA, opC);
		opA.count(3);
		
	}
	opC.count();
	if (x != NULL && x->size != 1)
	{
		x->size -= 1;
		opA.count();
		return x;
	}
}

void updateArray(int* arr, int i, int n)
{
	for (int j = i; j < n; j++)
	{
		arr[j] = arr[j + 1];
	}
}

int generateRandom(int l, int r)
{
	return (rand() % (r - l + 1)) + l;
}

void prettyPrint(NodeT* p, int level)
{
	if (p == NULL)
	{
		return;
	}
	prettyPrint(p->right, level + 1);
	for (int i = 0; i <= level; i++)
	{
		printf("    ");
	}
	printf("%d\n", p->data);
	prettyPrint(p->left, level + 1);

}

void demo()
{	
	int *arr = (int*)malloc(sizeof(int) * 11);
	FillRandomArray(arr, 11, 10, 30, true, ASCENDING);
	int n = 11;
	Operation opA = p.createOperation("operation", n);
	Operation opC = p.createOperation("operation", n);
	Operation opB = p.createOperation("operation", n);
	Operation opBC = p.createOperation("operation", n);
	NodeT* root = BuildTree(arr,0, 10,opB,opBC);
	prettyPrint(root, 0);
	printf("\n\n");
	//printf("Selected nodes: ");
	int m = n;
	for (int i = 0; i < 3; i++)
	{	
		printf("Selected node: ");
		int selIndex = generateRandom(1,m);
		printf("%d ", selIndex);
		NodeT* selNode = OS_SELECT(root, selIndex, n,opA,opC);
		printf("%d  ", selNode->data);
		printf("\n\n");
		//int deleteIndex = rand() % m;
		root = OS_DELETE(root, selNode->data, n, opA, opC);
		//updateArray(arr, selIndex, m);
		prettyPrint(root, 0);
		printf("\n\n");
		m--;
	}
	printf("\n");
}

void perf()
{
	int n, k;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{	
		Operation opA = p.createOperation("Assign", n);
		Operation opC = p.createOperation("Comp", n);
		for (k = 0; k < NR_TESTS; k++)
		{
			int* v = (int*)malloc(sizeof(int) * n);
			FillRandomArray(v, n, 10, 50000, true, ASCENDING);
			NodeT* root = BuildTree(v, 0, n - 1,opA,opC);
			int m = n;
			for (int i = 0; i < n; i++)
			{
				int randomIndex = generateRandom(1,m);
				NodeT* selNode = OS_SELECT(root, randomIndex, n, opA, opC);
			    root = OS_DELETE(root, selNode->data, n, opA, opC);
				//updateArray(v, randomIndex, m);
				m--;
			}
		}
	}
	p.divideValues("Assign", NR_TESTS);
	p.divideValues("Comp", NR_TESTS);
	p.createGroup("Ops", "Assign", "Comp");
	p.addSeries("AllOps", "Assign", "Comp");

	p.showReport();
}


int main()
{
	demo();
	//perf();
	return 0;
}