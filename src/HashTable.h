#ifndef HASHTABLE_H
#define HASHTABLE_H

// Dependencies for HashTable
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>

/**
 * Result struct
 *
 * Description:
 * This struct stores data about the performance of a hashing algorithm, including:
 * - The "name"
 * - The collision score (the # of collisions per sample size)
 * - The usage score (the # of indexes used in the hash table)
 * - The overall score (avg. of the collision score and usage score)
 *
 * Example:
 * Result rst ("elf", 67, 86);
 */
struct Result {
    std::string algName;
    double collisionScore;
    double usageScore;
    double overallScore;
    Result(){};

    /**
     * Function prototype:
     * Result::Result(std::string name, double colScore, double usgScore)
     *
     * Function description:
     * Constructor of Result struct: sets variables and calculate overall score
     *
     * Example:
     * Result rst ("elf", 67, 86);
     *
     * Pre-conditions: 0 <= colScore <= 100 and 0 <= usgScore <= 100
     * Post-conditions: the overallScore will be set
     */
    Result (std::string name, double colScore, double usgScore) {
        algName = name;
        collisionScore = colScore * 100;
        usageScore = usgScore * 100;
        overallScore = 0.5 * (collisionScore + usageScore);
    };
};

/**
 * Movie struct
 *
 * Description:
 * This struct stores data about a movie, including:
 * - The title
 * - The release year
 *
 * Example:
 * Movie mov ("Inception", 2010);
 */
struct Movie{
    std::string title;
    int year;
    Movie(){};

    /**
     * Function prototype:
     * Movie::Movie(std::string in_title, int in_year)
     *
     * Function description:
     * Constructor of Movie struct: sets variables
     *
     * Example:
     * Movie mov ("Inception", 2010);
     *
     * Pre-conditions: not empty parameters
     * Post-conditions: struct variables defined
     */
    Movie (std::string in_title, int in_year) {
        title = in_title;
        year = in_year;
    };
};

class HashTable
{
    public:
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
        HashTable(std::string);
        ~HashTable();

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
        void run();
    protected:
    private:
        std::vector< std::vector<Movie> > hashVector;
        int tableSize;
        int multiMConstant;
        double multiAConstant;
        double dataPercentage;
        bool fileError;
        std::string fileName;
        std::vector<Movie> movieVector;

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
        int simpleHash(std::string);

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
        int multiHash(std::string);

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
        int sumHash(std::string);

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
        int elfHash(std::string);

        /**
         * Function prototype:
         * int HashTable::factoryHash(std::string, std::string)
         *
         * Function description:
         * Acts as an interface to call the 3 hashing methods: simple, sum, and elf.
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
        int factoryHash (std::string, std::string);

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
        std::string getStr(std::string);

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
        double getDouble(std::string);

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
        Result testHash(std::string);

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
        int mainMenu();

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
        void clearTable();

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
        void runTests();

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
        void readData();
};

#endif // HASHTABLE_H
