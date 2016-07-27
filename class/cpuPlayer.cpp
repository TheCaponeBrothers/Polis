#include <iostream>
#include "cpuPlayer.h"
#include "Library.h"
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
#include "Cave.h"
#include "Farm.h"
#include "Mine.h"
#include "Wall.h"
#include "Barrack.h"
#include "Temple.h"
using namespace std;

cpuPlayer::cpuPlayer(int _id,int _x,int _y) : Player(_id,_x,_y){}

void cpuPlayer::evolvePolis(Player * _g1,Player * _g2){    
    int nextIron = myPolis->getNumIron(), nextStone = myPolis->getNumStone(), nextGrain = myPolis->getNumGrain();
    nextResources(nextIron,nextStone,nextGrain);
    
    if(getTemple()){
        int choice = rand()%20;
        if(choice < 4 && nextIron > 100){
            choice = rand()%26+25;
            getPolis()->subNumIron(choice);
            nextIron -= choice;
        }else if(choice < 8 && nextStone > 90){
            choice = rand()%26+25;
            getPolis()->subNumStone(choice);
            nextStone -= choice;
        }else if(choice < 10 && nextGrain > 120){
            choice = rand()%26+25;
            getPolis()->subNumGrain(choice);
            nextGrain -= choice;
        }
    }    
    Battalion * ptr = checkAttack(_g1,_g2);    
    generateEdifice(ptr,nextGrain);
    generateCitizen(ptr,nextIron,nextGrain,nextStone,_g1,_g2);
    bool v = false;
    if(rand()%2 == 0){
        if(_g1 != NULL) cpuAttack(_g1,ptr,nextGrain,v);
        if(_g2 != NULL) cpuAttack(_g2,ptr,nextGrain,v);
    }else{
        if(_g2 != NULL) cpuAttack(_g2,ptr,nextGrain,v);
        if(_g1 != NULL) cpuAttack(_g1,ptr,nextGrain,v);
    }    
    
}

void cpuPlayer::nextResources(int & _iron, int & _stone, int & _grain){
     for(int i=0; i<1+(myPolis->getNumEdify(1)); i++) _stone += myPolis->getNumCity(0)*6;
     for(int i=0; i<1+(myPolis->getNumEdify(2)); i++) _grain += myPolis->getNumCity(0)*6;
     for(int i=0; i<1+(myPolis->getNumEdify(3)); i++) _iron += myPolis->getNumCity(0)*6;
     _grain -= myPolis->getNumCitizens()*2;
     for(int i=0;i<myPolis->getNumBattalions();i++) _grain -= myPolis->getBattalion(i)->getNumVett()*5;
}

Battalion * cpuPlayer::checkAttack(Player * _g1, Player * _g2){
    Battalion * empty = NULL;
    if(_g1 != NULL){
        for(int i=0;i<_g1->getPolis()->getNumBattalions();i++){
            if(_g1->getPolis()->getBattalion(i)->getObjective() == getPolis()->getId())
            if(empty == NULL) empty = _g1->getPolis()->getBattalion(i);
            else if(empty->getDistance() < _g1->getPolis()->getBattalion(i)->getDistance()) empty = _g1->getPolis()->getBattalion(i);
        }
    }
    if(_g2 != NULL){
        for(int i=0;i<_g2->getPolis()->getNumBattalions();i++){
            if(_g2->getPolis()->getBattalion(i)->getObjective() == getPolis()->getId())
            if(empty == NULL) empty = _g2->getPolis()->getBattalion(i);
            else if(empty->getDistance() < _g2->getPolis()->getBattalion(i)->getDistance()) empty = _g2->getPolis()->getBattalion(i);
        }
    }
    return empty;
}
//------------------------------------------------------------------------------

