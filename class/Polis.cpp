#include <iostream>
#include <math.h>
#include "Library.h"
#include "Polis.h"
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
#include "Cave.h"
#include "Farm.h"
#include "Mine.h"
#include "Wall.h"
#include "Barrack.h"
#include "Temple.h"
using namespace std;

template void Polis::newCitizen<Worker>();
template void Polis::newCitizen<Lancer>();
template void Polis::newCitizen<Knave>();
template void Polis::newCitizen<Knight>();
template void Polis::newCitizen<Archer>();
template void Polis::newCitizen<Peltast>();
template void Polis::newCitizen<Hoplite>();
template void Polis::newCitizen<Pezhetairos>();
template void Polis::newEdifice<Cave>();
template void Polis::newEdifice<Farm>();
template void Polis::newEdifice<Mine>();
template void Polis::newEdifice<Barrack>();
template void Polis::newEdifice<Temple>();
template void Polis::newEdifice<Wall>();
template bool Polis::deleteEdifice<Mine>(int);
template bool Polis::deleteEdifice<Cave>(int);
template bool Polis::deleteEdifice<Farm>(int);
template bool Polis::deleteEdifice<Barrack>(int);
template bool Polis::deleteEdifice<Temple>(int);
template bool Polis::deleteEdifice<Wall>(int);

Polis::Polis(int _typePolisId,int _xcord,int _ycord) : 
    typePolisId(_typePolisId), 
    xcord(_xcord), 
    ycord(_ycord),
    iron(1000),
    stone(1000),
    grain(1000)
{
    int n;	
	switch(_typePolisId){
        case 0: stone += 500; n = Library::Random(12,16); break;
        case 1: iron += 500; n = Library::Random(14,14); break;
        case 2: grain += 500; n = Library::Random(13,15); break;
	}
	
	for(int i=0;i<9;i++) numCitizens[i] = 0;
	for(int i=0;i<7;i++) numEdifices[i] = 0;
	for(int i=0;i<n;i++){ numCitizens[0]++; newCitizen<Worker>(); }
}

Polis::~Polis(){
    for(int i=0;i<battalions.size();i++) delete battalions.at(i); battalions.clear();
    for(int i=0;i<edifices.size();i++) delete edifices.at(i); edifices.clear();
}

int Polis::getId() const{ return typePolisId; }
int Polis::getXcord() const{ return xcord; }
int Polis::getYcord() const{ return ycord; }
int Polis::getNumIron() const{ return iron; }
int Polis::getNumStone() const{ return stone; }
int Polis::getNumGrain() const{ return grain; }
int Polis::getNumBattalions() const{ return battalions.size(); }
int Polis::getNumCitizens() const{ return citizens.size(); }
int Polis::getNumEdifices() const{ return edifices.size(); }
int Polis::getNumCity(int _i) const{ return numCitizens[_i]; }
int Polis::getNumEdify(int _i) const{ return numEdifices[_i]; }
int Polis::getDistance(int _x,int _y) const{ return (int)sqrt(pow(_x-getXcord(),2)+pow(_y-getYcord(),2)); }
int Polis::getDistance(Polis * _polis) const{ return getDistance(_polis->getXcord(),_polis->getYcord()); }
int Polis::getCalculate(int _v[],int _type){
    int val = 0, m = 0;
    for(int i=0;i<7;i++){
        Soldier * p;
        if(i == 0) p = new Pezhetairos;
        else if(i == 1) p = new Lancer;
        else if(i == 2) p = new Knave;
        else if(i == 3) p = new Hoplite;
        else if(i == 4) p = new Knight;
        else if(i == 5) p = new Archer;
        else if(i == 6) p = new Peltast;
        if(_type == 0) val += p->getAttack()*_v[i];
        else if(_type == 1) val += p->getDefense()*_v[i];
        else if(_type == 2) val += p->getSpeed()*_v[i];
        m += 1*_v[i];
        delete p;
    }
    if(_type != 2) m = 1;
    return val/m;
}

