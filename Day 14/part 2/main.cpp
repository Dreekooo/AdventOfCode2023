#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void solve(std::vector<std::string> rows);
void moveRocksNorth(std::vector<std::string> &rows);
void moveRocksEast(std::vector<std::string> &rows);
void moveRocksSouth(std::vector<std::string> &rows);
void moveRocksWest(std::vector<std::string> &rows);
bool checkLoop(std::vector<std::string> rows, std::vector<std::vector<std::string>> &saveRows, int &iterator);

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
    int totalLoad = 0;
    bool loopFound = false;

    std::vector<std::vector<std::string>> saveRows;
    saveRows.push_back(rows);

    for(int i = 0; i <= 1000000000; i++){
        moveRocksNorth(rows);
        if(!loopFound){
            loopFound = checkLoop(rows, saveRows, i);
            saveRows.push_back(rows);
        }

        moveRocksWest(rows);
        if(!loopFound){
            if(!loopFound){
                loopFound = checkLoop(rows, saveRows, i);
            }
            saveRows.push_back(rows);
        }


        moveRocksSouth(rows);
        if(!loopFound){
            if(!loopFound){
                loopFound = checkLoop(rows, saveRows, i);
            }
            saveRows.push_back(rows);
        }


        moveRocksEast(rows);
        if(!loopFound){
            if(!loopFound){
                loopFound = checkLoop(rows, saveRows, i);
            }
            saveRows.push_back(rows);
        }
    }


    for(int y = rows.size(); y > 0; y--){
        for(int x = 0; x < rows[0].length(); x++){
            if(rows[rows.size() - y][x] == 'O')
                totalLoad += y;
        }
    } 

    std::cout << totalLoad;
}

void moveRocksNorth(std::vector<std::string> &rows){
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

void moveRocksWest(std::vector<std::string> &rows){
    int rocksIndex;
    for(int y = 0; y < rows.size(); y++){
        rocksIndex = 0;
        for(int x = 0; x < rows[0].length(); x++){
            if(rows[y][x] == '#'){
                rocksIndex = x + 1;
                continue;
            } else if(rows[y][x] == 'O'){
                rows[y][x] = '.';
                rows[y][rocksIndex] = 'O';
                rocksIndex++;
            }
        }
    }
}
void moveRocksSouth(std::vector<std::string> &rows){
    int rocksIndex;
    for(int x = 0; x < rows[0].length(); x++){
        rocksIndex = rows.size() - 1;
        for(int y = rows.size() - 1; y >= 0; y--){
            if(rows[y][x] == '#'){
                rocksIndex = y - 1;
                continue;
            } else if(rows[y][x] == 'O'){
                rows[y][x] = '.';
                rows[rocksIndex][x] = 'O';
                rocksIndex--;
            }
        }
    }
}
void moveRocksEast(std::vector<std::string> &rows){
    int rocksIndex;
    for(int y = 0; y < rows.size(); y++){
        rocksIndex = rows[0].length() - 1;
        for(int x = rows[0].length() - 1; x >= 0; x--){
            if(rows[y][x] == '#'){
                rocksIndex = x - 1;
                continue;
            } else if(rows[y][x] == 'O'){
                rows[y][x] = '.';
                rows[y][rocksIndex] = 'O';
                rocksIndex--;
            }
        }
    }
}

bool checkLoop(std::vector<std::string> rows, std::vector<std::vector<std::string>> &saveRows, int &iterator){
    bool loopFound = false;
    for(int j = 0; j < saveRows.size(); j++){
        if(rows == saveRows[j]){
            iterator = 1000000000 - j;
            loopFound = true;
        }
    }
    return loopFound;
}