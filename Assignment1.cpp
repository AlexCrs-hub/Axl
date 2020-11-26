// Assignment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
/* The best case can be evaluated when an ascending sorted array is provided as the input.
 For this case the most efficient algorithms are bubble sort and insertion sort since they have a running time of O(n). Bubble sort has to go through the array only once. Insertion sort, at each iteration compares the first remaining element of the input with the right most element of the sorted section.
 Selection sort is the most inefficient here having a running time of O(n^2).
 In this case both bubble sort and selection sort perform O(1) swaps, while insertion sort performs O(n).
 
 In the average case all the algorithms have O(n^2) complexity. Bubble sort and insertion sort perform O(n^2) swaps and selection sort does O(n) swaps.
 In this case the most efficient algorithm is selection sort because it does fewer swaps.

 In the worst case scenario all the algorithms perform O(n^2) comparisons.
 Bubble sort and insertion sort perform O(n^2) swaps and selection sort O(n) swaps.
 So for this case selection sort is the most efficient.

 Bubble sort and insertion sort are stable algorithms because they do not change the relative order of the elements.
 Selection sort is unstable because it works by finding the minimum element in the usorted array and putting it in its correct position by swapping it with the element in that position.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Profiler.h"
#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

Profiler p("Sorting Algorithms");

void bubblesort(int v[],int n)
{
	Operation bubComp = p.createOperation("bubbleComp", n);
	Operation bubAttr = p.createOperation("bubbleAttr", n);
	int flag = 0;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{	
			if (v[j] > v[j + 1])
			{	
				bubAttr.count();
				int aux = v[j];
				bubAttr.count();
				v[j] = v[j+1];
				bubAttr.count();
				v[j+1]=aux;
				flag = 1;
			}
			bubComp.count();
		}
		if (flag == 0)
		{
			break;
		}
	}
}

void insertionsort(int v[], int n)
{	
	Operation insertionComp = p.createOperation("insertionComp", n);
	Operation insertionAttr = p.createOperation("insertionAttr", n);
	int inIndex,subject;
	for (int i = 1; i < n; i++)
	{	
	    inIndex = i-1;
	    subject = v[i];
		insertionAttr.count();
		while (inIndex >= 0 && subject < v[inIndex])
		{
			insertionComp.count();
			v[inIndex+1] = v[inIndex];
			insertionAttr.count();
			inIndex--;
		}
		if (inIndex >= 0)
		{
			insertionComp.count();
		}
		v[inIndex + 1] = subject;
		insertionAttr.count();
	}
}

void selectionsort(int v[],int n)
{	
	Operation selComp = p.createOperation("selComp", n);
	Operation selAttr = p.createOperation("selAttr", n);
	int minIndex;
	for (int i = 0; i < n; i++)
	{
		 minIndex = i;
		for (int j = i + 1; j < n; j++)
		{	
			
			if (v[minIndex] > v[j])
			{	
				minIndex = j;
			}
			selComp.count();
		}
		if (minIndex != i)
		{
			int aux = v[i];
			selAttr.count();
			v[i] = v[minIndex];
			selAttr.count();
			v[minIndex] = aux;
			selAttr.count();
		}
	}
}
void bubbledemo()
{
	int v[] = { 2,4,5,9,1 };
	int n = sizeof(v) / sizeof(v[0]);
	bubblesort(v, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

void insertiondemo()
{
	int a[] = { 3,5,1,7,6 };
	int x = sizeof(a) / sizeof(a[0]);
	insertionsort(a, x);
	for (int i = 0; i < x; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void selectiondemo()
{
	int b[] = { 2,6,8,1,4,5 };
	int n = sizeof(b) / sizeof(b[0]);
	selectionsort(b, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", b[i]);
	}
	printf("\n");
}


void perf(int order)
{
	int v[MAX_SIZE];
	int a[MAX_SIZE];
	int b[MAX_SIZE];
	for (int n = STEP_SIZE; n <= MAX_SIZE; n+=STEP_SIZE)
	{
		for (int test = 0; test <= NR_TESTS; test++)  
		{
			FillRandomArray(v, n, 10, 50000, false, order);
			for (int i = 0; i < n; i++)
			{
				a[i] = v[i];
				b[i] = v[i];
			}
			bubblesort(v, n);
			insertionsort(a, n);
			selectionsort(b, n);
			for (int i = 0; i < n; i++)
			{
				printf("%d ", v[i]);
			}
			printf("\n");
			for (int i = 0; i < n; i++)
			{
				printf("%d ", a[i]);
			}
			printf("\n");
			for (int i = 0; i < n; i++)
			{
				printf("%d ", b[i]);
			}
			printf("\n");
		}

	}
	p.divideValues("bubbleComp", NR_TESTS);
	p.divideValues("bubbleAttr", NR_TESTS);
	p.divideValues("insertionComp", NR_TESTS);
	p.divideValues("insertionAttr", NR_TESTS);
	p.divideValues("selComp", NR_TESTS);
	p.divideValues("selAttr", NR_TESTS);
	p.createGroup("attr", "bubbleAttr", "insertionAttr", "selAttr");
	p.createGroup("comps", "bubbleComp", "insertionComp", "selComp");
	p.addSeries("bubbleSum","bubbleComp", "bubbleAttr");
	p.addSeries("insertionSum", "insertionComp", "insertionAttr");
	p.addSeries("selectionSum", "selComp", "selAttr");

	p.showReport();
}

void worstcaseSelection()
{
	int v[MAX_SIZE];
	for (int n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test <= NR_TESTS; test++)
		{
			FillRandomArray(v, n, 10, 50000, false, ASCENDING);
			int aux = v[n-1];
			for (int i = n-1; i > 0; i--)
			{
				v[i] = v[i - i];
			}
			v[0] = aux;
			selectionsort(v,n);
		}
	}
	p.divideValues("selComp", NR_TESTS);
	p.divideValues("selAttr", NR_TESTS);
	p.addSeries("selectionSum", "selComp", "selAttr");
	p.showReport();

}



void perfall()
{
	perf(UNSORTED);  // average case
	p.reset("best");
	perf(ASCENDING);  // best case
	p.reset("worst");
	perf(DESCENDING); // worst case
	p.reset("selectionworst");
}

int main()
{	
	//bubbledemo();
	//insertiondemo();
	//selectiondemo();
	perfall();
	worstcaseSelection();
	printf("\n");
	return 0;
}

