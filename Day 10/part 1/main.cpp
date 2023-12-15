#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct path{
    int current_X;
    int current_Y;
    int old_X = -1;
    int old_Y = -1;
};

void solve(std::vector<std::string> rows);
void findStart(std::vector<std::string> rows, int &X, int &Y);
void findPath(std::vector<std::string> rows, path &firstPath, path secondPath, bool &loop);
void nextStep(path &checkPath, path secondPath, bool &found, int nextX, int nextY, bool &madeStep);


int main()
{
    std::ifstream file("input.txt");
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
    path firstPath, secondPath;

    findStart(rows, X, Y);
    firstPath.current_X = X;
    firstPath.current_Y = Y;
    secondPath.current_X = X;
    secondPath.current_Y = Y;

    bool loop = true;
    while(loop){
        iteration++;
        findPath(rows, firstPath, secondPath, loop);
        findPath(rows, secondPath, firstPath, loop);
    }

    std::cout << iteration;
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

void findPath(std::vector<std::string> rows, path &checkPath, path secondPath, bool &loop){
    char pipe = rows[checkPath.current_Y][checkPath.current_X];
    bool madeStep = false;
    loop = false;

    if(pipe == '|'){
        nextStep(checkPath, secondPath, loop, 0, -1, madeStep); // up
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, 0, 1, madeStep); // down
    } else if(pipe == '-'){
        nextStep(checkPath, secondPath, loop, -1, 0, madeStep); // left
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, 1, 0, madeStep); // right
    } else if(pipe == '7'){
        nextStep(checkPath, secondPath, loop, 0, 1, madeStep); // down
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, -1, 0, madeStep); // left
    } else if(pipe == 'F'){
        nextStep(checkPath, secondPath, loop, 0, 1, madeStep); // down
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, 1, 0, madeStep); // right
    } else if(pipe == 'J'){
        nextStep(checkPath, secondPath, loop, 0, -1, madeStep); // up
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, -1, 0, madeStep); // left
    } else if(pipe == 'L'){
        nextStep(checkPath, secondPath, loop, 0, -1, madeStep); // up
        if(!madeStep)
            nextStep(checkPath, secondPath, loop, 1, 0, madeStep); // right
    } else if(pipe == 'S'){
        char pipeUp = rows[checkPath.current_Y - 1][checkPath.current_X];
        char pipeDown = rows[checkPath.current_Y + 1][checkPath.current_X];
        char pipeLeft = rows[checkPath.current_Y][checkPath.current_X - 1];
        char pipeRight = rows[checkPath.current_Y][checkPath.current_X + 1];

        if((pipeUp == '|' || pipeUp == 'F' || pipeUp == '7') && secondPath.current_Y != checkPath.current_Y - 1){
            nextStep(checkPath, secondPath, loop, 0, -1, madeStep); // up
        } else if((pipeDown == '|' || pipeDown == 'L' || pipeDown == 'J') &&secondPath.current_Y != checkPath.current_Y + 1){
            nextStep(checkPath, secondPath, loop, 0, 1, madeStep); // down
        } else if((pipeLeft == '-' || pipeLeft == 'L' || pipeLeft == 'F') && secondPath.current_X != checkPath.current_X - 1){
            nextStep(checkPath, secondPath, loop, -1, 0, madeStep); // left
        } else if((pipeRight == '-' || pipeRight == 'J' || pipeRight == '7') && secondPath.current_X != checkPath.current_X + 1){
            nextStep(checkPath, secondPath, loop, 1, 0, madeStep); // right
        }
    }
}

void nextStep(path &checkPath, path secondPath, bool &found, int nextX, int nextY, bool &madeStep){
    if(checkPath.old_X == checkPath.current_X + nextX && checkPath.old_Y == checkPath.current_Y + nextY){
        //stop
    } else if(secondPath.current_X == checkPath.current_X + nextX && secondPath.current_Y == checkPath.current_Y + nextY){
        //stop
    } else if(secondPath.old_X == checkPath.current_X + nextX && secondPath.old_Y == checkPath.current_Y + nextY){
        //stop
    } else{        
        checkPath.old_X = checkPath.current_X;
        checkPath.old_Y = checkPath.current_Y;
        checkPath.current_X += nextX;
        checkPath.current_Y += nextY;
        found = true;
        madeStep = true;
    }
    
}