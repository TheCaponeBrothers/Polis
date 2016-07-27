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

void trackBattalion(Player *p){
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

int main(){
    mciSendString("open music/music.wma type mpegvideo alias Start",NULL,0,0);   
    mciSendString("play Start",NULL,0,0);
    SetConsoleTitle("Polis");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    HWND console = GetConsoleWindow();
    MoveWindow(console,0,0,800,getmaxheight()-10,TRUE); 
    srand(unsigned(time(NULL)));
    vector <int> enemyPolis;
    enemyPolis.push_back(0);
    enemyPolis.push_back(1);
    enemyPolis.push_back(2);    
    string typePolis = "";
    Sleep(400);
    Library::slowPrint(60,"Da tempi immemorabili tre Polis si davano battaglia, per la conquista \ndell'egemonia della Grecia. Dure lotte, li aspettavano. \nFiumi di sangue innocente avevano sostituito i corsi d'acqua. \nAl di la, oltre ogni divisione, innocenti aspettavano i loro cari, di ritorno \nda quelle interminabili battaglie.\n\nInizia la tua partita e proteggi la tua Polis...\n");
    do{
        Library::slowPrint(60,"0) Atene\n1) Sparta\n2) Tebe\nScegli una Polis: ");
        cin >> typePolis;
        system("CLS");
    }while(typePolis != "0" && typePolis != "1" && typePolis != "2");
    int typePolisId;
    istringstream (typePolis) >> typePolisId;
    enemyPolis.erase(enemyPolis.begin()+typePolisId);    
    random_shuffle(enemyPolis.begin(),enemyPolis.end());

    Player * player = new Player(typePolisId,Library::coordinate[typePolisId],Library::coordinate[typePolisId+3]);
    Player * enemyFirst = new cpuPlayer(enemyPolis.at(0),Library::coordinate[enemyPolis.at(0)],Library::coordinate[enemyPolis.at(0)+3]);
    Player * enemySecond = new cpuPlayer(enemyPolis.at(1),Library::coordinate[enemyPolis.at(1)],Library::coordinate[enemyPolis.at(1)+3]);
    Polis * myPolis = player->getPolis();
    
    mciSendString("pause Start", NULL, 0, NULL);
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
        
        if(player != NULL) trackBattalion(player);
        if(enemyFirst != NULL) trackBattalion(enemyFirst);
        if(enemySecond != NULL) trackBattalion(enemySecond);        
        exeAttack = true;
        string selectMenuPolis = "";
        
        if(player->getPolis()->getNumGrain() < 0){
            if(player->getPolis()->getNumCitizens()>0){
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
            if(player != NULL){
                cout << "                    Giocatore 1 (" << player->namePolis() << ")"<<endl;
                cout << *player << endl;
                cout << "     +------------------------+" << endl;
                cout << "     |        Men" << (char)(163) << "            |" << endl;
                cout << "     +------------------------+" << endl;
                cout << "     | 0)   Statistiche       |" << endl;
                cout << "     | 1)     Edifici         |" << endl;
                cout << "     | 2)    Cittadini        |" << endl;
                cout << "     | 3)   Battaglioni       |" << endl;
                cout << "     | 4)  Crea Cittadini     |" << endl;
                cout << "     | 5)     Attacca         |" << endl;
                cout << "     | 6)   Costruisci        |" << endl;
                if(player->getPolis()->getNumEdifices() > 0)
                    cout << "     | 7)    Distruggi        |" << endl;
                if(player->getPolis()->getNumBattalions() > 0){
                    retireB = true;
                    cout << "     | 8)     Ritira          |" << endl;
                }else retireB = false;
                if(player->getTemple())
                    cout << "     | 9)   Offri agli dei    |" << endl;
                cout << "     | *)  Passa il turno     |" << endl;
                cout << "     +------------------------+" << endl<<endl;
                cout << "Fai la tua scelta: ";
                cin >> selectMenuPolis;
                cout << endl;

                if(player->getAction(0) && player->getAction(1) && player->getAction(2)){
                    cout << "Hai esaurito le azioni disponibili." << endl;
                    selectMenuPolis = "*";
                }
            
                if(selectMenuPolis == "0") player->statisticsTurn();
                else if(selectMenuPolis == "1") myPolis->viewEdifices();
                else if(selectMenuPolis == "2") myPolis->viewCitizens();
                else if(selectMenuPolis == "3") myPolis->viewBattalion();
                else if((selectMenuPolis == "4") && (!player->getAction(1))) player->makeCitizen();
                else if((selectMenuPolis == "4") && (player->getAction(1))) cout << "Hai gi" << (char)(133) << " creato cittadini in questo turno." << endl;
                else if((selectMenuPolis == "5") && (!player->getAction(2))) player->attack(enemyFirst,enemySecond,enemyPolis);
                else if((selectMenuPolis == "5") && (player->getAction(2))) cout << "Hai gi" << (char)(133) << " attaccato in questo turno." << endl;                 
                else if((selectMenuPolis == "6") && (!player->getAction(0))) player->makeEdifice();
                else if((selectMenuPolis == "6") && (player->getAction(0))) cout << "Hai gi" << (char)(133) << " costruito in questo turno." << endl;                 
                else if(selectMenuPolis == "7" && player->getPolis()->getNumEdifices() > 0) player->destroyEdify();
                else if((selectMenuPolis == "8") && retireB) player->retire();
                else if((selectMenuPolis == "9") && player->getTemple()) player->offer();
                else if(selectMenuPolis != "*") cout << "Nessun comando " << (char)(138) << " stato trovato." << endl;
                cout << endl << "Continua...";
                getchar();
                getchar();
                system("CLS");        
                exeAttack = false;
            }else{
                cout << "La tua Polis " << (char)(138) << " stata distrutta." <<endl;
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
        
        if(player != NULL && player->getPolis() != NULL && player->getTemple()){
            int gift = player->getPolis()->getGift();
            if(enemyFirst != NULL){
                if(rand()%10 < 9 + gift){ 
                    cout << "                    Giocatore 2 (" << enemyFirst->namePolis() << ")\n";
                    cout << *enemyFirst << endl;
                    if(rand()%25 < gift) enemyFirst->getPolis()->viewBattalion();
                    if(rand()%50 < gift) enemyFirst->getPolis()->viewCitizens();
                }
            }
            if(enemySecond != NULL){
                if(rand()%10 < 9 + gift){ 
                    cout << "\n\n                    Giocatore 3 (" << enemySecond->namePolis() << ")\n";
                    cout << *enemySecond << endl;
                    if(rand()%25 < gift) enemySecond->getPolis()->viewBattalion();
                    if(rand()%50 < gift) enemySecond->getPolis()->viewCitizens();
                }
            }
            system("pause");
            system("CLS");
        }
        Library::changeTurn(player,enemyFirst,enemySecond);
    }
    mciSendString("pause Theme", NULL, 0, NULL);
    mciSendString("open music/end.mp3 type mpegvideo alias End",NULL,0,0);   
    mciSendString("play End",NULL,0,0);
    system("pause");
    cout << "Game " << ((player == NULL) ? "Over" : "Win") << ".";
    getchar();
    //clean up
    closegraph();
    return 0;
}
