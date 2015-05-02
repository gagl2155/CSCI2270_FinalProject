# FinalProject

# Project Summary
This project will be a continuation of the hash table assignment. Like the assignment, this program will use a list Movie structs as the data that needs to be stored in a hash table. The program will accept a text file as input containing a list of movies, including their title and year. Next, it will construct a hash table using various hashing functions in a similar way to the assignment. The goal of the project is to compare various hashing algorithms and hash table sizes. Three or four hashing algorithms will be implemented and for each of them it will construct a hash table with the data from the file. The comparisons will be based on how well the algorithm performs with different amounts of data and table sizes. The number of collisions in the hash table and the overall usage of the table will be a helpful indication of the performance of the hashing algorithm. The user will input what percent of the data should be used and what the table size should be and the program will then report on the number of collisions for each algorithm.

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
	Table size: 40
	Sample size percent: 100

	Algorithm "simple": 24 collision(s), 26/40 indexes used
	Algorithm "elf": 23 collision(s), 27/40 indexes used
	Algorithm "sum": 23 collision(s), 27/40 indexes used
	Algorithm "multiplication": 28 collision(s), 22/40 indexes used
	Algorithm "crypto": 20 collision(s), 30/40 indexes used

	Best algorithm: crypto

    
# Future Todos

    1) Validate inputs from menu
    2) Validate bad input from movie text file
    3) Detect average space between used indexes
    4) Output ascii range for all titles: min - 250, max - 1000

# Dependencies
No third-party dependencies

# System Requirements
Running Ubuntu (64 bit) through VirtualBox

# Group Members
Garrett Glissmann
    
# Contributors
