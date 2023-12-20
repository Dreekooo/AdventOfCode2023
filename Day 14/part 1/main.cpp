#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void solve(std::vector<std::string> rows);
void moveRocks(std::vector<std::string> &rows);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::fstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    file.close();

    solve(rows);

    return 0;
}

void solve(std::vector<std::string> rows){
    int totalLoad = 0;
    moveRocks(rows);

    for(int y = rows.size(); y > 0; y--){
        for(int x = 0; x < rows[0].length(); x++){
            if(rows[rows.size() - y][x] == 'O')
                totalLoad += y;
        }
    } 

    std::cout << totalLoad;
}

void moveRocks(std::vector<std::string> &rows){
    int rocksIndex;
    for(int x = 0; x < rows[0].length(); x++){
        rocksIndex = 0;
        for(int y = 0; y < rows.size(); y++){
            if(rows[y][x] == '#'){
                rocksIndex = y + 1;
                continue;
            } else if(rows[y][x] == 'O'){
                rows[y][x] = '.';
                rows[rocksIndex][x] = 'O';
                rocksIndex++;
            }
        }
    }
}