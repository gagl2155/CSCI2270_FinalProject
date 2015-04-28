#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Name of the text file to use
    string fileName = argv[1];
    // Start the HashTable program
    HashTable ht (fileName);
    ht.run();
    return 0;
}
