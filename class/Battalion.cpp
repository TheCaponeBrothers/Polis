#include <iostream>
#include <windows.h>
#include "Battalion.h"
#include "Citizen.h"
#include "Worker.h"
#include "Soldier.h"
#include "Archer.h"
#include "Lancer.h"
#include "Knave.h"
#include "Knight.h"
#include "Peltast.h"
#include "Hoplite.h"
#include "Pezhetairos.h"
#include "Edifice.h"
#include "Wall.h"
using namespace std;

Battalion::Battalion(int pez,int l,int kna,int hop,int kni,int a,int pel,vector <Citizen*> &s,int type,int type2 = 3) :
    objective(((type2 == 3) ? type : type2)),
    objective2(((type2 == 3) ? type : type2)),
    myPolisId(type),
    inMotion(true),
    distance(0), 
    distFromHome(0),
    fight(false)
{   
    for(int i=0;i<7;i++) numSoldiers[i] = 0;
    makeSoldier<Pezhetairos>(pez,s,0);
    makeSoldier<Lancer>(l,s,1);
    makeSoldier<Knave>(kna,s,2);
    makeSoldier<Hoplite>(hop,s,3);
    makeSoldier<Knight>(kni,s,4);
    makeSoldier<Archer>(a,s,5);b
    makeSoldier<Peltast>(pel,s,6);
}

Battalion::~Battalion(){ for(int i=0;i<soldiers.size();i++) delete soldiers.at(i); soldiers.clear(); }
Soldier * Battalion::getSoldier(int _i){ return soldiers.at(_i); }
vector <Soldier*> Battalion::getTroops(){ return soldiers; }

template <typename T> void Battalion::makeSoldier(int _n,vector <Citizen*> &s,int _i){
    int i = 0, conta = 0;
    while((i < s.size()) && (conta < _n)){
        Citizen * p = s.at(i);
        if(typeid(*p) == typeid(T)){
            soldiers.push_back((T*)p);
            s.erase(s.begin()+i);
            conta++;
        }else i++;
    }
    numSoldiers[_i] = conta;
}

int Battalion::setDamage(int att,int& _danno){
    int conta = 0;
    bool ridotto = false;
    while((!ridotto) && (conta < soldiers.size())){
        if(att - soldiers[conta]->getDefense()){
            att -= soldiers[conta]->getDefense();
            if(att - soldiers[conta]->getHealth() >= 0){
                att -= soldiers[conta]->getHealth();
                conta++;
            }else ridotto = true;
        }else ridotto = true;
    }
    //Il return dà quanti soldati bisogna eliminare, _danno viene inizializzato al valore del danno che subisce l'ultimo soldato ad essere colpito.
    _danno = att;
    return conta;
}

int Battalion::getAttack() const{
    int att = 0;
    for(int i=0;i<soldiers.size();i++) att += soldiers[i]->getAttack();
    return att;
}

int Battalion::getDefense() const{
    int def = 0;
    for(int i=0;i<soldiers.size();i++) def += soldiers[i]->getDefense();
    return def;
}

int Battalion::getSpeed() const{
    int i, spe = 0;
    for(i=0;i<soldiers.size();i++) spe += soldiers[i]->getSpeed();
    return ((soldiers.size() == 0) ? 0 : spe/i);
}

int Battalion::getPolisId() const{ return myPolisId; }
int Battalion::getObjective() const{ return objective; }
int Battalion::getObjective2() const{ return objective2; }
int Battalion::getDistance() const{ return distance; }
int Battalion::getHome() const{ return distFromHome; }
int Battalion::getNumVett() const{ return soldiers.size(); }
int Battalion::getNumSoldiers(int _i) const{ return numSoldiers[_i]; }
int Battalion::getTotSoldiers() const{ 
    int n = 0;
    for(int i=0;i<7;i++) n += numSoldiers[i];
    return n;
}

bool Battalion::getFight() const{ return fight; }
bool Battalion::getMotion() const{ return inMotion; }

