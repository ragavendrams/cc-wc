
# Unix ccwc commandline tool 

## Overview
The `ccwc` application is a command-line utility that counts the number of words, bytes, lines, and characters in a given text file. It provides various options to customize the output based on user preferences. It is a re-implementation of the commonly used wc commandline tool, done as part of the Coding Challenges https://codingchallenges.fyi/challenges/challenge-wc.

## Command-Line Options
The application supports the following command-line options:
- `-w`: Count the number of words.
- `-c`: Count the number of bytes.
- `-l`: Count the number of lines.
- `-m`: Count the number of characters.
- `--help`: Display help information about the usage of the application.


## Usage
To build and run the application, follow these steps:

1. **Clone the Repository**:
   ```sh
   git clone <repository_url> 
   cd <repository_directory>
2. **Create a build directory and build the application**
   ```sh
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --target ccwc ccwc_test  
   ```
3. **Run the application**
   ```sh
   # Count words, lines, bytes, chars from files 
   ./ccwc -w -l -m -c test2.txt test.txt
   # Count words from stdin
   ./ccwc -w <enter input from stdin, CTRL-D to stop>
   # Pipe input from a different application
   echo 'temp' | ./ccwc -c
   ```
4. **Run tests**
    ```sh
    # From test directory
    ./ccwc_test # to run all tests
    ./ccwc_test [no_arguments] # to run a specific test with a tag 
    ```

## Limitations / Improvements
- Works with ASCII / UTF-8 encoded input files but not other encodings like UTF-16, UTF-32. 
- To support all encodings - icu library can be used which has an extensive collection of supported encodings.  