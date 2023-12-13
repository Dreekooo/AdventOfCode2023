#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

void solve(std::vector<std::string> rows);
std::vector<long long int> separateNumbers(std::string row);
long long int findNextNum(std::vector<long long int> numbers);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    solve(rows);

    return 0;
}

void solve(std::vector<std::string> rows){
    long long int sum = 0;
    std::vector<std::vector<long long int>> numbers;

    for(long long int i = 0; i < rows.size(); i++)
        numbers.push_back(separateNumbers(rows[i]));

    for(int i = 0; i < numbers.size(); i++){
        std::reverse(numbers[i].begin(), numbers[i].end());
    }

    for(long long int i = 0; i < numbers.size(); i++){
        sum += findNextNum(numbers[i]);
    }

    std::cout << sum;
}

std::vector<long long int> separateNumbers(std::string row){
    std::vector<long long int> numbers;
    long long int tempNumber = 0;
    bool minus = false;
    for(long long int i = 0; i < row.length(); i++){
        if(row[i] == '-')
            minus = true;
        if(isdigit(row[i])){
            tempNumber += row[i] - 48;
            while(true){
                i++;
                if(isdigit(row[i])){
                    tempNumber *= 10;
                    tempNumber += row[i] - 48;
                } else{
                    i--;
                    if(minus)
                        tempNumber *= -1;
                    numbers.push_back(tempNumber);
                    tempNumber = 0;
                    minus = false;
                    break;
                }
            }
        }
    }
    return numbers;
}

long long int findNextNum(std::vector<long long int> numbers){
    long long int nextNum = 0;
    std::vector<std::vector<long long int>> numRows;
    std::vector<long long int> tempVec;
    bool end = false;
    numRows.push_back(numbers);

    while(!end){
        end = true;

        for(long long int i = 0; i < numRows[numRows.size() - 1].size() - 1; i++){
            tempVec.push_back((numRows[numRows.size() - 1][i + 1] - numRows[numRows.size() - 1][i]));
        }
        numRows.push_back(tempVec);
        tempVec.clear();

        for(long long int i = 0; i < numRows[numRows.size() - 1].size(); i++)
            if(numRows[numRows.size() - 1][i] != 0)
                end = false;
    }
    for(long long int i = numRows.size() - 1; i > 0; i--){
        nextNum += numRows[i - 1][numRows[i - 1].size() - 1];
    }
    return nextNum;
}