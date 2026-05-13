#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Standard.h"
#include "BinaryTree.h"

//-----------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------

// Reads values from file and inserts into tree
void ReadInData(ifstream& fin, binaryTree& tree);

// Initializes a new node
void CreateNode(node* pNewNode, int newNumber);

// Function pointer helpers
int Min(int valueA, int valueB);
int Max(int valueA, int valueB);

#endif 
