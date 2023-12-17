#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct pattern
{
    bool horizontal = false, vertical = false;
    int mirrorIndex = 0;
};


void solve(std::vector<std::string> rows);
void getPatterns(std::vector<std::string> rows, std::vector<std::vector<std::string>> &patterns);
pattern patternSolver(std::vector<std::string> patternRows);
bool checkHorizontal(std::vector<std::string> patternRows, int index);
std::vector<std::string> reversePattern(std::vector<std::string> &patternRows);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");

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
    std::vector<std::vector<std::string>> patterns;
    std::vector<pattern> structVec;
    getPatterns(rows, patterns);
    int answer = 0, tempValue;

    for(int i = 0; i < patterns.size(); i++){
        structVec.push_back(patternSolver(patterns[i]));
    }

    for(pattern p : structVec){
        tempValue = p.mirrorIndex + 1;
        if(p.horizontal)
            tempValue *= 100;
        answer += tempValue;
    }
    std::cout << answer;
}

void getPatterns(std::vector<std::string> rows, std::vector<std::vector<std::string>> &patterns){
    std::vector<std::string> tempVector;
    for(std::string row : rows){
        if(row == ""){
            patterns.push_back(tempVector);
            tempVector.clear();
            continue;
        }

        tempVector.push_back(row);
    }
    patterns.push_back(tempVector);
}

pattern patternSolver(std::vector<std::string> patternRows){
    pattern p;
    int mirrorIndex;
    bool horizontal = false; 

    //check horizontal
    for(int i = 0; i < patternRows.size() - 1; i++){
        if(patternRows[i] == patternRows[i + 1]){
            horizontal = checkHorizontal(patternRows, i);
            if(horizontal){
                mirrorIndex = i;
                break;
            }
        }
    }

    if(horizontal){
        p.horizontal = true;
        p.mirrorIndex = mirrorIndex;
        return p;
    }

    //check vertical
    patternRows = reversePattern(patternRows);
    for(int i = 0; i < patternRows.size() - 1; i++){
        if(patternRows[i] == patternRows[i + 1]){
            horizontal = checkHorizontal(patternRows, i);
            if(horizontal){
                mirrorIndex = i;
                break;
            }
        }
    }

    p.vertical = true;
    p.mirrorIndex = mirrorIndex;
    return p;
}

bool checkHorizontal(std::vector<std::string> patternRows, int index){
    int bottomIndex = index + 1;
    while(index >= 0 && bottomIndex < patternRows.size()){
        if(patternRows[index] == patternRows[bottomIndex]){
            index--;
            bottomIndex++;
        } else{
            return false;
        }
    }
    return true;
}

std::vector<std::string> reversePattern(std::vector<std::string> &patternRows){
    std::vector<std::string> tempVector;
    std::string tempString;
    for(int i = 0; i < patternRows.size(); i++){
        for(int j = 0; j < patternRows[i].length(); j++){
            tempString = "";
            if(j < tempVector.size()){
                tempString = tempVector[j];
            }
            tempString += patternRows[i][j];
            if(j < tempVector.size())
                std::swap(tempVector[j], tempString);
            else
                tempVector.push_back(tempString);
        }
    }

    return tempVector;
}