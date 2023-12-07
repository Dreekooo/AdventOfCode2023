#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <map>

void addCopies(std::vector<int> winningNumbers, std::vector<int> playerNumbers, std::map<int, int> &copies, int lineIndex){
    int pairs = 0;
    for(int pNumber : playerNumbers){
        for(int wNumber : winningNumbers){
            if(pNumber == wNumber){
                pairs++;
            }
        }
    }
    for(int i = 0; i < pairs; i++){
        if(copies[lineIndex + 1 + i] == 0)
            copies[lineIndex + 1 + i] = 1;
        copies[lineIndex + 1 + i] += 1 * copies[lineIndex];
    }
}

int createNumber(std::string text, int index, int &number){
    for(int i = 0; i >= 0; i++){
        if(isdigit(text[index + i])){
            number *= 10;
            number += text[index + i] - 48;
        } else{
            return i;
        }
    }
}

void createVectors(std::string line, int &scAmmount, std::map<int, int> &copies, int lineIndex){
    std::vector<int> winningNumbers, playerNumbers;
    int tempNumber;
    std::string tempText = "";
    int startIndex, endIndex;
    startIndex = line.find(':') + 1;
    endIndex = line.find('|');
    tempText.append(line, startIndex, endIndex - startIndex);

    for(int i = 0; i < tempText.length(); i++){
        if(isdigit(tempText[i])){
            tempNumber = 0;
            i += createNumber(tempText, i, tempNumber);
            winningNumbers.push_back(tempNumber);
        }
    }
    tempText = "";
    startIndex = line.find('|') + 1;
    endIndex = line.length();
    tempText.append(line, startIndex, endIndex - startIndex);
    for(int i = 0; i < tempText.length(); i++){
        if(isdigit(tempText[i])){
            tempNumber = 0;
            i += createNumber(tempText, i, tempNumber);
            playerNumbers.push_back(tempNumber);
        }
    }

    if(copies[lineIndex] == 0)
        copies[lineIndex] = 1;
    addCopies(winningNumbers, playerNumbers, copies, lineIndex);
    scAmmount += copies[lineIndex];
}

int main(){
    int scAmmount = 0, lineIndex = 0;
    std::map<int, int> copies; //first int => line index; second int => copies ammount;
    for(std::string line; std::getline(std::cin, line);){
        lineIndex++;
        if(line.empty())
            break;
        createVectors(line, scAmmount, copies, lineIndex);
    }

    std::cout << scAmmount;
return 0;
}
