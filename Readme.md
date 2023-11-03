C++ Logger Application
Table of Contents
Introduction
Prerequisites
Compilation
Running the Program
Design Choices
Introduction
This is a C++ logging application that demonstrates the use of C++ threads and a lock-based solution to manage log messages from multiple threads. The program uses a Logger class to add log messages to a queue and remove messages from the queue while ensuring thread safety.

Prerequisites
Before compiling and running the code, you'll need the following:

C++ Compiler (e.g., g++)
Standard C++ Library
pthread library (for thread support)
Compilation
To compile the code, follow these steps:

Open your terminal.

Navigate to the directory where your code is located.

Use the following command to compile the code. Make sure to replace Application.cpp with the actual name of your source code file:

shell
Copy code
g++ -std=c++11 -pthread Application.cpp
This command compiles your code with C++11 support and links it with the pthread library.

Running the Program
After successful compilation, you can run the program using the following command:

shell
Copy code
./a.out
This will execute the program, which will add log messages from multiple threads to the queue and then remove and display those messages.

Design Choices
1. Logger Class
The Logger class is designed as a singleton to ensure that only one instance of the logger exists. This design choice simplifies access to the logger from different parts of the program.

2. Thread Safety
To ensure thread safety, the Logger class uses a mutex to protect the log message queue. This prevents concurrent threads from accessing the queue simultaneously and avoids data corruption.

3. Lazy Initialization
The Logger class uses lazy initialization, which ensures that the singleton instance is created when needed. In C++11, the standard guarantees that concurrent execution will wait for the completion of the initialization, eliminating the need for double-checked locking.

4. Message Class
The Message class is used to encapsulate log messages. Each message has a name (thread ID) and a message string. This design choice allows us to identify which thread added the message and what the message content is.

5. Error Handling
The code includes basic error handling for exceptions. If an exception is thrown during thread execution, it catches the exception and displays an informative error message.

6. Thread Creation
The main function creates several threads, each of which adds a message to the logger's queue. After a short delay, another thread is created to remove messages from the queue and display them
