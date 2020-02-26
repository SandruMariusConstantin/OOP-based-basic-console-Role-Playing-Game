/** Name: Sandru Marius-Constantin  
  * Grupa: 143
*/
#include <iostream>
#include "manageGame.h"
#define NAME_LENGHT 20

using namespace std;

int main() { 
    game survivalGame; 
    int choice;
    char* favoriteAgent = new char [NAME_LENGHT + 1];
    char* modifiedAgent = new char [NAME_LENGHT + 1];

    do
    {
        cout << "\nPress 1 - to show the map";
        cout << "\nPress 2 - to show the list of agents";
        cout << "\nPress 3 - to place a bet";
        cout << "\nPress 4 - eliminate an agent";
        cout << "\nPress 5 - move an agent";
        cout << "\nPress 6 - to make a step";
        cout << "\nPress 7 - to finish the game";

        cout << "Choose: ";
        cin >> choice;

        switch(choice) {
            case 1:
                survivalGame.showMap();
                break;
            case 2:
                survivalGame.showAgentsNames();
                break;
            case 3:
                cout << "\nWhat agent do you bet on? - ";
                cin.getline(favoriteAgent, NAME_LENGHT);
                survivalGame.placeYourBet(favoriteAgent);
                break;
            case 4:
                cout << "\nWhat agent do you want to eliminate? - ";
                cin.getline(modifiedAgent, NAME_LENGHT);
                survivalGame.eliminateAgent(modifiedAgent);
                break;
            case 5:
                cout << "\nWhat agent do you want to modify? - ";
                cin.getline(modifiedAgent, NAME_LENGHT);
                survivalGame.moveAgent(modifiedAgent);
                break;
            case 6:
                survivalGame.oneStep();
                break;
            case 7:
                survivalGame.endGame();
                break;
            default:
                cout << "\nYou made a bad choice";
        }
    }while(choice != 4 || survivalGame.isTheEnd() >= 2);

    delete [] modifiedAgent;
}