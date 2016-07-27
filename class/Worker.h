#ifndef WORKER_H
#define WORKER_H
#include "Citizen.h"

class Worker : public Citizen{
       
    public:
        Worker();
        int getIron();
        int getStone();
        int getGrain();
        
};

#endif
