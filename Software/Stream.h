#ifndef STREAM_H_INCLUDE
#define STREAM_H_INCLUDE

//Stream.h declares the Stream class
//This class takes a single input stream, encrypts and decrypts bit by bit using XOR


#include<iostream>
#include<fstream>
#include<vector>
#include <string>
#include <sstream>


class Stream{
public:
    Stream(){}
    
    bool streamCipher(std::ifstream& inputStream, std::ifstream& keyStream, std::ofstream& outputFile); 
    bool encrypt();
    
    std::vector<char> inputText;
    std::vector<char> key;
};

#endif
