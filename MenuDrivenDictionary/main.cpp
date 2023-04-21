/*==========================================================================*/
/*  PROGRAM Menu Driven Dictionary

    AUTHOR: Khoa Dao

SUMMARY

The program will ask the user to enter a file name for the input data.
Once the file is opened, the data will be processed. Otherwise, an error
message will be sent and terminate the program. The program will read the
file and obtain the values. Then it will let the user know the available
commands along with its description. Then the program will ask the user 
to enter the command. If the command is invalid, it will display an error
message and ask the user to enter again. There are four commands that can
be used in this program which are sort, look up, dump and exit. Sort 
command will sort the dictionary (word book) into alphabet order. Look
up command will look up the word in the dictionary and display its 
defintion if available. If not, an error message will be displayed to let
the user know that the word does not exist in the dictionary. Dump command
will display all of the terms along with its definition in the dicionary
in the other that it is being sotred. Exit command will allow the user
to exit the program and send a message to let the user know the program
is terminated. Additionally, the user will be asked to press enter 
to continue after finishing processed a command. 




INPUT

The user will be asked to enter the file name. If the user inputs a 
file name, and the file can not open using that name, the program
will be terminated. If the program can open the file, the user then 
will be asked to make an input command for the program to process.
There are four comamnd: sort, look up, dump, exit. If the commmand 
is invalid, the program will keep re-prompting the user for a 
command name until a valid command is enter. Also, the program
will ask the user to press enter after every command has processed. 


OUTPUT

The program prints an output the program's intro, and let the user 
know the amount of words in the dictionary. Then the available 
command with its decriptions will be displayed and notify the user
to enter the commmand. If the command is invalid, the user will be 
asked to enter again. If the command is entered, the user will
be notify when the program has finished executing and let the user
know to press enter to continue. For the look up command, if the 
word does not exist, it will let the user know. And for the dump
command, it will let the user know that the dictionary is empty. 



ASSUMPTIONS

We assume that any data file used as input to this program is completely
valid. The program is therefore not guaranteed to work correctly if bad data
in the file is entered.

*/


/*==========================================================================*/

//standard header
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;





/*==========================================================================*/
// constants, typedefs and struct

struct dictionaryItems
{
    string  key,             // string key to store the term
            definition;     // string definition to store definition
};
// initialize a structure type variable with two strings named key 
// and definition

const int MAX_WORD = 25;
// the maximum amount of word that the dictionary can process

typedef dictionaryItems dictionary[MAX_WORD];
//name dictionaryItems as a new variable of an array with a size of 
// MAX_WORD




/*==========================================================================*/
//function prototypes
void printIntro();
void openFile(ifstream&);
int getNumberOfWords(ifstream&);
void buildDictionary(ifstream&, dictionary&, const int);
void lookupWord(dictionary, const int);
void dumpDictionary(dictionary, const int);
void sortDictionary(dictionary&, const int);
string askCommand();
void displayCommand();
bool isEmpty(ifstream&);
void exitProgram();








/*==========================================================================*/
/* main function */
int main()
{   // main function begins

    ifstream inFile;        // initial file stream
    dictionary wordBook;    // wordBook(dictionary) to store the terms 
                            // and definitions
    
    string command;         // value for storing command

    printIntro();           // print intro of the program

    openFile(inFile);       // call the open file function

    const int NUMBERS_OF_WORDS = getNumberOfWords(inFile);
    // find and initialize a constant integer for the amount of words
    // in the dictionary

    buildDictionary(inFile, wordBook, NUMBERS_OF_WORDS);
    // store the values in the files into an array of dictionaryItems struct
    
    displayCommand();   // display the available command

    while (true){   // while true
        
        command = askCommand();     // get the command from the user
        cout << endl;

        // process of the command obtain from the file
        if (command == "sort"){     // if the commmand is sort

            sortDictionary (wordBook, NUMBERS_OF_WORDS); 
            // process the command sort
            cout <<"\nProcess completed";

        } else if (command == "lookup"){    // if the command is lookup

            lookupWord(wordBook, NUMBERS_OF_WORDS);
            // process the command lookup
            cout <<"\nProcess completed";


        } else if (command == "dump"){      // if the command is dump

            dumpDictionary (wordBook, NUMBERS_OF_WORDS);
            // process the command dump
            cout <<"\nProcess completed";



        } else if (command == "exit"){      // if the command is exit

            exitProgram();

        } else if (command == "help"){      // if the command is help

            displayCommand();

        } else {    // if the command is invalid

            // print the error message and ask the user to try again
            cout << "Invalid Command." << endl;
            cout << "Please try again." << endl;
        }   // else
        
        cout << endl;

        
        cout << endl;
    }   // while true

return (EXIT_SUCCESS);
} // main function ends





