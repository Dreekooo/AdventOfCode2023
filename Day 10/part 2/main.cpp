#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct path{
    int current_X;
    int current_Y;
    int old_X = -1;
    int old_Y = -1;
};

void solve(std::vector<std::string> rows);
void findStart(std::vector<std::string> rows, int &X, int &Y);
void findPath(std::vector<std::string> rows, path &firstPath, path secondPath, bool &loop, std::vector<std::pair<int, int>> &loopPipes);
void nextStep(path &checkPath, path secondPath, bool &found, int nextX, int nextY, bool &madeStep);
void replaceStart(std::vector<std::string> &rows, int i, int j);
int countTiles(std::string row);

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
    int X = 0, Y = 0, tiles = 0;
    path firstPath, secondPath;
    std::vector<std::pair<int, int>> loopPipes;

    findStart(rows, X, Y);
    firstPath.current_X = X;
    firstPath.current_Y = Y;
    secondPath.current_X = X;
    secondPath.current_Y = Y;
    loopPipes.push_back(std::make_pair(X, Y));

    bool loop = true;
    while(loop){
        findPath(rows, firstPath, secondPath, loop, loopPipes);
        findPath(rows, secondPath, firstPath, loop, loopPipes);
    }

    
    for(int i = 0; i < rows.size(); i++){
        for(int j = 0; j < rows[i].length(); j++){
            if(std::find(loopPipes.begin(), loopPipes.end(), std::pair<int, int>(j, i)) == loopPipes.end())
                rows[i][j] = '.';
            else if(rows[i][j] == 'S')
                replaceStart(rows, i, j);
        }
        tiles += countTiles(rows[i]);
    }

    std::cout << tiles;
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

void findPath(std::vector<std::string> rows, path &checkPath, path secondPath, bool &loop, std::vector<std::pair<int, int>> &loopPipes){
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
        char pipeUp;
        char pipeDown;
        char pipeLeft;
        char pipeRight;
        
        if(checkPath.current_Y != 0)
            pipeUp = rows[checkPath.current_Y - 1][checkPath.current_X];
        if(checkPath.current_Y != rows.size() - 1)
            pipeDown = rows[checkPath.current_Y + 1][checkPath.current_X];
        if(checkPath.current_X != 0)
            pipeLeft = rows[checkPath.current_Y][checkPath.current_X - 1];
        if(checkPath.current_X != rows[0].length() - 1)
            pipeRight = rows[checkPath.current_Y][checkPath.current_X + 1];   

        if((pipeUp == '|' || pipeUp == 'F' || pipeUp == '7') && secondPath.current_Y != checkPath.current_Y - 1 && checkPath.current_Y != 0){
            nextStep(checkPath, secondPath, loop, 0, -1, madeStep); // up
        } else if((pipeDown == '|' || pipeDown == 'L' || pipeDown == 'J') &&secondPath.current_Y != checkPath.current_Y + 1 && checkPath.current_Y != rows.size() - 1){
            nextStep(checkPath, secondPath, loop, 0, 1, madeStep); // down
        } else if((pipeLeft == '-' || pipeLeft == 'L' || pipeLeft == 'F') && secondPath.current_X != checkPath.current_X - 1  && checkPath.current_X != 0){
            nextStep(checkPath, secondPath, loop, -1, 0, madeStep); // left
        } else if((pipeRight == '-' || pipeRight == 'J' || pipeRight == '7') && secondPath.current_X != checkPath.current_X + 1  && checkPath.current_X != rows[0].length() - 1){
            nextStep(checkPath, secondPath, loop, 1, 0, madeStep); // right
        }
    }

    loopPipes.push_back(std::make_pair(checkPath.current_X, checkPath.current_Y));
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

void replaceStart(std::vector<std::string> &rows, int i, int j){
    bool up = false, down = false, left = false, right = false;

    if(i != 0){
        char tempChar = rows[i-1][j];
        if(tempChar == '|' || tempChar == '7' || tempChar == 'F')
            up = true;
    }
    if(i != rows.size() - 1){
        char tempChar = rows[i+1][j];
        if(tempChar == '|' || tempChar == 'J' || tempChar == 'L')
            down = true;
    }
    if(j != 0){
        char tempChar = rows[i][j-1];
        if(tempChar == '-' || tempChar == 'L' || tempChar == 'F')
            left = true;
    }
    if(j != rows[0].length() - 1){
        char tempChar = rows[i][j+1];
        if(tempChar == '-' || tempChar == 'J' || tempChar == '7')
            right = true;
    }

    if(up == true){
        if(down == true)
            rows[i][j] = '|';
        if(left == true)
            rows[i][j] = 'J';
        if(right == true)
            rows[i][j] = 'L'; 
    } else if(down == true){
        if(left == true)
            rows[i][j] = '7';
        if(right == true)
            rows[i][j] = 'F'; 
    } else
        rows[i][j] = '-';
}

