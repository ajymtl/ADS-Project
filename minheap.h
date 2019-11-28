#ifndef MINHEAP_H
#define MINHEAP_H

#include "building.h"

const int MAX = 2000;

//Minheap class: Works on buildingnode.
class minheap {
	private:	
		void heapDown(int index); //called when a delete is called. heapifies a heap from top to bottom.
		void heapUp(int index); //called when an insert occurs. heapifies a heap from bottom up.
	public:
		building* m_heap[MAX];
		int tail = 0;
		void insert(building* value); //inserts a buildingnode at the end of active array and accordingly modifies the minheap array.
		building* getMin(); //returns min positioned building node.
		void deleteMin(); //deletes the min positioned building node and accordingly modifies the minheap array.
};
#endif