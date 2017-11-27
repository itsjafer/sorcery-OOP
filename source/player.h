#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "card.h"

class NonPlayer;
class Ritual;
class Minion;

class Player: public Card {
    friend BoardModel;
    int health = 20;
    int magic = 3;
    std::vector<std::unique_ptr<NonPlayer>> deck;
    std::vector<std::unique_ptr<NonPlayer>> hand;
    Ritual *ritual;
    std::vector<std::unique_ptr<NonPlayer>> graveyard;
    std::vector<std::unique_ptr<Minion>> minions;
    int playerNumber;
    void addCard(std::ifstream &cardData);
    void updateState(std::vector<Event> &events);
public:
    Player(std::string &name, std::ifstream &deck);
    void drawCard(int numCards = 1);
    const Minion &minion(int i) const;                                  //to be accessed only for Display
    const std::vector<std::unique_ptr<NonPlayer>> &getHand() const;     //same here
    void play(int i);                                                   //minions, rituals, & spells w/ no target
    void play(int i, int p, char t = 'r');                              //spells (w/ target) & enchantments 
    void use(int i);                                                    //untargetted activated ability of ith minion
    void use(int i, int p, char t = 'r');                               //targetted activated ability of ith minion
    void attack(int i, int j = 0);
    ~Player();
};

#endif