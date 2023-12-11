#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

void solve(std::vector<std::string> rows);
void getNumbers(std::vector<int> &numVector, std::string line);
int numOfWaysToWin(int time, int distance);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");

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
    int solution = 1;
    std::vector<int> time, distance;
    getNumbers(time, rows[0]);
    getNumbers(distance, rows[1]);

    for(int i = 0; i < time.size(); i++){
        solution *= numOfWaysToWin(time[i], distance[i]);
    }

    std::cout << solution;
}

void getNumbers(std::vector<int> &numVector, std::string line){
        for(int i = 0; i < line.length(); i++){
        if(isdigit(line[i])){
            int tempNumber = line[i] - 48;
            while(true){
                if(isdigit(line[i + 1])){
                    i++;
                    tempNumber *= 10;
                    tempNumber += line[i] - 48;
                } else{
                    numVector.push_back(tempNumber);
                    break;
                }
            }
        }
    }
}

int numOfWaysToWin(int time, int distance){
    int wins = 0;
    for(int mpm = 0; mpm <= time; mpm++){
        if(mpm * (time - mpm) > distance)
            wins++;
    }
    return wins;
}