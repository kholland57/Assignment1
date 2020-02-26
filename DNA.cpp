
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 1
*/



//Libraries included here.
#include "DNA.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>


//----------------------------------------------------------------------------
//Constructors:
//Default constructor when no parameters are given
DNA::DNA(){
  DNASequence = "";
  sum = 0;
  mean = 0;
  variance = 0;
  standardDeviation = 0;
  totalStrings = 0;
}

//Constructor when a DNA string is given. The other variables are dependent
//on the DNA string so the user does not have to enter them in as parameters.
DNA::DNA(string DNA){
  DNASequence = DNA;
  DNASequence = UpperCase(DNASequence);
  sum = calcSum(DNASequence);
  mean = calcMean(DNASequence);
  variance = calcVariance(DNASequence);
  standardDeviation = calcStandardDeviation(DNASequence);
}

//Destructor that deletes the class
DNA::~DNA()
{
  cout << "Class Deleted" << endl;
}

//-----------------------------------------------------------------

//This method changes every character in the string to upper case.
//It also removes characters that are not DNA nucleotides or newlines.
string DNA::UpperCase(string DNA){
  string dnaNew = "";

  for (int i = 0; i < DNA.size(); ++i)
  {
    DNA[i] = toupper(DNA[i]);
    if (DNA[i] == 'A')
    {
      dnaNew += DNA[i];
    }
    else if (DNA[i] == 'T'){
        dnaNew += DNA[i];
    }
    else if (DNA[i]== 'G'){
        dnaNew += DNA[i];
    }
    else if (DNA[i] == 'C')
    {
        dnaNew += DNA[i];
    }
    else if (DNA[i] == '\n')
    {
        dnaNew += DNA[i];
    }
    else
    {
      cout << "Invalid DNA File, \'"  << DNA[i] << "\' is not a nucleotide." << endl;
      cout << "Invalid characters will be removed.\n" << endl;
    }
  }
  return dnaNew;
}
//----------------------------------------------------------
//Math Calculations

//This method calculates the sum by looping through the DNA string and
//counting each character. It returns a float and sets the sum variable.
int DNA::calcSum(string DNA){
  int sum = 0;
  for (int i = 0; i < DNA.size(); ++i)
  {
    if (DNA[i] != '\n')
    {
      sum +=1;
    }
  }
  setSum(sum);
  //this->sum = sum;
  return sum;
}

//----
//This method calculates the mean. It first calculates the sum in case it was
//not yet calculated, and the total string number. It then sets the mean
//and returns a float value.
float DNA::calcMean(string DNA){

  float totalStrings = calcTotalStrings(DNA);
  float sum = calcSum(DNA);
  float mean = 0;

  mean = sum/totalStrings;
  setMean(mean);
  //this->mean = mean;
  return mean;
}

//----
//This caluculates the variance by counting each size of the string, and
//using the mean in other valvulations. It sets the variance variable
//and returns a float.
float DNA::calcVariance(string DNA){
  //float mean = this->mean;
  float mean = getMean();
  float stringSize = 0;
  float tempNum = 0;
  float totalString = this->totalStrings;
  float variance = 0;

  for (int i = 0; i < DNA.size(); ++i)
  {
    if (DNA[i] != '\n')
    {
      stringSize += 1;
    }
    else
    {
      stringSize =  (stringSize - mean);
      stringSize = stringSize * stringSize;
      tempNum = tempNum + stringSize;
      stringSize = 0;
    }
  }

  variance = (tempNum/(totalString));
  //this->variance = variance;
  setVariance(variance);
  return variance;
}

