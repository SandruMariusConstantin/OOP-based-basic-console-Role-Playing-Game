#include "items.h"
#define MAP_LENGHT 22

healthPotion::healthPotion() {
    specBoost = 500;
}

shield::shield() {
    specBoost = 400;
}

necklace::necklace() {
    specBoost = 200;
}

helmet::helmet() {
    specBoost = 300;
}

void healthPotion::increaseSpec(agent* agentOfDeath) {
    agentOfDeath->HP += specBoost;
}

void shield::increaseSpec(agent* agentOfDeath) {
    agentOfDeath->defense += specBoost;
}

void necklace::increaseSpec(agent* agentOfDeath) {
    agentOfDeath->damage += specBoost;
}

void helmet::increaseSpec(agent* agentOfDeath) {
    agentOfDeath->defense += specBoost;
}