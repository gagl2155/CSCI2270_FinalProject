#include "HashTable.h"

bool compareByMovie (const Movie& lhs, const Movie& rhs) {
    return lhs.title < rhs.title;
}

HashTable::HashTable(std::string name)
{
    //ctor
    fileName = name;
    tableSize = 30;
    dataPercentage = 100;
}

HashTable::~HashTable()
{
    //dtor
}

// Hashing function - given string returns an index
int HashTable::sumHash(std::string inStr) {
    int sum = 0;
    for (int i = 0; i < inStr.length(); i++) {
        sum += int(inStr.at(i));
    }
    return sum % tableSize;
}

// Hashing function - given string returns an index
int HashTable::simpleHash(std::string inStr) {
    return inStr.length() % tableSize;
}

int HashTable::elfHash (std::string inStr) {
    int hashValue = 0;
    for (int pos = 0; pos < inStr.length(); pos++) {
        hashValue = (hashValue << 4) + inStr.at(pos);
        int hiBits = hashValue & 0xF0000000;
        if (hiBits != 0)
            hashValue ^= hashValue >> 24;
        hashValue &= ~hiBits;
    }
    return hashValue % tableSize;
}

std::string HashTable::getStr (std::string strMsg) {
    if (strMsg != "")
        std::cout << strMsg << std::endl;
	std::string input;
	getline(std::cin, input);
	return input;
}

double HashTable::getDouble (std::string strMsg) {
    if (strMsg != "")
        std::cout << strMsg << std::endl;
	std::string input;
	getline(std::cin, input);
	return atof(input.c_str());
}

int HashTable::mainMenu () {
    std::cout << "======Main Menu======" << std::endl;
	std::cout << "1. Set table size" << std::endl;
	std::cout << "2. Set data percent" << std::endl;
	std::cout << "3. Run tests" << std::endl;
	std::cout << "4. Quit" << std::endl;
	return getDouble("");
}

void HashTable::clearTable () {
    hashVector.clear();
    for (int i = 0; i < tableSize; i++) {
        hashVector.push_back(std::vector<Movie>());
    }
}

void HashTable::testHash (std::string hashType) {
    clearTable();
    int collisions = 0
    , index
    , sampleSize = int((dataPercentage / 100) * movieVector.size())
    , indexesUsed = 0;

    for (int i = 0; i < sampleSize; i++) {
        if (hashType == "simple")
            index = simpleHash(movieVector[i].title);
        else if (hashType == "elf")
            index = elfHash(movieVector[i].title);
        else
            index = sumHash(movieVector[i].title);

        if (index > -1 && index < tableSize) {
            if (hashVector[index].size() > 0)
                collisions++;
            hashVector[index].push_back(movieVector[i]);
            // std::sort(hashVector[index].begin(), hashVector[index].end(), compareByMovie);
        }
    }

    for (int j = 0; j < tableSize; j++) {
        if (hashVector[j].size() > 0) indexesUsed++;
    }

    std::cout << "Algorithm \""
    << hashType
    << "\": "
    << collisions
    << " collision(s), "
    << indexesUsed
    << "/"
    << tableSize
    << " indexes used in table ("
    << int(dataPercentage)
    << "% of data)"
    << std::endl;
}

void HashTable::runTests () {
    // Validate limits
    if (dataPercentage < 1 || dataPercentage > 100)
        dataPercentage = 100;
    if (tableSize == 0 || tableSize > 300)
        tableSize = 20;
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Total movies: " << movieVector.size() << std::endl;
    std::cout << "Table size: " << tableSize << std::endl;
    std::cout << "Sample size percent: " << int(dataPercentage) << std::endl;
    std::cout << "-------------------------------------------------------------" << std::endl;

    // Simple hash
    testHash("simple");
    // Elf hash
    testHash("elf");
    // Sum hash
    testHash("sum");
}

void HashTable::readData() {
    std::string lineStr;
    std::ifstream dataFile;
    dataFile.open(fileName.c_str());

    if (dataFile.fail()) {
        std::cout << "ERROR" << std::endl;
    }
    else {
        int lineIx = 0, year;
        size_t firstComma;
        std::string title;

        while (!dataFile.eof()) {
            getline(dataFile, lineStr);
            if (lineStr == "") {
                continue;
            }
            firstComma = lineStr.find(",");
            title = lineStr.substr(0, firstComma);
            year = atoi( lineStr.substr(firstComma + 1, lineStr.length()).c_str() );

            Movie newMov (title, year);
            movieVector.push_back(newMov);
        }
    }
}

void HashTable::run() {
    readData();
    int opt;
    while ((opt = int(mainMenu())) != 4) {
        switch (opt) {
            case 1:
                tableSize = int(getDouble("Number: "));
                break;
            case 2:
                dataPercentage = getDouble("Percent: ");
                break;
            case 3:
                runTests();
                break;
        }
    }
    std::cout << "Goodbye!" << std::endl;
}
