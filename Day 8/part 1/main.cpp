#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <chrono>

void solve(std::vector<std::string> rows);
std::map<std::string, std::pair<std::string, std::string>> mappingRows(std::vector<std::string> rows);


int main(){
    std::string row;
    std::vector<std::string> rows;
    std::fstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    auto start = std::chrono::high_resolution_clock::now(); // Start time
    solve(rows);
    // Code snippet
    auto stop = std::chrono::high_resolution_clock::now(); // Stop time
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start); // Duration
    printf("\nTime measured: %.6f seconds.\n", duration.count() * 1e-9);

    return 0;
}

void solve(std::vector<std::string> rows){
    std::map<std::string, std::pair<std::string, std::string>> map;
    std::string pattern = rows[0];
    map = mappingRows(rows);
    std::string currentValue = map.begin()->first;
    int patternIndex = 0, steps = 0;
    
    while(currentValue != "ZZZ"){
        if(pattern[patternIndex] == 'L')
            currentValue = std::get<0>(map[currentValue]);
        else
            currentValue = std::get<1>(map[currentValue]);

        patternIndex++;
        steps++;
        if(patternIndex >= pattern.length())
            patternIndex = 0;
    }
    std::cout << steps;
}

std::map<std::string, std::pair<std::string, std::string>> mappingRows(std::vector<std::string> rows){
    std::string value1 = "", value2 = "", value3 = "";
    std::map<std::string, std::pair<std::string, std::string>> map;
    for(int i = 2; i < rows.size(); i++){
        value1.append(rows[i], 0, 3);
        value2.append(rows[i], 7, 3);
        value3.append(rows[i], 12, 3);
        map.insert(std::make_pair(value1, std::make_pair(value2, value3)));
        value1 = "";
        value2 = "";
        value3 = "";
    }
    return map;
}