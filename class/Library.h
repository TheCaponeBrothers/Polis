#ifndef LIBRARY_H
#define LIBRARY_H
#include "Player.h"

class Library{
    
    public:
        Library();
        static int numTurn;
        static int coordinate[6];
        static const int constBattalions;
        static const int constEdifices;
        static int Random(int,int);
        static char * getNamePolis(char *,int);
        static void slowPrint(unsigned long,const char *);
        static void changeTurn(Player *,Player *,Player *);
        
};

#endif
