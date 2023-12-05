#include <iostream>
#include <cctype>
#include <string>

bool checkCubes(std::string tempString){
    if(tempString.find("red") != std::string::npos){
        int redCubes = tempString[tempString.find("red") - 2] - 48;
        if(tempString[tempString.find("red") - 3] - 48 > 0 && tempString[tempString.find("red") - 3] - 48 < 10)
            redCubes += (tempString[tempString.find("red") - 3] - 48)*10;
        if(redCubes > 12)
            return true;
    }
    if(tempString.find("green") != std::string::npos){
        int greenCubes = tempString[tempString.find("green") - 2] - 48;
        if(tempString[tempString.find("green") - 3] - 48 > 0 && tempString[tempString.find("green") - 3] - 48 < 10)
            greenCubes += (tempString[tempString.find("green") - 3] - 48)*10;
        if(greenCubes > 13)
            return true;
    }
    if(tempString.find("blue") != std::string::npos){
        int blueCubes = tempString[tempString.find("blue") - 2] - 48;
        if(tempString[tempString.find("blue") - 3] - 48 > 0 && tempString[tempString.find("blue") - 3] - 48 < 10)
            blueCubes += (tempString[tempString.find("blue") - 3] - 48)*10;
        if(blueCubes > 14)
            return true;
    }
    return false;
}

void splitFunction(std::string gameLine, char separator, int &gameIDs, int gameID){
    int startIndex = 0, endIndex = 0;
    bool tooMuchCubes = false;
    std::string tempString;
    for(int i = 0; i <= gameLine.length(); i++){
        if(gameLine[i] == separator || i == gameLine.length()){
            endIndex = i;
            tempString.append(gameLine, startIndex, endIndex - startIndex);
            tooMuchCubes = checkCubes(tempString);
            if(tooMuchCubes)
                break;

            tempString = "";
            startIndex = endIndex + 1;
        }
    }
    if(!tooMuchCubes)
        gameIDs += gameID;
}

int main(){
    int gameIDs = 0;
    int gameID = 0;
    for(std::string gameLine; std::getline(std::cin, gameLine);){
        gameID++;
        if(gameLine.empty())
            break;

        splitFunction(gameLine, ';', gameIDs, gameID);
    }
    std::cout << gameIDs;
}