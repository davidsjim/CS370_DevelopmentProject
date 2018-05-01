#ifndef CIPHER_H_INCLUDE
#define CIPHER_H_INCLUDE


#include<iostream>
#include<fstream>
#include <string>
#include <string.h>
#include <sstream>





using namespace std;


class Cipher{
public:
    

// read the input file
bool ReadInput(); 
void ReadKeyFile(istream& istr);
void WriteToFile(string& filename, string contents, char CipherType);
int RandNumGen(int limit);
void ReadWordBank(istream& istr);


//encryption methods
string BlockCipher();
string StreamCipher();
string Xor(string &input ,  const string key); 
string Pad(string& input);
string Swap(string & input, const string key);


//decryption  USED FOR TESTING
string DecipherBlock (string & input , string key);
string DecipherStream( string & input , string key);
void RemovePad(string& input);


 



string inputfile ="";
string password = "";
string keyfile = "";
string Xoredoutput = "";    
string wordbank [200];
string Bank = "";

    
};
#endif
