#ifndef PEZHETAIROS_H
#define PEZHETAIROS_H
#include "Soldier.h"

class Pezhetairos : public Soldier{
       
    public:
        Pezhetairos();
        int getIron();
        int getStone();
        int getGrain();
        int getSpeed();
        int getAttack();
        int getDefense();
        
};

#endif
