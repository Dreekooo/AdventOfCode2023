#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

void solve(std::vector<std::string> rows);
void getNumbers(std::vector<long long int> &numVector, std::string line);
long long int numOfWaysToWin(long long int time, long long int distance);

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
    long long int solution = 1;
    std::vector<long long int> time, distance;
    getNumbers(time, rows[0]);
    getNumbers(distance, rows[1]);

    for(long long int i = 0; i < time.size(); i++){
        solution *= numOfWaysToWin(time[i], distance[i]);
    }

    std::cout << solution;
}

void getNumbers(std::vector<long long int> &numVector, std::string line){
    long long int tempNumber = 0;
    for(long long int i = 0; i < line.length(); i++){
        if(isdigit(line[i])){
            tempNumber *= 10;
            tempNumber += line[i] - 48;
        }
    }
    std::cout << tempNumber << '\n';
    numVector.push_back(tempNumber);
}

long long int numOfWaysToWin(long long int time, long long int distance){
    long long int wins = 0;
    for(long long int mpm = 0; mpm <= time; mpm++){
        if(mpm * (time - mpm) > distance)
            wins++;
    }
    return wins;
}