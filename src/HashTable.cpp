#include "HashTable.h"

HashTable::HashTable(std::string name)
{
    //ctor
    fileName = name;
    tableSize = 30;
    dataPercentage = 100;
    fileError = false;

    int power = int(log2(double(tableSize)));
    multiMConstant = pow(2, power);
    multiAConstant = 13.0 / 32.0;
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

int HashTable::multiHash (std::string inStr) {
    double sum = 0, dbl, rem;
    for (int i = 0; i < inStr.length(); i++) {
        sum += double(inStr.at(i));
    }
    dbl = sum * multiAConstant;
    rem = dbl - double(int(dbl));
    rem *= multiMConstant;
    return int(rem);
}

int HashTable::factoryHash (std::string hashType, std::string inStr) {
    if (hashType == "elf") {
        return elfHash(inStr);
    }
    else if (hashType == "sum") {
        return sumHash(inStr);
    }
    else if (hashType == "multiplication") {
        return multiHash(inStr);
    }
    else {
        return simpleHash(inStr);
    }
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
    std::cout << "=======================================================================" << std::endl;
	std::cout << "1. Set table size" << std::endl;
	std::cout << "2. Set sample size" << std::endl;
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

Result HashTable::testHash (std::string hashType) {
    clearTable();
    int collisions = 0
    , index
    , sampleSize = int((dataPercentage / 100) * movieVector.size())
    , indexesUsed = 0;

    for (int i = 0; i < sampleSize; i++) {
        index = factoryHash(hashType, movieVector[i].title);
        if (index > -1 && index < tableSize) {
            if (hashVector[index].size() > 0)
                collisions++;
            hashVector[index].push_back(movieVector[i]);
        }
    }

    for (int j = 0; j < tableSize; j++) {
        if (hashVector[j].size() > 0) indexesUsed++;
    }

    std::cout << "\tAlgorithm \""
    << hashType
    << "\": "
    << collisions
    << " collision(s), "
    << indexesUsed
    << "/"
    << tableSize
    << " indexes used"
    << std::endl;

    return Result(
        hashType
        , double(collisions) / double(sampleSize)
        , double(indexesUsed) / double(tableSize)
    );
}

void HashTable::runTests () {
    // Validate limits
    if (dataPercentage < 1 || dataPercentage > 100)
        dataPercentage = 100;
    if (tableSize == 0 || tableSize > 300)
        tableSize = 20;
    std::cout << std::endl;
    std::cout << "\tTotal # movies: " << movieVector.size() << std::endl;
    std::cout << "\tTable size: " << tableSize << std::endl;
    std::cout << "\tSample size percent: " << int(dataPercentage) << std::endl;
    std::cout << std::endl;

    std::string algs[4] = {"simple", "elf", "sum", "multiplication"};
    Result best, rtn;
    for (int i = 0; i < 4; i++) {
        rtn = testHash(algs[i]);
        if (i == 0 || rtn.overallScore > best.overallScore) {
            best = rtn;
        }
    }
    std::cout << std::endl;
    std::cout << "\tBest algorithm: " << best.algName << std::endl;
    std::cout << std::endl;
}

void HashTable::readData() {
    std::string lineStr;
    std::ifstream dataFile;
    dataFile.open(fileName.c_str());

    if (dataFile.fail()) {
        std::cout << "FILE ERROR" << std::endl;
        fileError = true;
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
    if (!fileError) {
        int opt;
        while ((opt = int(mainMenu())) != 4) {
            switch (opt) {
                case 1:
                    tableSize = int(getDouble("Integer: "));
                    break;
                case 2:
                    dataPercentage = getDouble("Percent: ");
                    break;
                case 3:
                    runTests();
                    break;
            }
        }
    }
    std::cout << "Goodbye!" << std::endl;
}
