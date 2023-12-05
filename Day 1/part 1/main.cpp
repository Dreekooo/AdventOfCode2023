#include <iostream>
#include <string>
#include <cctype>

int main() {
    int sum = 0, left = NULL, right = NULL;
    for (std::string value; std::getline(std::cin, value);) {
        if (value.empty())
            break;
        for (int i = 0; i < value.length(); i++) {
            if (isdigit(value[i])) {
                if (left == NULL)
                    left = value[i] - 48;
                right = value[i] - 48;
            }
        }
        sum += (left * 10) + right;
        left = NULL;
        right = NULL;
    }
    std::cout << sum;
    
    return 0;
}