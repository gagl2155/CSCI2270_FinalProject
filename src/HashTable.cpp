#include "HashTable.h"

/**
 * Function prototype:
 * HashTable::HashTable(std::string);
 *
 * Function description:
 * Constructor of HashTable. Accepts the string name of the file to read, and initializes other class variables.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 *
 * Pre-conditions: valid file name string
 * Post-conditions: tableSize and dataPercentage defaulted, fileError and fileName set
 */
HashTable::HashTable(std::string name)
{
    //ctor
    fileName = name;
    tableSize = 30;
    dataPercentage = 100;
    fileError = false;
    multiAConstant = 13.0 / 32.0;
    multiMConstant = 1;
}

HashTable::~HashTable()
{
    //dtor
}

/**
 * Function prototype:
 * int HashTable::sumHash(std::string);
 *
 * Function description:
 * Performs a hash of a string based off summing the ascii values of the string.
 * Returns the sum % the size of the table (an integer).
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.sumHash("string");
 *
 * Pre-conditions: valid input string, string not empty, tableSize > 0
 * Post-conditions: returns index >= 0
 */
int HashTable::sumHash(std::string inStr) {
    int sum = 0;
    for (int i = 0; i < inStr.length(); i++) {
        sum += int(inStr.at(i));
    }
    return sum % tableSize;
}

/**
 * Function prototype:
 * int HashTable::simpleHash(std::string);
 *
 * Function description:
 * Performs a basic hashing of a string, based off the length of the string.
 * Returns the length % the size of the table (an integer).
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.simpleHash("string");
 *
 * Pre-conditions: valid input string, string not empty, tableSize > 0
 * Post-conditions: returns index >= 0
 */
int HashTable::simpleHash(std::string inStr) {
    return inStr.length() % tableSize;
}

/**
 * Function prototype:
 * int HashTable::elfHash(std::string);
 *
 * Function description:
 * Performs a more complex hashing algorithm.
 * See: http://courses.cs.vt.edu/~cs3114/Summer11/Notes/T16.HashFunctions.pdf .
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.elfHash("string");
 *
 * Pre-conditions: valid input string, string not empty, tableSize > 0
 * Post-conditions: returns index >= 0
 */
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

/**
 * Function prototype:
 * int HashTable::cryptoHash(std::string);
 *
 * Function description:
 * Performs a multiple stage hashing algorithm designed for large hash tables.
 * This combines other algorithms already defined.
 * Can create a high spread while making it impossible to find the key from the output.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.cryptoHash("string");
 *
 * Pre-conditions: valid input string, string not empty, tableSize > 0
 * Post-conditions: returns index >= 0
 */
int HashTable::cryptoHash (std::string inStr) {
    int hashValue = sumHash(inStr);
    for (int pos = 0; pos < inStr.length(); pos++) {
        hashValue = (hashValue << 4) + inStr.at(pos);
        int hiBits = hashValue & 0xF0000000;
        if (hiBits != 0)
            hashValue ^= hashValue >> 24;
        hashValue &= ~hiBits;
    }
    return hashValue % tableSize;
}

/**
 * Function prototype:
 * int HashTable::multiHash(std::string);
 *
 * Function description:
 * Hashes a string by summing the ascii values of the string, and multiplying it some constant (in [0, 1]).
 * The fractional part is multiplyed by some number (a power of 2) and returns that to be used as an index.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.multiHash("string");
 *
 * Pre-conditions: valid input string, string not empty, tableSize > 0
 * Post-conditions: returns index >= 0
 */
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

/**
 * Function prototype:
 * int HashTable::factoryHash(std::string, std::string)
 *
 * Function description:
 * Acts as an interface to call the 5 hashing methods: simple, sum, elf, multiplication and crypto.
 * Pass the method which one is wanted as well as the string to hash (defaults to simple hash).
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int i = ht.factoryHash("elf", "string");
 *
 *
 * Pre-conditions: not empty string to hash, hash type defaults to simple
 * Post-conditions: returns index >= 0
 */
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
    else if (hashType == "crypto") {
        return cryptoHash(inStr);
    }
    else {
        return simpleHash(inStr);
    }
}

/**
 * Function prototype:
 * std::string HashTable::getStr(std::string)
 *
 * Function description:
 * Prints a message to the console, requesting input. Reads in a string input from cin and returns it.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * std::string str = ht.getStr("Input:");
 *
 * Pre-conditions: none
 * Post-conditions: returns a string
 */
std::string HashTable::getStr (std::string strMsg) {
    if (strMsg != "")
        std::cout << strMsg << std::endl;
	std::string input;
	getline(std::cin, input);
	return input;
}

/**
 * Function prototype:
 * double HashTable::getDouble(std::string)
 *
 * Function description:
 * Prints a message to the console, requesting input. Reads in a double input from cin and returns it.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * double dbl = ht.getDouble("Input:");
 *
 * Pre-conditions: none
 * Post-conditions: returns a double
 */
