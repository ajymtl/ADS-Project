#include "redblacktree.h"

//constructor of rbt
redblacktree::redblacktree() {
	external = new redblacknode(-1,-1,-1,0,nullptr,nullptr,nullptr);
	root = external;
}

//called to enforce rbt properties once a delete and rbtransplant is done.
void redblacktree::fixDelete(redblacknode* node) {
	while (node != root && node->m_color == 0) {
		redblacknode* tempnode;
		if (node == node->m_parent->m_left) {
			tempnode = node->m_parent->m_right;
			if (tempnode->m_color == 1) {	//case 1 - node’s sibling is red
				tempnode->m_color = 0;
				node->m_parent->m_color = 1;
				leftRotate(node->m_parent);
				tempnode = node->m_parent->m_right;
			}
			if (tempnode->m_left->m_color == 0 && tempnode->m_right->m_color == 0) {	//case 2 - node’s sibling is black, and both of the sibling’s children are black.
				tempnode->m_color = 1;
				node = node->m_parent;
			} else {
				if (tempnode->m_right->m_color == 0) {	//case 3 - node’s sibling is black, sibling’s left child is red, and sibling’s right child is black.

					tempnode->m_left->m_color = 0;
					tempnode->m_color = 1;
					rightRotate(tempnode);
					tempnode = node->m_parent->m_right;
				} 
				tempnode->m_color = node->m_parent->m_color;	//case 4 - node’s sibling is black, and sibling’s right child is red.
				node->m_parent->m_color = 0;
				tempnode->m_right->m_color = 0;
				leftRotate(node->m_parent);
				node = root;
			}
		} else {
			tempnode = node->m_parent->m_left;
			if (tempnode->m_color == 1) {	//case 1
				tempnode->m_color = 0;
				node->m_parent->m_color = 1;
				rightRotate(node->m_parent);
				tempnode = node->m_parent->m_left;
			}
			if (tempnode->m_left->m_color == 0 && tempnode->m_right->m_color == 0) {	//case 2
				tempnode->m_color = 1;
				node = node->m_parent;
			} else {
				if (tempnode->m_left->m_color == 0) {	//case 3
					tempnode->m_right->m_color = 0;						
					tempnode->m_color = 1;
					leftRotate(tempnode);
					tempnode = node->m_parent->m_left;
				} 
				tempnode->m_color = node->m_parent->m_color;	//case 4
				node->m_parent->m_color = 0;
				tempnode->m_left->m_color = 0;
				rightRotate(node->m_parent);
				node = root;
			}
		} 
	}
	node->m_color = 0;
}

//upon deletion of a arbitrary node delete, joins the child of node(if any) with its parents(if any).
void redblacktree::rbTransplant(redblacknode* node1, redblacknode* node2){
	if (node1->m_parent == external) {
		root = node2;
	} else if (node1 == node1->m_parent->m_left){
		node1->m_parent->m_left = node2;
	} else {
		node1->m_parent->m_right = node2;
	}
	node2->m_parent = node1->m_parent;
}

//given a node, deletes a node from rbtree.
void redblacktree::deleteNode(redblacknode* node) {
	redblacknode *node1,*node2;
	node2 = node;
	int original_color = node2->m_color;	
	if (node->m_left == external) {
		node1 = node->m_right;
		rbTransplant(node, node->m_right);
	} else if (node->m_right == external) {
		node1 = node->m_left;
		rbTransplant(node, node->m_left);
	} else {
		node2 = minimum(node->m_right);
		original_color = node2->m_color;
		node1 = node2->m_right;
		if (node2->m_parent == node) {
			node1->m_parent = node2;
		} else {
			rbTransplant(node2, node2->m_right);
			node2->m_right = node->m_right;
			node2->m_right->m_parent = node2;
		}
		rbTransplant(node, node2);
		node2->m_left = node->m_left;
		node2->m_left->m_parent = node2;
		node2->m_color = node->m_color;
	}
	if (original_color == 0){
		fixDelete(node1);
	}
}

