#include "utilities.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;


vector<string> split(const string& line, char c) {
	// Return a vector of strings that were separated by the character c in line
	vector<string> v_strings;
	stringstream ss(line);
	string item;
	while (getline(ss, item, c)) {
		if (item[0] != 'v' && item[0] != 'f' && item[0] != 'm' && item[0] != 'u' && item[0] != 'n' && item[0] != 'N' && item[0] != 'K' && item[0] != 'm') {
			if (c == ' ' && item.size() != 0) {
				v_strings.push_back(item);
			}
			if (c == '/') { // with '/' we want to keep void elements
				v_strings.push_back(item);
			}
		}
	}
	return v_strings;
}
