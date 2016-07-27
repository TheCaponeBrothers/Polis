#ifndef PLAYER_H
#define PLAYER_H
#include"Polis.h"
#include<string>
using namespace std;

class Player{
    
    protected:
        Polis * myPolis;
        bool actions[3];  // 0 : -> hai costruito 1 edificio
                          // 1 : -> hai creato dei cittadini
                          // 2 : -> hai attaccato 1 giocatore
        
    public:
        Player(int,int,int);
        ~Player();
        Polis * getPolis();
        string namePolis();
        bool getCpu() const;
        bool getAction(int) const;
        bool getTemple();
        void setAction(int,bool);
        void makeCitizen();
        void makeEdifice();
        void retire();
        void retire(int);
        void actionTurn();
        void statisticsTurn();
        void attack(Player *,Player *,vector <int>);
        void showBattalions(Player *&,Player *&,bool);
        void destroyEdify();
        void destroy(Player *&);        
        void deletePolis();
        static void deletePlayer(Player *&);
        Battalion * selectEnemy(Player *,Player *,Battalion *,Player *&);                
        template <typename T> bool exectCitizen(int);
        template <typename T> bool exectEdifice(int);
        template <typename T> int returConst(int,int);
        virtual void offer();
        virtual ostream & put (ostream &os);
        friend ostream &operator<<(ostream &os,Player &obj);

};

#endif
