#include <Stream.h>
using namespace std;

//This class takes a single input stream, encrypts and decrypts bit by bit using XOR


//takes ifstreams of the key and input file, and the ofstream of the file
//grabs input, calls encryption, outputs to file
bool Stream::streamCipher(ifstream& inputStream, ifstream& keyStream, ofstream& outputFile){
  if(inputStream.fail() || keyStream.fail()){
    return false;
  }
  
  //grabbing the input
  char c1;
  while(inputStream.get(c1)){
    inputText.push_back(c1);
  }
  
  //grabbing the key
  char c2;
  while(keyStream.get(c2)){
    key.push_back(c2);
  }
  
  
  //call encrypt to actually encrypt
  if(!encrypt()){
    return false;
  }
  
  //write to output file
  for(unsigned int i = 0; i < inputText.size(); i++){
    outputFile << inputText.at(i);
  }
  
  
  
  return true;
}


bool Stream::encrypt(){
  unsigned int index = 0;
  if(key.size() == 0){
    return false;
  }
  
  for(unsigned int i = 0; i < inputText.size(); i++){
    //if at the end of the key, reset back to 0 
    if(index >= key.size()){
      index = 0;
    }
    inputText.at(i) = inputText.at(i) ^ key.at(index);
    ++index;
  }
  
  
  return true;
}
