#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

int countPoints(std::vector<int> winningNumbers, std::vector<int> playerNumbers){
    int points = 0;
    for(int pNumber : playerNumbers){
        for(int wNumber : winningNumbers){
            if(pNumber == wNumber){
                if(points == 0)
                    points = 1;
                else
                    points *= 2;
                break;
            }
        }
    }

    return points;
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

void createVectors(std::string line, int &cardPoints){
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

    cardPoints = countPoints(winningNumbers, playerNumbers);
}

int main(){
    int sum = 0, cardPoints;
    std::string row;
    std::ifstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            cardPoints = 0;
            createVectors(row, cardPoints);
            sum += cardPoints;
        }
    }

    std::cout << sum;
return 0;
}
