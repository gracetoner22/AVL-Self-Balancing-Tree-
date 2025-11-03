#include <iostream>
#include <sstream>
#include <string>
#include "AVL.h"
using namespace std;

int main(){
	AVLTree tree;
	std::string numCommands;
	std::getline(std::cin, numCommands);
	for (int i =0; i<std::stoi(numCommands); i++) {
		string line;
		std::getline(std::cin, line);
		std::istringstream iss(line);
		string function;
		getline(iss, function, ' ');
		string next;
		getline(iss, next, '"');
		string realName;
		getline(iss, realName, '"');
		string next2;
		getline(iss, next2, ' ');

		string realID;
		getline(iss, realID);

		if (function=="insert") {
			if (tree.insert(realName, realID)) {
				std::cout << "successful" << std::endl;
			} else {
				std::cout << "unsuccessful" << std::endl;
			}
		}
		else if (function == "remove") {
			if (tree.removeID(line.substr(7))) {
				std::cout << "successful" << std::endl;
			} else {
				std::cout << "unsuccessful" << std::endl;
			}
		}
		else if (function == "search"){
			int ind1 = line.find('\"');
			int ind2 = line.find('\"', ind1+1);
            if (ind1 != std::string::npos && ind2 != std::string::npos) {
	            tree.searchName(line.substr(ind1+1, ind2-ind1-1));
            }
				else {
					std::string ufid = line.substr(7);
					ufid.erase(ufid.find_last_not_of(' ') + 1);
					std::string thisUFID = tree.searchIDhelper(ufid);
					if (!thisUFID.empty()) {
						std::cout << thisUFID << std::endl;
					} else {
						std::cout << "unsuccessful" << std::endl;
					}
				}
		}
        else if (function =="printInorder") {
        	tree.actualInorder();
        }
		else if (function =="printPreorder") {
			tree.actualPreorder();
		}
		else if (function =="printPostorder") {
			tree.actualPostorder();
		}
		else if (function =="printLevelCount") {
			tree.actualLevelcount();
		}
		else if (function =="removeInorder") {
			tree.removeInorderN(stoi(line.substr(14)));
		}
		else {
			std::cout << "unsuccessful" << std::endl;
		}
	}
	return 0;
}
