#ifndef EDIFICE_H
#define EDIFICE_H

class Edifice{
        
    public:
        Edifice();
        virtual int getIron() = 0;
        virtual int getStone() = 0;
        virtual int getGrain() = 0;
    
};

#endif
