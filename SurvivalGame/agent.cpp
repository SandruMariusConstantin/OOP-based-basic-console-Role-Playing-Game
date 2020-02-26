#include <iostream>
#include <fstream>
#include <cstring>
#include "agent.h"
#define MAP_LENGHT 22
#define OBSTACLE '*'
#define AGENTS_NUMBER 40
#define FREE_SPACE '_'
#define NAME_MAX_LENGHT 20

using namespace std;

ifstream f("numele_agentilor.txt");

int agent::getLifeStatus() {
    if(HP > 0)
        if(rowIndex >= 0 && columnIndex >= 0  && rowIndex < MAP_LENGHT && columnIndex < MAP_LENGHT)
            return 1;
    return 0;
}

Warrior::Warrior() {
    HP = 1000;
    defense = 300;
    damage = 100;
    
    name = new char [NAME_MAX_LENGHT + 1];
    f.getline(name, NAME_MAX_LENGHT);
    name[strlen(name) - 1] = '\0';
}

Warrior::~Warrior() {
    delete name;
}

Hunter::Hunter() {
    HP = 800;
    defense = 150;
    damage = 250;
    
    name = new char [NAME_MAX_LENGHT + 1];
    f.getline(name, NAME_MAX_LENGHT);
    name[strlen(name) - 1] = '\0';
}

Hunter::~Hunter() {
    delete name;
}

Priest::Priest() {
    HP = 1500;
    defense = 200;
    damage = 80;
    
    name = new char [NAME_MAX_LENGHT + 1];
    f.getline(name, NAME_MAX_LENGHT);
    name[strlen(name) - 1] = '\0';
}

Priest::~Priest() {
    delete name;
}

Mage::Mage() {
    HP = 700;
    defense = 200;
    damage = 400;
    
    name = new char [NAME_MAX_LENGHT + 1];
    f.getline(name, NAME_MAX_LENGHT);
    name[strlen(name) - 1] = '\0';
}

Mage::~Mage() {
    delete name;
}

void agent::attack(agent* agentOfDeath) {
    while(getLifeStatus() && agentOfDeath->getLifeStatus()) {
        if(agentOfDeath->defense > 0)
            agentOfDeath->defense -= damage;
        if(agentOfDeath->defense < 0){
            agentOfDeath->HP += agentOfDeath->defense;
            agentOfDeath->defense = 0;
        }
        if(agentOfDeath->getLifeStatus()) {
            if(defense > 0)
                defense -= agentOfDeath->damage;
            if(defense < 0){
                HP += defense;
                defense = 0;
            }
        }
    }

    if(!getLifeStatus() && !agentOfDeath->getLifeStatus())
        cout <<'\n' << name << " and " << agentOfDeath->name << " killed each other";
    else
    {
        if(!getLifeStatus())
            cout << '\n' << agentOfDeath->name << " killed " << name;
        if(!agentOfDeath->getLifeStatus()) 
            cout << '\n' << name << " killed " << agentOfDeath->name;  
    }
}

void Warrior::move(int & rIndex, int & cIndex, int step) {
    rIndex++;
}

void Hunter::move(int & rIndex, int & cIndex, int step) {
    if(step%2) 
    {
        rIndex = rIndex - 1;
        cIndex = cIndex - 1;
    }
    else
    {
        cIndex = cIndex - 1;
    }
}

void Priest::move(int & rIndex, int & cIndex, int step) {
    if(step%2 == 0) 
    {
        rIndex = rIndex + 1;
        cIndex = cIndex + 1;
    }
    else
    {
        rIndex = rIndex - 1;
        cIndex = cIndex - 1;
    }
}

void Mage::move(int & rIndex, int & cIndex, int step) {
    if(step%2) 
    {
        rIndex = rIndex + 2;
        cIndex = cIndex + 1;
    }
    else
    {
        rIndex = rIndex - 1;
        cIndex = cIndex - 2;
    }
}

void Warrior::changeDirection(int & rIndex, int & cIndex) {
    cIndex++;
}

void Hunter::changeDirection(int & rIndex, int & cIndex) {
    rIndex--;
}

void Priest::changeDirection(int & rIndex, int & cIndex) {
    rIndex++;
}

void Mage::changeDirection(int & rIndex, int & cIndex) {
    cIndex += 2;
}

