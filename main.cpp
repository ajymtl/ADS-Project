// Main function.
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

#include "building.h"
#include "minheap.h"
#include "redblacknode.h"
#include "redblacktree.h"

using namespace std;

//processes a command from input file.
void processCommand(string command, string args, minheap* mh, redblacktree* rbt, ofstream& outfile) {
	if (command == "Insert") { //handles insert commands from the input file 
		long int buildingNum,totalTime;
		regex re("(.*),(.*)");
		if (regex_match(args, re)) {
			for (smatch m; regex_search(args, m, re); args = m.suffix()) {
				buildingNum = stol(m.str(1));
				totalTime = stol(m.str(2));
			}
			redblacknode* rbn = new redblacknode(buildingNum, 0, totalTime, 1, nullptr, rbt->external, rbt->external);
			rbt->insert(rbn);

			building* B = new building(buildingNum,0,totalTime,rbn);
			mh->insert(B);
		}
	} else if (command == "PrintBuilding") { //handles print commands from the input file		
		long int b1 = -1;
		long int b2 = -1;
		regex re("(.*),(.*)");
		if (regex_match(args, re)) { // case: print building with 2 args
			for (smatch m; regex_search(args, m, re); args = m.suffix()) {
				b1 = stol(m.str(1));
				b2 = stol(m.str(2));
			}
			vector<redblacknode*>* list = new vector<redblacknode*>;
			rbt->searchTreeBetween(b1, b2, list);
			int list_size = list->size();
			int i;
			for (i = 0; i < list_size-1; i++) {
				outfile << "(" << list->at(i)->m_buildingnum << "," << list->at(i)->m_executedtime << "," << list->at(i)->m_totaltime << ")" << ",";
			}
	
			if (list_size == 0) {
				outfile << "(" << 0 << "," << 0 << "," << 0 << ")" ;
			}
			else {
				outfile << "(" << list->at(i)->m_buildingnum << "," << list->at(i)->m_executedtime << "," << list->at(i)->m_totaltime << ")";
			}
			outfile << endl;
		} else { //case: print building with one arg
			b1 = stol(args);
			redblacknode* searchnode = rbt->searchTree(b1);
			if (searchnode->m_buildingnum == -1) {
				outfile << "(" << 0 << "," << 0 << "," << 0 << ")" << endl;
			}
			else {
				outfile << "(" << searchnode->m_buildingnum << "," << searchnode->m_executedtime << "," << searchnode->m_totaltime << ")" << endl;
			}
		}
	}
}

int work(int argc, char** argv) {
	if (argc != 2) {
		cout << "ERROR: No file provided.";
		return 1;
	}
	minheap* mh = new minheap;	//initializing minheap
	redblacktree* rbt = new redblacktree();	//initializing redblacktree

	vector<string> lines;
	string line = "";
	ifstream infile(argv[1]);
	if(!infile) {
		cout << "Cannot open input file.\n";
		return 1;
	}	
	while (getline(infile, line)) {//reading file in a input array of strings
		lines.push_back(line);
	}
	infile.close();	

	ofstream outfile;
	outfile.open("output_file.txt");

	int input_size = lines.size();
	
	long int line_num=0;	
	building* current=nullptr;
	int kill_loop = 0;	//loop kill flag
	long int time = 0;	//global time counter	
	int work_done = 0;	//work done each iteration, max = 5
	bool wayne_busy = false;	//if industry busy flag

	regex re("(.*): (.*)\\((.*)\\)"); // regex to split the input line in commandtime, command and args.
	long int commandtime = -1;
	string command;
	string args;	

	while(!kill_loop) {
		string line = "-1: Break()";
		if (line_num != input_size) {
			line = lines[line_num];
		}
		if (regex_match(line, re)) {

			for (smatch m; regex_search(line, m, re); line = m.suffix()) {
				commandtime = stol(m.str(1));
				command = m.str(2);
				args = m.str(3);
			}
			while (commandtime != time) {
				if((current!=nullptr) && (current->m_executedtime == current->m_totaltime)) { //case: building completed
					wayne_busy = false;
					outfile<< "(" << current->m_buildingnum << "," << time << ")" << endl;
					rbt->deleteNode(current->m_rbn);
					current = nullptr;
					if ((mh->tail == 0) && (commandtime == -1)) {
						kill_loop = 1;
						break;
					}
				} else if (current!=nullptr && work_done == 5) { //case: 5 units work is done.
					wayne_busy = false;
					mh->insert(current);
				} else if (current != nullptr) { //case: routine daily work of wayne industries
					work_done++;
					current->m_executedtime++;
					current->m_rbn->m_executedtime++;
				}	
				if(!wayne_busy && mh->tail!=0) { //case: industry free, pick new work.
					work_done = 0;
					wayne_busy = true;
					current = mh->getMin();
					mh->deleteMin();
					current->m_executedtime++;
					current->m_rbn->m_executedtime++;
					work_done ++;
				}
				time++;
			}
		    processCommand(command, args, mh, rbt, outfile);
			line_num++;
		}
		else {
			cout << "ERROR: Incompatible input format. Try dos2unix to convert input file to unix compatible format";
			return 1;
		}
	}
	outfile.close();
	return 0;
}

int main(int argc, char** argv) {
	int output = work(argc, argv);
	return output;
}
