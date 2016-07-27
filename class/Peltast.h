#ifndef PELTAST_H
#define PELTAST_H
#include "Soldier.h"

class Peltast : public Soldier{
       
    public:
        Peltast();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
                
};

#endif
