#include "Citizen.h"
Citizen::Citizen() : health(100){}
int Citizen::getHealth() const{ return health; }
void Citizen::Damage(int _d){ health -= _d; }
void Citizen::Heal(){ health = 100; }