void cpuPlayer::cpuAttack(Player *_g, Battalion * ptr, int nextGrain, bool & _v){
     if(getPolis()->getNumCity(1) > 0 && getPolis()->getNumGrain() > 0 && !_v && getPolis()->getNumBattalions() < 6){
         int decision = rand()%100;
         int index = 0;
    
         for(int i=0; i<getPolis()->getNumCity(1); i++) if(index < 20 || (index >= 20 && i%2 == 0)) index++;
         if(getPolis()->getNumCity(1) > 1500) index = 100;
         
         int arr[7];
         int num = 0;
         choiceTroops(arr,num);
         
         if(num == 0) return;
         if(getPolis()->getCalculate(arr,0) < 800) index -= 20;         
         int numturn = (getPolis()->getDistance(_g->getPolis()) / getPolis()->getCalculate(arr,2) )*2;
         
         while(nextGrain >= numturn*num*5 && Library::numTurn < 750){
            reduceTroops(arr,num,numturn,_g);
            if(num == 0) return;
            if(getPolis()->getCalculate(arr, 0) < 2000 && Library::numTurn > 40) return;
            if(ptr != NULL && getPolis()->getCalculate(arr, 0) < 4500 && Library::numTurn > 40) return;
         }

        if(ptr != NULL && getTemple() && _g->getPolis()->getNumCity(1) < getPolis()->getNumCity(1))
            for(int i=0;i<getPolis()->getNumCity(1)-_g->getPolis()->getNumCity(1);i++) index++;
            
        if(Library::numTurn > 50) index += 20;
        
        int numSoldiers = 0;
        for(int i=0; i<getPolis()->getNumBattalions(); i++)
             numSoldiers += getPolis()->getBattalion(i)->getTotSoldiers();
        
        if(ptr != NULL && numSoldiers > getPolis()->getNumCity(1)){
            if(getTemple() && ptr->getTotSoldiers()*2 < getPolis()->getNumCity(1) || !(getTemple()))
            {
                      int arr[7];
                      for(int i=0;i<7;i++) arr[i] = getPolis()->getNumCity(i+2);
                      bool control = false;
                      for(int i=0;(i<getPolis()->getNumBattalions() && !control);i++)
                           if(getPolis()->getBattalion(i)->getObjective() == 3) control = true;
            
                      Battalion * p = NULL;
                      if(getPolis()->getNumBattalions() > 0) p = getPolis()->getBattalion(0);
                      if(getPolis()->getNumBattalions() > 0 && getPolis()->getCalculate(arr, 0) < 2000 && !control){
                          for(int i=1; i<getPolis()->getNumBattalions()-1;i++ )
                               for(int j=i+1; j<getPolis()->getNumBattalions();j++)
                                    if(getPolis()->getBattalion(i)->getDistance() > p->getDistance()) p = getPolis()->getBattalion(i);
                      }
                      if(p != NULL && p->getDistance() > p->getHome()) p->comeBack();
            }
        }
        
        if(decision < index){
             getPolis()->newBattalion(num,arr,_g->getPolis()->getId());
             getPolis()->getBattalion(getPolis()->getNumBattalions()-1)->setDistance(getPolis()->getDistance(_g->getPolis()));
             _v = true;
        }
     }
}

void cpuPlayer::reduceTroops(int * arr, int & num, int & numturn, Player * _g){
    num = 0;
    for(int i=0;i<7;i++){
        *(arr+i) /= 2;
        num += *(arr+i);
    }
    if(num == 0) return;
    numturn = (getPolis()->getDistance(_g->getPolis()) / getPolis()->getCalculate(arr, 2) )*2;
}

void cpuPlayer::choiceTroops(int * arr,int & sum){
    for(int i=0; i<7; i++){
        *(arr+i) = getPolis()->getNumCity(i+2)/2;
        if(*(arr+i) > 0) *(arr+i) += rand()%(getPolis()->getNumCity(i+2)/2);
        sum += *(arr+i);
    }
}

//----------------------------------------------------------------------------

