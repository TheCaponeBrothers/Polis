#ifndef HOPLITE_H
#define HOPLITE_H
#include "Soldier.h"

class Hoplite : public Soldier{
       
    public:
        Hoplite();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
                
};

#endif
