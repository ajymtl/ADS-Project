#include "building.h"

building::building(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn) {
	setBuilding(buildingNum, executedTime, totalTime, rbn);
}

void building::setBuilding(long int buildingNum, long int executedTime, long int totalTime, redblacknode* rbn) {
	m_buildingnum = buildingNum;
	m_executedtime = executedTime;
	m_totaltime = totalTime;
	m_rbn = rbn;
}