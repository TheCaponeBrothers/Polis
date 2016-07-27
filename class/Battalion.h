#ifndef BATTALION_H
#define BATTALION_H
#include <vector>
#include "Soldier.h"
#include "Edifice.h"
using namespace std;

class Battalion{
    
     private:
             vector <Soldier*> soldiers;
             int numSoldiers[7]; /* 0->Pezeteri
                                    1->Lancieri
                                    2->Fanti
                                    3->Opliti
                                    4->Cavalieri
                                    5->Arcieri
                                    6->Peltasti
                                 */
             int myPolisId;
             int objective;
             int objective2;
             int distance;
             int distFromHome;
             bool fight;
             bool inMotion;
             
     public:
            Battalion(int,int,int,int,int,int,int,vector <Citizen*>&,int,int);
            ~Battalion();
            Soldier * getSoldier(int);
            vector <Soldier*> getTroops();
            template <typename T> void makeSoldier(int,vector <Citizen*>&,int);
            int setDamage(int,int&);
            int getAttack() const;
            int getDefense() const;
            int getSpeed() const;
            int getPolisId() const;
            int getObjective() const;
            int getObjective2() const;
            int getDistance() const;
            int getHome() const;
            int getNumVett() const;
            int getNumSoldiers(int) const;
            int getTotSoldiers() const;
            bool getFight() const;
            bool getMotion() const;
            void removeSoldier(int&);
            void setDistance(int);
            void startFight(Battalion*, Edifice*&, Edifice*&);
            void move();
            void comeBack();
            void showBattalion();
            void showAttack();
};

#endif
