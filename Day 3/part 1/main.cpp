#include <iostream>
#include <string>
#include <vector>
#include <cctype>

void getText(std::vector<std::string> &text);
void findNumber(std::vector<std::string> text, int &sum);
bool findSymbol(std::vector<std::string>, int lineIndex, int numIndex, int numLength);

int main(){
    std::vector<std::string> text;
    int sum = 0;
    getText(text);
    findNumber(text, sum);

    std::cout << sum;
}

void getText(std::vector<std::string> &text){
    for(std::string line; std::getline(std::cin, line);){
        if(line.empty())
            break;
        text.push_back(line);
    }
}

void findNumber(std::vector<std::string> text, int &sum){
    int numLength = 0;
    int numIndex;
    int lineIndex = 0;
    int tempNumber;
    bool foundCharacter = false;
    for(std::string line : text){
        for(int i = 0; i < line.length(); i++){
            if(isdigit(line[i])){
                numIndex = i;
                numLength = 1;
                tempNumber = line[i] - 48;
                while(true){
                    i++;
                    if(isdigit(line[i])){
                        numLength++;
                        tempNumber *= 10;
                        tempNumber += line[i] - 48;
                    } else{
                        break;
                    }
                }
                foundCharacter = findSymbol(text, lineIndex, numIndex, numLength);
                if(foundCharacter)
                    sum += tempNumber;

                foundCharacter = false;
            }
        }
        lineIndex++;
    }
}

bool findSymbol(std::vector<std::string> text, int lineIndex, int numIndex, int numLength){
    std::string aboveLine = text[lineIndex - 1], thisLine = text[lineIndex];
    //line above
    if(lineIndex != 0){
        if(numIndex != 0){
            for(int i = 0; i < numLength + 2; i++){
                if(!isdigit(aboveLine[(numIndex - 1) + i]) && aboveLine[(numIndex - 1) + i] != '.' && aboveLine[(numIndex - 1) + i] != '\0'){
                    return true;
                }
            }
        } else {
            for(int i = 0; i < numLength + 1; i++){
                if(!isdigit(aboveLine[(numIndex) + i]) && aboveLine[(numIndex) + i] != '.' && aboveLine[(numIndex) + i] != '\0'){
                    return true;
                }
            }
        }
    }
    //this line
    if(!isdigit(thisLine[numIndex - 1]) && thisLine[numIndex - 1] != '.' && thisLine[numIndex - 1] != '\0' && numIndex != 0){
        return true;
    }
    if(!isdigit(thisLine[numIndex + numLength]) && thisLine[numIndex + numLength] != '.' && thisLine[numIndex + numLength] != '\0'){
        return true;
    }
    //line under
    if(lineIndex != text.size() - 1){
        std::string underLine = text[lineIndex+1];
        if(numIndex != 0){
            for(int i = 0; i < numLength + 2; i++){
                if(!isdigit(underLine[(numIndex - 1) + i]) && underLine[(numIndex - 1) + i] != '.' && underLine[(numIndex - 1) + i] != '\0'){
                    return true;
                }
            }
        } else{
            for(int i = 0; i < numLength + 1; i++){
                if(!isdigit(underLine[(numIndex) + i]) && underLine[(numIndex) + i] != '.' && underLine[(numIndex) + i] != '\0'){
                    return true;
                }
            }
        }
    }

    return false;
}