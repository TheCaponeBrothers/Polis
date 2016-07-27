#ifndef POLIS_H
#define POLIS_H
#include "Battalion.h"
#include "Citizen.h"
#include "Edifice.h"
using namespace std;

class Polis{

    private:
        int iron;
        int stone;
        int grain;
        int typePolisId;
        vector <Battalion*> battalions;
        vector <Citizen*> citizens;
        vector <Edifice*> edifices;
        int numCitizens[9]; /* 0->Lavoratori
                               1->Soldati
                               2->Pezeteri
                               3->Lancieri
                               4->Fanti
                               5->Opliti
                               6->Cavalieri
                               7->Arcieri
                               8->Peltasti
                            */ 
        int numEdifices[7]; /* 0->Risorse
                               1->Cava
                               2->Fattoria
                               3->Miniera
                               4->Caserma
                               5->Tempio
                               6->Muro
                            */ 
        int xcord;
        int ycord;
    
    public:
        Polis(int,int,int);
        ~Polis();
        int getId() const;
        int getXcord() const;
        int getYcord() const;
        int getNumIron() const;
        int getNumStone() const;
        int getNumGrain() const;
        int getNumBattalions() const;
        int getNumCitizens() const;
        int getNumEdifices() const;
        int getNumCity(int) const;
        int getNumEdify(int) const;
        int getDistance(int,int) const;
        int getDistance(Polis *) const;
        int getCalculate(int[],int);
        Battalion * getBattalion(int);
        Citizen * getCitizen(int);
        Edifice * getEdifice(int);
        void addTemple(int);
        int getGift();
        void destroyEdifice(int);
        void destroyCitizens();
        template <typename T> void newCitizen();
        template <typename T> void newEdifice();
        template <typename T> bool deleteEdifice(int);
        bool makeBattalion(int);
        bool controlBattalion(int,int,int,int,int,int,int,int);
        void newBattalion(int,int[],int);
        void eraseBattalion(int);
        void defend();
        void addCitizen(Citizen *);
        void addEdifice(Edifice *);
        void addNumCitizen(int);
        void addNumEdifice(int);
        void subNumEdifice(int);
        void addNumIron(int);
        void addNumStone(int);
        void addNumGrain(int);
        void subNumIron(int);
        void subNumStone(int);
        void subNumGrain(int);
        void viewBattalion();
        void viewCitizens();
        void viewEdifices();
};

#endif
