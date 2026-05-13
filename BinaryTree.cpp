#include "BinaryTree.h"
#include "Standard.h"

//------------------------------------------------------------------------------------------------
// File Name: BinaryTree.cpp
// Written by: Oscar Lan
//------------------------------------------------------------------------------------------------
// Contents:
//
// Contains the implementation of the Binary Search Tree and AVL Tree class
// methods. Includes recursive traversal methods, insertion and deletion
// operations, AVL balancing functions, tree rotations, height management,
// node counting, and dynamic memory cleanup functionality.
//
//------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------
// Method Name: binaryTree
// Description:
//
// Initializes the binary tree by setting the root pointer to nullptr and initializing the node 
// counter to 0.
//------------------------------------------------------------------------------------------------

binaryTree::binaryTree()
{
	_pRoot = nullptr;
	_nodeCount = 0;
}

//------------------------------------------------------------------------------------------------
// Method Name: ~binaryTree
// Description:
//
// Frees all dynamically allocated nodes in the binary tree and resets the root pointer to nullptr.
//------------------------------------------------------------------------------------------------
binaryTree::~binaryTree()
{
	FreeAllNodes(_pRoot);
	_pRoot = nullptr;
}

//------------------------------------------------------------------------------------------------
// Method Name: GetNodeCount
// Description:
//
// Returns the current number of nodes stored in the binary tree.
//------------------------------------------------------------------------------------------------
int binaryTree::GetNodeCount()
{
	return _nodeCount;
}

//------------------------------------------------------------------------------------------------
// Method Name: IncreaseNodeCount
// Description:
//
// Increases the node counter by 1 after a new node is inserted into the binary tree.
//------------------------------------------------------------------------------------------------
void binaryTree::IncreaseNodeCount()
{
	_nodeCount++; //increase the node count by 1
}

//------------------------------------------------------------------------------------------------
// Method Name: DecreaseNodecount
// Description:
//
// Decreases the node counter by 1 after a node is removed from the binary tree.
//------------------------------------------------------------------------------------------------
void binaryTree::DecreaseNodecount()
{
	_nodeCount--; //decrease the node count by 1
}

//------------------------------------------------------------------------------------------------
// Method Name: IsTreeEmpty
// Description:
//
// Determines whether the provided node pointer is equal to nullptr. Returns true if the node is 
// empty and false otherwise.
//------------------------------------------------------------------------------------------------
bool binaryTree::IsTreeEmpty(node* pNode)
{
	return (pNode == nullptr);
}

//------------------------------------------------------------------------------------------------
// Method Name: GetRoot
// Description:
//
// Returns the root pointer of the binary tree.
//------------------------------------------------------------------------------------------------
node* binaryTree::GetRoot()
{
	return _pRoot;
}

//------------------------------------------------------------------------------------------------
// Method Name: FreeAllNodes
// Description:
//
// Recursively traverses the binary tree, deletes all dynamically allocated nodes, and decreases
//  the node counter as nodes are removed.
//------------------------------------------------------------------------------------------------
void binaryTree::FreeAllNodes(node* pCurrent)
{
	//Base case
	if (pCurrent == nullptr) return;

	//recursive case
	FreeAllNodes(pCurrent->pLeft);
	FreeAllNodes(pCurrent->pRight);

	//delete node
	delete pCurrent;
	DecreaseNodecount();
}

//------------------------------------------------------------------------------------------------
// Method Name: PreOrderSearch
// Description:
//
// Performs a recursive pre-order traversal of the binary tree and applies the provided function
// pointer to each visited node value. Initializes returnValue to the root's number to prevent
// incorrect comparisons against 0 when using function pointers such as Min.
//------------------------------------------------------------------------------------------------
int binaryTree::PreOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	// Initialize returnValue to -1 if tree is empty, or root's number if not
	static int returnValue = IsTreeEmpty(_pRoot) ? -1 : _pRoot->record.number;

	// Base case
	if (pCurrentNode == nullptr) return returnValue;

	// Pre-order: visit, left, right
	returnValue = func(returnValue, pCurrentNode->record.number);
	PreOrderSearch(pCurrentNode->pLeft, func);
	PreOrderSearch(pCurrentNode->pRight, func);

	return returnValue;
}

