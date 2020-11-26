// Assignment3.cpp : This file contains the 'main' function. Program execution begins and ends there.
// In the average case, quicksort performs better than heapsort. Both algorithms run in O(nlgn) time, but
// quicksort does less attributions and less comparisons.
// In the worst case, quicksort runs in O(n^2). By having the array sorted and choosing the pivot to be the last or the first element, the partitions will always
// have lenghts 0 and n-i.
// In the best case, quicksorts performs almost the same as in the average case, also O(nlgn), but the algorithm does fewer operations by always partitioning the arrays in half.

#include <stdio.h>
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5
#include "Profiler.h"

Profiler p("HeapSort vs QuickSort");

void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void copyArr(int v[], int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        a[i] = v[i];
    }
}

void heapify(int v[], int n, int i, Operation BUPcomps, Operation BUPattr)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && v[left] > v[max])
    {   
        BUPcomps.count();
        max = left;
    }
    if (right < n && v[right] > v[max])
    {   
        BUPcomps.count();
        max = right;
    }
    if (max != i)
    {
        swap(&v[i], &v[max]);
        BUPattr.count(3);
        heapify(v, n, max, BUPcomps, BUPattr);
    }
}

void buildHeap(int v[], int n,Operation heapSortAttr, Operation heapSortComps)
{
   
    for (int i = n / 2 - 1; i >= 0; i--) 
    {
        heapify(v, n, i, heapSortComps, heapSortAttr);
    }
}

void heapsort(int v[], int n)
{
    Operation heapSortAttr = p.createOperation("heapSortAttr", n);
    Operation heapSortComps = p.createOperation("heapSortComps", n);
    buildHeap(v, n,heapSortComps,heapSortAttr);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&v[0], &v[i]);
        heapSortAttr.count(3);
        heapify(v, i, 0, heapSortComps, heapSortAttr);
    }

}

int partition(int v[], int b, int t,int n)
{   
    Operation quickComps = p.createOperation("QuickSortComps", n);
    Operation quickAttr = p.createOperation("QuickSortAttr", n);
    int piv = v[t];
    quickAttr.count();
    int i = b - 1;
    for (int j = b; j < t; j++)
    {   
        quickComps.count();
        if (v[j] < piv)
        {
            i++;
            swap(&v[i], &v[j]);
            quickAttr.count(3);
        }
    }
    swap(&v[i + 1], &v[t]);
    quickAttr.count(3);
    return (i + 1);
}

int Random(int b, int t)
{
    int num = (rand() % (t - b + 1)) + t;
    return num;
}

int RandomPartition(int v[], int b, int t,int n)
{
    int i = Random(b, t);
    swap(&v[b], &v[t]);
    return partition(v, b, t, n);
}

int QuickSelect(int v[], int b, int t, int i,int n)
{
    if (b == t)
    {
        return v[b];
    }
    int parti = RandomPartition(v, b, t, n);
    int k = parti - b + 1;
    if (i == k)
    {
        return v[parti];
    }
    else if(i < k)
    {
        QuickSelect(v, b,parti-1,i, n);
    }
    else
    {
        QuickSelect(v, parti + 1, t, i - k, n);
    }
}

int Middlepartition(int v[], int b, int t, int n)
{
    Operation quickMidComps = p.createOperation("QuickMidSortComps", n);
    Operation quickMidAttr = p.createOperation("QuickMidSortAttr", n);
    int piv = v[(b+t)/2];
    quickMidAttr.count();
    int i = b - 1;
    for (int j = b; j < t; j++)
    {
        quickMidComps.count();
        if (v[j] <= piv)
        {
            i++;
            swap(&v[i], &v[j]);
            quickMidAttr.count(3);
        }
    }
    swap(&v[i + 1], &v[t]);
    quickMidAttr.count(3);
    return (i + 1);
}

