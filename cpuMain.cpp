/*
  Name:
                ***** **               ***                        
             ******  ****               ***      *                
            **   *  *  ***               **     ***               
           *    *  *    ***              **      *                
               *  *      **    ****      **               ****    
              ** **      **   * ***  *   **    ***       * **** * 
              ** **      **  *   ****    **     ***     **  ****  
            **** **      *  **    **     **      **    ****       
           * *** **     *   **    **     **      **      ***      
              ** *******    **    **     **      **        ***    
              ** ******     **    **     **      **          ***  
              ** **         **    **     **      **     ****  **  
              ** **          ******      **      **    * **** *   
              ** **           ****       *** *   *** *    ****    
         **   ** **                       ***     ***             
        ***   *  *                                                
         ***    *                                                 
          ******                                                  
            ***   
  Copyright: MG
  Author: Pietro Martello e Gaetano Zappalà
  Date: 12/04/14 00:00
  Description: 
*/
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <math.h>
#include "graphics.h"
#include "class/Library.h"
#include "class/Player.h"
#include "class/cpuPlayer.h"
using namespace std;

void trackBattalionCpu(Player *p){
    for(int i=0; i<p->getPolis()->getNumBattalions(); i++){
        if(p->getPolis()->getBattalion(i)->getObjective() != 3){
            double t = p->getPolis()->getBattalion(i)->getDistance()/sqrt(
            pow((Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()]-Library::coordinate[p->getPolis()->getId()]),2) +
            pow((Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()+3]-Library::coordinate[p->getPolis()->getId()+3]),2));       
            int x = (int)(Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()]+t*(Library::coordinate[p->getPolis()->getId()]-Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()]));
            int y = (int)(Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()+3]+t*(Library::coordinate[p->getPolis()->getId()+3]-Library::coordinate[p->getPolis()->getBattalion(i)->getObjective()+3]));
            char *filename;
            if(p->getPolis()->getId() == 0) filename = "MingW/truppe.jpg";
            else if(p->getPolis()->getId() == 1) filename = "MingW/truppe2.jpg";
            else if(p->getPolis()->getId() == 2) filename = "MingW/truppe3.jpg";
            readimagefile(filename,x+24,y+24,x,y);
        }
        
        if(p->getPolis()->getBattalion(i)->getObjective() == 3){
            double t = p->getPolis()->getBattalion(i)->getDistance()/sqrt(
            pow((Library::coordinate[p->getPolis()->getBattalion(i)->getObjective2()]-Library::coordinate[p->getPolis()->getId()]),2) +
            pow((Library::coordinate[p->getPolis()->getBattalion(i)->getObjective2()+3]-Library::coordinate[p->getPolis()->getId()+3]),2));       
            int x = (int)(Library::coordinate[p->getPolis()->getId()]+t*(Library::coordinate[p->getPolis()->getBattalion(i)->getObjective2()]-Library::coordinate[p->getPolis()->getId()]));
            int y = (int)(Library::coordinate[p->getPolis()->getId()+3]+t*(Library::coordinate[p->getPolis()->getBattalion(i)->getObjective2()+3]-Library::coordinate[p->getPolis()->getId()+3]));
            char *filename;
            if(p->getPolis()->getId() == 0) filename = "MingW/home.jpg";
            else if(p->getPolis()->getId() == 1) filename = "MingW/home2.jpg";
            else if(p->getPolis()->getId() == 2) filename = "MingW/home3.jpg";
            readimagefile(filename,x+24,y+24,x,y);
        }
    }
}

