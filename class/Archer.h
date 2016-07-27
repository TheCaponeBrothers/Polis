#ifndef ARCHER_H
#define ARCHER_H
#include "Soldier.h"

class Archer : public Soldier{
       
    public:
        Archer();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
        
};

#endif
