#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

void solve(std::vector<std::string> rows) {
    int sum = 0, left = 0, right = 0;
    for (std::string value : rows) {
        for (int i = 0; i < value.length(); i++) {
            if (isdigit(value[i])) {
                if (left == 0)
                    left = value[i] - 48;
                right = value[i] - 48;
            }
        }
        sum += (left * 10) + right;
        left = 0;
        right = 0;
    }
    std::cout << sum;
}

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