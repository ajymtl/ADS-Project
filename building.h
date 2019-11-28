#ifndef BUILDING_H
#define BUILDING_H
#include "redblacknode.h"

//Building class defining basic node structure of building
class building {
	private:
		void setBuilding(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn);
	public:
		long int m_buildingnum;
		long int m_executedtime;
		long int m_totaltime;
		redblacknode* m_rbn;
		building(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn);		
};
#endif