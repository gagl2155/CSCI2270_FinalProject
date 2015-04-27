# FinalProject

# Project Summary
This project will be a continuation of the hash table assignment. Like the assignment, this program will use Movie structs as data that needs to be stored in a hash table. The program will accept an input file with a list of movie titles, and other data about the movie. Next, it will construct a hash table in a similar way to the assignment. The goal of the project is to compare various hashing algorithms and hash table sizes. Two or three hashing algorithms will be implemented and for each of them, it will construct a hash table with the data from the file. The comparisons will be based on how the algorithm performs with different amounts of data and table sizes. The number of collisions in the hash table will be a helpful indication of the performance of the hashing algorithm. The user will input what percent of the data should be used and what the table sizes should be and the program will then report on the number of collisions for each algorithm.

# How to Run
Create an executable:

    g++ -o FinalProject FinalProject.cpp HashTable.cpp
    ./FinalProject Movies.txt

Movie file format:

    Inception,2010
    The Departed,2006

The menu:

    =======================================================================
    1. Set table size
    2. Set sample size
    3. Run tests
    4. Quit

Run tests:

    Total # movies: 50
    Table size: 30
    Sample size percent: 100
    Algorithm "simple": 25 collision(s), 25/30 indexes used
    Algorithm "elf": 22 collision(s), 28/30 indexes used
    Algorithm "sum": 28 collision(s), 22/30 indexes used
    Algorithm "multiplication": 37 collision(s), 13/30 indexes used
    Best algorithm: elf
    
# Todo

    1) Validate inputs from menu
    2) Validate bad input from movie text file
    3) Detect average space between used indexes
    4) Output ascii range for all titles: min - 250, max - 1000

# Dependencies
No third-party dependencies

# System Requirements
Running Ubuntu (64 bit) through VirtualBox

# Group Members
Garrett Glissmann, Adam Ephraim Parnes
    
# Contributors