int main2(){
//for(int k=0;k<100;k++){
    //Library::numTurn = 1;
    SetConsoleTitle("Polis");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    HWND console = GetConsoleWindow();
    MoveWindow(console,0,0,800,getmaxheight()-10,TRUE); 
    srand(unsigned(time(NULL)));
    vector <int> enemyPolis;
    enemyPolis.push_back(0);
    enemyPolis.push_back(1);
    enemyPolis.push_back(2);    
    string typePolis = "";
    do{
        system("CLS");
        cout << "0) Atene" << endl;
        cout << "1) Sparta" << endl;
        cout << "2) Tebe" << endl;
        cout << "Scegli una Polis: ";
        cin >> typePolis;
    }while(typePolis != "0" && typePolis != "1" && typePolis != "2");
    int typePolisId;
    istringstream (typePolis) >> typePolisId;
    enemyPolis.erase(enemyPolis.begin()+typePolisId);    
    random_shuffle(enemyPolis.begin(),enemyPolis.end());
    
    Player * player = new cpuPlayer(typePolisId,Library::coordinate[typePolisId],Library::coordinate[typePolisId+3]);
    Player * enemyFirst = new cpuPlayer(enemyPolis.at(0),Library::coordinate[enemyPolis.at(0)],Library::coordinate[enemyPolis.at(0)+3]);
    Player * enemySecond = new cpuPlayer(enemyPolis.at(1),Library::coordinate[enemyPolis.at(1)],Library::coordinate[enemyPolis.at(1)+3]);
    Polis * myPolis = player->getPolis();

    mciSendString("open music/theme.mp3 type mpegvideo alias Theme",NULL,0,0);   
    mciSendString("play Theme notify repeat",NULL,0,0);
    
    //Mappa
    int map = initwindow(1100,800,"Mappa",getmaxwidth()-1100,0);
    bool exeAttack = false, retireB = false;
    system("CLS");
    while((player != NULL) && ((enemyFirst != NULL) || (enemySecond != NULL))){
        
        clearviewport();        
        readimagefile("MingW/map.png",0,0,1100,800);
        setfillstyle(SOLID_FILL,BLACK);
        bar(950,746,getmaxwidth()-150,getmaxheight()-54);
        rectangle(950,746,getmaxwidth()-150,getmaxheight()-54);
        outtextxy(952,748,Library::getNamePolis("Giocatore: ",typePolisId));
        outtextxy(952,767,Library::getNamePolis("Giocatore2: ",enemyPolis.at(0)));
        outtextxy(952,785,Library::getNamePolis("Giocatore3: ",enemyPolis.at(1)));
        if(player == NULL) readimagefile("MingW/death.png",Library::coordinate[typePolisId],Library::coordinate[typePolisId+3],Library::coordinate[typePolisId]+50,Library::coordinate[typePolisId+3]+33);
        else readimagefile("MingW/myPolis.png",player->getPolis()->getXcord(),player->getPolis()->getYcord(),player->getPolis()->getXcord()+50,player->getPolis()->getYcord()+33);
        if(enemyFirst == NULL) readimagefile("MingW/death.png",Library::coordinate[enemyPolis.at(0)],Library::coordinate[enemyPolis.at(0)+3],Library::coordinate[enemyPolis.at(0)]+50,Library::coordinate[enemyPolis.at(0)+3]+33);
        else readimagefile("MingW/home.png",enemyFirst->getPolis()->getXcord(),enemyFirst->getPolis()->getYcord(),enemyFirst->getPolis()->getXcord()+50,enemyFirst->getPolis()->getYcord()+33);
        if(enemySecond == NULL) readimagefile("MingW/death.png",Library::coordinate[enemyPolis.at(1)],Library::coordinate[enemyPolis.at(1)+3],Library::coordinate[enemyPolis.at(1)]+50,Library::coordinate[enemyPolis.at(1)+3]+33);
        else readimagefile("MingW/home2.png",enemySecond->getPolis()->getXcord(),enemySecond->getPolis()->getYcord(),enemySecond->getPolis()->getXcord()+50,enemySecond->getPolis()->getYcord()+33);
        
        if(player != NULL) trackBattalionCpu(player);
        if(enemyFirst != NULL) trackBattalionCpu(enemyFirst);
        if(enemySecond != NULL) trackBattalionCpu(enemySecond);        
        exeAttack = true;
        string selectMenuPolis = "";
        //cout << k << endl;
        
        if(player->getPolis()->getNumGrain() < 0){
            if(player->getPolis()->getNumCitizens() > 0){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "Carestia di Grano! I Cittadini Muoiono!" << endl;
                player->getPolis()->destroyCitizens();
            }else{
                cout << "Tutti i cittadini sono morti o partiti..." << endl;
                delete player;
                player = NULL;
            }
        }
        
        do{
            
            int t = rand()%2;
            if(t == 1 && player != NULL) player->showBattalions(enemyFirst,enemySecond,exeAttack);
            if(rand()%2){
                if(enemyFirst != NULL && enemyFirst->getPolis() != NULL) enemyFirst->showBattalions(player,enemySecond,exeAttack);
                if(enemySecond != NULL && enemySecond->getPolis() != NULL) enemySecond->showBattalions(player,enemyFirst,exeAttack);
            }else{
                if(enemySecond != NULL && enemySecond->getPolis() != NULL) enemySecond->showBattalions(player,enemyFirst,exeAttack);
                if(enemyFirst != NULL && enemyFirst->getPolis() != NULL) enemyFirst->showBattalions(player,enemySecond,exeAttack);
            }
            if(t == 0 && player != NULL) player->showBattalions(enemyFirst,enemySecond,exeAttack);
            
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Turni: " << Library::numTurn << endl << endl;
            if(player != NULL){                 
                ((cpuPlayer *)player)->evolvePolis(enemyFirst,enemySecond);
                cout << "Turno del giocatore 1: " << player->namePolis() << endl << *player << " " << endl << endl;
                selectMenuPolis = "*";            
                if(player->getAction(0) && player->getAction(1) && player->getAction(2)){
                    cout << "Hai esaurito le azioni disponibili." << endl;
                    selectMenuPolis = "*";
                }                      
                exeAttack = false;
            }else{
                cout << "La tua Polis "<< (char)(138) << " stata distrutta." <<endl;
                selectMenuPolis = "*";
            }
            
        }while(selectMenuPolis != "*");
        
        if(enemyFirst != NULL && player != NULL){ 
            if(enemyFirst->getPolis()->getNumGrain() < 0){
                if(enemyFirst->getPolis()->getNumCitizens() > 0) enemyFirst->getPolis()->destroyCitizens();
                else{
                    delete enemyFirst;
                    enemyFirst = NULL;
                }
            }
            if(enemyFirst != NULL) ((cpuPlayer *)enemyFirst)->evolvePolis(player,enemySecond);
        }
        
        if(enemySecond != NULL && player != NULL){
            if(enemySecond->getPolis()->getNumGrain() < 0){
                if(enemySecond->getPolis()->getNumCitizens() > 0) enemySecond->getPolis()->destroyCitizens();
                else{
                    delete enemySecond;
                    enemySecond = NULL;
                }
            }
            if(enemySecond != NULL) ((cpuPlayer *)enemySecond)->evolvePolis(player,enemyFirst);
        }
        
        if(player == NULL) readimagefile("MingW/death.png",Library::coordinate[typePolisId],Library::coordinate[typePolisId+3],Library::coordinate[typePolisId]+50,Library::coordinate[typePolisId+3]+33);
        if(enemyFirst == NULL) readimagefile("MingW/death.png",Library::coordinate[enemyPolis.at(0)],Library::coordinate[enemyPolis.at(0)+3],Library::coordinate[enemyPolis.at(0)]+50,Library::coordinate[enemyPolis.at(0)+3]+33);
        if(enemyFirst != NULL && player != NULL){
            ((cpuPlayer *)enemyFirst)->evolvePolis(player,enemySecond);
            cout << "Turno del giocatore 2: " << enemyFirst->namePolis() << endl << *enemyFirst << " " << endl << endl;
        }        
        if(enemySecond == NULL) readimagefile("MingW/death.png",Library::coordinate[enemyPolis.at(1)],Library::coordinate[enemyPolis.at(1)+3],Library::coordinate[enemyPolis.at(1)]+50,Library::coordinate[enemyPolis.at(1)+3]+33);
        if(enemySecond != NULL && player != NULL){
            ((cpuPlayer *)enemySecond)->evolvePolis(player,enemyFirst);
            cout << "Turno del giocatore 3: " << enemySecond->namePolis() << endl << *enemySecond << " " << endl << endl;
        }

        //if(Library::numTurn > 1550) 
        Sleep(500);
        system("CLS");
        Library::changeTurn(player,enemyFirst,enemySecond);
    }

    cout << "Game " << ((player == NULL) ? "Over" : "Win") << ".";
    cout << "Turni: " << Library::numTurn << endl << endl;
    cout << "Il vincitore: "<<endl;
    if(player != NULL){ cout << "G1" << endl <<*player<<endl;   player->getPolis()->viewCitizens(); player->getPolis()->viewBattalion(); }
    if(enemyFirst != NULL){ cout<< "G2" << endl<<*enemyFirst<<endl; enemyFirst->getPolis()->viewCitizens(); enemyFirst->getPolis()->viewBattalion();}
    if(enemySecond != NULL){ cout<< "G3" << endl<<*enemySecond<<endl; enemySecond->getPolis()->viewCitizens(); enemySecond->getPolis()->viewBattalion();}
//}
    system("pause");
    getchar();
    //clean up
    closegraph();
    return 0;
}