//called to enforce rbt properties once a insert is done.
void redblacktree::fixInsert(redblacknode* node){
	redblacknode* tempnode;
	while (node->m_parent->m_color == 1) {
		if (node->m_parent == node->m_parent->m_parent->m_left) {
			tempnode = node->m_parent->m_parent->m_right;
			if (tempnode->m_color == 1) {	//case 1 - node’s uncle is red.
				tempnode->m_color = 0;
				node->m_parent->m_color = 0;
				node->m_parent->m_parent->m_color = 1;
				node = node->m_parent->m_parent;				
			} else {	
				if (node == node->m_parent->m_right) {	//case 2 - node’s uncle is black and node is a right child.
					node = node->m_parent;
					leftRotate(node);
				}
				node->m_parent->m_color = 0;	//case 3 - node’s uncle is black and node is a left child.
				node->m_parent->m_parent->m_color = 1;
				rightRotate(node->m_parent->m_parent);
			
			}
		} else {
			tempnode = node->m_parent->m_parent->m_left;
			if (tempnode->m_color == 1) {	//case 1
				tempnode->m_color = 0;
				node->m_parent->m_color = 0;
				node->m_parent->m_parent->m_color = 1;
				node = node->m_parent->m_parent;
			} else {
				if (node == node->m_parent->m_left) {	//case 2
					node = node->m_parent;
					rightRotate(node);
				}
				node->m_parent->m_color = 0;	//case 3
				node->m_parent->m_parent->m_color = 1;
				leftRotate(node->m_parent->m_parent);
			}
		}
	}
	root->m_color = 0;
}

//left rotation.
void redblacktree::leftRotate(redblacknode* node) {
	redblacknode* tempnode = node->m_right;
	node->m_right = tempnode->m_left;
	if (tempnode->m_left != external) {
		tempnode->m_left->m_parent = node;
	}
	tempnode->m_parent = node->m_parent;
	if (node->m_parent == external) {
		root = tempnode;
	} else if (node == node->m_parent->m_left) {
		node->m_parent->m_left = tempnode;
	} else {
		node->m_parent->m_right = tempnode;
	}
	tempnode->m_left = node;
	node->m_parent = tempnode;
}

//rightrotation.
void redblacktree::rightRotate(redblacknode* node) {
	redblacknode* tempnode = node->m_left;
	node->m_left = tempnode->m_right;
	if (tempnode->m_right != external) {
		tempnode->m_right->m_parent = node;
	}
	tempnode->m_parent = node->m_parent;
	if (node->m_parent == external) {
		root = tempnode;
	} else if (node == node->m_parent->m_right) {
		node->m_parent->m_right = tempnode;
	} else {
		node->m_parent->m_left = tempnode;
	}
	tempnode->m_right = node;
	node->m_parent = tempnode;
}

//inserts a node in the rbt.
void redblacktree::insert(redblacknode* node) {
	redblacknode* node1 = external;
	redblacknode* node2 = root;
	while (node2 != external) {
		node1 = node2;
		if (node->m_buildingnum < node2->m_buildingnum) {
			node2 = node2->m_left;
		} else {
			node2 = node2->m_right;
		}
	}
	node->m_parent = node1;
	if (node1 == external) {
		root = node;
	} else if (node->m_buildingnum < node1->m_buildingnum) {
		node1->m_left = node;
	} else {
		node1->m_right = node;
	}
	node->m_left = external;
	node->m_right = external;
	node->m_color = 1;
	fixInsert(node);
}

//returns the leftmost node
redblacknode* redblacktree::minimum(redblacknode* node) {
	while (node->m_left != external) {
		node = node->m_left;
	}
	return node;
}

redblacknode* redblacktree::searchTreeHelper(redblacknode* node, long int key) {
	if (node == external || key == node->m_buildingnum) {
		return node;
	}
	if (key < node->m_buildingnum) {
		return searchTreeHelper(node->m_left, key);
	} 
	return searchTreeHelper(node->m_right, key);
}

//searches a key in rbt and returns the corresponding redblacknode.
redblacknode* redblacktree::searchTree(long int key) {
	return searchTreeHelper(root, key);
}

void redblacktree::searchTreeBetweenHelper(redblacknode* node, long int building1, long int building2, vector<redblacknode*>* list) {
	if (!((node == external) || (node == nullptr))) {
		if (!(node->m_buildingnum < building1)) {
			searchTreeBetweenHelper(node->m_left, building1, building2, list);
		}
		if ((node->m_buildingnum >= building1) and (node->m_buildingnum <= building2)) {
			list->push_back(node);
		}
		if (!(node->m_buildingnum > building2)) {
			searchTreeBetweenHelper(node->m_right, building1, building2, list);
		}
	}
}

//returns all redblacknodes in a given range b1 and b2 (both included).
void redblacktree::searchTreeBetween(long int building1, long int building2, vector<redblacknode*>* list) {
	searchTreeBetweenHelper(root, building1, building2, list);
}
