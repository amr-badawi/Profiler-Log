#include <iostream> 
#include <string> 
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



int main()
{
    string myLine;
    string myText;

    // Read from the text file
    ifstream MyReadFile("input.txt");


    //reading file to a string  
    while (getline(MyReadFile, myLine)) {
        myText += "\n" + myLine;
    }

    //adding code to output a logFile.txt from the new program after instrumentation
    size_t found = myText.find("std;");
    myText.replace(found+5, 1, "ofstream f;");


    //Instrumentation
    found = myText.find("FunctionA",found +1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f << \" FunctionA Starts  \" << endl ; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, "f << \" FunctionA Ends  \" << endl ; ");

    found = myText.find("FunctionB", found + 1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f << \" FunctionB Starts  \" << endl ; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, "f << \" FunctionB Ends  \" << endl ; ");

    found = myText.find("FunctionC", found + 1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f << \" FunctionC Starts  \" << endl; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, "f << \" FunctionC Ends  \" << endl; ");

    found = myText.find("FunctionD", found + 1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f << \" FunctionD Starts  \"<< endl ; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, "f << \" FunctionD Ends  \"<< endl ; ");

    found = myText.find("FunctionE", found + 1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f << \" FunctionE Starts  \" << endl; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, "f << \" FunctionE Ends  \" << endl; ");

    found = myText.find("main", found + 1);
    found = myText.find("{", found + 1);
    myText.replace(found, 1, "{ f.open(\"Log File.txt\");  f << \"Log File \\n \"; f << \" Main Starts  \" << endl; ");
    found = myText.find(" return", found + 1);
    myText.replace(found, 1, " f << \" Main Ends  \" << endl; f.close();");




    //writing the new program in a new txt File
    ofstream MyFile("output.txt");
    MyFile << myText;

    MyFile.close();
    MyReadFile.close();



    //Convert to .cpp then Compile .cpp then run the .exe 

    system("rename output.txt output.cpp");
    system("g++ output.cpp -o Logfile.exe");
    system("start Logfile.exe");

    //Convert from .cpp to .txt again for the next run
         system("rename output.cpp output.txt");

    return 0;


}