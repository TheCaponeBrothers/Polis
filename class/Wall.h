#ifndef WALL_H
#define WALL_H
#include "Edifice.h"

// All in all we're just another brick in the wall
/* This is true. */

class Wall : public Edifice{

    private:
        int defense;
        
    public:
        Wall();
        int getIron();
        int getStone();
        int getGrain();
        int getDefense();
        void Damage(int);
    
};

#endif
