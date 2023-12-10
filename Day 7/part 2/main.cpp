#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

void solve(std::vector<std::string> rows);
int checkStrength(std::string tempCards);
void setVector(std::vector<std::pair<std::string, int>> &fiveOfKind,std::vector<std::pair<std::string, int>> &fourOfKind,std::vector<std::pair<std::string, int>> &fullHouse,std::vector<std::pair<std::string, int>> &threeOfKind,std::vector<std::pair<std::string, int>> &twoPair,std::vector<std::pair<std::string, int>> &onePair,std::vector<std::pair<std::string, int>> &highCard,int strength,std::string tempCards,int tempValue);
std::vector<std::pair<std::string, int>> sortCards(std::vector<std::vector<std::pair<std::string, int>>> allCards);
void bubbleSort(std::vector<std::pair<std::string, int>> &vec);
void getValue(char character, int &value);

int main(){
    std::string row;
    std::vector<std::string> rows;
    std::ifstream file("input.txt");

    if(file.is_open()){
        while(std::getline(file, row)){
            rows.push_back(row);
        }
    }

    solve(rows);
}

void solve(std::vector<std::string> rows){
    std::vector<std::pair<std::string, int>> fiveOfKind, fourOfKind, fullHouse, threeOfKind, twoPair, onePair, highCard;
    std::string tempCards = "", tempValueStr = "";
    int strength, tempValue;
    for(std::string line : rows){
        tempCards.append(line, 0, 5);
        tempValueStr.append(line, 6, line.length() - 1);
        tempValue = stoi(tempValueStr);
        strength = checkStrength(tempCards);
        setVector(fiveOfKind, fourOfKind, fullHouse, threeOfKind, twoPair, onePair, highCard, strength, tempCards, tempValue);
        
        tempCards = "";
        tempValueStr = "";
    }

    std::vector<std::vector<std::pair<std::string, int>>> allCards;
    allCards.push_back(highCard);
    allCards.push_back(onePair);
    allCards.push_back(twoPair);
    allCards.push_back(threeOfKind);
    allCards.push_back(fullHouse);
    allCards.push_back(fourOfKind);
    allCards.push_back(fiveOfKind);

    std::vector<std::pair<std::string, int>> sortedCards;
    sortedCards = sortCards(allCards);
    
    int result = 0;
    for(int i = 0; i < sortedCards.size(); i++){
        int cardValue = std::get<int>(sortedCards[i]);
        result += cardValue * (i + 1);
    }

    std::cout << result;
}

int checkStrength(std::string tempCards){
    int strength = 1, jokerAmmount = 0, mostPairsIndex, mostPairsAmmount = 0;
    std::map<char, int> pairs;
    for(int i = 0; i < 5; i++){
        if(tempCards[i] == 'J')
            jokerAmmount++;
        else if(pairs.find(tempCards[i]) == pairs.end()){
            pairs.insert(std::make_pair(tempCards[i], 1));
        } else{
            pairs[tempCards[i]]++;
        }
    }
    if(pairs.size() == 0)
        pairs.insert(std::make_pair('J', 5));
    else{
        for(int i = 0; i < pairs.size(); i++){
            if(pairs[i] > mostPairsAmmount){
                mostPairsAmmount = pairs[i];
                mostPairsIndex = i;
            }
        }
        pairs[mostPairsIndex] += jokerAmmount;
    }
    for(std::pair<char, int> pair : pairs){
        if(std::get<int>(pair) == 5){
            strength = 10;
            break;
        }else if(std::get<int>(pair) == 4){
            strength = 9;
        }

        if(std::get<int>(pair) == 3){
            strength += 5;
        }
        if(std::get<int>(pair) == 2){
            strength += 2;
        }
    }
    return strength;
}
void setVector(std::vector<std::pair<std::string, int>> &fiveOfKind,std::vector<std::pair<std::string, int>> &fourOfKind,std::vector<std::pair<std::string, int>> &fullHouse,std::vector<std::pair<std::string, int>> &threeOfKind,std::vector<std::pair<std::string, int>> &twoPair,std::vector<std::pair<std::string, int>> &onePair,std::vector<std::pair<std::string, int>> &highCard,int strength,std::string tempCards,int tempValue){
    switch (strength)
    {
    case 10:
        fiveOfKind.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 9:
        fourOfKind.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 8:
        fullHouse.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 6:
        threeOfKind.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 5:
        twoPair.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 3:
        onePair.push_back(std::make_pair(tempCards, tempValue));
        break;
    case 1:
        highCard.push_back(std::make_pair(tempCards, tempValue));
        break;
    default:
        std::cout << "error";
        break;
    }
}

std::vector<std::pair<std::string, int>> sortCards(std::vector<std::vector<std::pair<std::string, int>>> allCards){
    int left, right;
    std::vector<std::pair<std::string, int>> result;
    for(std::vector<std::pair<std::string, int>> vector : allCards){
        left = 0;
        right = vector.size();
        bubbleSort(vector);

        for(int i = 0; i < vector.size(); i++)
            result.push_back(vector[i]);
    }

    return result;
}

void bubbleSort(std::vector<std::pair<std::string, int>> &vec){
    int size = vec.size(), index, value1, value2;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size - 1; j++){
            index = 0;
            while(std::get<std::string>(vec[j])[index] == std::get<std::string>(vec[j + 1])[index]){
                index++;
                if(index > 4)
                    break;
            }
            getValue(std::get<std::string>(vec[j])[index], value1);
            getValue(std::get<std::string>(vec[j + 1])[index], value2);
            if(value1 > value2)
                swap(vec[j], vec[j + 1]);
        }
    }
}

void getValue(char character, int &value){
    if(isdigit(character))
        value = character - 48;
    else if(character == 'T')
        value = 10;
    else if(character == 'J')
        value = 1;
    else if(character == 'Q')
        value = 12;
    else if(character == 'K')
        value = 13;
    else if(character == 'A')
        value = 14;
}