void Battalion::removeSoldier(int &num){
    if(num > soldiers.size()) num = soldiers.size();
    for(int i=0;i<num;i++){
        if(typeid(*soldiers[i]) == typeid(Pezhetairos)) numSoldiers[0]--;
        else if(typeid(*soldiers[i]) == typeid(Lancer)) numSoldiers[1]--;
        else if(typeid(*soldiers[i]) == typeid(Knave)) numSoldiers[2]--;
        else if(typeid(*soldiers[i]) == typeid(Hoplite)) numSoldiers[3]--;
        else if(typeid(*soldiers[i]) == typeid(Knight)) numSoldiers[4]--;
        else if(typeid(*soldiers[i]) == typeid(Archer)) numSoldiers[5]--;
        else if(typeid(*soldiers[i]) == typeid(Peltast)) numSoldiers[6]--;
        delete soldiers[i];
    }
    soldiers.erase(soldiers.begin(),soldiers.begin()+num);
}

void Battalion::setDistance(int _d){ distance = _d; }

void Battalion::startFight(Battalion * enemy,Edifice *& wall1,Edifice *& wall2){
    int danno1, danno2;
    int enemyDamage = enemy->setDamage(getAttack(),danno1);
    int myDamage = setDamage(enemy->getAttack(),danno2);
    if(wall1 != NULL){
        enemyDamage -= enemyDamage/10;
        ((Wall*)wall1)->Damage(50 + getTotSoldiers()*2);
    }
    if(wall2 != NULL) enemyDamage -= enemyDamage/10;
    enemy->removeSoldier(enemyDamage);
    removeSoldier(myDamage);
    if(enemy->getNumVett() > 0) enemy->getSoldier(0)->Damage(danno1);
    if(getNumVett() > 0) getSoldier(0)->Damage(danno2);
}

void Battalion::move(){
    int control = distance;
    distance -= getSpeed();
    if(distance > control) distFromHome += getSpeed();
    if(distance <= 0 && objective != 3) fight = true;
    else if(distance <= 0 && objective == 3) inMotion = false;
}

void Battalion::comeBack(){
    if(objective != 3){
        distance = distFromHome;
        objective = 3;
        fight = false;
    }
}

void Battalion::showBattalion(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Battaglione proveniente da: ";
    switch(myPolisId){
         case 0 : cout << "Atene"; break;
         case 1 : cout << "Sparta"; break;
         case 2 : cout << "Tebe"; break;
    }
    switch(objective){
         case 0 : cout << " sta attaccando: Atene"; break;
         case 1 : cout << " sta attaccando: Sparta"; break;
         case 2 : cout << " sta attaccando: Tebe"; break;
         case 3 : cout << " sta tornando a casa."; break;
    }
    cout << ".\nTempo d'arrivo: " << ((distance%getSpeed() != 0) ? (distance/getSpeed())+1 : (distance/getSpeed())) << endl;
}

void Battalion::showAttack(){
    int sum = 0;
    for(int i=0;i<7;i++) sum += numSoldiers[i];
    if(sum > 0){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << endl << "Battaglione ";
        switch(myPolisId){
            case 0 : cout << "Ateniese:" << endl; break;
            case 1 : cout << "Spartano:" << endl; break;
            case 2 : cout << "Tebano:" << endl; break;
        }
        if(numSoldiers[0] > 0 && myPolisId == 2) cout << "Pezeteri: " << numSoldiers[0] << endl;
        if(numSoldiers[1] > 0) cout << "Lancieri: " << numSoldiers[1] << endl;
        if(numSoldiers[2] > 0) cout << "Fanti: " << numSoldiers[2] << endl;
        if(numSoldiers[3] > 0 && myPolisId == 1) cout << "Opliti: " << numSoldiers[3] << endl;
        if(numSoldiers[4] > 0) cout << "Cavalieri: " << numSoldiers[4] << endl;
        if(numSoldiers[5] > 0) cout << "Arceri: " << numSoldiers[5] << endl;
        if(numSoldiers[6] > 0 && myPolisId == 0) cout << "Peltasti: " << numSoldiers[6] << endl;
        cout << "Attacco: " << getAttack() << " Difesa: " << getDefense() << endl;
    }
}
