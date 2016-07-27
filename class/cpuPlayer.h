#ifndef CPUPLAYER_H
#define CPUPLAYER_H
#include "Player.h"

class cpuPlayer : public Player{
       
    public:
        cpuPlayer(int,int,int);
        void evolvePolis(Player *,Player *);
        void nextResources(int&, int&, int&);
        Battalion * checkAttack(Player *,Player *);
        void cpuAttack(Player *,Battalion *, int, bool&);
        void choiceTroops(int *,int &);
        void reduceTroops(int *,int &, int &, Player *);
        void generateEdifice(Battalion *, int);
        void generateCitizen(Battalion *, int, int, int, Player *, Player *);
        template <typename T> void createCitizen(int&,int,int);
        template <typename T> void createEdifice(int);
        ostream & put (ostream &os);
};

#endif
