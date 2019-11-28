#include "minheap.h"
#include "building.h"

void minheap::heapDown(int index)
{
	int index_l_child = 2*index + 1;
	int index_r_child = 2*index + 2;
	if(index_l_child >= tail) {
		return;
	}
	int index_min = index;
	building current = *m_heap[index];
	building lchild = *m_heap[index_l_child];
	building rchild = *m_heap[index_r_child];
	if(current.m_executedtime > lchild.m_executedtime)
	{
		index_min = index_l_child;
		current = lchild;
	}
	else if(current.m_executedtime == lchild.m_executedtime) {
		if (current.m_buildingnum > lchild.m_buildingnum) {
			index_min = index_l_child;
			current = lchild;
		}
	}
	if ((index_r_child < tail) && (current.m_executedtime > rchild.m_executedtime)) {
		index_min = index_r_child;
	} else if (current.m_executedtime == rchild.m_executedtime) {
		if (current.m_buildingnum > rchild.m_buildingnum) {
			index_min = index_r_child;
		}
	}
	if(index_min != index)
	{
		building* temp = m_heap[index];
		m_heap[index] = m_heap[index_min];
		m_heap[index_min] = temp;
		heapDown(index_min);
	}
}

void minheap::heapUp(int index)
{
	if (index == 0) {
		return;
	}
	int index_parent = (index-1)/2;
	building parent = *m_heap[index_parent];
	building current = *m_heap[index];
    if(parent.m_executedtime > current.m_executedtime)
    {
        building* temp = m_heap[index_parent];
        m_heap[index_parent] = m_heap[index];
        m_heap[index] = temp;
        heapUp(index_parent);
    } 
    else if (parent.m_executedtime == current.m_executedtime) {
		if (parent.m_buildingnum > current.m_buildingnum) {
		building* temp = m_heap[index_parent];
		m_heap[index_parent] = m_heap[index];
		m_heap[index] = temp;
		heapUp(index_parent);
		}
    }
}

void minheap::insert(building* value)
{
	m_heap[tail] = value;
	heapUp(tail);
	tail++;
}

building* minheap::getMin()
{
	return m_heap[0];
}

void minheap::deleteMin()
{
	if(tail == 0)
	{
		return;
	}	
	m_heap[0] = m_heap[tail-1];
	tail--;
	heapDown(0);
}