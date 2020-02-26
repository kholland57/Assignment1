
/*
Kelsey Holland
002298547
kholland@chapman.edu
CPSC-350-02
Assignment 1
*/


//Libraries included here
#include <iostream>
#include <string>

using namespace std;

//Class DNA header
class DNA{

  public:
    //Constructors
    DNA();
    DNA(string DNA);
    ~DNA();

    //---------------------
    //Calculation Functions for each variable
    int calcSum(string DNA);
    float calcMean(string DNA);
    float calcVariance(string DNA);
    float calcTotalStrings(string DNA);
    float calcStandardDeviation(string DNA);
    float probNucleotide(string DNA, char N);
    float probBigram(string DNA, char letterOne, char letterTwo);
    int gaussianDist(string DNA);

    //Output file and string generators.
    string generateString(int length);
    void generateOutFile(string DNA);

    //---------------------
    //Accessors
    string getDNASequence();
    float getSum();
    float getMean();
    float getVariance();
    float getStandardDeviation();

    //Mutators
    void setSum(float newSum);
    void setMean(float newMean);
    void setVariance(float newVariance);
    void setStandardDeviation(float newStandardDeviation);

    void setProbA(float A);
    void setProbT(float T);
    void setProbC(float C);
    void setProbG(float G);

//Private variables and methods that the user cannot directly access.
  private:
    string UpperCase(string DNA);

    string DNASequence;
    int totalStrings;

    float sum;
    float mean;
    float variance;
    float standardDeviation;
    //float nucleotideProb;
    //float bigramProb;

    float probA;
    float probT;
    float probG;
    float probC;
};
