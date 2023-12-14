#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

void solve(std::vector<std::string> rows) {
    int sum = 0, left = -1, right = -1, firstIndex = -1, lastIndex = -1, firstNumber = -1, lastNumber = -1;
    std::string numbers[10] = { "~NULL", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (std::string value : rows) {
        for (int i = 0; i < 10; i++) {
            if (value.find(numbers[i]) != std::string::npos) {
                if (firstIndex == -1 || (firstIndex != -1 && value.find(numbers[i]) < firstIndex)) {
                    firstIndex = value.find(numbers[i]);
                    firstNumber = i;
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            if (value.rfind(numbers[i]) != std::string::npos) {
                if (lastIndex == -1 || (lastIndex != -1 && value.rfind(numbers[i]) > lastIndex)) {
                    lastIndex = value.rfind(numbers[i]);
                    lastNumber = i;
                }
            }
        }
        for (int i = 0; i < value.length(); i++) {
            if (isdigit(value[i])) {
                if (left == -1) {
                    if (i < firstIndex || firstIndex == -1)
                        left = value[i] - 48;
                    else
                        left = firstNumber;
                }
                if (i > lastIndex)
                    right = value[i] - 48;
                else
                    right = lastNumber;
            }
        }
        if (left == -1 && right == -1 && firstNumber != -1 && lastNumber != -1) {
            left = firstNumber;
            right = lastNumber;
        }
        if (left != -1 && right != -1)
            sum += (left * 10) + right;
        left = -1;
        right = -1;
        firstIndex = -1;
        lastIndex = -1;
        firstNumber = -1;
        lastNumber = -1;
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