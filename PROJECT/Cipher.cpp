#include <Cipher.h>
#include <cstdlib>
#include <ctime>

using namespace std;

//generate  a random number to pick from the file
int Cipher::RandNumGen(int limit){
    srand(time(0));
    int random_integer = rand(); 
    return( random_integer % limit);
}





//read the string in to inputfile
bool Cipher::ReadInput () {
int linecount = 1;
string substr = "";


for(int i = 0; i <(int)Bank.length(); i++){
    
    if(Bank[i] == '\n'){
        wordbank[linecount] = substr;
        linecount++;
        std::cout <<"read inputfile =  " << substr << std::endl;
        substr = "";
         
    }
    else {
        substr += Bank[i]; 
    }
    
}

    
   
    std::cout <<"linecount =  " << linecount << std::endl;
     
    inputfile =   wordbank[RandNumGen(linecount)] + wordbank[(RandNumGen(linecount) + 278) % linecount ];
   
    std::cout <<"DECIPHEREDTEXT =  " << inputfile  << std::endl;
    password = inputfile;
  //   std::cout <<"read inputfile bytes =  " << inputfile.length() << std::endl;

     if(inputfile.length() == 0){return false;}
     return true;    
}


// read the key file into keyfile
void Cipher::ReadKeyFile (istream& istr) {
    char input;
    while (istr.get(input)){
        keyfile += input;
        
        
    }
}


// write to file
void Cipher::WriteToFile(string& filename , string contents){
    
  ofstream outputfile;
  outputfile.open (filename);
  outputfile <<contents;
  outputfile.close();
    
}



//PAD , XOR AND SWAP 
string Cipher :: BlockCipher(){
string Xorstr;
string Ciphertext;

    Pad(inputfile);
    Xorstr = Xor(inputfile , keyfile);
    Ciphertext = Swap(Xorstr, keyfile);
    
    return Ciphertext;
    
}

//XOR IF KEY IS EXHAUSTED LOOP THRU AGAIN
string Cipher :: StreamCipher(){
 string ciphertext = "";
 ciphertext = Xor(inputfile , keyfile);
 return ciphertext;
}


//PUT PADDINGS IF NECCESSARY TO THE INPUT STRING
string Cipher::Pad(string& input){
    
int bytes = input.length();
int leftovers = (bytes % 8);
unsigned char padder= 0x80;


if(leftovers > 0){
    for(int i = 0; i <(8 - leftovers); i++){
        input+= padder;
        
    }
}

return input;

}



//SWAP THE XORED OUTPUT 
string Cipher :: Swap (string & input, const string key){
int begining = 0;
int end = int(input.length()) -1;
   
           
char  startptr = input[begining];
char  endptr = input[end];

int counter = 0;
int keysize = int(key.length()); 
int i = 0;

while (begining < end){
    counter ++;
 if( i == keysize ){
      i =0;
 }
    for(; i < keysize; i++){
        if( (key.at(i) % 2)  != 0){
           input[begining] = endptr;
           input[end] = startptr;
           end--;
           begining++;
           if ((begining >= end)){return input;}
           startptr = input[begining];
           endptr = input[end];
           
           
      
        }
        else{
            begining++;
              if((begining >=  end)){return input;}
            startptr = input[begining];
       
        }
        
    }
    
}
    
    
    return input;
}



//REMOVE THE PADDER THAT MIGHTVE BEEN ADDED  USED FOR ENCRYPTED BANK
void Cipher :: RemovePad(string & input){
    
    unsigned char padder=   static_cast <unsigned char> (0x80) ;
    
     
    int counter = 0;
    for(int i = 0; i < int(input.length()); i++){
        if( static_cast <unsigned char> (input.at(i))  == padder){
            counter++;
        }
    }

    input = input.substr(0 , (int (input.length()) - (counter)) );
      
    
}


//DECIPHER THE STREAM ALGORTIHM
string Cipher :: DecipherStream( string & input , string key){
    string text="";
    text = Xor(input ,key);
    return  text;
}


//DECIPHER THE BLOCK ALGRORITHM
string Cipher :: DecipherBlock (string & input , string key){
    string text = "";
    text = Swap(input , key );
    text =  Xor(text , key );
    RemovePad(text);
    return text;
    
}




//XOR  FOR STREAM AND BLOCK
string Cipher :: Xor(string &input ,string key){
    string StreamXor ="";
    int inputsize = int(input.length());
    int keysize = int(key.length());
    int i =0;
    int k= 0;
    while(i < inputsize ){
        if(k < keysize){ 
            StreamXor += (input.at(i) ^ key.at(k));
            k++;
            i++;
        }
        else {
         k = 0;
        }
        
    }
    return StreamXor;
    
}


void Cipher::ReadWordBank (istream& istr) {

    
     char input;
    
     while(istr.get(input)){
        Bank += input;    
        
        
     }
     
     Bank = DecipherBlock(Bank  ,"AlphaPti");
  // std::cout <<"read inputfile bytes =  " << inputfile.length() << std::endl;

      
}