//-----------
//This calculates the standard deviation by taking the mean,
// counting the size of each string in the dna list, and following the
//calculations for standard deviation. It then sets the variable and
//returns a float.
float DNA::calcStandardDeviation(string DNA){
  //float mean = this->mean;
  float mean = getMean();
  float stringSize = 0;
  float tempSum = 0;
  float combinedMean = 0;
  float standardDeviation;

  for (int i = 0; i < DNA.size(); ++i)
  {
    if (DNA[i] != '\n')
    {
      stringSize += 1;
    }
    else
    {
      //cout << "String size : " << stringSize << endl;
      tempSum += ((stringSize - mean)*(stringSize - mean));
      stringSize = 0;
    }
  }
  combinedMean = tempSum/totalStrings;
  standardDeviation = sqrt(combinedMean);
  setStandardDeviation(standardDeviation);
  //this->standardDeviation = standardDeviation;

  return standardDeviation;
}
//-----------

//This calculates the probability of the entered char parameter in the
//entered DNA string by looping through.
float DNA::probNucleotide(string DNA, char N){
  int num = 0;
  float probability = 0;

  for (int i = 0; i < DNA.size(); ++i)
  {
    if (DNA[i] != '\n')
    {
      if (DNA[i] == N)
        num += 1;
    }
  }
  //probability = (num/this->sum);
  probability = (num/getSum());
  //this->nucleotideProb = probability;

  return probability;
}
//-----------
//This method calculates the probability of two characters entered
/*The for loop skips every other character in the DNA string so it counts
 by pairs of twos. The characters are added together in a string. If the
 character is a newline it subtracts by one so the next increment can start at
 the beggining of the next string.
*/
float DNA::probBigram(string DNA, char letterOne, char letterTwo){

    float num = 0;
    float probability = 0;
    string bigram = string(1,letterOne) += string(1,letterTwo);

  for (int i = 0; i < DNA.size(); i += 2 )
  {
      if (DNA[i] != '\n'){
        int num2 = i + 1;
        string check = string(1, DNA[i]) += string( 1, DNA[num2]);
        if (bigram == check){
          num += 1;
        }
      }
      else
      {
        i -- ;
      }

  }
    //float sum = (this->sum/2);
    float sum = (getSum()/2);
    probability = (num/sum);

    return probability;
}

//-----------

//This calculates a string length that falls within the gaussian distribution
//of the DNA list.
int DNA::gaussianDist(string DNAString){
  //variables are initialized here.
  float a = 0;
  float b = 0;
  double c = 0;
  double d = 0;
  int num = 0;


  // float mean = this->mean;
  // float standardDeviation = this->standardDeviation;
  float mean = getMean();
  float standardDeviation = getStandardDeviation();

  //Two random numbers generated here
  a = ((float)rand()/(RAND_MAX));
  b = ((float)rand()/(RAND_MAX));

  c = sqrt(-2 * log(a)) * cos(2 * 3.1415 * b);
  d = (standardDeviation * c) + mean;

  //This rounds the float number and converts it to an integer
  num = (int) floor(d + 0.5);

  return num;
}


//-----------

//This generates a new DNA string that is the length of the integer entered.
//The string takes the probability of each nucleotide from the text file
//entered.
string DNA::generateString(int length){
  string newString = "";
  float rangeA = this->probA;
  float rangeT = rangeA + this->probT;
  float rangeC = rangeT + this->probC;
  float rangeG = rangeC + this->probG;

  float num = 0;

  for (int i = 0; i < length; ++i)
  {
    num = ((float)rand()/(RAND_MAX));
    if (num < rangeA)
      newString += 'A';
    else if (num < rangeT)
      newString += 'T';
    else if (num < rangeC)
      newString += 'C';
    else
      newString += 'G';
  }
  return newString;
}
//-----------

//This calculates the total number of strings in the DNA file by counting
//each newline.
float DNA::calcTotalStrings(string DNA){
  int totalString = 0;
  for (int i = 0; i < DNA.size(); ++i)
  {
    if (DNA[i] == '\n')
    {
      totalString += 1;
    }
  }
  this->totalStrings  = totalString;
  return totalString;
}

