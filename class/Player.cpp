#include <iostream>
#include <sstream>
#include <math.h>
#include "Library.h"
#include "Player.h"
#include "Citizen.h"
#include "cpuPlayer.h"
#include "Edifice.h"
#include "Worker.h"
#include "Soldier.h"
#include "Archer.h"
#include "Lancer.h"
#include "Knave.h"
#include "Knight.h"
#include "Peltast.h"
#include "Hoplite.h"
#include "Pezhetairos.h"
#include "Cave.h"
#include "Farm.h"
#include "Mine.h"
#include "Wall.h"
#include "Barrack.h"
#include "Temple.h"
using namespace std;

Player::Player(int _id,int _x,int _y) : myPolis(new Polis(_id,_x,_y)){ for(int i=0;i<3;i++) actions[i] = false; }
Player::~Player(){ delete myPolis; }
Polis * Player::getPolis(){ return myPolis; }
string Player::namePolis(){
    if(getPolis()->getId() == 0) return "Atene";
    if(getPolis()->getId() == 1) return "Sparta";
    if(getPolis()->getId() == 2) return "Tebe";
    return "Eh??? Pietro Samukabuilpoppo";
}

bool Player::getAction(int _i) const{ return actions[_i]; }
void Player::setAction(int _i,bool _v){ actions[_i] = _v; }
bool Player::getTemple(){ return ((getPolis()->getNumEdify(5) > 0) ? true : false); }

void Player::makeCitizen(){
    int typeCitizenId;
    string selectCitizen = "";
    cout << "0) Lavoratore (" << myPolis->getNumCity(0) << "/" << returConst<Worker>((int)pow((double)99,3),0) << ")" << endl
         << "1) Arceri (" << myPolis->getNumCity(7) << "/" << returConst<Archer>((int)pow((double)99,3),0) << ")" << endl;
    if(myPolis->getNumEdify(4) > 0) cout << "2) Lancieri (" << myPolis->getNumCity(3) << "/" << returConst<Lancer>((int)pow((double)99,3),0) << ")" << endl;
    cout << "3) Fanti (" << myPolis->getNumCity(4) << "/" << returConst<Knave>((int)pow((double)99,3),0)<< ")" << endl;
    if(myPolis->getNumEdify(4) > 0) cout << "4) Cavalieri (" << myPolis->getNumCity(6) << "/" << returConst<Knight>((int)pow((double)99,3),0) << ")" << endl;
    if(myPolis->getId() == 0 && myPolis->getNumEdify(4) > 1) cout << "5) Peltasti: (" << myPolis->getNumCity(8) << "/" << returConst<Peltast>((int)pow((double)99,3),0) << ")" << endl;
    if(myPolis->getId() == 1 && myPolis->getNumEdify(4) > 1) cout << "5) Opliti: (" << myPolis->getNumCity(5) << "/" << returConst<Hoplite>((int)pow((double)99,3),0) << ")" << endl;
    if(myPolis->getId() == 2 && myPolis->getNumEdify(4) > 1) cout << "5) Pezeteri: (" << myPolis->getNumCity(2) << "/" << returConst<Pezhetairos>((int)pow((double)99,3),0) << ")" << endl;
    cout << "Cosa vuoi creare: ";
    cin >> selectCitizen;
    
    if(selectCitizen == "0" || selectCitizen == "1" || selectCitizen == "3" ||
      ((selectCitizen == "2" || selectCitizen == "4") && myPolis->getNumEdify(4) > 0) || 
      (selectCitizen == "5" && myPolis->getNumEdify(4) > 1) 
    ){
    
        istringstream (selectCitizen) >> typeCitizenId;        
        bool boolCitizen = true;
        int numCitizen;
        while(cout << endl << "Quanti cittadini vuoi creare: " && !(cin >> numCitizen)){
            boolCitizen = false;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            break;
        }
        
        cout << endl;        
        if(boolCitizen && numCitizen > 0){
            
            if(typeCitizenId == 0) numCitizen = returConst<Worker>(numCitizen,1);
            if(typeCitizenId == 1) numCitizen = returConst<Archer>(numCitizen,1);
            if(typeCitizenId == 2) numCitizen = returConst<Lancer>(numCitizen,1);
            if(typeCitizenId == 3) numCitizen = returConst<Knave>(numCitizen,1);
            if(typeCitizenId == 4) numCitizen = returConst<Knight>(numCitizen,1);
            if(typeCitizenId == 5 && myPolis->getId() == 0) numCitizen = returConst<Peltast>(numCitizen,1);
            if(typeCitizenId == 5 && myPolis->getId() == 1) numCitizen = returConst<Hoplite>(numCitizen,1);
            if(typeCitizenId == 5 && myPolis->getId() == 2) numCitizen = returConst<Pezhetairos>(numCitizen,1);
                      
            if(numCitizen > 0){
            
                string convalid = "";
                cout << "Sei sicuro di volerli creare [s/n]? ";
                cin >> convalid;
                if(convalid == "s"){
                
                    bool val = false;
                    for(int i=0;i<numCitizen;i++){
                        
                        if(typeCitizenId == 0) val = exectCitizen<Worker>(0);
                        if(typeCitizenId == 1) val = exectCitizen<Archer>(7);
                        if(typeCitizenId == 2) val = exectCitizen<Lancer>(3);
                        if(typeCitizenId == 3) val = exectCitizen<Knave>(4);
                        if(typeCitizenId == 4) val = exectCitizen<Knight>(6);
                        if(typeCitizenId == 5 && myPolis->getId() == 0) val = exectCitizen<Peltast>(8);
                        if(typeCitizenId == 5 && myPolis->getId() == 1) val = exectCitizen<Hoplite>(5);
                        if(typeCitizenId == 5 && myPolis->getId() == 2) val = exectCitizen<Pezhetairos>(2);
                        if(val){
                                
                            actions[1] = true;
                            cout << i << ") Cittadino creato." << endl;
                            
                        }else cout << i << ") Non puoi pi" << char(163) << " creare cittadini." << endl;
                        
                    }
                    
                }else if(convalid != "n") cout << endl << "Errore nella creazione." << endl;
                
            }else cout << "Non disponi delle risorse sufficenti per poter creare." << endl;
        
        }else cout << endl << "Errore nella creazione." << endl;
    
    }else{
        if(selectCitizen == "2" || selectCitizen == "4") cout << "\nPer creare questa unit" << (char)(133) << " devi avere una caserma." << endl;
        else if(selectCitizen == "5") cout << "\nPer creare questa unit" << (char)(133) << " devi avere due caserme." << endl;
        else cout << endl << "Carattere non riconosciuto." << endl;
    }
}

