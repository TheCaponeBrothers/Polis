#ifndef CITIZEN_H
#define CITIZEN_H

class Citizen{

    private:
        int health;
        
    public:
        Citizen();
        virtual int getIron() = 0;
        virtual int getStone() = 0;
        virtual int getGrain() = 0;
        int getHealth() const;
        void Damage(int);
        void Heal();
        
};

#endif
