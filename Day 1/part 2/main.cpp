#include <iostream>
#include <string>
#include <cctype>

int main() {
    int sum = 0, left = -1, right = -1, firstIndex = -1, lastIndex = -1, firstNumber = -1, lastNumber = -1;
    std::string numbers[10] = { "~", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    for (std::string value; std::getline(std::cin, value);) {
        if (value.empty())
            break;
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
        std::cout << "left: " << left << "\nright: " << right << "\nleftIndex: " << firstIndex << "\nrightIndex: " << lastIndex << "\nfirstNumber: " << firstNumber << "\nlastNumber: " << lastNumber << "\nsuma: " << sum << " + " << (left * 10) + right << " = " << sum + (left * 10) + right << "\n\n";
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

    return 0;
}