#include "Functions.h"
#include "Standard.h"

void CreateNode(node* pNewNode, int newNumber)
{
	pNewNode->record.number = newNumber;

	pNewNode->pLeft = nullptr;
	pNewNode->pRight = nullptr;

	pNewNode->_height = 1;
}

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

int Min(int valueA, int valueB)
{
	return (valueA < valueB) ? valueA : valueB;
}

int Max(int valueA, int valueB)
{
	return (valueA > valueB) ? valueA : valueB;
}