#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct element
{
    int shortestPath = 0;
    bool visited = false;
};


int solve(std::vector<std::string> rows);
std::vector<std::vector<element>> createElements(std::vector<std::string> rows);
std::vector<std::vector<element>> dijkstraAlgorithm(std::vector<std::vector<element>> vecOfElements, std::vector<std::string> rows);
std::pair<int, int> findSmallestValue(std::vector<std::vector<element>> vecOfElements);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("test_input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    file.close();

    int answer = solve(rows);
    std::cout << answer;

    return 0;
}

int solve(std::vector<std::string> rows){
    std::vector<std::vector<element>> vecOfElements = createElements(rows); //vector of shortest paths, to each element;
    std::vector<std::vector<element>> elementsWithPahts = dijkstraAlgorithm(vecOfElements, rows);

    for(int y = 0; y < elementsWithPahts.size(); y++){
        for(int x = 0; x < elementsWithPahts[y].size(); x++){
            std::cout << elementsWithPahts[y][x].visited << ' ';
        }
        std::cout << '\n';
    }

    return elementsWithPahts[elementsWithPahts.size() - 1][elementsWithPahts[0].size() - 1].shortestPath;
}

std::vector<std::vector<element>> createElements(std::vector<std::string> rows){
    std::vector<std::vector<element>> vecOfElements;
    std::vector<element> elements;
    element tempElement;
    for(int y = 0; y < rows.size(); y++){
        for(int x = 0; x < rows[y].length(); x++){
            elements.push_back(tempElement);
        }
        vecOfElements.push_back(elements);
        elements.clear();
    }

    return vecOfElements;
}

std::vector<std::vector<element>> dijkstraAlgorithm(std::vector<std::vector<element>> vecOfElements, std::vector<std::string> rows){
    std::vector<std::vector<element>> elementsWithPaths;
    int ammountOfElements = vecOfElements.size() * vecOfElements[0].size();
    int ammountOfVisitedElements = 0;
    std::pair<int, int> smallestValue = std::make_pair(0, 0);
    std::vector<element> tempEmptyVec;

    for(int i = 0; i < vecOfElements.size(); i++){
        elementsWithPaths.push_back(tempEmptyVec);
    }

    while(ammountOfVisitedElements < ammountOfElements){
        element *currentElement = &vecOfElements[smallestValue.first][smallestValue.second];
        ammountOfVisitedElements++;
        currentElement->visited = true;

        //check element above
        if(smallestValue.first > 0){
            element *elementAbove = &vecOfElements[smallestValue.first - 1][smallestValue.second];
            if(!elementAbove->visited){
                if(elementAbove->shortestPath != 0){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first - 1][smallestValue.second];
                    if(tempValue < elementAbove->shortestPath)
                        elementAbove->shortestPath = tempValue;
                } else if(elementAbove->shortestPath == 0){
                    elementAbove->shortestPath = currentElement->shortestPath + rows[smallestValue.first - 1][smallestValue.second];
                }
            }
        }

        //check element under
        if(smallestValue.first < vecOfElements.size() - 1){
            element *elementUnder = &vecOfElements[smallestValue.first + 1][smallestValue.second];
            if(!elementUnder->visited){
                if(elementUnder->shortestPath != 0){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first + 1][smallestValue.second];
                    if(tempValue < elementUnder->shortestPath)
                        elementUnder->shortestPath = tempValue;
                } else if(elementUnder->shortestPath == 0){
                    elementUnder->shortestPath = currentElement->shortestPath + rows[smallestValue.first + 1][smallestValue.second];
                }
            }
        }

        //check element left
        if(smallestValue.second > 0){
            element *elementLeft = &vecOfElements[smallestValue.first][smallestValue.second - 1];
            std::cout << elementLeft->visited <<'\n';
            if(!elementLeft->visited){
                if(elementLeft->shortestPath != 0){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second - 1];
                    if(tempValue < elementLeft->shortestPath)
                        elementLeft->shortestPath = tempValue;
                } else if(elementLeft->shortestPath == 0){
                    elementLeft->shortestPath = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second - 1];
                }
            }
        }
        
        //check element right
        if(smallestValue.second < vecOfElements[0].size() - 1){
            element *elementRight = &vecOfElements[smallestValue.first][smallestValue.second + 1];
            if(!elementRight->visited){
                if(elementRight->shortestPath != 0){
                    int tempValue = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second + 1];
                    if(tempValue < elementRight->shortestPath)
                        elementRight->shortestPath = tempValue;
                } else if(elementRight->shortestPath == 0){
                    elementRight->shortestPath = currentElement->shortestPath + rows[smallestValue.first][smallestValue.second + 1];
                }
            }
        }

        elementsWithPaths[smallestValue.first].insert(elementsWithPaths[smallestValue.first].begin() + smallestValue.second, vecOfElements[smallestValue.first][smallestValue.second]);
        smallestValue = findSmallestValue(vecOfElements);
    }

    return elementsWithPaths;
}

std::pair<int, int> findSmallestValue(std::vector<std::vector<element>> vecOfElements){
    std::pair<int, int> pair = std::make_pair(0, 0);
    for(int y = 0; y < vecOfElements.size(); y++){
        for(int x = 0; x < vecOfElements[y].size(); x++){
            if(!vecOfElements[y][x].visited && vecOfElements[y][x].shortestPath != 0 && (vecOfElements[y][x].shortestPath < vecOfElements[pair.first][pair.second].shortestPath || (pair.first == 0 && pair.second == 0))){
                pair.first = y;
                pair.second = x;
            }
        }
    }

    return pair;
}