double HashTable::getDouble (std::string strMsg) {
    if (strMsg != "")
        std::cout << strMsg << std::endl;
	std::string input;
	getline(std::cin, input);
	return atof(input.c_str());
}

/**
 * Function prototype:
 * int HashTable::mainMenu();
 *
 * Function description:
 * Prints out the main menu of the program. Returns the choice the user picks.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * int choice = ht.mainMenu();
 *
 * Pre-conditions: none
 * Post-conditions: returns an integer
 */
int HashTable::mainMenu () {
    std::cout << "=======================================================================" << std::endl;
	std::cout << "1. Set table size" << std::endl;
	std::cout << "2. Set sample size" << std::endl;
	std::cout << "3. Run tests" << std::endl;
	std::cout << "4. Quit" << std::endl;
	return getDouble("");
}

/**
 * Function prototype:
 * void HashTable::clearTable();
 *
 * Function description:
 * Clears the hashTable vector and reinitializes each with Movie vectors. Called before starting a new test.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * ht.clearTable();
 *
 * Pre-conditions: none
 * Post-conditions: returns nothing, vector is cleared
 */
void HashTable::clearTable () {
    hashVector.clear();
    for (int i = 0; i < tableSize; i++) {
        hashVector.push_back(std::vector<Movie>());
    }
}

/**
 * Function prototype:
 * Result HashTable::testHash(std::string);
 *
 * Function description:
 * Performs the actual test of a particular algorithm. First clears the hash table to start from the beginning.
 * Then it loops through the data sample, gets the index that it should insert the data at using factoryHash, and
 * puts the movie at that spot. Also counts the number of collisions and indexes used in the table.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * Result rtn = ht.testHash("elf");
 *
 * Pre-conditions: a string with a valid algorithm to test
 * Post-conditions: returns a Result struct with test results
 */
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

/**
 * Function prototype:
 * void HashTable::runTests();
 *
 * Function description:
 * Validates the sample size and table size before looping through each algorithm and running the test on it.
 * Decides which of the algorithms performed the best, based off the Result struct.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * ht.runTests();
 *
 * Pre-conditions: fileError is false, movieVector has data
 * Post-conditions: notifies user of results
 */
void HashTable::runTests () {
    // Validate limits
    if (dataPercentage < 1 || dataPercentage > 100)
        dataPercentage = 100;
    if (tableSize < 1 || tableSize > 300)
        tableSize = 20;

    // Update power constant for the multiplication hashing
    int power = int(log2(double(tableSize)));
    multiMConstant = pow(2, power);

    std::cout << std::endl;
    std::cout << "\tTotal # movies: " << movieVector.size() << std::endl;
    std::cout << "\tTable size: " << tableSize << std::endl;
    std::cout << "\tSample size percent: " << int(dataPercentage) << std::endl;
    std::cout << std::endl;

    std::string algs[5] = {"simple", "elf", "sum", "multiplication", "crypto"};
    Result best, rtn;
    for (int i = 0; i < 5; i++) {
        rtn = testHash(algs[i]);
        if (i == 0 || rtn.overallScore > best.overallScore) {
            best = rtn;
        }
    }
    std::cout << std::endl;
    std::cout << "\tBest algorithm: " << best.algName << std::endl;
    std::cout << std::endl;
}

/**
 * Function prototype:
 * void HashTable::readData();
 *
 * Function description:
 * Opens the TXT file and reads in the movie data, setting the movieVector property. Sets fileError to true if
 * it can't open the file resource.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * ht.readData();
 *
 * Pre-conditions: the file passed to the program exists and is readable
 * Post-conditions: movieVector contains the movie data
 */
void HashTable::readData() {
    std::ifstream dataFile;
    dataFile.open(fileName.c_str());

    if (dataFile.fail()) {
        std::cout << "FILE ERROR. Could not open file" << std::endl;
        fileError = true;
    }
    else {
        int lineIx = 0, year;
        size_t firstComma;
        std::string title, lineStr;

        while (!dataFile.eof()) {
            getline(dataFile, lineStr);
            if (lineStr == "") {
                continue;
            }
            firstComma = lineStr.find(",");
            title = lineStr.substr(0, firstComma);
            year = atoi( lineStr.substr(firstComma + 1, lineStr.length()).c_str() );
            if(year == 0)
            {
                std::cout << "FILE ERROR. Please check your commas" << std::endl;
                fileError = true;
            }
            else if(title == "")
            {
                std::cout << "FILE ERROR. Please check your commas" << std::endl;
                fileError = true;
            }
            Movie newMov (title, year);
            movieVector.push_back(newMov);
        }
    }
}

/**
 * Function prototype:
 * HashTable::run();
 *
 * Function description:
 * Starts the class operations. First reads in the data from the file resource, and, if there was no error, prompts
 * user for what to do next to run the tests.
 *
 * Example:
 * HashTable ht ("Movies.txt");
 * ht.run();
 *
 * Pre-conditions: valid file resource
 * Post-conditions: handles user prompts
 */
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