void Player::makeEdifice(){
     if(myPolis->getNumEdifices() < Library::constEdifices){
        int typeEdificeId;
        string selectEdifice = "";
        cout << "0) Cava (" << myPolis->getNumEdify(1) << ") " << ((returConst<Cave>((int)pow((double)99,3),0) > 0) ? "V" : "X") << endl;
        cout << "1) Fattoria (" << myPolis->getNumEdify(2) << ") " << ((returConst<Farm>((int)pow((double)99,3),0) > 0) ? "V": "X") << endl;
        cout << "2) Miniera (" << myPolis->getNumEdify(3) << ") " << ((returConst<Mine>((int)pow((double)99,3),0) > 0) ? "V" : "X") << endl;
        cout << "3) Caserma (" << myPolis->getNumEdify(4) << ") " << ((returConst<Barrack>((int)pow((double)99,3),0) > 0) ? "V": "X") << endl;
        cout << "4) Tempio (" << myPolis->getNumEdify(5) << ") " << ((returConst<Temple>((int)pow((double)99,3),0) > 0) ? "V" : "X") << endl;
        cout << "5) Muro (" << myPolis->getNumEdify(6) << ") " << ((returConst<Wall>((int)pow((double)99,3),0) > 0) ? "V" : "X") << endl;
        cout << "Cosa vuoi costruire: ";
        cin >> selectEdifice;
        
        if(selectEdifice == "0" || selectEdifice == "1" || 
            selectEdifice == "2" || selectEdifice == "3" || 
            selectEdifice == "4" || selectEdifice == "5"
        ){
    
            istringstream (selectEdifice) >> typeEdificeId;
            cout << endl;
            
            int numEdifice = 1;
            if(typeEdificeId == 0) numEdifice = returConst<Cave>(1,0);
            else if(typeEdificeId == 1) numEdifice = returConst<Farm>(1,0);
            else if(typeEdificeId == 2) numEdifice = returConst<Mine>(1,0);
            else if(typeEdificeId == 3) numEdifice = returConst<Barrack>(1,0);
            else if(typeEdificeId == 4) numEdifice = returConst<Temple>(1,0);
            else if(typeEdificeId == 5) numEdifice = returConst<Wall>(1,0);
            
            if(numEdifice > 0){
            
                string convalid = "";
                cout << endl << "Sei sicuro di volerlo costruire [s/n]? ";
                cin >> convalid;
                if(convalid == "s"){
                
                    bool val = false;
                    if(typeEdificeId == 0) val = exectEdifice<Cave>(1);
                    else if(typeEdificeId == 1) val = exectEdifice<Farm>(2);
                    else if(typeEdificeId == 2) val = exectEdifice<Mine>(3);
                    else if(typeEdificeId == 3) val = exectEdifice<Barrack>(4);
                    else if(typeEdificeId == 4) val = exectEdifice<Temple>(5);
                    else if(typeEdificeId == 5) val = exectEdifice<Wall>(6);
                    
                    if(val){
                        
                        if(typeEdificeId == 0 || typeEdificeId == 1 || typeEdificeId == 2) myPolis->addNumEdifice(0);
                        actions[0] = true;
                        cout << endl << "Edificio creato." << endl;
                        
                    }else cout << endl << "Edificio non creato." << endl;
                
                }else if(convalid != "n") cout << endl << "Errore nella costruzione." << endl;
            
            }else cout << endl << "Non disponi delle risorse sufficenti per poter costruire." << endl;
    
        }else cout << endl << "Errore nella costruzione." << endl;
    }else cout << "Non puoi costruire pi" << (char)(163) << " di 6 edifici. Demoliscine qualcuno." << endl;
}