int theOtherPartition(int v[], int b, int t, int n)
{   
    Operation bestQScomps = p.createOperation("bestQScomps", n);
    Operation bestQSattr = p.createOperation("bestQSattr", n);
    int piv = v[(b+t)/2];
    bestQSattr.count();
    int i = b - 1;
    int j = t + 1;
    while (true)
    {   
        do
        {   
            bestQScomps.count();
            i++;
        } while (v[i] < piv);
        do
        {   
            bestQScomps.count();
            j--;
        } while (v[j] > piv);
        if (i < j)
        {
            swap(&v[i], &v[j]);
            bestQSattr.count(3);
        }
        else return j;
    }
}

void quickSort(int v[], int b, int t, int n)
{   
    if (b < t)
    {
        int parti = partition(v, b, t, n);
        quickSort(v, b, parti - 1, n);
        quickSort(v, parti + 1, t, n);

    }
}

void quickSortBest(int v[], int b, int t, int n)
{
    if (b < t)
    {
        int parti = theOtherPartition(v, b, t, n);
        quickSortBest(v, b, parti, n);
        quickSortBest(v, parti + 1, t, n);

    }
}

void printArray(int v[],int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void QuickSortdemo()
{
    int v[] = { 3,1,10,8,22,4,6,5,2 };
    int n = sizeof(v) / sizeof(v[0]);
    quickSort(v, 0, n - 1,n);
    printArray(v, n);
}

void QuickSortBestDemo()
{
    int v[] = { 3,1,10,8,22,4,6,5,2 };
    int n = sizeof(v) / sizeof(v[0]);
    quickSortBest(v, 0, n - 1, n);
    printArray(v, n);
}

void QuickSelectDemo()
{
    int v[] = { 1,7,6,4,8,2,9,3,11,25,5 };
    int n = sizeof(v) / sizeof(v[0]);
    printf("\n%d\n",QuickSelect(v, 0, n - 1, 4,n)); 
}

void HeapSortDemo()
{
    int v[] = { 4,1,3,2,16,9,10,14,8,7 };
    int n = sizeof(v) / sizeof(v[0]);
    heapsort(v, n);
    printArray(v, n);
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
            heapsort(v, n);
            quickSort(a, 0, n - 1,n);
            printArray(v, n);
            printf("\n");
            printArray(a, n);
        }
    }
    p.divideValues("heapSortComps", NR_TESTS);
    p.divideValues("heapSortAttr", NR_TESTS);
    p.divideValues("QuickSortComps", NR_TESTS);
    p.divideValues("QuickSortAttr", NR_TESTS);
    p.createGroup("Comps", "heapSortComps", "QuickSortComps");
    p.createGroup("Attr", "heapSortAttr", "QuickSortAttr");
    p.addSeries("HeapTotal", "heapSortComps", "heapSortAttr");
    p.addSeries("QuickTotal", "QuickSortComps", "QuickSortAttr");
    p.createGroup("TotalOperations", "HeapTotal", "QuickTotal");
    p.showReport();

}

void WorstBestPerf(int order)
{
    int v[MAX_SIZE];
    int a[MAX_SIZE];
    for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
    {
        for (int t = 0; t < NR_TESTS; t++)
        {
            FillRandomArray(v, n, 10, 50000, false, order);
            copyArr(v, a, n);
            quickSort(v, 0, n - 1, n);
            quickSortBest(a, 0, n - 1, n);
            printArray(v, n);
            printArray(a, n);
        }
    }
    p.divideValues("QuickSortComps", NR_TESTS);
    p.divideValues("QuickSortAttr", NR_TESTS);
    p.divideValues("bestQScomps", NR_TESTS);
    p.divideValues("bestQSattr", NR_TESTS);
    p.addSeries("WorstTotal", "QuickSortComps", "QuickSortAttr");
    p.addSeries("BestTotal", "bestQScomps", "bestQSattr");
    p.createGroup("BestVSWorst", "WorstTotal", "BestTotal");
    p.showReport();

}

void perfall()
{
    perf(UNSORTED);
    p.reset("worst-best case");
    WorstBestPerf(ASCENDING);
    
}

int main()
{   
    QuickSortdemo();
    //QuickSelectDemo();
    //HeapSortDemo();
    //QuickSortBestDemo();
   // perfall();
	return 0;
}

