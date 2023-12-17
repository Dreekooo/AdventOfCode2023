#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct galaxy
{
    long long int X = 0;
    long long int Y = 0;
};


void solve(std::vector<std::string> rows);
void editVector(std::vector<std::string> &rows, std::vector<long long int> &emptyRows, std::vector<long long int> &emptyColums);
long long int findLengths(std::vector<galaxy> galaxies, long long int galaxyIndex, std::vector<long long int> emptyRows, std::vector<long long int> emptyColums);

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
    long long int sumOfLengths = 0;
    galaxy G;
    std::vector<galaxy> galaxies;
    std::vector<long long int> emptyRows, emptyColums;

    editVector(rows, emptyRows, emptyColums);
    for(long long int i = 0; i < rows.size(); i++){
        for(long long int j = 0; j < rows[i].length(); j++){
            if(rows[i][j] == '#'){
                G.X = j;
                G.Y = i;
                galaxies.push_back(G);
            }
        }
    }

    for(long long int i = 0; i < galaxies.size(); i++){
        sumOfLengths += findLengths(galaxies, i, emptyRows, emptyColums);
    }
    std::cout << sumOfLengths;
}

void editVector(std::vector<std::string> &rows, std::vector<long long int> &emptyRows, std::vector<long long int> &emptyColums){
    bool noGalaxies;
    for(long long int i = 0; i < rows.size(); i++){
        noGalaxies = true;
        for(long long int j = 0; j < rows[i].size(); j++){
            if(rows[i][j] == '#'){
                noGalaxies = false;
                break;
            }
        }
        if(noGalaxies)
            emptyRows.push_back(i);   
    }
    for(long long int i = 0; i < rows[0].size(); i++){
        noGalaxies = true;
        for(long long int j = 0; j < rows.size(); j++){
            if(rows[j][i] == '#'){
                noGalaxies = false;
                break;
            }
        }
        if(noGalaxies)
            emptyColums.push_back(i);
    }    
}

long long int findLengths(std::vector<galaxy> galaxies, long long int galaxyIndex, std::vector<long long int> emptyRows, std::vector<long long int> emptyColums){
    long long int sumOfLengths = 0;
    long long int tempX, tempY;
    long long int current_X = galaxies[galaxyIndex].X, current_Y = galaxies[galaxyIndex].Y;
    long long int emptySize, emptyRowsAmmount, emptyColumsAmmount;
    long long int iterator;

    for(long long int i = galaxyIndex + 1; i < galaxies.size(); i++){
        emptySize = 1000000;
        emptyRowsAmmount = 0;
        emptyColumsAmmount = 0;
        iterator = 0;
        tempX = galaxies[i].X;
        tempY = galaxies[i].Y;

        if(current_X > tempX){
            if(!emptyColums.empty()){
                while(emptyColums[iterator] < current_X && iterator < emptyColums.size()){
                    if(emptyColums[iterator] > tempX && emptyColums[iterator] < current_X){
                        emptyColumsAmmount++;
                    }
                    iterator++;
                }
            }
            sumOfLengths += (current_X - tempX) + (emptyColumsAmmount * emptySize) - emptyColumsAmmount;
        } else{
            if(!emptyColums.empty()){
                while(emptyColums[iterator] < tempX && iterator < emptyColums.size()){
                    if(emptyColums[iterator] > current_X && emptyColums[iterator] < tempX){
                        emptyColumsAmmount++;
                    }
                    iterator++;
                }
            }
            sumOfLengths += (tempX - current_X) + (emptyColumsAmmount * emptySize) - emptyColumsAmmount;
        }
        iterator = 0;
        if(!emptyRows.empty()){
            while(emptyRows[iterator] < tempY && iterator < emptyRows.size()){
                if(emptyRows[iterator] > current_Y)
                    emptyRowsAmmount++;
                iterator++;
            }
        }
        sumOfLengths += (tempY - current_Y) + (emptyRowsAmmount * emptySize) - emptyRowsAmmount;
    }

    return sumOfLengths;
}
