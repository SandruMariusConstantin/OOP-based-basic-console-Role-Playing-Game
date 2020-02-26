#ifndef MANAGEGAME_H_INCLUDED
#define MANAGEGAME_H_INCLUDED

#include <vector>
#include "items.h"

using namespace std;

class game {
        char *map;
        char *bet;
        vector<class agent*> agents;
        item **listItems;
    public:
        int step;
        game();
        ~game();
        void initializeMap();
        void initializeAgents();
        void initializeItems();
        void freeSpace(int &, int &);
        void killed(agent*, int);
        void showMap();
        void showAgentsNames();
        void moveAgent(char*);
        void eliminateAgent(char*);
        void placeYourBet(char*);
        void endGame();
        void oneStep();
        char at(int, int) const;
        int index(int x, int y) const;
        int getPositionAgent(agent*);
        int searchAgent(int, int);
        int isTheEnd();
};

#endif