//------------------------------------------------------------------------------------------------
// Method Name: InOrderSearch
// Description:
//
// Performs a recursive in-order traversal of the binary tree and applies the provided function
// pointer to each visited node value. Initializes returnValue to the root's number to prevent
// incorrect comparisons against 0 when using function pointers such as Min.
//------------------------------------------------------------------------------------------------
int binaryTree::InOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	// Initialize returnValue to -1 if tree is empty, or root's number if not
	static int returnValue = IsTreeEmpty(_pRoot) ? -1 : _pRoot->record.number;

	// Base case
	if (pCurrentNode == nullptr) return returnValue;

	// In-order: left, visit, right
	InOrderSearch(pCurrentNode->pLeft, func);
	returnValue = func(returnValue, pCurrentNode->record.number);
	InOrderSearch(pCurrentNode->pRight, func);

	return returnValue;
}

//------------------------------------------------------------------------------------------------
// Method Name: PostOrderSearch
// Description:
//
// Performs a recursive post-order traversal of the binary tree and applies the provided function
// pointer to each visited node value. Initializes returnValue to the root's number to prevent
// incorrect comparisons against 0 when using function pointers such as Min.
//------------------------------------------------------------------------------------------------
int binaryTree::PostOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	// Initialize returnValue to -1 if tree is empty, or root's number if not
	static int returnValue = IsTreeEmpty(_pRoot) ? -1 : _pRoot->record.number;

	// Base case
	if (pCurrentNode == nullptr) return returnValue;

	// Post-order: left, right, visit
	PostOrderSearch(pCurrentNode->pLeft, func);
	PostOrderSearch(pCurrentNode->pRight, func);
	returnValue = func(returnValue, pCurrentNode->record.number);

	return returnValue;
}

//------------------------------------------------------------------------------------------------
// Method Name: PreOrderSearch
// Description:
//
// Performs a recursive pre-order traversal of the binary tree and writes each visited node value 
// to the output file stream.
//------------------------------------------------------------------------------------------------
void binaryTree::PreOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	//visit
	out << pCurrentNode->record.number << " ";

	//traverse
	PreOrderSearch(out, pCurrentNode->pLeft);
	PreOrderSearch(out, pCurrentNode->pRight);
}

//------------------------------------------------------------------------------------------------
// Method Name: InOrderSearch
// Description:
//
// Performs a recursive in-order traversal of the binary tree and writes each visited node value to 
// the output file stream.
//------------------------------------------------------------------------------------------------
void binaryTree::InOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	InOrderSearch(out, pCurrentNode->pLeft);

	//visit
	out << pCurrentNode->record.number << " ";

	InOrderSearch(out, pCurrentNode->pRight);
}

//------------------------------------------------------------------------------------------------
// Method Name: PostOrderSearch
// Description:
//
// Performs a recursive post-order traversal of the binary tree and writes each visited node value to 
// the output file stream.
//------------------------------------------------------------------------------------------------
void binaryTree::PostOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	PostOrderSearch(out, pCurrentNode->pLeft);
	PostOrderSearch(out, pCurrentNode->pRight);

	//visit
	out << pCurrentNode->record.number << " ";
}

//------------------------------------------------------------------------------------------------
// Method Name: InsertNode
// Description:
//
// Recursively searches for the correct location in the binary tree to insert a new node. After 
// insertion, the method recalculates and updates the height of each node while the recursion unwinds.
//------------------------------------------------------------------------------------------------
node* binaryTree::InsertNode(node* pCurrent, node* pNewNode)
{
	//Base Case
	if (pCurrent == nullptr) return pNewNode;

	// Recursive case
	if (pNewNode->record.number <= pCurrent->record.number)
	{
		pCurrent->pLeft = InsertNode(pCurrent->pLeft, pNewNode);
	}
	else
	{
		pCurrent->pRight = InsertNode(pCurrent->pRight, pNewNode);
	}

	//Update height
	int leftHeight = GetHeight(pCurrent->pLeft);
	int rightHeight = GetHeight(pCurrent->pRight);

	pCurrent->_height = Max(leftHeight, rightHeight) + 1;

	return pCurrent;
}

