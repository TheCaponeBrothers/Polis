#ifndef KNAVE_H
#define KNAVE_H
#include "Soldier.h"

class Knave : public Soldier{
       
    public:
        Knave();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
        
};

#endif
