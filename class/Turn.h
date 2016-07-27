#ifndef TURN_H
#define TURN_H

#include "Player.h"
using namespace std;

class Turn
{
      private:
              static int numTurn;
      public:
             Turn();
             void setActions(Player * _g1, Player * _g2, Player * _g3);
             void setResources(Player * _g);
             void moveBattalions(Player * _g);
             void actionTurn(Player * _g1, Player * _g2, Player * _g3);
};

#endif
