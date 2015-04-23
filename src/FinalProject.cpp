#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

int main(int argc, char* argv[]) {
    string fileName = argv[1];
    HashTable ht (fileName);
    ht.run();
    return 0;
}
