#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include "manageGame.h"
#define MAP_LENGHT 22
#define FREE_SPACE '_'
#define OBSTACLE '*'
#define AGENTT 'A'

using namespace std;

int random(int limInf, int limSup) {
    int randomNumber;
    srand (time(NULL));
    randomNumber = limInf + rand() % (limSup - limInf + 1);

    return randomNumber;
}

game::game() {
    step = 0;
    map = new char [MAP_LENGHT];
    listItems = new item* [5];
    bet = NULL;

    initializeMap();
    initializeAgents();
    initializeItems();

    showMap();
}

game::~game() {
    delete [] map;
    delete [] listItems;
    delete [] bet;
    if(agents[0] != NULL) {
        delete [] agents[0]->name;
        delete agents[0];
        agents.clear();
    }
}

int game::index(int x, int y) const {
    return x*MAP_LENGHT + y;
}

char game::at(int x, int y) const {
    return map[index(x, y)];
}

void game::freeSpace(int & row, int & column) {
    int rowIndex, columnIndex;

    do
    {
        rowIndex = random(0, MAP_LENGHT);
        columnIndex = random(0, MAP_LENGHT);
    }while(at(rowIndex, columnIndex) != FREE_SPACE);

    row = rowIndex;
    column = columnIndex;
}

int game::getPositionAgent(agent* agentOfDeath) {
    int rowIndex, columnIndex;

    freeSpace(rowIndex, columnIndex);

    agentOfDeath->rowIndex = rowIndex;
    agentOfDeath->columnIndex = columnIndex;

    return rowIndex*MAP_LENGHT + columnIndex;
}

void game::initializeMap() {
    int rowIndex, columnIndex;

    for(int i = 0; i < MAP_LENGHT*MAP_LENGHT; i++)
        map[i] = FREE_SPACE;
    for(int i = 0; i < 10; i++) {
        freeSpace(rowIndex, columnIndex);
        map[index(rowIndex, columnIndex)] = OBSTACLE;
    }
}

void game::initializeAgents() {
    for(int i = 0; i < 10; ++i){
        agent* agentOfDeath1 = new Warrior;
        map[getPositionAgent(agentOfDeath1)] = AGENTT;
        agents.push_back(agentOfDeath1);

        agent* agentOfDeath2 = new Hunter;
        map[getPositionAgent(agentOfDeath2)] = AGENTT;
        agents.push_back(agentOfDeath2);

        agent* agentOfDeath3 = new Priest;
        map[getPositionAgent(agentOfDeath3)] = AGENTT;
        agents.push_back(agentOfDeath3);

        agent* agentOfDeath4 = new Mage;
        map[getPositionAgent(agentOfDeath4)] = AGENTT;
        agents.push_back(agentOfDeath4); 
    }
}

void game::initializeItems() {
    listItems[1] = new healthPotion;
    listItems[2] = new shield;
    listItems[3] = new necklace;
    listItems[4] = new helmet;

    for(int i = 0; i < 5; ++i) {
        int rowIndex, columnIndex;
        
        freeSpace(rowIndex, columnIndex);
        map[index(rowIndex, columnIndex)] = '1'; 

        freeSpace(rowIndex, columnIndex);
        map[index(rowIndex, columnIndex)] = '2'; 

        freeSpace(rowIndex, columnIndex);
        map[index(rowIndex, columnIndex)] = '3'; 

        freeSpace(rowIndex, columnIndex);
        map[index(rowIndex, columnIndex)] = '4';    
    }
}

void game::killed(agent* agentOfDeath, int index) {
    delete [] agentOfDeath->name;
    agents.erase(agents.begin() + index);
    delete agentOfDeath;
}

void game::showMap() {
    for(int i = 0; i < MAP_LENGHT; i++) {
        cout<<'|';
        for(int j = 0; j < MAP_LENGHT; j++)
            cout<<at(i,j)<<' ';
        cout<<'|'<<endl;
    }
}

void game::showAgentsNames() {
    cout << endl << "List of agents: \n";
    for (int i = 0; i < agents.size(); i++) 
        cout << agents[i]->name << endl; 
}

