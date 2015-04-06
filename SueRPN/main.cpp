//
//  main.cpp
//  SueRPN
//
//  Created by cj on 4/6/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>




using namespace std;

enum TOKEN { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, NUMBER };

/*
input:  123 2 + 50 25 25 + + *
 (123+2) | 25 + 25 + 50|
   125       100
 125 * 100
output: 12500
input:  99999999999999999999999999999999999999999999999 2 * 1 -
 2 *  999....  - 1
output: 199999999999999999999999999999999999999999999997
input:  -3 -4 *
output: 12
*/
string myinputstring = "123 + 231";
string usecase2 ="5 1 2 + 4 * + 3 -";
string usecase3 ="123 2 + 50 25 25 + + *";

vector<string> parseString(string inputString){

    vector<string> parsedInput;
    
    string token;
    stringstream stringStream(inputString);
    
    while(getline(stringStream,token,' ')){
        parsedInput.push_back(token);
        //cout << token << " " << endl;
    }
    
    return parsedInput;
}

//if its + * / .... assume it is a operator
// if it is a - .... we need to check to see if there is a following.

void option1(vector<string> parsedInput){
    

    for(int i = 0; i < parsedInput.size(); i++){
        
        if(parsedInput[i] == "+" || parsedInput[i] == "*" || parsedInput[i] == "/" || parsedInput[i] == "-" ){
            
            cout <<  parsedInput[i] <<" is an operator "<< endl;
            
        }else{
            cout <<  parsedInput[i] <<" is a number "<< endl;
        }
        
    }

}



TOKEN tokenDetector(string s){
    
    if(s == "+" || s == "*" || s == "x" || s == "X" || s == "/" || s == "\\"  || s == "-" ){
        
        //cout <<  s <<" is an operator "<<  endl;
        
        if(s == "+" ){
            return ADDITION;
        }else if(s == "*" || s == "x" || s == "X" ){
            return MULTIPLICATION;
        }else if (s == "/" || s == "\\" ){
            return DIVISION;
        }else if (s == "-"){
            return SUBTRACTION;
        }else{
            cout << "Error" << endl;
            return NUMBER;
        }

    }else{
        //cout <<  s <<" is a number "<< endl;
        return NUMBER;
    }
    
}



void RPNCalcuator(vector<string>parsedInput){
    
    vector<int> myStack;
    for(int i = 0; i < parsedInput.size(); i++){
        if(tokenDetector(parsedInput[i]) != NUMBER){
            //If it is an operator -- Do some math
            
            //pop last two values
            int second = myStack.back();
            myStack.pop_back();
            int first = myStack.back();
            myStack.pop_back();
            
            int result;
            
            //Determine which operator &
            //do the calcuation
            TOKEN oper = tokenDetector(parsedInput[i]);
            switch (oper){
                    case ADDITION:

                    result = first + second;
                    
                    break;
                case DIVISION:
                    if(second != 0){
                        result = first / second;
                    }else{
                        cout << "Attempted to divide by 0" << endl;
                        return;
                    }

                    break;
                case SUBTRACTION:
                    result = first - second;
                    
                    break;
                case MULTIPLICATION:
                    result = first * second;
                    
                    break;
                    
                default:
                    cout<< "Error: Operator not found" << endl;
            }
            cout <<  result << " " << first << " " << second << endl;
            
            //Push the result back onto the stack
            myStack.push_back(result);
            
        }else{
            //If it is a number -- just add it to the stack.
            myStack.push_back(atoi(parsedInput[i].c_str()));
        }
    }
    
    cout << "My Calculation: " << myStack.back() << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<string> parsedInput = parseString(usecase3);
    //option1(parsedInput);
    RPNCalcuator(parsedInput);
    
    return 0;
}
