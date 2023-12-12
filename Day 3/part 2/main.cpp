#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>

void getText(std::vector<std::string> &text);
void findStar(std::vector<std::string> text, int &sum);
void findNumbers(std::vector<std::string> text, int lineIndex, int starIndex, int &firstNumber, int &secondNumber);
int setNumber(std::vector<std::string> text, std::string line, int foundIndex);

int main(){
    std::string row;
    std::vector<std::string> text;
    std::ifstream file("input.txt");
    int sum = 0;
    
    if(file.is_open()){
        while(std::getline(file, row)){
            text.push_back(row);
        }
    }
    findStar(text, sum);

    std::cout << sum;
}

void getText(std::vector<std::string> &text){
    for(std::string line; std::getline(std::cin, line);){
        if(line.empty())
            break;
        text.push_back(line);
    }
}

void findStar(std::vector<std::string> text, int &sum){
    int starIndex;
    int lineIndex = 0;
    int firstNumber = 0, secondNumber = 0;
    for(std::string line : text){
        for(int i = 0; i < line.length(); i++){
            if(line[i] == '*'){
                starIndex = i;
                findNumbers(text, lineIndex, starIndex, firstNumber, secondNumber);
                if(firstNumber != 0 && secondNumber != 0 && firstNumber != secondNumber){
                    sum += firstNumber * secondNumber;
                    firstNumber = 0;
                    secondNumber = 0;
                } else{
                    firstNumber = 0;
                    secondNumber = 0;
                }
            }
        }
        lineIndex++;
    }
}

void findNumbers(std::vector<std::string> text, int lineIndex, int starIndex, int &firstNumber, int &secondNumber){
    std::string aboveLine = text[lineIndex - 1], thisLine = text[lineIndex];
    //line above
    for(int i = 0; i < 3; i++){
        if(isdigit(aboveLine[(starIndex - 1) + i])){
            if(firstNumber == 0){
                firstNumber = setNumber(text, aboveLine, ((starIndex - 1) + i));
            } else{
                secondNumber = setNumber(text, aboveLine, ((starIndex - 1) + i));
            }
        }
    }
    //this line
    if(isdigit(thisLine[starIndex - 1])){
        if(firstNumber == 0){
            firstNumber = setNumber(text, thisLine, (starIndex - 1));
        } else{
            secondNumber = setNumber(text, thisLine, (starIndex - 1));
        }
    }
    if(isdigit(thisLine[starIndex + 1])){
        if(firstNumber == 0){
            firstNumber = setNumber(text, thisLine, (starIndex + 1));
        } else{
            secondNumber = setNumber(text, thisLine, (starIndex + 1));
        }
    }
    //line under
    if(lineIndex != text.size() - 1){
        std::string underLine = text[lineIndex+1];
        for(int i = 0; i < 3; i++){
            if(isdigit(underLine[(starIndex - 1) + i])){
                if(firstNumber == 0){
                    firstNumber = setNumber(text, underLine, ((starIndex - 1) + i));
                } else{
                    secondNumber = setNumber(text, underLine, ((starIndex - 1) + i));
                }
            }
        }
    }

    if(firstNumber == 0 || secondNumber == 0){
        firstNumber = 0;
        secondNumber = 0;
    }
}


int setNumber(std::vector<std::string> text, std::string line, int foundIndex){
    while(true){
        if(isdigit(line[foundIndex - 1]))
            foundIndex--;
        else
            break;
    }

    int number = line[foundIndex] - 48;
    while(true){
        if(isdigit(line[++foundIndex])){
            number *= 10;
            number += line[foundIndex] - 48;
        } else
            break;
    }

    return number;
}

