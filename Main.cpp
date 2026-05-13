#include "BinaryTree.h"
#include "Functions.h"
#include "Standard.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// Students Name: Oscar Lan
// Course: CST-202: Data Structures
// Program Name: Module 8 Lab - Binary Tree
// Date: May 12, 2026
//
//-------------------------------------------------------------------------------------------------
// Program Description:
// 
// This program implements a Binary Search Tree and extends it into an AVL Tree using recursive 
// algorithms, dynamic memory allocation, and tree balancing rotations. The program reads integer 
// data from an input file, inserts the values into the tree structure, performs tree traversals,
// calculates minimum and maximum values using function pointers, deletes selected nodes, and 
// re-balances the tree after modifications.
//
//-------------------------------------------------------------------------------------------------
// Inputs:
// 
// - Integer values read from Numbers.txt
// - User-defined tree operations and traversal functions
//
//-------------------------------------------------------------------------------------------------
// Processing:
// 
// - Create nodes dynamically using pointers
// - Insert nodes recursively into the binary tree
// - Maintain AVL tree heights and balance factors
// - Perform left and right tree rotations when necessary
// - Traverse the tree using pre-order, in-order, and post-order recursion
// - Calculate minimum and maximum values using function pointers
// - Delete selected nodes and re-balance the tree
// - Track and display the total node count
//
//-------------------------------------------------------------------------------------------------
// Outputs:
// 
// - Tree traversal results written to output files
// - Minimum and maximum values found in the tree
// - Updated traversal results after deletions
// - Node count displayed on the screen and output files
//
///////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	// Memory leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// create the tree
	binaryTree tree;

	//Function pointer
	int (*funcPtr)(int, int) = nullptr;

	//File streams
	ifstream fin;
	ofstream outPre, outIn, outPost;

	// Open all required input and output files
	fin.open("Numbers.txt");
	outPre.open("PreOrder.txt");
	outIn.open("InOrder.txt");
	outPost.open("PostOrder.txt");

	// Verify that all files opened successfully
	if (!fin || !outPre || !outIn || !outPost)
	{
		cout << "There is an error opening the files!\n";
		return 1;
	}

	// Print the lab header to the screen and all three output files
	PrintHeader(cout, DASH);
	PrintHeader(outPre, DASH);
	PrintHeader(outIn, DASH);
	PrintHeader(outPost, DASH);

	// Read integer values from the input file and insert them into the tree
	ReadInData(fin, tree); 

	// Display the current node count to the screen for debugging purposes
	cout << "Node Count: " << tree.GetNodeCount() << "\n"; //Node count to screen 

	// Perform and print all three tree traversals
	tree.PreOrderSearch(outPre, tree.GetRoot());
	tree.InOrderSearch(outIn, tree.GetRoot());
	tree.PostOrderSearch(outPost, tree.GetRoot());

	// Set the function pointer to the Max function
	funcPtr = Max;

	// Find the maximum value using all three traversal methods
	int maxPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	int maxIn = tree.InOrderSearch(tree.GetRoot(), funcPtr);
	int maxPost = tree.PostOrderSearch(tree.GetRoot(), funcPtr);
	
	// Output the maximum values to their respective files
	outPre << "\nMax:" << maxPre;
	outIn << "\nMax: " << maxIn;
	outPost << "\nMax:" << maxPost;

	// Set the function pointer to the Min function
	funcPtr = Min;

	// Find the minimum value using all three traversal methods
	int minPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	int minIn = tree.InOrderSearch(tree.GetRoot(), funcPtr);
	int minPost = tree.PostOrderSearch(tree.GetRoot(), funcPtr);

	// Output the minimum values to their respective files
	outPre << "\nMin:" << minPre;
	outIn << "\nMin:" << minIn;
	outPost << "\nMin:" << minPost;

	// Output the current node count to all traversal files
	outPre << "\nNode Count: " << tree.GetNodeCount();
	outIn << "\nNode Count: " << tree.GetNodeCount();
	outPost << "\nNode Count: " << tree.GetNodeCount();

	// Delete the minimum value, maximum value, and additional specified nodes
	tree.Delete(minPre); 	//Delete the min value
	tree.Delete(maxPre);	//Delete the max value
	tree.Delete(5);			//Delete 5
	tree.Delete(15);		//Delete 15
	tree.Delete(48);		//Delete 48
	tree.Delete(37);		//Delete 37
	tree.Delete(31);		//Delete 31

	//Print the trees again after the deletion
	outPre << "\n\nAfter Deletion:\n";
	outIn << "\n\nAfter Deletion:\n";
	outPost << "\n\nAfter Deletion:\n";

	// Print the updated tree traversals after node deletions
	tree.PreOrderSearch(outPre, tree.GetRoot());
	tree.InOrderSearch(outIn, tree.GetRoot());
	tree.PostOrderSearch(outPost, tree.GetRoot());

	// Recalculate the minimum value after deletions
	funcPtr = Min;
	minPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);

	// Recalculate the maximum value after deletions
	funcPtr = Max;
	maxPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	
	// Output the updated node count after deletions
	outPre << "\nNode Count: " << tree.GetNodeCount();
	outIn << "\nNode Count: " << tree.GetNodeCount();
	outPost << "\nNode Count: " << tree.GetNodeCount();

	// Close all opened files before ending the program
	fin.close();
	outPre.close();
	outIn.close();
	outPost.close();

	return 0;
}