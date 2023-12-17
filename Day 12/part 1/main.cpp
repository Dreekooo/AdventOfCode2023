#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void solve(std::vector<std::string> rows){
    
}

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("test_input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    file.close();

    solve(rows);

    return 0;
}