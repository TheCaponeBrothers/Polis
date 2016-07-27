#include "Turn.h"
#include "Player.h"
using namespace std;

int Turn::numTurn = 0;

Turn::Turn()
{}

void setActions(Player * _g1, Player * _g2, Player * _g3)
{
     for(int i=0;i<3;i++)
     {
         _g1->setAction(i, false);
         _g2->setAction(i, false);
         _g3->setAction(i, false);
     }
}

void setResources(Player * _g)
{
    _g->getPolis()->modNumIron(-(_g->getPolis()->getNumCity(0)*10));
    _g->getPolis()->modNumStone(-(_g->getPolis()->getNumCity(0)*10));
    _g->getPolis()->modNumGrain(-(_g->getPolis()->getNumCity(0)*10));
    _g->getPolis()->modNumGrain(_g->getPolis()->getNumCitizens()*2);
}

void moveBattalions(Player * _g)
{
    for(int i=0;i<_g->getPolis()->getNumBattalions();i++)
    {
        Battalion * p = _g->getPolis()->getBattalion(i);
        _g->getPolis()->modNumGrain(p->getNumVett()*9);
        if(p->getMotion())
            if(p->getFight()) 
            {
                  
            }
            else
            {
                  p->move();
            }
    }
}

void actionTurn(Player * _g1, Player * _g2, Player * _g3)
{
    setActions(_g1, _g2, _g3);
    
    setResources(_g1);
    setResources(_g2);
    setResources(_g3);
    
    moveBattalions(_g1);
    moveBattalions(_g2);
    moveBattalions(_g3);
}
