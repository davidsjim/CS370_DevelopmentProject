#include <Cipher.h>
#include <iostream>
#include <fstream>
#include <sstream>


using std::istringstream;
using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::ostream;

int Usage(char* arg0){
    cout << "Please Sacrifice a Goat"  << endl;
    return -1;
}

int main(int argc, char* argv[]){
    
    // if not passed with 5 param send your fail state.
    if (argc != 5){
        std::cout <<"needs 4 argumetns passed " << std::endl;
        return Usage(argv[0]);
    }
    
    
    
     //take care of first argumet Wheter its a Block Type or Stream Type Cipher if none throw error
     string  Ciphertype =   argv[1];
     if(Ciphertype != "B"   &&  Ciphertype != "S"){
        std::cout <<"Needs to be Block or Stream Type arguments passed :  " << Ciphertype << std::endl; 
        return Usage(argv[0]);
     }
     
   
  
    //try to open wordbank if it doesnt send error
    ifstream wordbank(argv[2]);
    if (wordbank.fail()){ 
        std::cout <<" wordbank file Access denied || file doesnt exist" << std::endl;
        return Usage(argv[0]);}
        
    //try to open key file if it doesnt send error    
        ifstream keyfile(argv[4]);
    if (keyfile.fail()){ 
        std::cout <<" keyfile Access denied || file doesnt exist" << std::endl;
        return Usage(argv[0]);}
        
    string outputfilename = argv[3];    
        
    string ciphertext;
        
       Cipher cipher; 
       cipher.ReadKeyFile(keyfile);
       bool notempty =  cipher.ReadInput(wordbank);
       
       
       
//START ENCRYPTING  DEPENDING ON THE ENCRYTPION STYLE
   if(notempty){
       
         if(Ciphertype  == "B"){
          ciphertext = cipher.BlockCipher();
          cipher.WriteToFile(outputfilename , ciphertext);
         }
         else{ 
            ciphertext = cipher.StreamCipher();
            cipher.WriteToFile(outputfilename , ciphertext);
         }
       
       
      
    }
    else{
        string  empty = "";
        cipher.WriteToFile(outputfilename ,empty);
    }
      
      
          
    return 0;
    
}
