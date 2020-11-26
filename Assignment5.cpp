// Assignment5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//The insert and search operations, in the average case, have the complexity O(1).
//In the worst case, the operations perform in O(n) time.
//The worst case would happen if the hash function would give the same index int he hash table for all the elements.
//As the fill factor increases the results for the result will also increase because of the increased probability of finding collisions.
//As for the not found elements, the number of the effort increases because the area searched is also increasing.


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Profiler.h"
#define MAX_SIZE 10007
#define NR_TESTS 5
#define m 3000

Profiler p("Hash Table");


typedef struct {
    int id;
    char name[30];
} Entry;

void initHash(Entry T[],int n)
{
    for (int i = 0; i < n; i++)
    {
        T[i].id = -1;
    }
}

int auxHash(int k)
{
    return (k % MAX_SIZE);
}

int quadProbing(int k, int i)
{   
    int x = auxHash(k);
    return ((x + 1 * i + 1 * i * i) % MAX_SIZE);
}

int hashInsert(int k,const char s[],Entry hashTable[])
{      

    int i = 0;
    do
    {
        int j = quadProbing(k, i);
        if (hashTable[j].id == -1)
        {
            hashTable[j].id = k;
            strcpy(hashTable[j].name, s);
            return j;
        }
        else
        {
            i = i + 1;
        }
    } while (i != MAX_SIZE);
    if (i == m)
    {
        //printf("\nFull table\n");
        return -1;
    }
    return -1;
}

int hashSearch(int &k,Entry hashTable[], int &effort)
{   
    int i = 0;
    int j;
    do
    {
        ++effort;
        j = quadProbing(k, i);
        if (hashTable[j].id == k)
        {
            return j;
        }
        else
        {
            i++;
        }
    }while ((hashTable[j].id != -1) && (i != MAX_SIZE));
    return -1;
}

void demo()
{
    Entry* T = (Entry*)malloc(sizeof(Entry) * MAX_SIZE);
    initHash(T, MAX_SIZE);
    int effortDemo = 0;
    int arr[10] = { 13,22,7,8,10,1,2,3,4,5 };
    const char* s[10] = { "Jojo" , "Giornor","Bucky","Bob","Dude","Sam","Bilbo","Gandalf","Polnareff","Iggy" };
    for (int i = 0; i < 10; i++)
    {
        hashInsert(arr[i], s[i], T);
    }
    for (int i = 0; i < 10; i++)
    {
        int found = hashSearch(i, T, effortDemo);
        if (found == -1)
        {
            printf("\nNo element found");
        }
        else
        {
            printf("\nI found %s", T[found].name);
        }
    }
}

void perf()
{      
    float maxEffortFound = 0;
    float avgEffortFound = 0;
    float maxEffortNotFound = 0;
    float avgEffortNotFound = 0;
    float totalEffortF = 0;
    float totalEffortNF = 0;
    float alfa[5] = { 0.8,0.85,0.9,0.95,0.99 };
    for (int i = 0; i < 5; i++)
    {  
        for (int t = 0; t < NR_TESTS; t++)
        {
            float fillFactor = alfa[i];
            int n = floor(MAX_SIZE * fillFactor);
            Entry hashTable[MAX_SIZE];
            initHash(hashTable, MAX_SIZE);
            int *arr = (int*)malloc(sizeof(int)*n);
            FillRandomArray(arr, n, 10, 20000, true, UNSORTED);
            for (int i = 0; i < n; i++)
            {  
                    hashInsert(arr[i], "JoJo", hashTable);
            }
            int *foundarr = (int*)malloc(sizeof(int) * (m / 2));
            int *notFoundarr = (int*)malloc(sizeof(int) * (m / 2));
            for (int i = 0; i < m / 2; i++) {       
                 foundarr[i] = arr[rand() % n];
            }
            FillRandomArray(notFoundarr, m / 2, 20001, 50000, true, UNSORTED);
            for (int i = 0; i < m / 2; i++)
            {   
                int count = 0;
                hashSearch(foundarr[i], hashTable, count);
               // printf("%d\n", count);
                totalEffortF += count;
                if (maxEffortFound < count)
                {
                    maxEffortFound = count;
                }
            }
            for (int i = 0; i < m / 2; i++)
            {   
                int countnf = 0;
                hashSearch(notFoundarr[i], hashTable, countnf);
                totalEffortNF += countnf;
               // printf("%d\n", countnf);
                if (maxEffortNotFound < countnf)
                {
                    maxEffortNotFound = countnf;
                }
            }
        }
        avgEffortFound = totalEffortF / (1500 * 5);
        avgEffortNotFound = totalEffortNF / (1500*5);
        printf(" effort for %.2f is : max %.2f avg %.4f\n", alfa[i], maxEffortFound, avgEffortFound);
        printf(" effort not found for %.2f is : max %.2f avg %.4f\n", alfa[i], maxEffortNotFound, avgEffortNotFound);
    }
}

int main()
{
    demo();
    //perf();
    return 0;
}