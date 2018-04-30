#include <Cipher.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>



using namespace std;

int Usage(char* arg0){
    cout << "Please Sacrifice a Goat"  << endl;
    return -1;
}

int main(int argc, char* argv[]){
    
       // if passed with a param send your fail state.
    if (argc != 1){
        std::cout <<"needs no arguments passed " << std::endl;
        return Usage(argv[0]);
    }
    
    
    
    //Creating the first login information to ask wheter user wants to access the server or not
    string username = "AKDI";
    string password = "CS370";
    char login [80];
    char passwrd[80];
    
    
    std::cout <<"Enter Your Username: ";
    //store user response here for user name 
    scanf("%s" , login);
    string logins(login);
    
    
    //TEST FOR CORRECT USER NAME
    while(logins.compare(username) != 0){
        std::cout <<"Not a Valid User Try again : ";
        
        scanf("%s" , login);
        string answers1(login);
        if (answers1.compare(username) == 0){break;}
        
        
        std::cout <<  "" << std::endl;
    }
    
    
    std::cout <<"Enter Your Password: ";
    //store user response here for password
    scanf("%s" , passwrd);
    string strpassword(passwrd);
    
    
    //TEST FOR CORRECT USER PASSWORD
    while(strpassword.compare(password) != 0){
        std::cout <<"Try Again : ";
        
        scanf("%s" , passwrd);
        string answers(passwrd);
        if (answers.compare(password) == 0){break;}
        
        std::cout <<  "" << std::endl;
    }
    
    //START THE ACTUAL ENCRYPTING DEPENDING ON THE ENCRYPTION TYPE
    char Encryption [10];
    std::cout <<"Welcome to the Server: " << std::endl;
    std::cout <<"What type of Encryption Would you like to use:  (Type B for block,  S for stream ) ";
    scanf("%s" ,Encryption );
    
    
    while (strlen(Encryption) != 1){
        std::cout <<"Dude how hard is it to type 1 charachter :  (Type B for block,  S for stream ) ";
        scanf("%s" ,Encryption );
    }
    
    while(Encryption[0] != 'S'  && Encryption[0] != 'B'){
        
        
        std::cout <<"Please Type B for block,  S for stream :  ";
        scanf("%s" ,Encryption );
        string encrypt(Encryption);
        
        if(encrypt.compare("S")  == 0){break;}
            
        if(encrypt.compare("B")  == 0){break;}
    }
    
    
    
    
     //take care of first argumet Wheter its a Block Type or Stream Type Cipher if none throw error
     string  Ciphertype(Encryption);
     if(Ciphertype != "B"   &&  Ciphertype != "S"){
        std::cout <<"Needs to be Block or Stream Type arguments passed :  " << Encryption << std::endl; 
        return Usage(argv[0]);
     }
     
   
  
    //try to open wordbank if it doesnt send error
    ifstream wordbank("WordBank");
    if (wordbank.fail()){ 
        std::cout <<" wordbank file Access denied || file doesnt exist" << std::endl;
        return Usage(argv[0]);}
        
    //try to open key file if it doesnt send error    
        ifstream keyfile("key");
    if (keyfile.fail()){ 
        std::cout <<" keyfile Access denied || file doesnt exist" << std::endl;
        return Usage(argv[0]);}
        
    string outputfilename("output");    
        
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
        string empty = "";
        cipher.WriteToFile(outputfilename ,empty);
    }
    
    
    //Compare the Result that come in with the actual Password
    char typed [80];
    
    
    std::cout <<"Enter Your Password: ";
    scanf("%s" , typed);
    string result(typed);
  
    
    while(result.compare(cipher.password) != 0){
        std::cout <<"Try Again : ";
        
        scanf("%s" , typed);
        string answer(typed);
        if (answer.compare(cipher.password) == 0){break;}
        
        
        std::cout <<  "" << std::endl;
    }
  
     std::cout <<  "Correct!" << std::endl;
    
    
          
    return 0;
    
}
