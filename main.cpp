
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 1
*/


//Libraries included here
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DNA.h"


using namespace std;

//This method asks the user if they would like to enter another file.
//If they type no, the program will quit, but typing anthing else
//will cause the program to continue.
void continuePrompt()
{
    string quit = "";
    cout<< "\nWould you like to process another file?" << endl;
    cout <<"Type 'no' if you want to quit, else type 'yes' to continue: " << endl;
    cin >> quit;
    if (quit == "no")
    {
      exit(-1);
    }
}

//Main method for the program, which takes in a command line argument
//for the text file.
int main(int argc, char **argv){

  if (argc <2){
    cout << "Invalid text file input. Exiting program." << endl;
    return 1;
  }

//----------------------------------------
//Creates the input stream
  ifstream inFS;
  string fileName = argv[1];

  while (true){
    string DNAString;
    string totalString;
//Opens the name of the textfile, if file cannot be access the program closes
    cout << "Opening " << fileName << endl;
    inFS.open(fileName);

    if (!inFS.is_open())
    {
      cout << "ERROR, could not open file " << fileName  << endl;
      cout << "Exiting Program." << endl;
      return 1;
    }

    while (!inFS.eof()) {
       inFS >> DNAString;
       if (!inFS.fail()) {
          totalString = totalString + DNAString + "\n";
       }
    }
    inFS.close();

  //----------------------------------------

//This creates a new class and stores it on the heap. It uses the
//constructor with the string parameter
    DNA *dnaSequence = new DNA(totalString);

    string dnaNew = dnaSequence->getDNASequence();
//The other variables are calculated and set with these methods
    dnaSequence->calcSum(dnaNew);
    dnaSequence->calcMean(dnaNew);
    dnaSequence->calcVariance(dnaNew);
    dnaSequence->calcStandardDeviation(dnaNew);
//The probability of each nucleotide is calculated and then is set
    float probA = dnaSequence->probNucleotide(dnaNew, 'A');
    float probT = dnaSequence->probNucleotide(dnaNew, 'T');
    float probC = dnaSequence->probNucleotide(dnaNew, 'C');
    float probG = dnaSequence->probNucleotide(dnaNew, 'G');
    dnaSequence->setProbA(probA);
    dnaSequence->setProbT(probT);
    dnaSequence->setProbC(probC);
    dnaSequence->setProbG(probG);
//Seed for random is generated with time for the gaussian distribution method
    srand(time(0));
//Outfile is generated and class is deleted.
    dnaSequence->generateOutFile(dnaNew);
    delete dnaSequence;

  //----------------------------------------
  //The continue method is called, and will determine if the while loop
  //repeats. If the program does not exit a new filenam is entered.
    continuePrompt();

    fileName = "";
    cout << "Enter the name of the new file you want to read in : "  << endl;
    cout << "(Do not add quotation marks around the file name)" << endl;

    cin >> fileName;
  }
  return 0;
}
