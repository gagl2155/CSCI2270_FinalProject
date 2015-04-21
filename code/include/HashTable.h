#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

struct Movie{
    std::string title;
    int year;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    };

};

class HashTable
{
    public:
        HashTable(std::string);
        ~HashTable();
        void run();
    protected:
    private:
        std::vector< std::vector<Movie> > hashVector;
        int tableSize;
        double dataPercentage;
        std::string fileName;
        std::vector<Movie> movieVector;

        int simpleHash(std::string);
        int sumHash(std::string);
        int elfHash(std::string);
        std::string getStr(std::string);
        double getDouble(std::string);

        void testHash(std::string);
        int mainMenu();
        void clearTable();
        void runTests();
        void readData();
};

#endif // HASHTABLE_H
