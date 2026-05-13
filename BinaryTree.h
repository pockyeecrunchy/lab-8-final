#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Standard.h"

// Record structure
struct recordType
{
    int number;
};

// Node structure
struct node
{
    recordType record;
    node* pLeft;
    node* pRight;
    int _height;
};

class binaryTree
{
private:
    node* _pRoot;
    int _nodeCount;

    //the private methods
    node* InsertNode(node* pCurrent, node* pNewNode);
    node* DeleteNode(node* pCurrent, int numberToDelete);

    int Max(int valueA, int valueB);
    int GetHeight(node* pNode);
    void SetHeight(node* pNode, int newHeight);
    void IncreaseNodeCount();
    void DecreaseNodecount();

    int BalanceFactor(node* pNode);
    void RebalanceTree();

    node* RightRotate(node* pNode);
    node* LeftRotate(node* pNode);

    void FreeAllNodes(node* pCurrent);

public:

    binaryTree(); //constructor
    ~binaryTree(); //destructor

    int GetNodeCount();
    bool IsTreeEmpty(node* pNode);
    node* GetRoot();

    //traversals
    int PreOrderSearch(node* pCurrentNode, int (*func) (int valueA, int valueB));
    int InOrderSearch(node* pCurrentNode, int (*func) (int valueA, int valueB));
    int PostOrderSearch(node* pCurrentNode, int (*func) (int valueA, int valueB));

    void PreOrderSearch(ofstream& out, node* pCurrentNode);
    void InOrderSearch(ofstream& out, node* pCurrentNode);
    void PostOrderSearch(ofstream& out, node* pCurrentNode);

    void Insert(node* pNewNode);
    void Delete(int valueToDelete);
};

#endif 
