#include "redblacknode.h"

redblacknode::redblacknode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right) {
	setNode(buildingNum, executedTime, totalTime, color, parent, left, right);
}

void redblacknode::setNode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right) {
	m_buildingnum = buildingNum;
	m_executedtime = executedTime;
	m_totaltime = totalTime;
	m_color = color;
	m_parent = parent;
	m_left = left;
	m_right = right;
}