void Player::retire(){
    myPolis->viewBattalion();
    int numberBattaglion;
    while(cout << endl << "Inserisci il numero del battaglione da ritirare: " && !(cin >> numberBattaglion)){
        cout << endl << "Errore." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return;
    }
    retire(numberBattaglion);
}

void Player::retire(int numberBattalion){
    if(numberBattalion < myPolis->getNumBattalions()){    
        if(myPolis->getBattalion(numberBattalion)->getObjective() != 3 && myPolis->getBattalion(numberBattalion)->getObjective() != myPolis->getId())
            myPolis->getBattalion(numberBattalion)->comeBack();
        else cout << "Questo battaglione non pu" << (char)(162) << " essere ritirato!" << endl;        
    }else cout << "Errore." << endl;
}

void Player::actionTurn(){
    for(int i=0;i<3;i++) actions[i] = false;
    for(int i=0; i<1+(myPolis->getNumEdify(1)); i++)
        if(myPolis->getNumStone() < 9999) myPolis->addNumStone(myPolis->getNumCity(0)*6);
    for(int i=0; i<1+(myPolis->getNumEdify(3)); i++)
        if(myPolis->getNumIron() < 9999) myPolis->addNumIron(myPolis->getNumCity(0)*6);
        
    myPolis->subNumGrain(myPolis->getNumCitizens()*2);    
    for(int i=0;i<myPolis->getNumBattalions();i++){
        Battalion * p = myPolis->getBattalion(i);
        myPolis->subNumGrain(p->getNumVett()*5);
        if(p->getMotion() && !(p->getFight())) p->move();
    } 
    for(int i=0; i<1+(myPolis->getNumEdify(2)); i++)
        if(myPolis->getNumGrain() < 9999) myPolis->addNumGrain(myPolis->getNumCity(0)*6);
}

