#ifndef FARM_H
#define FARM_H
#include "EdificeResource.h"

class Farm : public Edifice{

    public:
        Farm();
        int getIron();
        int getStone();
        int getGrain();
    
};

#endif
