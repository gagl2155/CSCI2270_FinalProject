# FinalProject

# Project Summary
This project will be a continuation of the hash table assignment. Like the assignment, this program will use Movie structs as data that needs to be stored in a hash table. The program will accept an input file with a list of movie titles, and other data about the movie. Next, it will construct a hash table in a similar way to the assignment. The goal of the project is to compare various hashing algorithms and hash table sizes. Two or three hashing algorithms will be implemented and for each of them, it will construct a hash table with the data from the file. The comparisons will be based on how the algorithm performs with different amounts of data and table sizes. The number of collisions in the hash table will be a helpful indication of the performance of the hashing algorithm. The user will input what percent of the data should be used and what the table sizes should be and the program will then report on the number of collisions for each algorithm.

# How to Run
Run the excecutable - requires movie data

    ./FinalProject inputfile.txt

Movie file format:
    Inception,2010,Christopher Nolan
    The Departed,2006,Martin Scorsese

The menu:
============== Menu ==============
1. Set table size   (accepts a number 5-n)
2. Set data percent (accepts a number 1-100)
3. Run tests

Run tests:
    "Algoirthm 1": n collisions, 87% of table used, average of 2 movie(s) at index
    "Algoirthm 2": n collisions, 92% of table used, average of 2 movie(s) at index
    "Algoirthm 3": n collisions, 99% of table used, average of 1 movie(s) at index
    
# Dependencies
No dependencies

# System Requirements
Running Ubuntu (64 bit) through VirtualBox

# Group Members
# Contributors
