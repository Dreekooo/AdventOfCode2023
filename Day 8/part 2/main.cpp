#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <numeric>

void solve(std::vector<std::string> rows);
std::map<std::string, std::pair<std::string, std::string>> mappingRows(std::vector<std::string> rows);
std::vector<std::string> findPaths(std::map<std::string, std::pair<std::string, std::string>> map);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::fstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    solve(rows);

    return 0;
}

void solve(std::vector<std::string> rows){
    std::map<std::string, std::pair<std::string, std::string>> map;
    std::vector<std::string> paths;
    std::string pattern = rows[0];
    map = mappingRows(rows);
    paths = findPaths(map);
    int patternIndex = 0, steps = 0;
    bool end = false;

    std::map<std::string, int> mapValues;
    std::vector<int> values;
    unsigned long long answer = 1;

    while(!end){
        steps++;
        for(std::string &value : paths){
            if(pattern[patternIndex] == 'L')
                value = std::get<0>(map[value]);
            else
                value = std::get<1>(map[value]);

            if(value[2] == 'Z' && mapValues.find(value) == mapValues.end()){
                mapValues.insert(std::make_pair(value, steps));
            } else if(value[2] == 'Z'){
                for(std::map<std::string, int>::iterator i = mapValues.begin(); i != mapValues.end(); i++)
                    values.push_back(i->second);

                for(int i = values.size() - 1; i >= 0; i--){
                    answer = std::lcm(answer, values[i]);
                }

                end = true;
                std::cout << '\n' << answer;
            }
        }
        patternIndex++;
        if(patternIndex >= pattern.length())
            patternIndex = 0;      
    }
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

std::vector<std::string> findPaths(std::map<std::string, std::pair<std::string, std::string>> map){
    std::vector<std::string> paths;
    for(auto &i : map){
        if(i.first[2] == 'A')
            paths.push_back(i.first);
    }
    return paths;
}