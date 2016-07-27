#ifndef TEMPLE_H
#define TEMPLE_H
#include "Edifice.h"

class Temple : public Edifice{
    private:
        int gift;
           
    public:
        Temple();
        int getIron();
        int getStone();
        int getGrain();
        int getGift();
        void resetGift();
        void addGift(int);
};

#endif