void Player::statisticsTurn(){
    int _iron = myPolis->getNumIron();
    int _stone = myPolis->getNumStone();
    int _grain = myPolis->getNumGrain();
    
    for(int i=0; i<1+(myPolis->getNumEdify(1)); i++)
        if(myPolis->getNumStone() < 9999) _stone += myPolis->getNumCity(0)*6;
    for(int i=0; i<1+(myPolis->getNumEdify(3)); i++)
        if(myPolis->getNumIron() < 9999) _iron += myPolis->getNumCity(0)*6;
    for(int i=0;i<myPolis->getNumBattalions();i++)
        _grain -= myPolis->getBattalion(i)->getNumVett()*5;
    _grain -= myPolis->getNumCitizens()*2;
    for(int i=0; i<1+(myPolis->getNumEdify(2)); i++)
        if(myPolis->getNumIron() < 9999) _grain += myPolis->getNumCity(0)*6;
    
    cout << "Le mie statistiche al prossimo turno: " << endl
         << "Ferro: " << _iron << endl
         << "Pietra: " << _stone << endl
         << "Grano: " << _grain << endl;
}

void Player::attack(Player * _g1,Player * _g2,vector <int> _v){
   if(myPolis->getNumCity(1) > 0 && myPolis->getNumBattalions() < Library::constBattalions){        
        string typeEnemy;
        int typeEnemyId;
        if(_g1 != NULL) cout << "0) Giocatore2: " << Library::getNamePolis("",_v.at(0)) << endl;
        if(_g2 != NULL) cout << "1) Giocatore3: " << Library::getNamePolis("",_v.at(1)) << endl;
        cout << "Chi vuoi attaccare? ";
        cin >> typeEnemy;
        cout << endl;
        
        if((typeEnemy == "0") && (_g1 != NULL)){
            typeEnemyId = _v.at(0);
            if(myPolis->makeBattalion(typeEnemyId)) 
                myPolis->getBattalion(myPolis->getNumBattalions()-1)->setDistance(myPolis->getDistance(_g1->getPolis()));
            else return;
        }else if((typeEnemy == "1") && (_g2 != NULL)){
            typeEnemyId = _v.at(1);
            if(myPolis->makeBattalion(typeEnemyId)) 
                myPolis->getBattalion(myPolis->getNumBattalions()-1)->setDistance(myPolis->getDistance(_g2->getPolis()));
            else return;
        }else{
            cout << "Nessun comando " << (char)(138) << " stato trovato." << endl;
            return;
        }   
        cout << endl << "Il tuo Battaglione " << (char)(138) << " in viaggio." << endl;
        actions[2] = true;
    }else if(!(myPolis->getNumCity(1) > 0))cout << "Non esistono soldati in citt" << (char)(133) << "." << endl;
    else cout << "Possiedi Troppi Battaglioni." << endl;
}

