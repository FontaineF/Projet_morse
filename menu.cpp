//La fonction centrale, appelant les fonction texte->morse ou morse->texte selon le choix de l'utilisateur


#include<iostream>
#include<stdio.h>
#include<string.h>
#include <cmath>
#include <fstream>
using namespace std;

#include "txt_to_morse.h"
#include "morse_to_txt.h"

void menu(){
    printf("\n\n\t\t\t* Le code morse *\n\n\n");
    printf(" Vous desirez :\n\n");
    printf("\t1 : Coder un texte en morse\n\n");
    printf("\t2 : Decoder un texte morse\n\n");


    char c;
    std::cin >> c;
    if(c=='1'){
        //Code le message en morse
        saisie_t();
    }
    else{
        //Décode le message
        saisie_m();
    }
}