/*==========================================================================*/
void printIntro()

// This function simply prints out an opening title and heading for the user

{
cout<< "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<< endl;
cout<< "                 Menu Driven Dictionary                     " << endl;
cout<< "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<< endl
<< endl;
}
// This function simply prints out an opening title and heading for the user





/*==========================================================================*/
void openFile
(ifstream& inFile)    // input file stream

// This function asks the user to enter a file name, and then tries to open
// the file. The function will only ask the user to enter the file once. 
// If the program can not open the file, the program will be terminated.

{

    string fileName;    //string for storing file name

    // ask the user input for the file name
    cout  <<  "Enter the name of the data file (no blanks!) -> ";   
    cin  >>  fileName;

    // attempt to open the file
    inFile.open ( fileName.c_str( ) );
    
    if (!inFile) { // if can not open file
    
        // clear the file stream
        inFile.clear ();

        // print the error message
        cout << endl << "Can not open the file. "<< endl;
        cout << "File does not exist. " << endl; 
        cout << "Please check the file name or the file path again" << endl 
        << endl;

        // terminate the program
        exit(EXIT_FAILURE);
        
    }   // if can not open file
    
    // prints out the open succesfully message
    cout << endl;
    cout << "File opened succesfully" << endl << endl;

}





/*==========================================================================*/
int getNumberOfWords
(ifstream& inFile)  // input file stream

// This function will read the file and obtained a value that will be the  
// number of words in the file (dictionary) and return the value as an int

{

    int data;       // value for storing the data for the ammount of words
    inFile >> data;     // obtain the value from the file

    // check whether the file is empty or not
    if (isEmpty(inFile))    // if file is empty
    {
        data = 0;   // set the value to 0 
    }   // if file is empty

    // prints out the message to let the user knows the amount of words 
    // stored in the dictionary
    cout << "There are "<< data 
    << " words in this dictionary." << endl << endl;
    inFile.ignore(256, '\n');

    return data;   // return the value as an int
}





/*==========================================================================*/
void buildDictionary
(ifstream& inFile,  // input file stream
dictionary& dict,   // the value that store the words 
const int size)     // the size of the dictionary

// This function will read the file and obtain the values which then can be
// use to process the values as a dictionary array type structure.

{

    int lcv = 0;    // loop control variable

    while ( lcv < size ){   // loop control variable is less than size
    
        inFile >> dict[lcv].key;    // obtain the term
        inFile.ignore(256, '\n');   // skip the rest of line
        getline(inFile, dict[lcv].definition);  //obtains the value from the file
        lcv++;

    }   // loop control variable is less than size
}





/*==========================================================================*/
void lookupWord
(dictionary dict,   // the value that store the words 
const int size)     // the size of the dictionary

// This function will be using linear search to look up the word.
// If the word is found in the list of words (dicitonary), the word will
// be printed along with its definition. If the word can not be found, 
// the word will be print and let the user know it does not exist.

{

    int lcv = 0;    // loop control variable
    bool found = false;     
    // initialize a boolean to check whether the word is found or not
    
    string word;    // string value to store word

    // ask the user to enter the word to look up
    cout  <<  "Enter the word that you want to look "
    << "up in the dictionary (no blanks!) -> ";
    cin  >>  word;  // obtain the user input

    // find the value in the diciotnary
    while ( lcv < size && !found ){
        // while is still in range of the diciotnary and have not found

        if (dict[lcv].key == word){     // if the word is found

            found = true;                // set found is true

        } else {    // otherwise

            lcv ++ ;    // move to the next word in the string

        }   // otherwise

    }

    if (found)  // found is true
    {

        // prints out the term along with the value
        cout << endl<< "The definition of the word \"" 
        << word << "\" is:" << endl << dict[lcv].definition << endl; 

    } else {    // found is false

        // prints out the term and let the user know the word does not exits
        cout << endl << "The definition of the word \"" 
        << word << "\" does not exist in the dictionary." << endl;

    }   // found is false

}