void Player::showBattalions(Player *& defender,Player *& defender2, bool _exe){
    for(int i=0; i<myPolis->getNumBattalions(); i++){
        Battalion * p = myPolis->getBattalion(i);
        Player * enemyPlayer = NULL;
        Battalion * enemyBattalion = NULL;
        if(p->getMotion() && p->getObjective() != p->getPolisId()){
            if(p->getFight()){
                cout << "Attacco a";
                switch(p->getObjective()){
                    case 0 : cout << "d Atene"; break;
                    case 1 : cout << " Sparta"; break;
                    case 2 : cout << " Tebe"; break;
                }
                cout << " portato da";
                switch(p->getPolisId()){
                    case 0 : cout << " Atene."; break;
                    case 1 : cout << " Sparta."; break;
                    case 2 : cout << " Tebe."; break;
                }
                enemyBattalion = selectEnemy(defender,defender2,p,enemyPlayer);
                if(enemyPlayer != NULL && typeid(*enemyPlayer)==typeid(Player))
                      if(enemyPlayer->getTemple())  cout << " Soldati: " << p->getTotSoldiers();
                cout << endl;
                cout << "Armata Attaccante: \n";
                p->showAttack();
             //  ---------------------- ATTACCO IN CORSO ----------------------   //
                
                if(enemyBattalion != NULL)
                {
                    if((p->getNumVett() > 0) && (enemyBattalion->getNumVett() > 0)){
                            if(_exe){   
                                   Edifice * wall1 = NULL;
                                   Edifice * wall2 = NULL;
                                   Edifice ** wall = &wall1;
                                   for(int i=0; i<enemyPlayer->getPolis()->getNumEdifices() && enemyPlayer->getPolis()->getNumEdify(6)>0; i++)
                                   {
                                           if(typeid(*(enemyPlayer->getPolis()->getEdifice(i)))==typeid(Wall)){
                                                  *wall = enemyPlayer->getPolis()->getEdifice(i);
                                                  wall = &wall2;
                                           }
                                   }
                                   p->startFight(enemyBattalion, wall1, wall2);
                                   for(int i=0; i<enemyPlayer->getPolis()->getNumEdifices() && enemyPlayer->getPolis()->getNumEdify(6)>0; i++)
                                   {
                                           if(typeid(*(enemyPlayer->getPolis()->getEdifice(i)))==typeid(Wall)){
                                                  if(((Wall*)enemyPlayer->getPolis()->getEdifice(i))->getDefense() <= 0){
                                                        delete enemyPlayer->getPolis()->getEdifice(i);
                                                        enemyPlayer->getPolis()->subNumEdifice(6);
                                                        enemyPlayer->getPolis()->destroyEdifice(i);
                                                  }
                                           }
                                   }
                            }
                            cout << endl << "Battaglioni dopo l'attacco." << endl;
                            p->showAttack();
                            enemyBattalion->showAttack();
                    }
                    if((p->getNumVett() > 0) && (enemyBattalion->getNumVett() <= 0)){
                            /*if(typeid(*this) == typeid(cpuPlayer)){
                                      for(int i=0; i < getPolis()->getNumBattalions()-1;i++)
                                          if(getPolis()->getBattalion(i)->getObjective() == p->getObjective())
                                               getPolis()->getBattalion(i)->comeBack();
                            }
                            else      */p->comeBack();
                            destroy(enemyPlayer);
                            cout << endl << "Gli attaccanti hanno conquistato la Polis!" << endl;
                            if(defender != NULL && defender->getPolis() == NULL) Player::deletePlayer(defender);
                            if(defender2 != NULL && defender2->getPolis() == NULL) Player::deletePlayer(defender2);
                    }
                    else if (p->getNumVett() <= 0)
                    {
                            myPolis->eraseBattalion(i);
                            cout << endl << "Il battaglione attaccante " << (char)(138) << " stato sopraffatto." << endl;
                    }
                }
                else
                {
                    /*if(typeid(*this) == typeid(cpuPlayer)){
                            for(int i=0; i < getPolis()->getNumBattalions()-1;i++)
                                 if(getPolis()->getBattalion(i)->getObjective() == p->getObjective())
                                       getPolis()->getBattalion(i)->comeBack();
                    }
                    else      */p->comeBack();
                    if(enemyPlayer != NULL && enemyPlayer->getPolis() != NULL){
                            destroy(enemyPlayer);
                            cout << endl << "Gli attaccanti hanno conquistato la Polis!" << endl;
                            if(defender != NULL && defender->getPolis() == NULL) Player::deletePlayer(defender);
                            if(defender2 != NULL && defender2->getPolis() == NULL) Player::deletePlayer(defender2);
                    }
                    else    cout << "La polis dev'essere stata distrutta..." << endl;
                }
            // ----------------------- FINE ATTACCO ----------------------   //
            }
            else 
            {
                p->showBattalion();
            }
            cout << endl;
        }
        else
        {
            myPolis->eraseBattalion(i);
        }
    }//end for
}

