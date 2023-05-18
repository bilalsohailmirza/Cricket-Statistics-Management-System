# Cricket-Statistics-Management-System
A management system for cricket statistics using OOP in C++. The System was integrated with a local SQLite database to perform CRUD operations.

## Technologies and Tools

**Language:** C++ 11 

**Database:** SQLite 

**IDE:** Code Blocks 

## Features

- Console Window View
- Local Storage of Data with Database
- CRUD Operations



## Installation and Integration

- The SQLite was inte grated with c++ using [SQLite amalgamation](https://sqlite.org/download.html) as source code of C language. 
- Functions for interacting with the database are C based functions but C++ specifics also work fine alongside the pre-defined functions in the sqlite.h header file.
- I used Code Blocks for this project but you can figure out some other IDE or code editor for yourself.
- To integrate SQlite with Code Blocks you might find this [youtube tutorial](https://www.youtube.com/playlist?list=PLfLTVALFJVQJ22XeGZ2b2i2sQnMygbCHh) helpful.
- To use the database file with .db extension you can use [sqlite brwoser](https://sqlitebrowser.org/). 
    
## Lessons Learned

By building this project I learned about different ways to connect a database to a codebase.
I actually build this project for my second semester OOP course so there were some restrictions I had to oblige with
so that also held me back a little bit.
After writing quite some code I realized that I was writing c++ code very poorly.
I had not seprate the class prototypes and definitions in header files and main file.
I could reduce the number of classes and functions by making them more generic and alot more stuff could be done to
optimize the process. But since this was my first time creating a project on my own, I am content with what I was able to achieve in span of few days.

