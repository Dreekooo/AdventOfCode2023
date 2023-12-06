#include <iostream>
#include <cctype>
#include <string>

void checkCubes(std::string tempString, int &minRed, int &minGreen, int &minBlue){
    if(tempString.find("red") != std::string::npos){
        int redCubes = tempString[tempString.find("red") - 2] - 48;
        if(tempString[tempString.find("red") - 3] - 48 > 0 && tempString[tempString.find("red") - 3] - 48 < 10)
            redCubes += (tempString[tempString.find("red") - 3] - 48)*10;

        if(redCubes > minRed)
            minRed = redCubes;
    }
    if(tempString.find("green") != std::string::npos){
        int greenCubes = tempString[tempString.find("green") - 2] - 48;
        if(tempString[tempString.find("green") - 3] - 48 > 0 && tempString[tempString.find("green") - 3] - 48 < 10)
            greenCubes += (tempString[tempString.find("green") - 3] - 48)*10;

        if(greenCubes > minGreen)
            minGreen = greenCubes;
    }
    if(tempString.find("blue") != std::string::npos){
        int blueCubes = tempString[tempString.find("blue") - 2] - 48;
        if(tempString[tempString.find("blue") - 3] - 48 > 0 && tempString[tempString.find("blue") - 3] - 48 < 10)
            blueCubes += (tempString[tempString.find("blue") - 3] - 48)*10;
        
        if(blueCubes > minBlue)
            minBlue = blueCubes;
    }
}

void splitFunction(std::string gameLine, char separator, int &powerSum){
    int startIndex = 0, endIndex = 0;
    std::string tempString;
    int minRed = 0, minGreen = 0, minBlue = 0;
    for(int i = 0; i <= gameLine.length(); i++){
        if(gameLine[i] == separator || i == gameLine.length()){
            endIndex = i;
            tempString.append(gameLine, startIndex, endIndex - startIndex);
            checkCubes(tempString, minRed, minGreen, minBlue);

            tempString = "";
            startIndex = endIndex + 1;
        }
    }
    powerSum += minRed * minGreen * minBlue;
}

int main(){
    int powerSum = 0;
    for(std::string gameLine; std::getline(std::cin, gameLine);){
        if(gameLine.empty())
            break;

        splitFunction(gameLine, ';', powerSum);
    }
    std::cout << powerSum;
}