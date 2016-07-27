#ifndef LANCER_H
#define LANCER_H
#include "Soldier.h"

class Lancer : public Soldier{
       
    public:
        Lancer();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
        
};

#endif