void cpuPlayer::generateEdifice(Battalion * ptr, int nextGrain){
     int decision = rand()%100;
     if(ptr != NULL && getPolis()->getNumEdifices() < 6){
          int index = 50;
          if(((getPolis()->getNumEdify(4) < 2) && (getPolis()->getNumEdifices() < 4) || getPolis()->getNumEdify(4) < 1) && decision < index) createEdifice<Wall>(6);
     }else if(getPolis()->getNumEdifices() < 6){
          int resIndex=40, barIndex=20, walIndex=15, temIndex=15;
          
          if(getPolis()->getNumGrain() < 1000){
              resIndex += 9;
              barIndex -= 3;
              walIndex -= 3;
              temIndex -= 3;
          }
          if(getPolis()->getNumStone() < 1000){
              resIndex += 9;
              barIndex -= 3;
              walIndex -= 3;
              temIndex -= 3;
          }
          if(getPolis()->getNumStone() < 1000){
              resIndex += 9;
              barIndex -= 3;
              walIndex -= 3;
              temIndex -= 3;
          }
          if(getPolis()->getNumEdify(0) < 3){
              resIndex += 6*(3-getPolis()->getNumEdify(0));
              barIndex -= 2*(3-getPolis()->getNumEdify(0));
              walIndex -= 2*(3-getPolis()->getNumEdify(0));
              temIndex -= 2*(3-getPolis()->getNumEdify(0));
          }
          else{
              resIndex -= 6*(getPolis()->getNumEdify(0)-2);
              barIndex += 2*(getPolis()->getNumEdify(0)-2);
              walIndex += 2*(getPolis()->getNumEdify(0)-2);
              temIndex += 2*(getPolis()->getNumEdify(0)-2);
          }
          if(getPolis()->getNumEdifices() > 4){
              resIndex -= 10;
              barIndex -= 10;
              walIndex -= 10;
              temIndex -= 10;
          }
          if(getPolis()->getNumEdify(5) == 0){
              walIndex += 6;
              resIndex -= 2;
              barIndex -= 2;
              temIndex -= 2;
          }
          else{
              walIndex -= 12;
              resIndex += 4;
              barIndex += 4;
              temIndex += 4;
          }
          if(getPolis()->getNumEdify(4) < 1){
              barIndex += 12;
              resIndex -= 2;
              walIndex -= 2;
              temIndex -= 2;
          }
          else if(getPolis()->getNumEdify(4) < 2){
              barIndex += 6;
              resIndex += 4;
              walIndex += 4;
              temIndex += 4;
          }
          else{
              barIndex -= 12;
              resIndex += 4;
              walIndex += 4;
              temIndex += 4;
          }
          if(getPolis()->getNumEdify(6) == 0){
              temIndex += 6;
              resIndex -= 2;
              barIndex -= 2;
              walIndex -= 2;
          }
          else{
              temIndex -= 15;
              resIndex += 4;
              barIndex += 4;
              walIndex += 4;
          }
          if(decision < resIndex-1){
                decision = rand()%100;
                int grIndex=40, stIndex=25, irIndex=25;
                
                if(getPolis()->getNumGrain() < 1000){
                      grIndex += 10;
                      stIndex -= 3;
                      irIndex -= 3;
                }
                if(getPolis()->getNumStone() < 1000){
                      grIndex -= 3;
                      stIndex += 10;
                      irIndex -= 3;
                }
                if(getPolis()->getNumGrain() < 1000){
                      grIndex -= 3;
                      stIndex -= 3;
                      irIndex += 10;
                }
                if(decision < grIndex-1) createEdifice<Farm>(2);
                else if(decision < grIndex+stIndex-1) createEdifice<Cave>(1);
                else if(decision < grIndex+stIndex+irIndex-1) createEdifice<Mine>(3);
          }
          else if(decision < resIndex+barIndex-1) createEdifice<Barrack>(4);
          else if(decision < resIndex+barIndex+walIndex-1 && getPolis()->getNumEdify(6) == 0) createEdifice<Wall>(5);
          else if(decision < resIndex+barIndex+walIndex+temIndex-1 && getPolis()->getNumEdify(5) == 0) createEdifice<Temple>(6);
     
     }else{
        int resIndex = 50;
        bool too_barrack=false;
         
        if(getPolis()->getNumEdify(4) > 2) too_barrack=true;
        if(getPolis()->getNumEdify(0) > 3) resIndex += 25;
        if(getPolis()->getNumGrain() < 5000||getPolis()->getNumStone() < 5000||getPolis()->getNumIron() < 5000) resIndex -= 40;
        if(getPolis()->getNumEdify(5) == 0) resIndex -= 10;
               
        bool aux = false;
        if(decision < resIndex){
            int grIndex=2, stIndex=10, irIndex=2;                     
            if(getPolis()->getNumGrain() > 8000) grIndex += 8;                         
            if(getPolis()->getNumIron() > 8000) irIndex += 8;                         
            if(getPolis()->getNumStone() > 6000) stIndex += 10;                     
            if(decision < grIndex) aux = myPolis->deleteEdifice<Farm>(2);
            else if(decision < grIndex+irIndex) aux = myPolis->deleteEdifice<Mine>(3);
            else if(decision < grIndex+irIndex+stIndex) aux = myPolis->deleteEdifice<Cave>(1);
            if(aux) myPolis->subNumEdifice(0);
        }else if(too_barrack) aux = myPolis->deleteEdifice<Barrack>(4);
     }
}