Battalion * Polis::getBattalion(int _n){ return battalions.at(_n); }
Citizen * Polis::getCitizen(int _n){ return citizens.at(_n); }
Edifice * Polis::getEdifice(int _n){ return edifices.at(_n); }

void Polis::addTemple(int _n){
    for(int i=0; i<getNumEdifices(); i++){
        Temple *p = dynamic_cast <Temple*> (getEdifice(i));
        if(p != 0) p->addGift(_n);
    }
}

int Polis::getGift(){
    for(int i=0; i<getNumEdifices(); i++){
        Temple *p = dynamic_cast <Temple*> (getEdifice(i));
        if(p != 0){ 
            int aux = p->getGift();
            p->resetGift();
            return aux;
        }
    }
    return 0;
}

void Polis::destroyEdifice(int _i){ edifices.erase(edifices.begin()+_i); }
void Polis::destroyCitizens(){ citizens.erase(citizens.begin()+rand()%citizens.size()); }

template <typename T> void Polis::newCitizen(){ Citizen * a = new T; citizens.push_back(a); }
template <typename T> void Polis::newEdifice(){ Edifice * a = new T; edifices.push_back(a); }
template <typename T> bool Polis::deleteEdifice(int typeEdificeId){
    if(getNumEdify(typeEdificeId) > 0){
        for(int i=0;i<getNumEdifices();i++){
            if(typeid(*getEdifice(i)) == typeid(T)){
                delete getEdifice(i);
                subNumEdifice(typeEdificeId);
                edifices.erase(edifices.begin()+i);
                return true;
            }
        }
    }
    return false;
}

bool Polis::makeBattalion(int obj){
    if(numCitizens[1] != 0){
        if(getNumBattalions() < Library::constBattalions){
            int num[7];
            string name[] = {"Pezeteri","Lancieri","Fanti","Opliti","Cavalieri","Arcieri","Peltasti"};
            for(int i = 0;i<7;i++){
                num[i] = 0;
                bool control = false;
                if(i == 0 && typePolisId == 2) control = true;
                else if(i == 3 && typePolisId == 1) control = true;
                else if(i == 6 && typePolisId == 0) control = true;
                else if(i != 0 && i != 3 && i != 6) control = true;
                if(control && numCitizens[i+2] > 0){
                    while(cout << "Inserisci numero di " << name[i] << "(" << numCitizens[i+2] << ")" <<  ": " && !(cin >> num[i])){
                        cout << endl << "Errore." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(),'\n');
                        return false;
                    }
                }
            }
            return controlBattalion(num[0],num[1],num[2],num[3],num[4],num[5],num[6],obj);
        }else cout << "Non puoi creare pi" << (char)(151) << " battaglioni." << endl;
    }else cout << "Non esistono soldati in citt" << (char)(133) << "." << endl;
    return false;
}

bool Polis::controlBattalion(int pez,int l,int kna,int hop,int kni,int a,int pel,int obj){
    int num[7];
    num[0] = ((pez > getNumCity(2)) ? getNumCity(2) : pez);
    num[1] = ((l > getNumCity(3)) ? getNumCity(3) : l);
    num[2] = ((kna > getNumCity(4)) ? getNumCity(4) : kna);
    num[3] = ((hop > getNumCity(5)) ? getNumCity(5) : hop);
    num[4] = ((kni > getNumCity(6)) ? getNumCity(6) : kni);
    num[5] = ((a > getNumCity(7)) ? getNumCity(7) : a);
    num[6] = ((pel > getNumCity(8)) ? getNumCity(8) : pel);
    int _soldier = 0; for(int i=0;i<7;i++) _soldier += num[i];    
    if(_soldier != 0){
        cout << endl << "Soldati: (" << _soldier << "/" << getNumCity(1) << ")" << endl;
        cout << "Lancieri: (" << num[1] << "/" << getNumCity(3) << ")" << endl;
        cout << "Fanti: (" << num[2] << "/" << getNumCity(4) << ")" << endl;
        cout << "Cavalieri: (" << num[4] << "/" << getNumCity(6) << ")" << endl;
        cout << "Arceri: (" << num[5] << "/" << getNumCity(7) << ")" << endl;
        if(typePolisId == 0) cout << "Peltasti: (" << num[6] << "/" << getNumCity(8) << ")" << endl;
        else if(typePolisId == 1) cout << "Opliti: (" << num[3] << "/" << getNumCity(5) << ")" << endl;
        else if(typePolisId == 2) cout << "Pezeteri: (" << num[0] << "/" << getNumCity(2) << ")" << endl;
        cout << endl << "Attacco: " << getCalculate(num,0) << " Difesa: " << getCalculate(num,1) << " Velocit" << (char)(133) << ": " << getCalculate(num,2) << " Tempo di arrivo: " << (getDistance(Library::coordinate[obj],Library::coordinate[obj+3])/getCalculate(num,2))+1 << endl;
        string convalid = "";
        cout << endl << "Vuoi creare questo battaglione [s/n]? ";
        cin >> convalid;
        
        if(convalid == "s"){
            newBattalion(_soldier,num,obj);
            return 1;
        }else if(convalid != "n") cout << "Nessun comando " << (char)(138) << " stato trovato." << endl;
        
    }else cout << endl << "Battaglione vuoto." << endl;
    return 0;
}

