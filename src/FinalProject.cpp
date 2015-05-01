#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main(int argc, char* argv[]) {
	// Requires string filename
	if (argc > 1 && string(argv[1]) != "") {
	    // Name of the text file to use
	    string fileName = argv[1];
	    // Start the HashTable program
	    HashTable ht (fileName);
	    ht.run();
	}
	else {
		cout << "ERROR. Missing file name as parameter" << endl;
	}
    return 0;
}
