#include "BinaryTree.h"
#include "Standard.h"

//Constructor method
binaryTree::binaryTree()
{
	_pRoot = nullptr;
	_nodeCount = 0;
}

//Destructor method
binaryTree::~binaryTree()
{
	FreeAllNodes(_pRoot);
	_pRoot = nullptr;
}

int binaryTree::GetNodeCount()
{
	return _nodeCount;
}

void binaryTree::IncreaseNodeCount()
{
	_nodeCount++; //increase the node count by 1
}

void binaryTree::DecreaseNodecount()
{
	_nodeCount--; //decrease the node count by 1
}

bool binaryTree::IsTreeEmpty(node* pNode)
{
	return (pNode == nullptr);
}

node* binaryTree::GetRoot()
{
	return _pRoot;
}

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

int binaryTree::PreOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	if (pCurrentNode == nullptr) return 0; //base value

	int result = pCurrentNode->record.number;

	result = func(result, PreOrderSearch(pCurrentNode->pLeft, func));
	result = func(result, PreOrderSearch(pCurrentNode->pRight, func));

	return result;
}

int binaryTree::InOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	if (pCurrentNode == nullptr) return 0; //base value

	int left = InOrderSearch(pCurrentNode->pLeft, func);
	int result = func(left, pCurrentNode->record.number);

	result = func(result, InOrderSearch(pCurrentNode->pRight, func));

	return result;
}

int binaryTree::PostOrderSearch(node* pCurrentNode, int (*func)(int valueA, int valueB))
{
	if (pCurrentNode == nullptr) return 0; //base case

	int result = PostOrderSearch(pCurrentNode->pLeft, func);
	result = func(result, PostOrderSearch(pCurrentNode->pRight, func));

	result = func(result, pCurrentNode->record.number);

	return result;
}

void binaryTree::PreOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	//visit
	out << pCurrentNode->record.number << " ";

	//traverse
	PreOrderSearch(out, pCurrentNode->pLeft);
	PreOrderSearch(out, pCurrentNode->pRight);
}

void binaryTree::InOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	InOrderSearch(out, pCurrentNode->pLeft);

	//visit
	out << pCurrentNode->record.number << " ";

	InOrderSearch(out, pCurrentNode->pRight);
}

void binaryTree::PostOrderSearch(ofstream& out, node* pCurrentNode)
{
	if (pCurrentNode == nullptr) return;

	PostOrderSearch(out, pCurrentNode->pLeft);
	PostOrderSearch(out, pCurrentNode->pRight);

	//visit
	out << pCurrentNode->record.number << " ";
}

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

int binaryTree::Max(int valueA, int valueB)
{
	return (valueA > valueB) ? valueA : valueB;
}

int binaryTree::GetHeight(node* pNode)
{
	if (pNode == nullptr) return 0;

	return pNode->_height;
}

void binaryTree::SetHeight(node* pNode, int newHeight)
{
	if (pNode != nullptr)
		pNode->_height = newHeight;
}

int binaryTree::BalanceFactor(node* pNode)
{
	if (pNode == nullptr) return 0;

	int leftHeight = GetHeight(pNode->pLeft);
	int rightHeight = GetHeight(pNode->pRight);

	return leftHeight - rightHeight;
}

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