void Polis::newBattalion(int _soldier,int num[],int obj){
    Battalion * b = new Battalion(num[0],num[1],num[2],num[3],num[4],num[5],num[6],citizens,typePolisId,obj);
    battalions.push_back(b);
    numCitizens[1] -= _soldier;
    for(int i=0;i<7;i++) numCitizens[i+2] -= num[i];
}

void Polis::eraseBattalion(int index){
    cout << "Il numero di soldati tornati dalla battaglia sono: " << battalions.at(index)->getTroops().size() << endl << endl;
    if(battalions.at(index)->getTroops().size() > 0) battalions.at(index)->getSoldier(0)->Heal();
    for(int i=0; i<battalions.at(index)->getTroops().size(); i++){
        Citizen * ptr = battalions.at(index)->getSoldier(i);
        numCitizens[1]++;
        if(typeid(*ptr) == typeid(Pezhetairos)) numCitizens[2]++;
        else if(typeid(*ptr) == typeid(Lancer)) numCitizens[3]++;
        else if(typeid(*ptr) == typeid(Knave)) numCitizens[4]++;
        else if(typeid(*ptr) == typeid(Hoplite)) numCitizens[5]++;
        else if(typeid(*ptr) == typeid(Knight)) numCitizens[6]++;
        else if(typeid(*ptr) == typeid(Archer)) numCitizens[7]++;
        else if(typeid(*ptr) == typeid(Peltast)) numCitizens[8]++;
        citizens.push_back(ptr);
    }
    battalions.erase(battalions.begin()+index);
}

void Polis::defend(){
    int arr[7];
    for(int i=0;i<7;i++) arr[i] = numCitizens[i+2];
    newBattalion(numCitizens[1],arr,3);
}

void Polis::addCitizen(Citizen *_ptr){ Citizen * ptr = _ptr; citizens.push_back(ptr); }
void Polis::addEdifice(Edifice *_ptr){ Edifice * ptr = _ptr; edifices.push_back(ptr); }
void Polis::addNumCitizen(int _i){ numCitizens[_i]++; }
void Polis::addNumEdifice(int _i){ numEdifices[_i]++; }
void Polis::subNumEdifice(int _i){ numEdifices[_i]--; }
void Polis::addNumIron(int _n){ iron += _n; }
void Polis::addNumStone(int _n){ stone += _n; }
void Polis::addNumGrain(int _n){ grain += _n; }
void Polis::subNumIron(int _n){ iron -= _n; }
void Polis::subNumStone(int _n){ stone -= _n; }
void Polis::subNumGrain(int _n){ grain -= _n; }

