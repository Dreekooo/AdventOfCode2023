#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct element
{
    int shortestPath = INT_MAX;
    bool visited = false;
    std::string gotByDirection = "NONE";
};


int solve(std::vector<std::string> rows);
std::vector<std::vector<element>> createElements(std::vector<std::string> rows);
std::vector<std::vector<element>> dijkstraAlgorithm(std::vector<std::vector<element>> vecOfElements, std::vector<std::string> rows);
std::pair<int, int> findSmallestValue(std::vector<std::vector<element>> vecOfElements);
bool checkIfRow(std::vector<std::vector<element>> vecOfElements, int Y, int X);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("test_input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
        file.close();
    }

    int answer = solve(rows);
    std::cout << answer;

    return 0;
}

int solve(std::vector<std::string> rows){
    std::vector<std::vector<element>> vecOfElements = createElements(rows); //vector of shortest paths, to each element;
    std::vector<std::vector<element>> elementsWithPahts = dijkstraAlgorithm(vecOfElements, rows);
    std::cout << "\n\n" << elementsWithPahts.size() << ' ' << elementsWithPahts[0].size() << '\n';
    // for(int y = 0; y < elementsWithPahts.size(); y++){
    //     for(int x = 0; x < elementsWithPahts[y].size(); x++){
    //         std::cout << elementsWithPahts[y][x].visited << ' ';
    //     }
    //     std::cout << '\n';
    // }

    return elementsWithPahts[elementsWithPahts.size() - 1][elementsWithPahts[0].size() - 1].shortestPath;
}

std::vector<std::vector<element>> createElements(std::vector<std::string> rows){
    std::vector<std::vector<element>> vecOfElements;
    for(int y = 0; y < rows.size(); y++){
        std::vector<element> elements;
        for(int x = 0; x < rows[y].length(); x++){
            elements.push_back(element());
        }
        vecOfElements.push_back(elements);
    }

    return vecOfElements;
}

std::vector<std::vector<element>> dijkstraAlgorithm(std::vector<std::vector<element>> vecOfElements, std::vector<std::string> rows){
    std::vector<std::vector<element>> elementsWithPaths;
    int ammountOfElements = vecOfElements.size() * vecOfElements[0].size();
    int ammountOfVisitedElements = 0;
    std::pair<int, int> smallestValue = std::make_pair(0, 0);

    elementsWithPaths.resize(vecOfElements.size());
    for(int i = 0; i < vecOfElements.size(); i++){
        elementsWithPaths[i].resize(vecOfElements[i].size());
    }

    vecOfElements[0][0].shortestPath = 0;
    while(ammountOfVisitedElements < ammountOfElements){
        element *currentElement = &vecOfElements[smallestValue.first][smallestValue.second];
        ammountOfVisitedElements++;
        currentElement->visited = true;

        //check element above
        if(smallestValue.first > 0){
            element *elementAbove = &vecOfElements[smallestValue.first - 1][smallestValue.second];
            if(!elementAbove->visited){
                if(elementAbove->shortestPath != INT_MAX){
                    int tempValue = currentElement->shortestPath + (rows[smallestValue.first - 1][smallestValue.second] - '0');
                    if(tempValue < elementAbove->shortestPath){
                        elementAbove->shortestPath = tempValue;
                        elementAbove->gotByDirection = "above";
                    }
                } else if(elementAbove->shortestPath == INT_MAX){
                    elementAbove->shortestPath = currentElement->shortestPath + (rows[smallestValue.first - 1][smallestValue.second] - '0');
                    elementAbove->gotByDirection = "above";
                }
            }
        }

        //check element under
        if(smallestValue.first < vecOfElements.size() - 1){
            element *elementUnder = &vecOfElements[smallestValue.first + 1][smallestValue.second];
            if(!elementUnder->visited){
                if(elementUnder->shortestPath != INT_MAX){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first + 1][smallestValue.second] - '0';
                    if(tempValue < elementUnder->shortestPath){
                        elementUnder->shortestPath = tempValue;
                        elementUnder->gotByDirection = "under";
                    }
                } else if(elementUnder->shortestPath == INT_MAX){
                    elementUnder->shortestPath = currentElement->shortestPath + rows[smallestValue.first + 1][smallestValue.second] - '0';
                    elementUnder->gotByDirection = "under";
                }
            }
        }

        //check element left
        if(smallestValue.second > 0){
            element *elementLeft = &vecOfElements[smallestValue.first][smallestValue.second - 1];
            if(!elementLeft->visited){
                if(elementLeft->shortestPath != INT_MAX){
                    std::cout << "test";
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second - 1] - '0';
                    if(tempValue < elementLeft->shortestPath){
                        elementLeft->shortestPath = tempValue;
                        elementLeft->gotByDirection = "left";
                    }
                } else if(elementLeft->shortestPath == INT_MAX){
                    elementLeft->shortestPath = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second - 1] - '0';
                    elementLeft->gotByDirection = "left";
                }
            }
        }
        
        //check element right
        if(smallestValue.second < vecOfElements[0].size() - 1){
            element *elementRight = &vecOfElements[smallestValue.first][smallestValue.second + 1];
            if(!elementRight->visited){
                if(elementRight->shortestPath != INT_MAX){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second + 1] - '0';
                    if(tempValue < elementRight->shortestPath){
                        elementRight->shortestPath = tempValue;
                        elementRight->gotByDirection = "right";
                    }
                } else if(elementRight->shortestPath == INT_MAX){
                    elementRight->shortestPath = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second + 1] - '0';
                    elementRight->gotByDirection = "right";
                }
            }
        }
        std::cout << smallestValue.first << ' ' << smallestValue.second << ' ' << vecOfElements[smallestValue.first][smallestValue.second].shortestPath << '\n';
        std::cout << elementsWithPaths.size() << ' ' << elementsWithPaths[0].size() << '\n';

        elementsWithPaths[smallestValue.first][smallestValue.second] = vecOfElements[smallestValue.first][smallestValue.second];
        smallestValue = findSmallestValue(vecOfElements);
    }

    return elementsWithPaths;
}

