#include "activated.h"
#include <fstream>
#include <iostream>

using namespace std;

SummonActive::SummonActive(string &name, int cost, int owner, string &description, int summonAmount,
                           string &summonMinion, Minion *minion):
Activated(name, cost, owner, description, minion), summonAmount(summonAmount), summonMinion(summonMinion){}

void SummonActive::updateState(vector<Event> &events) {

}

void SummonActive::castCard() {
  ifstream cardData{summonMinion};
  string cardType; getline(cardData, cardType);
  if (cardType == "Minion") {
      //Adding a minion type
      string cardName; getline(cardData, cardName);
      int cardCost; cardData >> cardCost;
      int cardAttack; cardData >> cardAttack;
      int cardDefense; cardData >> cardDefense;


      vector<ifstream> cardAbilityFiles;
      string ability;
      while (getline(cardData, ability)) {
          cardAbilityFiles.emplace_back(move(ability));
      }

      for (int i = 0; i < summonAmount && board->players.at(this->getOwner())->numMinions() < 5; ++i) {
          board->players.at(this->getOwner())->addMinion(make_shared<Minion>(cardName, cardCost, this->getOwner(), cardAttack, cardDefense, cardAbilityFiles));
      }
  }

}

void SummonActive::castCard(int p, int t) {

}
