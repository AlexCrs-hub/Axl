// Assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Grigore Alexandru Cristian
/*For building the heap the most efficient algorithm is the bottom-up one, having O(n) complexity.
* The top-down manner has also O(n) but the bottom-up approach requires less operations.
* The worst case  presumes that we build a heap using a sorted array. Here we can clearly see that the bottom-up algorithm is the most efficient.
* Both algortihms run in O(n) time but the top-down algorithm requires considerably more operations.
* Advantage of bottom-up algorithm: faster, easier to write.
  Advantage of top-down algorithm: faster when the heap is already built, because the insertion of a new element takes only O(logn). 
*/

#include <stdio.h>
#include <math.h>
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#include "Profiler.h"

Profiler p("Buildheap and HeapSort");

void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void heapify(int v[], int n, int i, Operation BUPcomps, Operation BUPattr)
{   
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    BUPcomps.count();
    if (left < n && v[left] > v[max])
    {   
        max = left;
    }
    BUPcomps.count();
    if (right < n && v[right] > v[max])
    {   
        max = right;
    }
    if (max != i)
    {
        swap(&v[i], &v[max]);
        BUPattr.count(3);
        heapify(v, n, max,BUPcomps,BUPattr);
    }
}

void buildHeap(int v[], int n)
{
    Operation BUPcomps = p.createOperation("BottomUpComparisons", n);
    Operation BUPattr = p.createOperation("BottomUpAttributions", n);
    for (int i = n / 2 - 1; i >= 0; i--)  // build maxheap bottom-up starting from the last non-leaf node
    {
        heapify(v, n, i, BUPcomps, BUPattr);
    }
}

void heapIncreaseKey(int v[], int i, int key, Operation TOPDcomps, Operation TOPDattr)
{   
    TOPDcomps.count();
    if (key < v[i])
    {
        printf("new key smaller than the current one");
    }
    v[i] = key;
    TOPDattr.count();
    while (i > 0 && v[(i-1) / 2 ] < v[i])
    {   
        TOPDcomps.count();
        swap(&v[i], &v[(i-1) / 2]);
        TOPDattr.count(3);
        i = (i-1) / 2;
    }
    if (i > 0)
    {
        TOPDcomps.count();
    }
}

void maxHeapInsert(int v[], int key, int heapSize, Operation TOPDcomps, Operation TOPDattr)
{   
    v[heapSize] = -INFINITY;
    TOPDattr.count();
    heapIncreaseKey(v, heapSize, key, TOPDcomps, TOPDattr);
}

void buildMaxHeap(int v[], int n)  //top-down build
{   
    Operation TOPDcomps = p.createOperation("TopDownComps", n);
    Operation TOPDattr = p.createOperation("TopDownAttr", n);

    for (int i = 1; i < n; i++)
    {   
        
        maxHeapInsert(v, v[i],i,TOPDcomps,TOPDattr);
    }
}

void heapsort(int v[], int n)
{   
    Operation heapSortAttr = p.createOperation("heapSortAttr", n);
    Operation heapSortComps = p.createOperation("heapSortComps", n);
    buildHeap(v,n);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&v[0], &v[i]);
        heapSortAttr.count(3);
        heapify(v, i, 0,heapSortComps,heapSortAttr);
        heapSortAttr.count();
    }

}

void buildHeapDemo()
{
    int v[] = { 4,1,3,2,16,9,10,14,8,7 };
    int n = sizeof(v) / sizeof(v[0]);
    buildHeap(v, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }

}

void demo()
{
    int v[] = { 4,1,3,2,16,9,10,14,8,7 };
    int n = sizeof(v) / sizeof(v[0]);
    heapsort(v, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
}

void topDownDemo()
{
    int v[] = { 4,1,3,2,16,9,10,14,8,7 };
    int n = sizeof(v) / sizeof(v[0]);
    buildMaxHeap(v, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
}

void perf(int order)
{
    int v[MAX_SIZE];
    int a[MAX_SIZE];
    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int t = 0; t < NR_TESTS; t++)
        {
            FillRandomArray(v, n, 10, 50000, false, order);
            for (int i = 0; i < n; i++)
            {
                a[i] = v[i];
            }
            buildHeap(v, n);
            heapsort(v, n);
            buildMaxHeap(a, n);
            for (int i = 0; i < n; i++)
            {
                printf("%d ", v[i]);
            }
            printf("\n");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", a[i]);
            }
        }
    }
    p.divideValues("BottomUpComparisons", NR_TESTS);
    p.divideValues("BottomUpAttributions", NR_TESTS);
    p.divideValues("TopDownComps", NR_TESTS);
    p.divideValues("TopDownAttr", NR_TESTS);
    p.createGroup("BuildComps", "BottomUpComparisons", "TopDownComps");
    p.createGroup("BuildAttr", "BottomUpAttributions", "TopDownAttr");
    p.addSeries("allOpsBU", "BottomUpComparisons", "BottomUpAttributions");
    p.addSeries("allOpsTD", "TopDownComps", "TopDownAttr");
    p.createGroup("allOps", "allOpsBU", "allOpsTD");
    p.showReport();
}

void perfall()
{
    perf(UNSORTED);
    p.reset("worstCase");
    perf(ASCENDING);
}

int main()
{
   //demo();
   //buildHeapDemo();
   //printf("\n");
   //topDownDemo();
   perfall();
    return 0;
}


