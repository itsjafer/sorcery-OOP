#include "ritual.h"

using namespace std;

AddMinionRitual::AddMinionRitual(string &cardName, int cost, int owner, int charges, int activationCost,
                                 int attMod, int defMod, int actPerTurn, int abilityCost, int silencer, Event trigger,
                                 string &target, string &&description):
NonPlayer(cardName, cost, owner, description), Ritual(charges, activationCost, trigger), attMod(attMod), defMod(defMod), actPerTurn(actPerTurn), abilityCost(abilityCost), target(target){
    if (silencer == 0) {
        silence = false;
    } else {
        silence = true;
    }
}