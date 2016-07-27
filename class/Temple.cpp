#include "Temple.h"
Temple::Temple() : Edifice(), gift(0){}
int Temple::getIron(){ return 1000; }
int Temple::getStone(){ return 1000; }
int Temple::getGrain(){ return 1000; }
int Temple::getGift(){ return gift; }
void Temple::resetGift(){ gift = 0; }
void Temple::addGift(int _a){ gift += _a; }