int countTiles(std::string row){
    int tiles = 0;
    bool countON = false;
    char savedChar = '\0';

    for(int i = 0; i < row.length(); i++){
        if(row[i] == '.'){
            if(countON)
                tiles++;
            continue;
        } else if(row[i] == '-'){
            continue;
        } else if(row[i] == '|'){
            countON = !countON;
        } else{
            if(savedChar != '\0'){
                bool up = false;
                bool down = false;
                if(savedChar == '7' || savedChar == 'F')
                    up = true;
                else
                    down = true;

                if(row[i] == '7' || row[i] == 'F')
                    up = true;
                else
                    down = true;

                if(up && down)
                    countON = !countON;
                savedChar = '\0';
            } else
                savedChar = row[i];
        }
    }
    return tiles;
}

/*
Alright.

Given a line that looks like this, where all pipes are part of the loop:

.|.|L---J..F---7|.|L7.F-J...|..|
How many "." are actually inside the region?

Well we know, that we are outside at the beginning. So lets go through each character and see if anything changes:

Char = "."; case = "not-in-region": clearly, we do not count this
(i'll abbreviate char as c, "not-in-region" as not and "in-region" as yes)

c = "|"; case = not: this is a border. The left cell was not in the region,
so the right cell must be in the region (or a border). So we
swap the case to "in-region".

c = "."; case = yes: this is not a pipe, we are in a region, we
count up;

c = "|"; case = yes: this is a border, we were in a region, so we
swap the case to "not-in-region".

c = "."; case = not: this is not a pipe, we are not in a region, we
do nothing;

c = "L"; case = not: This is a corner, lets remember that.
Certainly, the cell after this corner cannot be in the region, because it has to connect to a pipe

c = "-"; case = not: This is a sideways pipe, but the cell after must be a pipe too, so we
do nothing

c = "-"; case = not: Sideways pipe,
do nothing

c = "-"; case = not: Sideways pipe,
do nothing

c = "J"; case = not: This is a corner. What was the previous corner we saw?
An "L". So this whole section between both corners is U Shape.
A U Shape never changes the region. A cell before the U and after the U cannot be in different regions.
So we do nothing.

c = "."; case = not: Not a pipe, not in a region,
do nothing.

c = "."; case = not: Not a pipe, not in a region,
do nothing.

c = "F"; case = not: Corner, remember it.

c = "-"; case = not: Sideways pipe,
do nothing (there must be a pipe after it)

c = "-"; case = not: Sideways pipe,
do nothing

c = "-"; case = not: Sideways pipe,
do nothing

c = "7"; case = not: Corner. Previous corner was an "F". So this is a U Shape.
Do nothing.

c = "|"; case = not: Border. We were not in a region, so the cell after must be in a region.
Swap the case.

c = "."; case = yes: Not a pipe, but we are in a region, so we
count up.

c = "|"; case = yes: Border. We were in a region, so the cell after must be not in a region.
Swap the case.

c = "L"; case = not: Corner, remember it.

c = "7"; case = not: Corner. Previous corner was an "L". So this isn't a U Shape.
Meaning cells on either end of both corners must be in different regions.
Swap the case.

c = "."; case = yes: Not a pipe, but we are in a region, so we
count up.

c = "F"; case = yes: Corner, remember it.

c = "-"; case = yes: Sideways pipe,
do nothing.

c = "J"; case = yes: Corner. Previous corner was an "F". So this is not a U Shape.
Swap the case.

c = "."; case = not: Not a pipe, not in a region,
do nothing.

c = "."; case = not: Not a pipe, not in a region,
do nothing.

c = "."; case = not: Not a pipe, not in a region,
do nothing.

c = "|"; case = not: Border. We were not in a region, so the cell after must be in a region.
Swap the case.

c = "."; case = yes: Not a pipe, but we are in a region, so we
count up.

c = "."; case = yes: Not a pipe, but we are in a region, so we
count up.

c = "|"; case = yes: Border. We were in a region, so the cell after must be not in a region.
Swap the case.

In total, we counted 5 cells in the region.
*/