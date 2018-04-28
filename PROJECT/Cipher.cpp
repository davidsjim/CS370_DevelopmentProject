#include <Cipher.h>
#include <cstdlib>
#include <ctime>



//generate  a random number to pick from the file
int Cipher::RandNumGen(int limit){
    srand(time(0));
    int random_integer = rand(); 
     std::cout <<"random int =  " << random_integer % limit << std::endl;
    return( random_integer % limit);
}





//read the string in to inputfile
bool Cipher::ReadInput (istream& istr) {
int linecount = 0;
    
     string  inputline;
     while(getline(istr ,inputline)){

      
        wordbank[linecount] = inputline;
        linecount++;
   
          std::cout <<"read inputfile =  " << inputline << std::endl;
     }
          std::cout <<"linecount =  " << linecount << std::endl;
     
   inputfile =   wordbank[RandNumGen(linecount)] + wordbank[(RandNumGen(linecount) + 278) % linecount ];
   
    std::cout <<"DECIPHEREDTEXT =  " << inputfile  << std::endl;
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

//XOR the input file with the key
/*string Cipher :: Xor(string input , string key){
   char  Xorchar;
  string substring = "";
  std::cout <<"fullstring of inputfile  =  " <<input << std::endl;
   std::cout <<"size inputfile  =  " <<input.length() << std::endl;
      std::cout <<"keysize  =  " <<key.length() << std::endl;
  for(int i = 0; i <int(input.length()); i+= 8){
     substring = input.substr(i , 8);
      
     std::cout <<"substring size  =  " <<substring.length() << std::endl;
  

     
     for( unsigned int j = 0; j < input.length(); j++){
        Xorchar = (substring[j]  ^ keyfile[j]);
        Xoredoutput += Xorchar;
     }
    
      
  }
  
  return Xoredoutput;
}
*/

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



//REMOVE THE PADDER THAT MIGHTVE BEEN ADDED
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