//------------------------------------------------------------------------------------------------
// Method Name: Insert
// Description:
//
// Inserts a new node into the binary tree by calling InsertNode, increases the node count, 
// updates the root height, and re-balances the AVL tree.
//------------------------------------------------------------------------------------------------
void binaryTree::Insert(node* pNewNode)
{
	//insert note into the tree
	_pRoot = InsertNode(_pRoot, pNewNode);

	//Increase node count
	IncreaseNodeCount();

	//reset height of the root
	if (_pRoot != nullptr)
	{
		int leftHeight = GetHeight(_pRoot->pLeft);
		int rightHeight = GetHeight(_pRoot->pRight);

		_pRoot->_height = Max(leftHeight, rightHeight) + 1;
	}

	//Rebalance tree
	RebalanceTree();
}

//------------------------------------------------------------------------------------------------
// Method Name: DeleteNode
// Description:
//
// Recursively searches the binary tree for a specified value and deletes the matching node. Handles 
// deletion cases for leaf nodes, nodes with one child, and nodes with two children. Updates node 
// heights while recursion unwinds.
//------------------------------------------------------------------------------------------------
node* binaryTree::DeleteNode(node* pCurrent, int valueToDelete)
{
	node* ptemp = nullptr;

	// The base case
	if (pCurrent == nullptr) return nullptr;

	//recursive search
	if (valueToDelete < pCurrent->record.number)
	{
		pCurrent->pLeft = DeleteNode(pCurrent->pLeft, valueToDelete);
	}
	else if (valueToDelete > pCurrent->record.number)
	{
		pCurrent->pRight = DeleteNode(pCurrent->pRight, valueToDelete);
	}
	else
	{
		// I FOUND THE NODE!

		// case 1: no children
		if (pCurrent->pLeft == nullptr && pCurrent->pRight == nullptr)
		{
			delete pCurrent;
			DecreaseNodecount();
			return nullptr;
		}

		// case 2: only the right child
		else if (pCurrent->pLeft == nullptr)
		{
			ptemp = pCurrent->pRight;
			delete pCurrent;
			DecreaseNodecount();
			return ptemp;
		}

		//case 3: only the left child
		else if (pCurrent->pRight == nullptr)
		{
			ptemp = pCurrent->pLeft;
			delete pCurrent;
			DecreaseNodecount();
			return ptemp;
		}

		//case 4: You have two children
		else
		{
			// Find smallest node in right subtree
			ptemp = pCurrent->pRight;
			while (ptemp->pLeft != nullptr)
			{
				ptemp = ptemp->pLeft;
			}

			//replace value
			pCurrent->record.number = ptemp->record.number;

			//Delete duplicate from right subtrees
			pCurrent->pRight = DeleteNode(pCurrent->pRight, ptemp->record.number);
		}
	}

	// update the height
	int leftHeight = GetHeight(pCurrent->pLeft);
	int rightHeight = GetHeight(pCurrent->pRight);
	pCurrent->_height = Max(leftHeight, rightHeight) + 1;

	return pCurrent;
}

//------------------------------------------------------------------------------------------------
// Method Name: Delete
// Description:
//
// Removes a specified value from the binary tree by calling DeleteNode, updates the root height, and 
// re-balances the AVL tree if necessary.
//------------------------------------------------------------------------------------------------
void binaryTree::Delete(int valueToDelete)
{
	_pRoot = DeleteNode(_pRoot, valueToDelete);

	if (_pRoot != nullptr)
	{
		int leftHeight = GetHeight(_pRoot->pLeft);
		int rightHeight = GetHeight(_pRoot->pRight);

		_pRoot->_height = Max(leftHeight, rightHeight) + 1;
	}

	RebalanceTree();
}

//------------------------------------------------------------------------------------------------
// Method Name: Max
// Description:
//
// Compares two integer values and returns the larger of the two.
//------------------------------------------------------------------------------------------------
int binaryTree::Max(int valueA, int valueB)
{
	return (valueA > valueB) ? valueA : valueB;
}