void game::moveAgent(char* agentName) {
    int rowIndex, columnIndex, i = 0;

    while(strcmp(agents[i]->name, agentName) && i < agents.size())
        i++;
    if(i == agents.size())
        cout << "\nThe agent you are searching for doesn't exist";
    else
    {
        cout << "\nYour position row index: ";    cin >> rowIndex;
        cout << "\nYour position column index";   cin >> columnIndex;

        if(at(rowIndex, columnIndex) != FREE_SPACE)
            cout << "\nThis place is occupied";
        else
        {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            agents[i]->rowIndex = rowIndex;
            agents[i]->columnIndex = columnIndex;
            cout << "\nThe agent has been moved";
        }
    }
}

void game::eliminateAgent(char* agentName) {
    int rowIndex, columnIndex, i = 0;

    while(strcmp(agents[i]->name, agentName) && i < agents.size())
        i++;
    if(i == agents.size())
        cout<<"\nThe agent you are searching for doesn't exist";
    else
    {
        map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
        killed(agents[i], i);
        cout<<"\nThe agent has been eliminated";   
    }
}

void game::placeYourBet(char* agentName) {
    bet = agentName;
}

int game::searchAgent(int rIndex, int cIndex) {
    int i = -1;

    do
    {
        i++;
    } while (agents[i]->rowIndex != rIndex || agents[i]->columnIndex != cIndex || i == agents.size());   
}

void game::oneStep() {
    int row, column;

    for (int i = 0; i < agents.size(); i++) { 
        row = agents[i]->rowIndex;
        column = agents[i]->columnIndex;
        int actionTaken = 0;
        
        agents[i]->move(row, column, step);

        while(at(row, column) == OBSTACLE) {
            agents[i]->changeDirection(row, column);
        }

        if(row >= MAP_LENGHT || row < 0 || column >= MAP_LENGHT || column < 0) {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            killed(agents[i], i);
            i--;
            actionTaken = 1;
        }

        if(!actionTaken && at(row, column) == '1') {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            listItems[1]->increaseSpec(agents[i]);
            agents[i]->rowIndex = row;
            agents[i]->columnIndex = column;
            actionTaken = 1;
        }

        if(!actionTaken && at(row, column) == '2') {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            listItems[2]->increaseSpec(agents[i]);
            agents[i]->rowIndex = row;
            agents[i]->columnIndex = column;
            actionTaken = 1;
        }

        if(!actionTaken && at(row, column) == '3') {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            listItems[3]->increaseSpec(agents[i]);
            agents[i]->rowIndex = row;
            agents[i]->columnIndex = column;
            actionTaken = 1;
        }

        if(!actionTaken && at(row, column) == '4') {
            map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
            listItems[4]->increaseSpec(agents[i]);
            agents[i]->rowIndex = row;
            agents[i]->columnIndex = column;
            actionTaken = 1;
        }    

        if(!actionTaken && at(row, column) == AGENTT) {
            int position = searchAgent(row,column); 

            agents[i]->attack(agents[position]);

            int status1 = agents[i]->getLifeStatus();
            int status2 = agents[position]->getLifeStatus();

            if(status2 == 0 && position < i)
            {
                map[index(row, column)] = FREE_SPACE;
                killed(agents[position], position);
                i--;
            }

            if(status2 == 0 && position > i)
            {
                map[index(row, column)] = FREE_SPACE;
                killed(agents[position], position);
            }

            if(status1 == 0)
            {
                map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
                killed(agents[i], i);
                i--;
            }

            if(status2 == 0 && status1 == 1)
            {
                map[index(agents[i]->rowIndex, agents[i]->columnIndex)] = FREE_SPACE;
                map[index(row, column)] = AGENTT;
                agents[i]->rowIndex = row;
                agents[i]->columnIndex = column;
            }
        }
    }
    
    isTheEnd();

    step++;
}

void game::endGame() {
    while(agents.size() > 1)
        oneStep();
    showMap();

    isTheEnd();    
}

int game::isTheEnd() {
    if(agents.size() < 2) {
        if(agents.size() < 1)
            cout << "\n\nAll agents have died! That's horrible!";
        else
        {
            cout << "\n\nThe winner is " << agents[0]->name;
            if(bet != NULL)
                if(strcmp(agents[0]->name, bet) == 0)
                    cout << "\nYou won the bet!";
                else 
                    cout << "\nYou lost the bet!";
        }
        return 1;
    }
    return 0;
}