#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

void solve(std::vector<std::string> rows);
void findStart(std::vector<std::string> rows, int &X, int &Y);

int main()
{
    std::ifstream file("test_input_1.txt");
    std::string row;
    std::vector<std::string> rows;

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
    int X = 0, Y = 0, iteration = 0;
    std::map<std::pair<int, int>, int> madeSteps;
    findStart(rows, X, Y);
    madeSteps.insert(std::make_pair(std::make_pair(X, Y), iteration));
    iteration++;
    
}

void findStart(std::vector<std::string> rows, int &X, int &Y){
    bool found = false;
    while(!found){
        for(X = 0; X < rows[Y].length(); X++){
            if(rows[Y][X] == 'S'){
                found = true;
                break;
            }
        }
        if(!found)
            Y++;
    }
}
