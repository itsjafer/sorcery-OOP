#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "card.h"
#include "playermodel.h"

class NonPlayer;
class Ritual;
class Minion;

class PlayerController: public Card {
    friend BoardModel;
    PlayerModel playerModel;
    void addCard(std::ifstream &cardData);
    void updateState(std::vector<Event> &events) override;
public:
    PlayerController(std::string &name, std::unique_ptr<std::ifstream> &deck, int playerNumber);
    void drawCard(int numCards = 1);
    void shuffleDeck();
    const Minion &minion(int i) const;                                  //to be used by displays (i.e. Observers)
    const std::vector<std::shared_ptr<NonPlayer>> &getHand() const;     //same here
    void play(int i);                                                   //non-targetted spells & rituals, as well as placing minions on the field
    void play(int i, int p, char t = 'r');                              //spells (w/ target) & enchantments 
    void use(int i);                                                    //untargetted activated ability of ith minion
    void use(int i, int p, char t = 'r');                               //targetted activated ability of ith minion
    void attack(int i, int j = 0);
    void discard(int i);                                                //-testing mode only
    const PlayerModel &getPlayerData();  
    ~PlayerController();
};

#endif