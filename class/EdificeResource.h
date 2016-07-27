#ifndef EDIFICERESOURCE_H
#define EDIFICERESOURCE_H
#include "Edifice.h"

class EdificeResource : public Edifice{
    
    public:
        EdificeResource();
        virtual int getIron() = 0;
        virtual int getStone() = 0;
        virtual int getGrain() = 0;
        virtual int getResource() = 0;

};

#endif
