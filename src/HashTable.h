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
        
        HashTable(std::string);
        ~HashTable();
        // Start the class
        void run();

    protected:
    private:
        // Stores the actual hash table
        std::vector< std::vector<Movie> > hashVector;
        // Size of the hash table (default: 30)
        int tableSize;
        // Set for the "multiplication" hashing algorithm
        int multiMConstant;
        double multiAConstant;
        // Percent of the data to use (default: 100)
        double dataPercentage;
        // Stores the response from the file resources open
        bool fileError;
        // Filename of the movie list
        std::string fileName;
        // Cached movie list
        std::vector<Movie> movieVector;

        
        int simpleHash(std::string);
        int multiHash(std::string);
        int sumHash(std::string);
        int elfHash(std::string);
        int factoryHash (std::string, std::string);
        std::string getStr(std::string);
        double getDouble(std::string);
        Result testHash(std::string);
        int mainMenu();
        void clearTable();
        void runTests();
        void readData();
};

#endif // HASHTABLE_H
