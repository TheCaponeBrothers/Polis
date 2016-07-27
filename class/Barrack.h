#ifndef BARRACK_H
#define BARRACK_H
#include "Edifice.h"

class Barrack : public Edifice{
                  
    public:
        Barrack();
        int getIron();
        int getStone();
        int getGrain();
    
};

#endif
