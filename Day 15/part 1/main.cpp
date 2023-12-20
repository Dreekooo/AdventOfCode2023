#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int solve(std::vector<std::string> rows);
int checkValue(std::string row);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");
    int answer;

    if(file.is_open()){
        while(std::getline(file, row, ',')){
            rows.push_back(row);
        }
    }

    file.close();

    answer = solve(rows);
    std::cout << answer;
    
    return 0;
}

int solve(std::vector<std::string> rows){
    int sum = 0;
    for(std::string row : rows){
        sum += checkValue(row);
    }
    return sum;
}

int checkValue(std::string row){
    int value = 0;
    for(int i = 0; i < row.length(); i++){
        value += row[i];
        value *= 17;
        value %= 256;
    }
    return value;
}