//
//  main.cpp
//  LA03

#include <iostream>
#include "chirper.h"

using namespace std;

int main(){
    Chirp ch, ch2;
    ch.setup_account();
    ch.menu();
    
    cout << "See you next time\n";
    return 0; }
