#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

#include "agent.h"

int random(int, int);

class item {
    protected:
        int rowIndex, columnIndex;
        int specBoost;
    public:
        virtual void increaseSpec(agent*) = 0;
};

class healthPotion : public item {
    public:
        healthPotion();
        void increaseSpec(agent*);
};

class shield : public item {
    public:
        shield();
        void increaseSpec(agent*);
};

class necklace : public item {
    public:
        necklace();
        void increaseSpec(agent*);
}; 

class helmet : public item{
    public:    
        helmet();
        void increaseSpec(agent*);
};

#endif