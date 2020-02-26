#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED

int random(int, int );

class agent {
    public:
        int rowIndex, columnIndex;
        int HP, defense, damage;
        char *name;
    public:
        int getLifeStatus();
        void attack(agent*);
        virtual void move(int&, int&, int) = 0;
        virtual void changeDirection(int&, int&) = 0;
};

class Warrior : public agent {
    public:
        Warrior();
        ~Warrior();
        void move(int&, int&, int);
        void changeDirection(int&, int&);
};

class Hunter : public agent {
    public:
        Hunter();
        ~Hunter();
        void move(int&, int&, int);
        void changeDirection(int&, int&);
};

class Priest : public agent {
    public:
        Priest();
        ~Priest();
        void move(int&, int&, int);
        void changeDirection(int&, int&);
};

class Mage : public agent {
    public:
        Mage();
        ~Mage();
        void move(int&, int&, int);
        void changeDirection(int&, int&);
};

#endif