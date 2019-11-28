#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <vector>
#include "redblacknode.h"
using namespace std;

//redblacktree class: defines all functionalities of a redblack tree.
class redblacktree {
	private:
		void fixDelete(redblacknode* node);
		void rbTransplant(redblacknode* node_a, redblacknode* node_b);
		void fixInsert(redblacknode* node);
		redblacknode* searchTreeHelper(redblacknode* node, long int key);
		void leftRotate(redblacknode* node);
		void rightRotate(redblacknode* node);
		redblacknode* minimum(redblacknode* node);
		void searchTreeBetweenHelper(redblacknode* node, long int building1, long int building2, vector<redblacknode*>* list);
	public:
		redblacknode* root;	
		redblacknode* external;
		redblacktree();
		redblacknode* searchTree(long int buidingNum);
		void insert(redblacknode* node);
		void deleteNode(redblacknode* node);
		void searchTreeBetween(long int building1, long int building2, vector<redblacknode*>* list);
};
#endif