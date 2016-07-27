#ifndef SOLDIER_H
#define SOLDIER_H
#include "Citizen.h"

class Soldier : public Citizen{
       
    public:
        Soldier();
        virtual int getSpeed() = 0;
        virtual int getAttack() = 0;
        virtual int getDefense() = 0;
                
};

#endif
