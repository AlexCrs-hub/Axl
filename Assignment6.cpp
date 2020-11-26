
// For the first transformation we use a structure in which we store the key, the children nodes and the nr of children of each node.
// We initialize the nodes of the representation.
// We go through the array of parents, firstly searching for the root,by finding that it's parent is -1. If the root is not found we add the node to it's parent's children array. 
// The transformation runs in linear time because it doesn't go through each element multiple times, the algorithm only adds the elements to the child list of it's corresponding parent.
// For the second transformation, firstly we take the root from R2 and put it as root for R3.
// We go through it's children, putting the first one as a child node of the root and the rest as brothers of that node.
// The transformation runs in O(n) time because it goes through each node only once.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int rootInd;

//structure for the second representation
// store the key of the node, the array of children and the nr of children

typedef struct childrenNode {
    int key;
    struct childrenNode** kids;
    int nrChildren;
}Repr2;


Repr2* root;
Repr2* TreeM[30];  // used an array of nodes for the second representation

//structure for R3
// each node has a child on the left and a sibling on the right
//no additional memory used for R3

typedef struct binaryTree {
    int key;
    binaryTree* child;
    binaryTree* brother;
}binT;

binT* createNode(int key)
{
    binT* node = (binT*)malloc(sizeof(binT));
    node->key = key;
    node->brother = NULL;
    node->child = NULL;
    return node;
}

void printArr(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d -> %d\n", i+1, arr[i]);
    }
}

void addKids(int i,int parent)
{
    TreeM[parent]->kids[TreeM[parent]->nrChildren] = TreeM[i];
    TreeM[parent]->nrChildren++;
}

Repr2 *makeR2(int parents[], int size)
{   
    int root = 0;

    for (int i = 0; i <size; i++)
    {
        TreeM[i] = (Repr2*)malloc(sizeof(Repr2));
        TreeM[i]->key = i+1;
        TreeM[i]->nrChildren = 0;
        TreeM[i]->kids = (Repr2**)malloc(sizeof(Repr2)*10);
    }

    for (int i = 0; i <size; i++)
    {
        if (parents[i] == -1)
        {
            root = i;
        }
        else
        {
            addKids(i, parents[i]-1);
        }
    }
   /* for (int i = 0; i < size; i++)
    {
        printf("Nr of kids of %d is %d\n", TreeM[i]->key, TreeM[i]->nrChildren);
    }*/
    return TreeM[root];
}



void printR2(childrenNode* root, int level)
{
    if (root != NULL)
    {
        for (int i = 0; i < level; i++)
        {
            printf("   ");
        }
        printf("%d\n", root->key);
        for (int i = 0; i < root->nrChildren; i++)
        {
            printR2(root->kids[i], level + 1);
        }
    }

}

binT* makeR3(Repr2* root)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        binT* node = createNode(root->key);
        int nrKids = root->nrChildren;
        if(nrKids>0)
        {
           node->child = makeR3(root->kids[0]);
           binT* brotherList=(binT*)malloc(sizeof(binT));
           brotherList = node->child;
           int i = 1;
           while (i < nrKids)
           {   
               brotherList->brother = makeR3(root->kids[i]);
               if (brotherList != NULL)
               {
                   brotherList = brotherList->brother;
               }
               i++;
           }
        }
         return node;
    }
}

void prettyPrintuh(binT* root, int level)
{
    if (root != NULL)
    {
        for (int i = 0; i < level; i++)
        {
            printf("    ");
        }
        printf("%d\n", root->key);
        prettyPrintuh(root->child, level + 1);
        prettyPrintuh(root->brother, level);
    }
}

int main()
{   
    int parents[] = { 2,7,5,2,7,7,-1,5,2 };
    int size = 9;
    printArr(parents, size);
    root = makeR2(parents, size);
    printf("Multi way tree:\n");
    printR2(root,0);
    printf("\nBinary tree representation:\n");
    binT* rootBin = makeR3(root);
    prettyPrintuh(rootBin, 0);

    return 0;
}