std::pair<int, int> findSmallestValue(std::vector<std::vector<element>> vecOfElements){
    std::pair<int, int> pair = std::make_pair(0, 0);
    for(int y = 0; y < vecOfElements.size(); y++){
        for(int x = 0; x < vecOfElements[y].size(); x++){
            if(!vecOfElements[y][x].visited && vecOfElements[y][x].shortestPath != INT_MAX && (vecOfElements[y][x].shortestPath < vecOfElements[pair.first][pair.second].shortestPath || (pair.first == 0 && pair.second == 0))){
                bool inRow = checkIfRow(vecOfElements, y, x);
                if(!inRow){
                    pair.first = y;
                    pair.second = x;
                }
            }
        }
    }
    return pair;
}

bool checkIfRow(std::vector<std::vector<element>> vecOfElements, int Y, int X){
    bool row;
    //checkAbove
    row = true;
    for(int i = 1; i <= 3; i++){
        if(Y+i < vecOfElements.size()){
            if(vecOfElements[Y+i][X].gotByDirection != "above"){
                row = false;
                break;
            }
        } else{
            row = false;
            break;
        }
    }
    if(row == true)
        return true;
        
    //checkUnder
    row = true;
    for(int i = 1; i <= 3; i++){
        if(Y - i >= 0){
            if(vecOfElements[Y-i][X].gotByDirection != "under"){
                row = false;
                break;
            }
        } else {
            row = false;
            break;
        }
    }
    if(row == true)
        return true;

    //checkLeft
    row = true;
    for(int i = 1; i <= 3; i++){
        if(X + i < vecOfElements[Y].size()){
            if(vecOfElements[Y][X+i].gotByDirection != "left"){
                row = false;
                break;
            }
        } else {
            row = false;
            break;
        }
    }
    if(row == true)
        return true;

    //checkRight
    row = true;
    for(int i = 1; i <= 3; i++){
        if(X - i >= 0){
            if(vecOfElements[Y][X-i].gotByDirection != "right"){
                row = false;
                break;
            }
        } else{
            row = false;
            break;
        }
    }
    if(row == true)
        return true;

    return false;
}