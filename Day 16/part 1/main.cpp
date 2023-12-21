#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct square{
    char element;
    bool isEmpty = true;
    bool movedUp = false;
    bool movedDown = false;
    bool movedLeft = false;
    bool movedRight = false;
};

int solve(std::vector<std::vector<square>> rows);
void moveUp(std::vector<std::vector<square>> &rows, int X, int Y);
void moveDown(std::vector<std::vector<square>> &rows, int X, int Y);
void moveLeft(std::vector<std::vector<square>> &rows, int X, int Y);
void moveRight(std::vector<std::vector<square>> &rows, int X, int Y);

int main(){
    int rowIndex = 0;
    std::string row;
    square element;
    std::vector<std::vector<square>> rows;
    std::vector<square> tempVec;
    std::fstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(tempVec);
            for(int i = 0; i < row.length(); i++){
                if(row[i] != '.')
                    element.isEmpty = false;
                element.element = row[i];
                rows[rowIndex].push_back(element);
            }
            rowIndex++;
        }
    }

    file.close();
    
    int answer = solve(rows);

    std::cout << answer;

    return 0;
}

int solve(std::vector<std::vector<square>> rows){
    int count = 0;
    moveRight(rows, 0, 0);

    for(int i = 0; i < rows.size(); i++){
        for(int j = 0; j < rows[i].size(); j++){
            square element = rows[i][j];
            if(element.movedDown || element.movedUp || element.movedLeft || element.movedRight){
                count++;
            }
        }
    }

    return count;
}

void moveUp(std::vector<std::vector<square>> &rows, int X, int Y){
    while(Y >= 0){
        if(rows[Y][X].movedUp == false){
            if(rows[Y][X].element == '.'){
                rows[Y][X].movedUp = true;
                Y--;
            } else if(rows[Y][X].element == '/'){
                rows[Y][X].movedUp = true;
                moveRight(rows, X + 1, Y);
                break;
            } else if(rows[Y][X].element == '\\'){
                rows[Y][X].movedUp = true;
                moveLeft(rows, X - 1, Y);
                break;
            } else if(rows[Y][X].element == '-'){
                rows[Y][X].movedUp = true;
                moveLeft(rows, X - 1, Y);
                moveRight(rows, X + 1, Y);
                break;
            } else if(rows[Y][X].element == '|'){
                rows[Y][X].movedUp = true;
                Y--;
            }
        } else {
            break;
        }
    }
}
void moveDown(std::vector<std::vector<square>> &rows, int X, int Y){
    while(Y < rows.size()){
        if(rows[Y][X].movedDown == false){
            if(rows[Y][X].element == '.'){
                rows[Y][X].movedDown = true;
                Y++;
            } else if(rows[Y][X].element == '/'){
                rows[Y][X].movedDown = true;
                moveLeft(rows, X - 1, Y);
                break;
            } else if(rows[Y][X].element == '\\'){
                rows[Y][X].movedDown = true;
                moveRight(rows, X + 1, Y);
                break;
            } else if(rows[Y][X].element == '-'){
                rows[Y][X].movedDown = true;
                moveLeft(rows, X - 1, Y);
                moveRight(rows, X + 1, Y);
                break;
            } else if(rows[Y][X].element == '|'){
                rows[Y][X].movedDown = true;
                Y++;
            }
        } else {
            break;
        }
    }
}
void moveLeft(std::vector<std::vector<square>> &rows, int X, int Y){
    while(X >= 0){
        if(rows[Y][X].movedLeft == false){
            if(rows[Y][X].element == '.'){
                rows[Y][X].movedLeft = true;
                X--;
            } else if(rows[Y][X].element == '/'){
                rows[Y][X].movedLeft = true;
                moveDown(rows, X, Y + 1);
                break;
            } else if(rows[Y][X].element == '\\'){
                rows[Y][X].movedLeft = true;
                moveUp(rows, X, Y - 1);
                break;
            } else if(rows[Y][X].element == '-'){
                rows[Y][X].movedLeft = true;
                X--;
            } else if(rows[Y][X].element == '|'){
                rows[Y][X].movedLeft = true;
                moveDown(rows, X, Y + 1);
                moveUp(rows, X, Y - 1);
                break;
            }
        } else {
            break;
        }
    }
}
void moveRight(std::vector<std::vector<square>> &rows, int X, int Y){
    while(X < rows[0].size()){
        if(rows[Y][X].movedRight == false){
            if(rows[Y][X].element == '.'){
                rows[Y][X].movedRight = true;
                X++;
            } else if(rows[Y][X].element == '/'){
                rows[Y][X].movedRight = true;
                moveUp(rows, X, Y - 1);
                break;
            } else if(rows[Y][X].element == '\\'){
                rows[Y][X].movedRight = true;
                moveDown(rows, X, Y + 1);
                break;
            } else if(rows[Y][X].element == '-'){
                rows[Y][X].movedRight = true;
                X++;
            } else if(rows[Y][X].element == '|'){
                rows[Y][X].movedRight = true;
                moveDown(rows, X, Y + 1);
                moveUp(rows, X, Y - 1);
                break;
            }
        } else {
            break;
        }
    }
}