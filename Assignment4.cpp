// Assignment4.cpp : This file contains the 'main' function. Program execution begins and ends there.
// The complexity of the algorithm can be evaluated to O(nlogK), where n is the total number of elements contained by all the lsits.
// K is the number of lists. Building the heap and extracting the roots takes logK time.
// The algorithm performs n insertions into the final list, heapifying after each. 
// The merging algorithm consists in creating a min-heap with the linked lists. This is done at first only with the head of each list.
//The root is extracted into the final array.
// After that the heap is being rebuilt with the next elements in each list and extracting again until the heap is empty.

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#include "Profiler.h"

Profiler p("Merging k linked lists");

typedef struct node {
    int data;
    node* next;
}NodeT;

void swap(NodeT* x, NodeT* y)
{
        NodeT* temp=(NodeT*)malloc(sizeof(NodeT));
        *temp = *x;
        *x = *y;
        *y = *temp;
}

void addElement(int data, NodeT** head)
{
    NodeT* aux = (NodeT*)malloc(sizeof(NodeT));
    NodeT* x;
    aux->data = data;
    aux->next = NULL;
    if (*head == NULL)
    {
        *head = aux;
    }
    else
    {
        x = *head;
        while (x->next != NULL)
        {
            x = x->next;
        }
        x->next = aux;
    }
}

NodeT* arrList(int v[], int n)
{
    NodeT* head = NULL;
    for (int i = 0; i < n; i++)
    {
        addElement(v[i], &head);
    }
    return head;
}

void printData(NodeT *head)
{
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void heapify(NodeT *v[], int n, int i, Operation opC, Operation opA)
{   
    int min = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && v[min]->data > v[left]->data)
    {   
        opC.count();
        min = left;
    }
    if (right < n && v[min]->data > v[right]->data)
    {   
        opC.count();
        min = right;
    }
    if (min != i)
    {
        swap(v[i], v[min]);
        opA.count(3);
        heapify(v, n, min,opC,opA);
    }
}

void buildHeap(NodeT* v[], int n, Operation opC, Operation opA)
{
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        heapify(v, n, i, opC, opA);
    }
}



void generateLists(int k,int n,NodeT **nodes)
{  
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < k; i++)
    {
        FillRandomArray(arr, n, 10, 50000, false, ASCENDING);
        nodes[i] = arrList(arr, n);
        printData(nodes[i]);
    }
}

void mergeLists(int n, int k, NodeT* arr[], int finalList[], Operation opC, Operation opA)
{   
    NodeT* minHeap[MAX_SIZE];
    int heapSize = 0;
    int size = 0;
    for (int i = 0; i < k; ++i) {

        if (arr[i]->next) 
        {
            minHeap[heapSize] = arr[i];
            opA.count();
            heapSize++;
        }
    }
    buildHeap(minHeap, heapSize, opC, opA);
    while (heapSize != 0)
    {
        finalList[size] = minHeap[0]->data;
        opA.count();
        size++;
        opC.count();
        if (minHeap[0]->next != NULL)
        {
            minHeap[0] = minHeap[0]->next;
            opA.count();
        }
        else
        {
            minHeap[0] = minHeap[heapSize - 1];
            --heapSize;
            opA.count();
        }
        buildHeap(minHeap, heapSize, opC, opA);
    }
}

void demoLink()
{   
    int k = 5;
    int n = 20;
    Operation opC = p.createOperation("da", n);
    Operation opA = p.createOperation("yes", n);
    NodeT** arr = (NodeT**)malloc(sizeof(NodeT*)*5);
    int* finalList = (int*)malloc(sizeof(int)*20);
    for (int i = 0; i < k; i++)
    {
        arr[i] = NULL;
    }
    generateLists(5, 4, arr);
    mergeLists(4, 5, arr, finalList,opC,opA);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", finalList[i]);
    }
    
}

void perfNfixed()
{
    NodeT* arr[MAX_SIZE]; 
        for (int k = 10; k <= 500; k += 10)
        {
            int finalList[MAX_SIZE];
            Operation opComps = p.createOperation("comparisons", k);
            Operation opAttrs = p.createOperation("attributions", k);
            for (int t = 0; t < NR_TESTS; t++)
            {
                generateLists(k, MAX_SIZE / k, arr);
                mergeLists(MAX_SIZE / k, k, arr, finalList, opComps, opAttrs);
            }
        }
    p.divideValues("comparisons", NR_TESTS);
    p.divideValues("attributions", NR_TESTS);
    p.addSeries("allOps","comparisons","attributions");
    p.showReport();
}

void perfMultiK()
{
    NodeT* arr5[5], * arr10[10], * arr100[100];
    int finalArr5[MAX_SIZE], finalArr10[MAX_SIZE], finalArr100[MAX_SIZE];
    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        Operation opC5 = p.createOperation("Comps-5", n);
        Operation opA5 = p.createOperation("Attr-5", n);
        Operation opC10 = p.createOperation("Comps-10", n);
        Operation opA10 = p.createOperation("Attr-10", n);
        Operation opC100 = p.createOperation("Comps-100", n);
        Operation opA100 = p.createOperation("Attr-100", n);
        for (int t = 0; t < NR_TESTS; t++)
        {
            generateLists(5, n / 5, arr5);
            generateLists(10, n / 10, arr10);
            generateLists(100, n / 100, arr100);

            mergeLists(n / 5, 5, arr5, finalArr5, opC5, opA5);
            mergeLists(n / 10, 10, arr10, finalArr10, opC10, opA10);
            mergeLists(n / 100, 100, arr100, finalArr100, opC100, opA100);
        }
    }
    p.divideValues("Comps-5", NR_TESTS);
    p.divideValues("Attr-5", NR_TESTS);
    p.divideValues("Comps-10", NR_TESTS);
    p.divideValues("Attr-10", NR_TESTS);
    p.divideValues("Comps-100", NR_TESTS);
    p.divideValues("Attr-100", NR_TESTS);
    p.addSeries("Total5", "Comps-5", "Attr-5");
    p.addSeries("Total10", "Comps-10", "Attr-10");
    p.addSeries("Total100", "Comps-100", "Attr-100");
    p.createGroup("TotalOps", "Total5", "Total10", "Total100");

    p.showReport();
}

int main()
{   
    demoLink();
    //perfNfixed();
    //p.reset("vary n");
    //perfMultiK();
    return 0;
}