//------------------------------------------------------------------------------------------------
// Method Name: GetHeight
// Description:
//
// Returns the height of the specified node. If the node pointer is nullptr, the method returns 0.
//------------------------------------------------------------------------------------------------
int binaryTree::GetHeight(node* pNode)
{
	if (pNode == nullptr) return 0;

	return pNode->_height;
}

//------------------------------------------------------------------------------------------------
// Method Name: SetHeight
// Description:
//
// Assigns a new height value to the specified node if the node pointer is not equal to nullptr.
//------------------------------------------------------------------------------------------------
void binaryTree::SetHeight(node* pNode, int newHeight)
{
	if (pNode != nullptr)
		pNode->_height = newHeight;
}

//------------------------------------------------------------------------------------------------
// Method Name: BalanceFactor
// Description:
//
// Calculates the balance factor of a node by subtracting the height of the
// right subtree from the height of the left subtree.
//------------------------------------------------------------------------------------------------
int binaryTree::BalanceFactor(node* pNode)
{
	if (pNode == nullptr) return 0;

	int leftHeight = GetHeight(pNode->pLeft);
	int rightHeight = GetHeight(pNode->pRight);

	return leftHeight - rightHeight;
}

//------------------------------------------------------------------------------------------------
// Method Name: RebalanceTree
// Description:
//
// Checks the balance factor of the root node and performs AVL tree rotations when the tree becomes 
// left-heavy or right-heavy.
//------------------------------------------------------------------------------------------------

void binaryTree::RebalanceTree()
{
	if (_pRoot == nullptr) return;

	//left heavy
	if (BalanceFactor(_pRoot) > 1)
	{
		//left-right case
		if (BalanceFactor(_pRoot->pLeft) < 0)
		{
			_pRoot->pLeft = LeftRotate(_pRoot->pLeft);
		}

		_pRoot = RightRotate(_pRoot);
	}

	//Right heavy
	else if (BalanceFactor(_pRoot) < -1)
	{
		//right-left case
		if (BalanceFactor(_pRoot->pRight) > 0)
		{
			_pRoot->pRight = RightRotate(_pRoot->pRight);
		}

		_pRoot = LeftRotate(_pRoot);
	}
}

//------------------------------------------------------------------------------------------------
// Method Name: RightRotate
// Description:
//
// Performs a right rotation on the specified subtree, updates node heights, and returns the new root 
// of the rotated subtree.
//------------------------------------------------------------------------------------------------

node* binaryTree::RightRotate(node* pNode)
{
	//assign temp pointers
	node* pAlpha = pNode->pLeft;
	node* pBeta = pAlpha->pRight;

	//Rotate the nodes
	pAlpha->pRight = pNode;
	pNode->pLeft = pBeta;

	//update the heights
	SetHeight(pNode, 1 + Max(GetHeight(pNode->pLeft), GetHeight(pNode->pRight)));
	SetHeight(pAlpha, 1 + Max(GetHeight(pAlpha->pLeft), GetHeight(pAlpha->pRight)));

	//return the new root
	return pAlpha;
}

//------------------------------------------------------------------------------------------------
// Method Name: LeftRotate
// Description:
//
// Performs a left rotation on the specified subtree, updates node heights, and returns the new root 
// of the rotated subtree.
//------------------------------------------------------------------------------------------------
node* binaryTree::LeftRotate(node* pNode)
{
	//assign temp pointers
	node* pAlpha = pNode->pRight;
	node* pBeta = pAlpha->pLeft;

	//Rotate the nodes
	pAlpha->pLeft = pNode;
	pNode->pRight = pBeta;

	//Calculate the new heights
	SetHeight(pNode, 1 + Max(GetHeight(pNode->pLeft), GetHeight(pNode->pRight)));
	SetHeight(pAlpha, 1 + Max(GetHeight(pAlpha->pLeft), GetHeight(pAlpha->pRight))); 

	//return the new root
	return pAlpha;
}

