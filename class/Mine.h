#ifndef MINE_H
#define MINE_H
#include "EdificeResource.h"

class Mine : public Edifice{
        
    public:
        Mine();
        int getIron();
        int getStone();
        int getGrain();
        
};

#endif