void Player::destroyEdify(){
     if(!actions[0] && myPolis->getNumEdifices() > 0){
        int typeEdifice;
        string selectEdifice = "";
        if(myPolis->getNumEdify(1) > 0) cout << "0) Cava (" << myPolis->getNumEdify(1) << ")" << endl;
        if(myPolis->getNumEdify(2) > 0) cout << "1) Fattoria (" << myPolis->getNumEdify(2) << ")" << endl;
        if(myPolis->getNumEdify(3) > 0) cout << "2) Miniera (" << myPolis->getNumEdify(3) << ")" << endl;
        if(myPolis->getNumEdify(4) > 0) cout << "3) Caserma (" << myPolis->getNumEdify(4) << ")" << endl;
        if(myPolis->getNumEdify(5) > 0) cout << "4) Tempio (" << myPolis->getNumEdify(5) << ")" << endl;
        if(myPolis->getNumEdify(6) > 0) cout << "5) Muro (" << myPolis->getNumEdify(6) << ")" << endl;
        cout << "Cosa vuoi distruggere: ";
        cin >> selectEdifice;
            
        istringstream (selectEdifice) >> typeEdifice;
        if((selectEdifice == "0" || selectEdifice == "1" || selectEdifice == "2" || 
             selectEdifice == "3" || selectEdifice == "4" || selectEdifice == "5")
             && (myPolis->getNumEdify(typeEdifice+1) > 0)
             ){
            string convalid = "";
            cout << endl << "Sei sicuro di volerlo distruggere [s/n]? ";
            cin >> convalid;
            if(convalid == "s"){
                
                bool val = false;
                if(typeEdifice == 0) val = myPolis->deleteEdifice<Cave>(1);
                if(typeEdifice == 1) val = myPolis->deleteEdifice<Farm>(2);
                if(typeEdifice == 2) val = myPolis->deleteEdifice<Mine>(3);
                if(typeEdifice == 3) val = myPolis->deleteEdifice<Barrack>(4);
                if(typeEdifice == 4) val = myPolis->deleteEdifice<Temple>(5);
                if(typeEdifice == 5) val = myPolis->deleteEdifice<Wall>(6);
                if(val){
                    
                    if(typeEdifice == 0 || typeEdifice == 1 || typeEdifice == 2) myPolis->subNumEdifice(0);              
                    cout << endl << "Edificio distrutto." << endl;
                    actions[0] = true;
                    
                }else cout << endl << "Edificio non distrutto." << endl;
                
            }else if(convalid != "n") cout << endl << "Errore nella distruzione." << endl;
            
        }else cout << endl << "Errore nella distruzione." << endl;
        
    } else cout << endl << "Hai gi" << (char)(133) << " costruito in questo turno." << endl;
}

void Player::destroy(Player *& _loser){
    getPolis()->addNumIron(_loser->getPolis()->getNumIron()/2);
    getPolis()->addNumStone(_loser->getPolis()->getNumStone()/2);
    getPolis()->addNumGrain(_loser->getPolis()->getNumGrain()/2);
    for(int i=0; i<_loser->getPolis()->getNumCitizens(); i++){
        Citizen * ptr = _loser->getPolis()->getCitizen(i);
        if(typeid(*ptr) == typeid(Worker)){
            getPolis()->addCitizen(ptr);
            getPolis()->addNumCitizen(0);
        }
    }
    _loser->deletePolis();
}

void Player::deletePolis(){   // Questo serve veramente a qualcosa?
     delete myPolis;
     myPolis = NULL;
}

void Player::deletePlayer(Player *& _g){ delete _g; _g = NULL; }

Battalion * Player::selectEnemy(Player * defender, Player * defender2, Battalion * p, Player *& enemyPlayer){
    if(defender != NULL && p->getObjective() == defender->getPolis()->getId()){
        enemyPlayer = defender;
        for(int j=0;j<defender->getPolis()->getNumBattalions();j++){
            if(p->getObjective()==defender->getPolis()->getBattalion(j)->getObjective())
                return enemyPlayer->getPolis()->getBattalion(j);
        }
    
        if(defender->getPolis()->getNumCity(1) > 0){
            enemyPlayer->getPolis()->defend();
            return enemyPlayer->getPolis()->getBattalion((enemyPlayer->getPolis()->getNumBattalions())-1);
        }
    }
    
    if(defender2 != NULL && p->getObjective() == defender2->getPolis()->getId()){
        enemyPlayer = defender2;
        for(int j=0;j<defender2->getPolis()->getNumBattalions();j++){
            if(p->getObjective()==defender2->getPolis()->getBattalion(j)->getObjective())
                return enemyPlayer->getPolis()->getBattalion(j);
        }
    
        if(defender2->getPolis()->getNumCity(1) > 0){
            enemyPlayer->getPolis()->defend();
            return enemyPlayer->getPolis()->getBattalion((enemyPlayer->getPolis()->getNumBattalions())-1);
        }
    }
    return NULL;
}

