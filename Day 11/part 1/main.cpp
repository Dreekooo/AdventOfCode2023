#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct galaxy
{
    int X;
    int Y;
};


void solve(std::vector<std::string> rows);
void editVector(std::vector<std::string> &rows);
int findLengths(std::vector<galaxy> galaxies, int galaxyIndex);

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

void solve(std::vector<std::string> rows){
    editVector(rows);
    int sumOfLengths = 0;
    galaxy G;
    std::vector<galaxy> galaxies;

    for(int i = 0; i < rows.size(); i++){
        for(int j = 0; j < rows[i].length(); j++){
            if(rows[i][j] == '#'){
                G.X = j;
                G.Y = i;
                galaxies.push_back(G);
            }
        }
    }

    for(int i = 0; i < galaxies.size(); i++){
        sumOfLengths += findLengths(galaxies, i);
    }
    std::cout << sumOfLengths;
}

void editVector(std::vector<std::string> &rows){
    bool noGalaxies;
    for(int i = 0; i < rows.size(); i++){
        noGalaxies = true;
        for(int j = 0; j < rows[i].size(); j++){
            if(rows[i][j] == '#'){
                noGalaxies = false;
                break;
            }
        }
        if(noGalaxies){
            rows.insert(rows.begin() + i, rows[i]);
            i++;
        }    
    }
    for(int i = 0; i < rows[0].size(); i++){
        noGalaxies = true;
        for(int j = 0; j < rows.size(); j++){
            if(rows[j][i] == '#'){
                noGalaxies = false;
                break;
            }
        }
        if(noGalaxies){
            for(int j = 0; j < rows.size(); j++){
                std::string tempRow = "";
                tempRow.append(rows[j], 0, i + 1);
                tempRow += ".";
                tempRow.append(rows[j], i + 1, rows[j].length() - i - 1);
                rows[j] = tempRow; 
            }
            i++;
        }
    }    
}

int findLengths(std::vector<galaxy> galaxies, int galaxyIndex){
    int sumOfLengths = 0, tempX, tempY;
    int current_X = galaxies[galaxyIndex].X;
    int current_Y = galaxies[galaxyIndex].Y;

    for(int i = galaxyIndex + 1; i < galaxies.size(); i++){
        tempX = galaxies[i].X;
        tempY = galaxies[i].Y;

        if(current_X > tempX){
            sumOfLengths += current_X - tempX;
        } else{
            sumOfLengths += tempX - current_X;
        }
        sumOfLengths += tempY - current_Y;
    }

    return sumOfLengths;
}
