#ifndef KNIGH_H
#define KNIGH_H
#include "Soldier.h"

class Knight : public Soldier{
       
    public:
        Knight();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
        
};

#endif
