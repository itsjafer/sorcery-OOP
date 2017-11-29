#include "player.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

Player::Player(string &name, unique_ptr<ifstream> &deck): Card{name} {
    string cardFile;
    while (getline(*deck, cardFile)) {
        ifstream cardData{cardFile};
        addCard(cardData);
    }
}

void Player::addCard(ifstream &cardData) {

    //Get card type {spell, minion, enchantment, ritual}
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

        deck.emplace_back(make_unique<Minion>(cardName, cardCost, playerNumber, cardAttack, cardDefense, cardAbilityFiles));
    }
    else if (cardType == "Spell") {
        //Adding a spell card
        //Get spell type
        string spellType; getline(cardData, spellType);
        if (spellType == "move") {
            //Get move source
            string moveSrc; getline(cardData, moveSrc);
            //Get move destination
            string moveDest; getline(cardData, moveDest);
            //Get Target
            string target; getline(cardData, target);
            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);
            //Create card
            MoveSpell newSpell(cardName, cardCost, playerNumber, moveSrc, moveDest, target, static_cast<string &&>(cardDscr));
            deck.emplace_back(newSpell);
        } else if (spellType == "add") {
            //Get Target and modifiers
            string target; getline(cardData, target);
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);
            //Create card
            AddSpell newSpell(cardName, cardCost, attMod, defMod, playerNumber, target, static_cast<string &&>(cardDscr));
            deck.emplace_back(newSpell);
        }
    }
    else if (cardType == "Ritual") {
        //Adding a ritual card
        string ritualType; getline(cardData, ritualType);
        if (ritualType == "add") {
            string target; getline(cardData, target);
            if (target == "player") {
                //Get Ritual basics
                int activeCost; cardData >> activeCost;
                int charges; cardData >> charges;
                Event cardTrigger;
                string trigger; getline(cardData, trigger);
                if (trigger == "Beginning of turn") {
                    cardTrigger = Event::startTurn;
                } else if (trigger == "Enter controlled") {
                    cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
                } else if (trigger == "Enter any") {
                    cardTrigger = Event::minionEnteredPlay;
                }
                //Get player modifiers
                int healthMod; cardData >> healthMod;
                int magicMod; cardData >> healthMod;
                string targets; getline(cardData, targets);
                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                string cardDscr; getline(cardData, cardDscr);
                //Create card
                AddPlayerRitual newRitual(cardName, cardCost, playerNumber, charges, activeCost, healthMod, magicMod, cardTrigger, targets, static_cast<string &&>(cardDscr));
                deck.emplace_back(newRitual);
            } else if (target == "minion") {
                //Get modifiers
                //Get Ritual basics
                int activeCost; cardData >> activeCost;
                int charges; cardData >> charges;
                Event cardTrigger;
                string trigger; getline(cardData, trigger);
                if (trigger == "Beginning of turn") {
                    cardTrigger = Event::startTurn;
                } else if (trigger == "Enter controlled") {
                    cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
                } else if (trigger == "Enter any") {
                    cardTrigger = Event::minionEnteredPlay;
                }
                int attMod; cardData >> attMod;
                int defMod; cardData >> defMod;
                int actPerTurn; cardData >> actPerTurn;
                int abilityCost; cardData >> abilityCost;
                int silenced; cardData >> silenced;
                string target; getline(cardData, target);
                //Name and Cost and decsription
                string cardName; getline(cardData, cardName);
                int cardCost; cardData >> cardCost;
                string cardDscr; getline(cardData, cardDscr);
                //Create card
                AddMinionRitual newRitual(cardName, cardCost, playerNumber, charges, activeCost, attMod, defMod,actPerTurn, abilityCost, silenced, cardTrigger, target, static_cast<string &&>(cardDscr));
                deck.emplace_back(newRitual);
            }
        } else if (ritualType == "move") {
            //Get Ritual basics
            int activeCost; cardData >> activeCost;
            int charges; cardData >> charges;
            Event cardTrigger;
            string trigger; getline(cardData, trigger);
            if (trigger == "Beginning of turn") {
                cardTrigger = Event::startTurn;
            } else if (trigger == "Enter controlled") {
                cardTrigger = Event::minionEnteredPlay; //Note incorrect event type for now, will change later
            } else if (trigger == "Enter any") {
                cardTrigger = Event::minionEnteredPlay;
            }
            //Move data
            string target; getline(cardData, target);
            string destination; getline(cardData, destination);
            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);
            //Create card
            MoveRitual newRitual(cardName, cardCost, playerNumber, charges, activeCost, cardTrigger, target, destination, static_cast<string &&>(cardDscr));
            deck.emplace_back(newRitual);
        }
    }
    else if (cardType == "Enchantment") {  //cardType == "Enhancement"
        //Get ritual type
        string enchantType; getline(cardData, enchantType);
        if (enchantType == "add") {
            //Get modifiers
            int attMod; cardData >> attMod;
            int defMod; cardData >> defMod;
            int actPerTurn; cardData >> actPerTurn;
            int abilityCost; cardData >> abilityCost;
            int silenced; cardData >> silenced;
            //Name and Cost and decsription
            string cardName; getline(cardData, cardName);
            int cardCost; cardData >> cardCost;
            string cardDscr; getline(cardData, cardDscr);
            //Create card
            AddEnchant newEnchantment(cardName, cardCost, playerNumber, attMod, defMod, actPerTurn, abilityCost, silenced,cardDscr);
            deck.emplace_back(newEnchantment);
        }
    }
}

void Player::updateState(vector<Event> &events) {
    for (int i = 0; i < minions.size(); ++i) minions.at(i)->update(events);
    ritual->update(events);
}

void Player::drawCard(int numCards) {
    if (deck.size() > 0) {
        auto card = move(deck.back());
        deck.pop_back();
        hand.emplace_back(move(card));
    }
    else throw out_of_range(getName());
}

const Minion &Player::minion(int i) const {
    return *(minions.at(i - 1));
}

const vector<unique_ptr<NonPlayer>> &Player::getHand() const {
    return hand;
}

void Player::play(int i) {
    auto card = hand.at(i - 1).get();

    if (card->getType() == Type::Spell) {
        card->cast();               //will update the board: no need to do in here
        graveyard.emplace_back(move(card));
    }
    else if (card->getType() == Type::Ritual) {
        ritual = make_unique<Ritual>(move(card));
    }
    else if (card->getType() == Type::Minion) {
        minions.emplace_back(move(card));
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
}

void Player::play(int i, int p, char t) {
    auto card = hand.at(i - 1).get();

    if (card->getType() == Type::Spell) {
        card->cast(p, t);               //will update the board: no need to do in here
        graveyard.emplace_back(move(card));
    }
    else if (card->getType() == Type::Enchantment) {
        card->cast(p, t);
        minions.at((int)(t - 1))->enchantments.emplace_back(move(card));
    }
    else { }    //handle exception

    hand.erase(hand.begin() + (i - 1));     //remove card from hand
}

void Player::use(int i) {
    minions.at(i - 1)->cast();
}
    
void Player::use(int i, int p, char t) {
    minions.at(i - 1)->cast(p, t);
}

void Player::attack(int i, int j) {
    minions.at(i - 1)->attack(j);
}

Player::~Player() {
    deck.clear();
    graveyard.clear();
    hand.clear();
    minions.clear();
}
