#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "Library.h"
Library::Library(){}

int Library::numTurn = 1;
int Library::coordinate[] = {930,460,710,260,680,80};
const int Library::constBattalions = 6;
const int Library::constEdifices = 6;
int Library::Random(int min,int max){ return min+rand()%(max-min+1); }

char * Library::getNamePolis(char * c,int v){
    char * array[] = {"Atene","Sparta","Tebe"};
    char * str = (char*)(malloc(strlen(c)+strlen(array[v])+1));
    strcpy(str,c);
    strcat(str,array[v]);
    return str;
}

void Library::slowPrint(unsigned long speed,const char *s){
	int i = 0;
	while(s[i]!=0){
		cout << s[i++];
		cout.flush();
		Sleep(speed);
	}
}

void Library::changeTurn(Player * _g1,Player * _g2,Player * _g3){
    if(_g1 != NULL) _g1->actionTurn();
    if(_g2 != NULL) _g2->actionTurn();
    if(_g3 != NULL) _g3->actionTurn();
    numTurn++;
}
