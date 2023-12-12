#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

std::vector<long long int> getNumbers(std::string numbers);
long long int findLocation(std::vector<std::pair<bool, std::pair<long long int, long long int>>> seeds, std::vector<std::string> rows);
void changeToFalse(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &vector);
void searchThrough(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::string line);
long long int findSmallest(std::vector<std::pair<bool, std::pair<long long int, long long int>>> numbers);

void firstPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index);
void secondPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index);
void thirdPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index);
void fourthPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index);

int main(){
    std::vector<long long int> Numbers;
    std::vector<std::pair<bool, std::pair<long long int, long long int>>> seeds;
    std::string tempSeedsLine, seedsLine = "", row;
    long long int lowestLocation = -1, tempLocation;

    std::vector<std::string> rows;
    std::ifstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    tempSeedsLine = rows[0];
    rows.erase(rows.begin());
    seedsLine.append(tempSeedsLine, tempSeedsLine.find(':') + 1, tempSeedsLine.length() - tempSeedsLine.find(':') + 1);
    Numbers = getNumbers(seedsLine);
    for(int i = 0; i < Numbers.size(); i++){
        long long int firstNumber = Numbers[i], secondNumber = Numbers[++i];
        seeds.push_back(std::pair<bool, std::pair<long long int, long long int>>(false, std::pair<long long int, long long int>(firstNumber, secondNumber)));
    }
    lowestLocation = findLocation(seeds, rows);
    std::cout << lowestLocation;

    return 0;
}

std::vector<long long int> getNumbers(std::string numbers){
    long long int tempNumber;
    std::vector<long long int> vecNumbers;
    for(long long int i = 0; i < numbers.length(); i++){
        if(isdigit(numbers[i])){
            tempNumber = numbers[i] - 48;
            while(true){
                if(isdigit(numbers[i + 1])){
                    i++;
                    tempNumber *= 10;
                    tempNumber += numbers[i] - 48;
                } else{
                    vecNumbers.push_back(tempNumber);
                    break;
                }
            }
        }
    }
    return vecNumbers;
}

long long int findLocation(std::vector<std::pair<bool, std::pair<long long int, long long int>>> numbers, std::vector<std::string> rows){
    std::vector<long long int> Locations;
    long long int smallestLocation;
    for(std::string line : rows){
        if(line.empty()){
            changeToFalse(numbers);
            continue;
        }
        if(line.find(':') != std::string::npos)
            continue;
        if(isdigit(line[0])){
            searchThrough(numbers, line);
        }
    }
    smallestLocation = findSmallest(numbers);

    
    return smallestLocation;
}

void changeToFalse(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &vector){
    for(long long int i = 0; i < vector.size(); i++)
        vector[i].first = false;
}

void searchThrough(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::string line){
    std::vector<long long int> lineNumbers = getNumbers(line);
    for(long long int i = 0; i < numbers.size(); i++){
        long long X = std::get<0>(std::get<1>(numbers[i]));
        long long Y = std::get<0>(std::get<1>(numbers[i])) + std::get<1>(std::get<1>(numbers[i]));
        long long Z = lineNumbers[1] + lineNumbers[2];
        if(std::get<bool>(numbers[i]) == false){
            if(X > lineNumbers[1] && Y > lineNumbers[1] && X < Z && Y > Z){
                firstPossibility(numbers, lineNumbers, i); //line < X < Z < Y      => only right side   => seeds left side
            } else if(X >= lineNumbers[1] && Y >= lineNumbers[1] && X <= Z && Y <= Z){
                secondPossibility(numbers, lineNumbers, i); //line < X < Y < Z     => only middle       => seeds full
            } else if(X < lineNumbers[1] && Y > lineNumbers[1] && X < Z && Y < Z){
                thirdPossibility(numbers, lineNumbers, i); //X < line < Y < Z      => only left side    => seeds right side
            } else if(X <= lineNumbers[1] && Y >= lineNumbers[1] && X <= Z && Y >= Z){
                fourthPossibility(numbers, lineNumbers, i); //X < line < Z < Y     => full              => seeds middle
            }
        }
    }
}

long long int findSmallest(std::vector<std::pair<bool, std::pair<long long int, long long int>>> numbers){
    long long int smallestNumber = -1;
    for(std::pair<bool, std::pair<long long int, long long int>> number : numbers){
        if(std::get<0>(std::get<1>(number)) < smallestNumber || smallestNumber == -1){
            smallestNumber = std::get<0>(std::get<1>(number));
        }
    }

    return smallestNumber;
}

void firstPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index){
    std::pair<bool, std::pair<long long int, long long int>> leftSide, rightSide;
    std::pair<long long int, long long int> currNumbers = std::get<1>(numbers[index]);
    leftSide = std::make_pair<bool, std::pair<long long int, long long int>> (true, std::make_pair<long long int, long long int>(std::get<0>(currNumbers) + (lineNumbers[0] - lineNumbers[1]), lineNumbers[1] + lineNumbers[2] - std::get<0>(currNumbers)));
    rightSide = std::make_pair<bool, std::pair<long long int, long long int>> (false, std::make_pair<long long int, long long int> (lineNumbers[1] + lineNumbers[2], std::get<1>(currNumbers) - (lineNumbers[1] + lineNumbers[2] - std::get<0>(currNumbers))));
    numbers.erase(numbers.begin() + index);
    numbers.push_back(leftSide);
    numbers.push_back(rightSide);
}
void secondPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index){
    numbers[index].second.first += lineNumbers[0] - lineNumbers[1];
    numbers[index].first = true;
}
void thirdPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index){
    std::pair<bool, std::pair<long long int, long long int>> leftSide, rightSide;
    std::pair<long long int, long long int> currNumbers = std::get<1>(numbers[index]);
    leftSide = std::make_pair<bool, std::pair<long long int, long long int> > (false, std::make_pair<long long int, long long int>(currNumbers.first + 0, lineNumbers[1] - currNumbers.first));
    rightSide = std::make_pair<bool, std::pair<long long int, long long int>> (true, std::make_pair<long long int, long long int> (lineNumbers[0] + 0, currNumbers.second - lineNumbers[1] + currNumbers.first));
    numbers.erase(numbers.begin() + index);
    numbers.push_back(leftSide);
    numbers.push_back(rightSide);
}
void fourthPossibility(std::vector<std::pair<bool, std::pair<long long int, long long int>>> &numbers, std::vector<long long int> lineNumbers, int index){
    std::pair<bool, std::pair<long long int, long long int>> leftSide, middle, rightSide;
    std::pair<long long int, long long int> currNumbers = std::get<1>(numbers[index]);
    leftSide = std::make_pair<bool, std::pair<long long int, long long int>> (false, std::make_pair<long long int, long long int>(currNumbers.first + 0, lineNumbers[1] - currNumbers.first));
    middle = std::make_pair<bool, std::pair<long long int, long long int>> (true, std::make_pair<long long int, long long int> (lineNumbers[0] + 0, lineNumbers[2] + 0));
    rightSide = std::make_pair<bool, std::pair<long long int, long long int>> (false, std::make_pair<long long int, long long int> (lineNumbers[1] + lineNumbers[2], std::get<1>(currNumbers) - (lineNumbers[1] + lineNumbers[2] - std::get<0>(currNumbers))));
    numbers.erase(numbers.begin() + index);
    numbers.push_back(leftSide);
    numbers.push_back(middle);
    numbers.push_back(rightSide);
}