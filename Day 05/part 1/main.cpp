#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>

std::vector<long long int> getNumbers(std::string numbers);
long long int findLocation(std::vector<std::pair<bool, long long int>> seeds, std::vector<std::string> rows);
void changeToFalse(std::vector<std::pair<bool, long long int>> &vector);
void searchThrough(std::vector<std::pair<bool, long long int>> &numbers, std::string line);
long long int findSmallest(std::vector<std::pair<bool, long long int>> numbers);

int main(){
    std::vector<long long int> numbers;
    std::vector<std::pair<bool, long long int>> seeds;
    std::string tempSeedsLine, seedsLine = "", row;
    long long int lowestLocation = -1, tempLocation;;
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
    numbers = getNumbers(seedsLine);
    for(long long int number : numbers)
        seeds.push_back(std::pair<bool, long long int>(false, number));

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

long long int findLocation(std::vector<std::pair<bool, long long int>> numbers, std::vector<std::string> rows){
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

void changeToFalse(std::vector<std::pair<bool, long long int>> &vector){
    for(long long int i = 0; i < vector.size(); i++)
        vector[i].first = false;
}

void searchThrough(std::vector<std::pair<bool, long long int>> &numbers, std::string line){
    std::vector<long long int> lineNumbers = getNumbers(line);
    for(long long int i = 0; i < numbers.size(); i++){
        if(std::get<bool>(numbers[i]) == false){
            if(std::get<long long int>(numbers[i]) >= lineNumbers[1] && std::get<long long int>(numbers[i]) < lineNumbers[1] + (lineNumbers[2])){
                numbers[i].first = true;
                numbers[i].second += lineNumbers[0] - lineNumbers[1];
            }
        }
    }
}

long long int findSmallest(std::vector<std::pair<bool, long long int>> numbers){
    long long int smallestNumber = -1;
    for(std::pair<bool, long long int> number : numbers){
        if(number.second < smallestNumber || smallestNumber == -1){
            smallestNumber = number.second;
        }
    }

    return smallestNumber;
}