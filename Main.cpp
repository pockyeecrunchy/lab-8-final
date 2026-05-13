#include "BinaryTree.h"
#include "Functions.h"
#include "Standard.h"


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

	fin.open("Numbers.txt");
	outPre.open("PreOrder.txt");
	outIn.open("InOrder.txt");
	outPost.open("PostOrder.txt");

	if (!fin || !outPre || !outIn || !outPost)
	{
		cout << "There is an error opening the files!\n";
		return 1;
	}

	//read data into tree
	ReadInData(fin, tree);

	// Print traversals
	tree.PreOrderSearch(outPre, tree.GetRoot());
	tree.InOrderSearch(outIn, tree.GetRoot());
	tree.PostOrderSearch(outPost, tree.GetRoot());

	// MAX FUNCTION
	funcPtr = Max;

	int maxPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	int maxIn = tree.InOrderSearch(tree.GetRoot(), funcPtr);
	int maxPost = tree.PostOrderSearch(tree.GetRoot(), funcPtr);

	outPre << "\nMax:" << maxPre;
	outIn << "\nMax: " << maxIn;
	outPost << "\nMax:" << maxPost;

	// MIN FUNCTION
	funcPtr = Min;

	int minPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	int minIn = tree.InOrderSearch(tree.GetRoot(), funcPtr);
	int minPost = tree.PostOrderSearch(tree.GetRoot(), funcPtr);

	outPre << "\nMin:" << minPre;
	outIn << "\nMin:" << minIn;
	outPost << "\nMin:" << minPost;

	//Node count
	outPre << "\nNode Count: " << tree.GetNodeCount();
	outIn << "\nNode Count: " << tree.GetNodeCount();
	outPost << "\nNode Count: " << tree.GetNodeCount();

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

	tree.PreOrderSearch(outPre, tree.GetRoot());
	tree.InOrderSearch(outIn, tree.GetRoot());
	tree.PostOrderSearch(outPost, tree.GetRoot());

	// recalculate the min
	funcPtr = Min;
	minPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);

	// recalculate the max
	funcPtr = Max;
	maxPre = tree.PreOrderSearch(tree.GetRoot(), funcPtr);
	
	//node count again
	outPre << "\nNode Count: " << tree.GetNodeCount();
	outIn << "\nNode Count: " << tree.GetNodeCount();
	outPost << "\nNode Count: " << tree.GetNodeCount();

	//close all of the files
	fin.close();
	outPre.close();
	outIn.close();
	outPost.close();

	return 0;
}