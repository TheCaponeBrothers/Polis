#ifndef CAVE_H
#define CAVE_H
#include "EdificeResource.h"

class Cave : public Edifice{
          
    public:
        Cave();
        int getIron();
        int getStone();
        int getGrain();
        
};

#endif
