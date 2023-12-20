#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

struct lens{
  std::string label;
  std::string operation;
  int focalLength;;
  int boxNumber;
};

int solve(std::vector<std::string> rows);
lens getLens(std::string row);
int checkValue(std::string row);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");
    int answer;

    if(file.is_open()){
        while(std::getline(file, row, ',')){
            rows.push_back(row);
        }
    }

    answer = solve(rows);
    std::cout << answer;
    
    return 0;
}

int solve(std::vector<std::string> rows){
    lens tempLens;
    std::map<int, std::vector<lens>> boxes;
    int sum = 0;
    for(std::string row : rows){
      bool exist = false;
      int index;
      tempLens = getLens(row);
      std::vector<lens> tempVector;

      if(tempLens.operation == "equals"){
        if(boxes.find(tempLens.boxNumber) != boxes.end())
          tempVector = boxes[tempLens.boxNumber];

        for(int i = 0; i < tempVector.size(); i++){
          if(tempVector[i].label == tempLens.label){
            exist = true;
            index = i;
          }
        }

        if(!exist){
          tempVector.push_back(tempLens);
          boxes[tempLens.boxNumber] = tempVector;
        } else{
          tempVector[index] = tempLens;
          boxes[tempLens.boxNumber] = tempVector;
        }
      } else{
        if(boxes.find(tempLens.boxNumber) != boxes.end())
          tempVector = boxes[tempLens.boxNumber];

        for(int i = 0; i < tempVector.size(); i++){
          if(tempVector[i].label == tempLens.label){
            exist = true;
            index = i;
          }
        }

        if(exist){
          tempVector.erase(tempVector.begin() + index);
          boxes[tempLens.boxNumber] = tempVector;
        }
      }
    }

    for(std::map<int, std::vector<lens>>::iterator mapValues = boxes.begin(); mapValues != boxes.end(); mapValues++){
      std::vector<lens> lensVector = mapValues->second;
      for(int i = 0; i < lensVector.size(); i++){
        sum += (lensVector[i].boxNumber + 1) * (i + 1) * lensVector[i].focalLength;
      }
    }

    return sum;
}

lens getLens(std::string row){
  lens newLens;
  auto operation = row.find('=');

  if(row.find('=') != std::string::npos){
    newLens.operation = "equals";
    newLens.focalLength = row[operation + 1] - 48;
    newLens.label = row.substr(0, operation);
  } else{
    newLens.operation = "dash";
    newLens.label = row.substr(0, row.size() - 1);
  }
  newLens.boxNumber = checkValue(newLens.label);

  return newLens;
}

int checkValue(std::string row){
    int value = 0;
    for(int i = 0; i < row.length(); i++){
        value += row[i];
        value *= 17;
        value %= 256;
    }
    return value;
}