void cpuPlayer::generateCitizen(Battalion * ptr, int nextIron, int nextGrain, int nextStone, Player * _g1, Player * _g2){
     int decision = rand()%101;
     int index = 80;
     int index1 = index/4;
     int num = 1;
     
     if(getPolis()->getNumGrain() >= 5000 && getPolis()->getNumIron() >= 5000 && getPolis()->getNumStone() >= 5000) index = 100;
     
     if(getPolis()->getNumCity(0) > 50) index1 = 0;     
     if(nextGrain > getPolis()->getNumGrain()&&
        nextIron > getPolis()->getNumStone()&& 
        nextStone > getPolis()->getNumIron()) index1 = 0;
        
     if(ptr != NULL) index1 = ((ptr->getDistance() < ptr->getHome()) ? 0 : index/2+index/4);   
     
     if(getPolis()->getNumCity(1) > 3000) index = 0;
     if(getTemple() && _g1 != NULL && _g2 != NULL)
          if(_g1->getPolis()->getNumCity(1)*3 < getPolis()->getNumCity(1) &&
              _g2->getPolis()->getNumCity(1)*3 < getPolis()->getNumCity(1))  index = 0;
     else if(getTemple() && _g1 != NULL)
          if(_g1->getPolis()->getNumCity(1)*3 < getPolis()->getNumCity(1))   index = 0;
     else if(getTemple() && _g2 != NULL)
          if(_g2->getPolis()->getNumCity(1)*3 < getPolis()->getNumCity(1))   index = 0;
     
     if(decision < index){
           if(decision < index1) createCitizen<Worker>(num, 0, nextGrain);
           else{
                  int index2, index3, index4, index5, index6;
                  if(getPolis()->getNumEdify(4) > 1 ){
                         index2 = (index-index1)/10;
                         index3 = (index-index1)/5;
                         index4 = (index-index1)/5;
                         index5 = (index-index1)/4;
                         index6 = (index-index1)/4;
                  }else if(getPolis()->getNumEdify(4) == 1){
                         index2 = (index-index1)/4;
                         index3 = (index-index1)/4;
                         index4 = (index-index1)/4;
                         index5 = (index-index1)/4;
                  }else{
                        index2 = (index-index1)/2;
                        index3 = (index-index1)/2;
                  }
                  
                  if(decision < index1+index2) createCitizen<Archer>(num, 7, nextGrain);
                  else if(decision < index1+index2+index3) createCitizen<Knave>(num, 4, nextGrain);
                  else if(decision < index1+index2+index3+index4) createCitizen<Lancer>(num, 3, nextGrain);
                  else if(decision < index1+index2+index3+index4+index5) createCitizen<Knight>(num, 6, nextGrain);
                  else if(decision < index1+index2+index3+index4+index5+index6 && getPolis()->getNumEdify(4) > 0){
                         if(getPolis()->getId() == 0) createCitizen<Peltast>(num, 8, nextGrain);
                         else if(getPolis()->getId() == 1) createCitizen<Hoplite>(num, 5, nextGrain);
                         else createCitizen<Pezhetairos>(num, 2, nextGrain);
                  }
           }
     }
}

template <typename T> void cpuPlayer::createCitizen(int & num,int type, int nextGrain){
    bool aux = true;
    T * ptr = new T;
       
    while(aux){
        if((getPolis()->getNumGrain()/2 > ptr->getGrain()*num)&&
           (getPolis()->getNumStone()/2 > ptr->getStone()*num)&&
           (getPolis()->getNumIron()/2 > ptr->getIron()*num)) num++;
        else aux = false; 
    }
       
    for(int i=0; i<num/2; i++) if(nextGrain - i*2 > getPolis()->getNumGrain() || type == 0)  aux = exectCitizen<T>(type);
    delete ptr;
    ptr = 0;
}

template <typename T> void cpuPlayer::createEdifice(int type){
    T * ptr = new T;    
    if((getPolis()->getNumGrain()/2 > ptr->getGrain())&&
        (getPolis()->getNumStone()/2 > ptr->getStone())&&
        (getPolis()->getNumIron()/2 > ptr->getIron())) exectEdifice<T>(type);
    if(type == 1 || type == 2 || type == 3) getPolis()->addNumEdifice(0);
}

ostream & cpuPlayer::put(ostream & os){
      return  os << "Risorse Avversarie: " << endl
                 << "Ferro: " << getPolis()->getNumIron() 
                 << "\tPietra: " << getPolis()->getNumStone() 
                 << "\tGrano: " << getPolis()->getNumGrain() << endl
                 << "Numero Cittadini: " << getPolis()->getNumCitizens() << endl
                 << "Numero Edifici: " << getPolis()->getNumEdifices() << endl;
}
