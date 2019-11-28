#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H

//class defining the structure of redblacktree node.
class redblacknode {
	private:
		void setNode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right);
	public:
		long int m_buildingnum;
		long int m_executedtime;
		long int m_totaltime;
		redblacknode* m_left;
		redblacknode* m_right;
		redblacknode* m_parent;
		int m_color; //red - 1, black - 0
		redblacknode(long int buildingNum, long int executedTime, long int totalTime, int color, redblacknode* parent, redblacknode* left, redblacknode* right);
};
#endif