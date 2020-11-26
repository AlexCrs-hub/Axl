// Assignment8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <stdio.h>
#include<stdlib.h>


typedef struct node {
    int key;
    int rank;
    struct node* parent;
}NodeT;

typedef struct edge {
    int weight;
    NodeT* source;
    NodeT* dest;
}Edge;

typedef struct graph {
    int V;
    int E;
    Edge* edges;
}Graph;

NodeT* makeSet(int key)
{
    NodeT* node = (NodeT*)malloc(sizeof(NodeT));
    if (node)
    {
        node->key = key;
        node->parent = node;
        node->rank = 0;

        return node;
    }
}

void linkSets(NodeT* x, NodeT* y)
{
    if (x->rank > y->rank)
    {
        y->parent = x;
    }
    else
    {
        x->parent = y;
        if (x->rank == y->rank)
        {
            y->rank = y->rank + 1;
        }
    }
}

NodeT* findSet(NodeT* x)
{
    if (x != x->parent)
    {
        x->parent = findSet(x->parent);
    }
    return x->parent;
}

void unionOfSets(NodeT* x, NodeT* y)
{
     linkSets(findSet(x),findSet(y));
}



void demo()
{
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    NodeT** nodes = (NodeT**)malloc(sizeof(NodeT*) * 9);
    for (int i = 0; i < 9; i++)
    {
        nodes[i] = makeSet(arr[i]);
        printf("%d ->  %d\n", nodes[i]->key,findSet(nodes[i])->key);
    }
    printf("\n\n");
    unionOfSets(nodes[0], nodes[5]);
    unionOfSets(nodes[3], nodes[7]);
    unionOfSets(nodes[2], nodes[6]);
    unionOfSets(nodes[4], nodes[8]);
    unionOfSets(nodes[1], nodes[8]);
    for (int i = 0; i < 9; i++)
    {
        nodes[i] = makeSet(arr[i]);
        printf("%d ->  %d\n", nodes[i]->key, findSet(nodes[i])->key);
    }
}

int main()
{   
    demo();
    return 0;
}