//-----------
//This opens a new text file and appends the data to it.
void DNA::generateOutFile(string DNA)
{
  ofstream outFS;

  cout<< "Opening and writing to output text file." << endl;
  outFS.open("holland.txt", ios::app);

  outFS << "Name : Kelsey Holland" << endl;
  outFS << "ID : 2298547" << endl;
  outFS << "CPSC 350-02 \n" << endl;

  outFS << "Sum : " << this->sum << endl;
  outFS << "Mean : " << this->mean << endl;
  outFS << "Variance : " << this->variance << endl;
  outFS << "Standard Deviation : " << this->standardDeviation << endl;

  outFS << "Probability A : " << this->probA << endl;
  outFS << "Probability T : " << this->probT << endl;
  outFS << "Probability C : " << this->probC << endl;
  outFS << "Probability] G : " << this->probG << "\n" << endl;

  outFS << "Probability AA : " << probBigram(this->DNASequence, 'A' , 'A') << endl;
  outFS << "Probability AT : " << probBigram(this->DNASequence, 'A' , 'T') << endl;
  outFS << "Probability AC : " << probBigram(this->DNASequence, 'A' , 'C') << endl;
  outFS << "Probability AC : " << probBigram(this->DNASequence, 'A' , 'G') << endl;

  outFS << "Probability TT : " << probBigram(this->DNASequence, 'T' , 'T') << endl;
  outFS << "Probability TA : " << probBigram(this->DNASequence, 'T' , 'A') << endl;
  outFS << "Probability TC : " << probBigram(this->DNASequence, 'T' , 'C') << endl;
  outFS << "Probability TG : " << probBigram(this->DNASequence, 'T' , 'G') << endl;

  outFS << "Probability CC : " << probBigram(this->DNASequence, 'C' , 'C') << endl;
  outFS << "Probability CA : " << probBigram(this->DNASequence, 'C' , 'A') << endl;
  outFS << "Probability CT : " << probBigram(this->DNASequence, 'C' , 'T') << endl;
  outFS << "Probability CG : " << probBigram(this->DNASequence, 'C' , 'G') << endl;

  outFS << "Probability GG : " << probBigram(this->DNASequence, 'G' , 'G') << endl;
  outFS << "Probability GA : " << probBigram(this->DNASequence, 'G' , 'A') << endl;
  outFS << "Probability GT : " << probBigram(this->DNASequence, 'G' , 'T') << endl;
  outFS << "Probability GC : " << probBigram(this->DNASequence, 'G' , 'C') << "\n" <<endl;

  //------
  //This generates the 1000 strings by calling the gaussianDist() method.
  outFS <<"1000 Strings Following Gaussian Distribution : " << endl;
  string gaussianString = "";
  for (int i = 0 ; i < 1000; ++ i)
  {
    gaussianString += generateString(gaussianDist(DNA));
    gaussianString += "\n";
  }
  outFS << gaussianString << endl;

  cout << "End of Writing, closing file." << endl;

  outFS.close();

}

//----------------------------------------------------------
//Accessor methods that return the private variable to the user.
string DNA::getDNASequence()
{
  return DNASequence;
}
float DNA::getSum()
{
  return sum;
}
float DNA::getMean()
{
  return mean;
}
float DNA::getVariance()
{
  return variance;
}
float DNA::getStandardDeviation()
{
  return standardDeviation;
}


//Mutators that change the value of the private variables.
void DNA::setSum(float newSum)
{
  this->sum = newSum;
}
void DNA::setMean(float newMean)
{
  this->mean = newMean;
}
void DNA::setVariance(float newVariance)
{
  this->variance = newVariance;
}
void DNA::setStandardDeviation(float newStandardDeviation)
{
  this->standardDeviation = newStandardDeviation;
}

void DNA::setProbA(float A){
  this->probA = A;
}
void DNA::setProbT(float T){
  this->probT = T;
}
void DNA::setProbC(float C){
  this->probC = C;
}
void DNA::setProbG(float G){
  this->probG = G;
}