/*==========================================================================*/
void dumpDictionary
(dictionary dict,   // the value that store the words 
const int size)     // the size of the dictionary

// This function will read the list of words (dictionary) and prints all
// the terms along with its definition in the order that it is being stored
// in the program

{
    int lcv;    // loop control variable

    if (size > 0)   // if there are words in the dicitonary
    {
        // loop through the array to print out the terms with its deifinition
        for ( lcv = 0; lcv < size; lcv++){

            cout << "Term:       " << dict[lcv].key << endl;
            cout << "Definition: "<< dict[lcv].definition << endl;
            cout << endl;

        }   // end of loop

    } else {    // if there isn't any words in dictionary

        cout << "Currently, this dictionary doesn't "
        << "contain any words nor definitions." << endl;
    
    }   // if there isn't any words in dictionary
}






/*==========================================================================*/
void sortDictionary
(dictionary& dict,   // the array to be sorted
const int size)     // number of array elements

// This function will use Selection Sort 
// to sort the dictionary into alphabetical order, by words and return it.

{
    int start,      // index to first value in unsorted portion
        smallest,   // index to smallest value in unsorted portion
        current;    // used to scan array for smallest value
                    
    dictionaryItems temp;  // temporary storage during a swap

    // perform size - 1 passes
    for ( start = 0; start < (size - 1); start++ ){

        smallest = start;
        // scan unsorted part of array to find 
        // smallest value
        for ( current = (start + 1); current < size; current++ ){
            if ( dict[current].key < dict[smallest].key ){
                smallest = current;
                
            }
        }
        // perform one exchange of elements if necessary
        if (smallest != start){

            // exchange the key terms of the dictionary
            temp =  dict[start];
            dict[start] = dict[smallest] ;
            dict[smallest] = temp;

            

        }   // outer for loop

    }   // selection short
    
}





/*==========================================================================*/
string askCommand()

// This function will list out the available commands that the user can 
// can use and ask the user to enter the command and return it.

{

    string command;     // value to store the user input

    // ask the user to enter the command
    cout <<  "What do you want to do with this dictionary ? " 
    << "( enter \"help\" to show available commands )"<< endl;
    cin.clear();
    cin >> command;     // obtain the user input

    return command;
}





/*==========================================================================*/
void displayCommand()

// This function will list out the available commands that the user can use

{

    // list out the availabel commands
    cout << "The availabe commands are: " << endl;
        
    cout << "    Type: \"sort\" for " << endl
    << "    Sort the dictionary into alphabetical order, by words." 
    << endl << endl;

    cout << "    Type: \"lookup\" for " << endl
    << "    Look up a word in the dictionary, and print its "
    <<"definition if it is found. If it is not found, print "
    <<"an appropriate message.  " << endl << endl;
    
    cout << "    Type: \"dump\" for " << endl
    << "    Print a table of the current dictionary contents."
    <<" If the dictionary is empty, print a message to that effect. " 
    << endl << endl;

    cout << "    Type: \"exit\" for " << endl
    << "    Exit the program. " 
    << endl << endl;

}





/*==========================================================================*/
bool isEmpty
(ifstream& inFile)  // input file stream

// This function will check whether the file is empty or not
// if the file is empty return true. If not, return false.


{
    return inFile.peek() == ifstream::traits_type::eof();
}





/*==========================================================================*/
void exitProgram()

// This function will prints out the process and terminate the program

{
    cout << "Exit Program" << endl;
    // process the command exit
    cout <<"\nProcess completed";
    exit (EXIT_SUCCESS);
}





/*===========================================================================*/
/*                          END OF PROGRAM                                  */
/*==========================================================================*/



