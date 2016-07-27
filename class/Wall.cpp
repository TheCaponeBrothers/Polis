#include "Wall.h"
Wall::Wall() : Edifice(),defense(500){}
int Wall::getIron(){ return 500; }
int Wall::getStone(){ return 500; }
int Wall::getGrain(){ return 250; }
int Wall::getDefense(){ return defense; }
void Wall::Damage(int _d){ defense -= _d; }
