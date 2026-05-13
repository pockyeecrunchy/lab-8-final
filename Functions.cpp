#include "Functions.h"
#include "Standard.h"

//------------------------------------------------------------------------------------------------
// File Name: Functions.cpp
// Written by: Oscar Lan
//------------------------------------------------------------------------------------------------
// Contents:
//
// Contains the implementation of helper functions used by the BST and AVL Tree program. Includes 
// functions for creating nodes,  reading integer data  from input files, and comparison functions 
// used with traversal function pointers.
//
//-------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------
// Function Name: CreateNode
// Description:
//
// Initializes a newly allocated node by assigning the provided integer value,  setting both child 
// pointers to nullptr (or NULL), and initializing the node height to 1.
//------------------------------------------------------------------------------------------------

void CreateNode(node* pNewNode, int newNumber)
{
	pNewNode->record.number = newNumber;

	pNewNode->pLeft = nullptr;
	pNewNode->pRight = nullptr;

	pNewNode->_height = 1;
}

//------------------------------------------------------------------------------------------------
// Function Name: ReadInData
// Description:
//
// Reads integer values from the input file one value at a time, dynamically creates new nodes 
// for each value, initializes the nodes, and inserts them into the binary tree.
//------------------------------------------------------------------------------------------

void ReadInData(ifstream& fin, binaryTree& tree)
{
	int value;
	node* pNewNode = nullptr;

	while (fin >> value)
	{
		pNewNode = new node;

		CreateNode(pNewNode, value);

		tree.Insert(pNewNode);

	}
}

//------------------------------------------------------------------------------------------------
// Function Name: Min
// Description:
//
// Compares two integer values and returns the smaller of the two.
//------------------------------------------------------------------------------------------------
int Min(int valueA, int valueB)
{
	return (valueA < valueB) ? valueA : valueB;
}

//------------------------------------------------------------------------------------------------
// Function Name: Max
// Description:
//
// Compares two integer values and returns the larger of the two.
//------------------------------------------------------------------------------------------------
int Max(int valueA, int valueB)
{
	return (valueA > valueB) ? valueA : valueB;
}