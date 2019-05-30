#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> t;
	for (auto& e : a)
		t.Insert(e);

	t.InOrder();
	cout << endl;

	BSTNode<int>* pNode = t.Find(9);
	if (pNode){
		cout << "9 is in BSTree" << endl;
	}
	else{
		cout << "9 is not in BSTree" << endl;
	}

	t.Erase(6);
	t.InOrder();
	cout << endl;
	t.Erase(8);
	t.InOrder();
	cout << endl;
	t.Erase(5);
	t.InOrder();

	return 0;
}