void Polis::viewBattalion(){
    if(battalions.size() == 0) cout << "Non esiste nessun battaglione." << endl;
    else{
        int totGrain = 0;
        for(int i=0;i<battalions.size();i++){
            if(battalions.at(i)->getNumVett() != 0){
                totGrain += (battalions.at(i)->getNumVett()*5);
                string nameEnemy = ((battalions.at(i)->getObjective()  == 3) ? "sta tornando a casa" : Library::getNamePolis("contro ",battalions.at(i)->getObjective()));
                cout << "Battaglione(" << i << ") " << battalions.at(i)->getNumVett() << " soldati " << nameEnemy << "." << endl;
                if(typePolisId == 2 && battalions.at(i)->getNumSoldiers(0) != 0) cout << "Pezeteri: " << battalions.at(i)->getNumSoldiers(0) << endl;
                if(battalions.at(i)->getNumSoldiers(1) != 0) cout << "Lancieri: " << battalions.at(i)->getNumSoldiers(1) << endl;
                if(battalions.at(i)->getNumSoldiers(2) != 0) cout << "Fanti: " << battalions.at(i)->getNumSoldiers(2) << endl;
                if(typePolisId == 1 && battalions.at(i)->getNumSoldiers(3) != 0) cout << "Opliti: " << battalions.at(i)->getNumSoldiers(3) << endl;
                if(battalions.at(i)->getNumSoldiers(4) != 0) cout << "Cavalieri: " << battalions.at(i)->getNumSoldiers(4) << endl;
                if(battalions.at(i)->getNumSoldiers(5) != 0) cout << "Arceri: " << battalions.at(i)->getNumSoldiers(5) << endl;
                if(typePolisId == 0 && battalions.at(i)->getNumSoldiers(6) != 0) cout << "Peltasti: " << battalions.at(i)->getNumSoldiers(6) << endl;
                cout << "Attacco: " << battalions.at(i)->getAttack() << " Difesa: " << battalions.at(i)->getDefense() 
                     << " Velocit" << (char)(133) << ": " << battalions.at(i)->getSpeed() << " Tempo di arrivo: " 
                     << (getDistance(Library::coordinate[battalions.at(i)->getObjective()],Library::coordinate[battalions.at(i)->getObjective()+3])/battalions.at(i)->getSpeed())+1 << endl
                     << "Ogni turno il tuo battaglione spende " << (battalions.at(i)->getNumVett()*5) << " di grano." << endl << endl << endl;
            }
        }
        cout << "Il costo totale per i battaglioni " << (char)(138) << " di " << totGrain << " di grano." << endl;
    }
}

void Polis::viewCitizens(){
    cout << "Lavoratori: " << getNumCity(0) << endl << endl
         << "Soldati: " << getNumCity(1) << endl
         << "Arceri: " << getNumCity(7) << endl
         << "Lancieri: " << getNumCity(3) << endl
         << "Fanti: " << getNumCity(4) << endl
         << "Cavalieri: " << getNumCity(6) << endl;
    if(typePolisId == 0) cout << "Peltasti: " << getNumCity(8) << endl;
    if(typePolisId == 1) cout << "Opliti: " << getNumCity(5) << endl;
    if(typePolisId == 2) cout << "Pezeteri: " << getNumCity(2) << endl;
    cout << "Ogni turno i tuoi cittadini spendono " << (getNumCitizens()*2) << " di grano." << endl;
}

void Polis::viewEdifices(){
    cout << "Risorse: " << getNumEdify(0) << endl
         << "Cava: " << getNumEdify(1) << endl
         << "Fattoria: " << getNumEdify(2) << endl
         << "Miniera: " << getNumEdify(3) << endl << endl
         << "Caserma: " << getNumEdify(4) << endl
         << "Tempio: " << getNumEdify(5) << endl
         << "Muro: " << getNumEdify(6) << endl << endl 
         << "Ogni turno le tue risorse producono: " << endl
         << "Ferro: " << (getNumCity(0)*10)*(1+(getNumEdify(3))*2) << endl
         << "Pietra: " << (getNumCity(0)*10)*(1+(getNumEdify(1))*2) << endl
         << "Grano: " << (getNumCity(0)*10)*(1+(getNumEdify(2))*2) << endl;
}