template <typename T> bool Player::exectCitizen(int typeCitizenId){
    T * a = new T;
    bool val = false;
    if(
        a->getIron() <= myPolis->getNumIron() &&
        a->getStone() <= myPolis->getNumStone() &&
        a->getGrain() <= myPolis->getNumGrain()
    ){
        myPolis->addNumCitizen(typeCitizenId);
        if(typeCitizenId != 0) myPolis->addNumCitizen(1);
        myPolis->subNumIron(a->getIron());
        myPolis->subNumStone(a->getStone());
        myPolis->subNumGrain(a->getGrain());
        myPolis->template newCitizen<T>();
        val = true;
    }
    delete a;
    return val;
}

template <typename T> bool Player::exectEdifice(int typeEdificeId){
    T * a = new T;
    bool val = false;
    if(
        a->getIron() <= myPolis->getNumIron() &&
        a->getStone() <= myPolis->getNumStone() &&
        a->getGrain() <= myPolis->getNumGrain()
    ){
        myPolis->addNumEdifice(typeEdificeId);
        myPolis->subNumIron(a->getIron());
        myPolis->subNumStone(a->getStone());
        myPolis->subNumGrain(a->getGrain());
        myPolis->template newEdifice<T>();
        val = true;
    }
    delete a;
    return val;
}

template <typename T> int Player::returConst(int _num = 1,int _type = 0){
    T * a = new T;
    int numObj = 0,_iron = myPolis->getNumIron(),_stone = myPolis->getNumStone(),_grain = myPolis->getNumGrain(); 
    for(;numObj<_num;numObj++){        
        if(_iron - a->getIron() < 0 || _stone - a->getStone() < 0 || _grain - a->getGrain() < 0) break;
        _iron -= a->getIron();
        _stone -= a->getStone();
        _grain -= a->getGrain();
    }
    if(_type && numObj > 0) cout << ((numObj < _num) ? "Puoi creare al massimo " : "Vuoi creare ") << numObj << " cittadin" << ((numObj > 1) ? "i" : "o") << "." << endl << endl;
    if(numObj > 0 && _num != pow(99,3)){
        cout << "Il costo in risorse " << (char)(138) << " di:" << endl
             << "Ferro: " << a->getIron()*numObj << endl
             << "Pietra: " << a->getStone()*numObj << endl
             << "Grano: " << a->getGrain()*numObj << endl;
    }
    delete a;
    return numObj;
}

void Player::offer(){
     cout << "Offri le tue risorse agli dei per ottenere più informazioni dall'oracolo.\nCosa vuoi offrire?\n";
     cout << "0) Ferro\n1) Pietra\n2) Grano\n";
     string selectResource;
     cin >> selectResource;     
     if(selectResource == "0" || selectResource == "1" || selectResource == "2"){
            int numRes;
            while(cout << endl << "Quante risorse offri? " && !(cin >> numRes)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                break;
            }
            cout << endl;
            getPolis()->addTemple(numRes);
            if(selectResource == "0" && getPolis()->getNumIron() >= numRes) getPolis()->subNumIron(numRes);
            else if(selectResource == "1" && getPolis()->getNumStone() >= numRes) getPolis()->subNumStone(numRes);
            else if(selectResource == "2" && getPolis()->getNumGrain() >= numRes) getPolis()->subNumGrain(numRes);
            else cout << "Risorse Insufficienti" << endl;
     }else cout << "Comando non Riconosciuto" << endl;
}

ostream & Player::put(ostream & os){
        return  os
            << "Le mie statistiche: " << endl
            << "Turno numero: " << Library::numTurn << endl
            << "Ferro: " << myPolis->getNumIron() << endl
            << "Pietra: " << myPolis->getNumStone() << endl
            << "Grano: " << myPolis->getNumGrain() << endl
            << "Battaglioni: " << myPolis->getNumBattalions() << endl
            << "Cittadini: " << myPolis->getNumCitizens() << endl
            << "Edifici: " << myPolis->getNumEdifices() << endl;
}

ostream &operator<<(ostream &os,Player &obj){
        return obj.put(os);
}
