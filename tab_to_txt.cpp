//Traduit le tableau de valeurs créé par morse_to_tab en txt

#include<iostream>
#include<stdio.h>
#include<string.h>
#include <cmath>
#include <fstream>
#include<map>
using namespace std;

#include"morse_to_tab.h"



std::string translation(int* valeur){

    char alpha[37]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','1','2','3','4','5','6','7','8','9','0','_'};
    std::string mors[37]={{".-"},{"-..."},{"-.-."},{"-.."},{"."},{"..-."},{"--."},{"...."},{".."},{".---"},{"-.-"},{".-.."},{"--"},{"-."},{"---"},{".--."},{"--.-"},{".-."},{"..."},{"-"},{"..-"},{"...-"},{".--"},{"-..-"},{"-.--"},{"--.."},{".----"},{"..---"},{"...--"},{"....-"},{"....."},{"-...."},{"--..."},{"---.."},{"---."},{"-----"},{"/"}};

    //on définit le dictionnaire que l'on va utiliser
    std::map<std::string, char> dct;
    for(int it = 0; it<37; it++){
        dct[mors[it]]=alpha[it];
    }


    std::string traduit_final;  //La distinction entre traduit et traduit_final permet d'enlever tous les '_' qui apparaissent
    std::string traduit;        //       à la fin du message décodé en raison de la taille du tableau initialisée à 1000
    std::string temp;           //Stocke les lettres une à une
    int i = 30;
    bool mot_en_cours = false;  //Variable pour savoir si un mot est en cours
    int pre_un = 0; //nombres de 1 juste avant le i dans le tableau de valeurs
    int pre_zero = 0; //nombres de 1 juste avant le i dans le tableau de valeurs
    while(i < 10000){
        if(valeur[i]==0){
            if(pre_un == 1){
                temp += ".";
            }
            if(pre_zero >= 5){
                if(mot_en_cours){
                    traduit += dct[temp];
                    traduit_final += traduit;
                    traduit = "";
                    pre_zero = 0;
                    temp = "";
                    mot_en_cours = false;

                }
                else if(pre_zero == 25){
                    traduit += "_";
                    pre_zero = 0;
                }
                else{
                    pre_zero += 1;
                }
            }
            else{
                pre_zero += 1;
            }
            pre_un = 0;
        }
        if(valeur[i]==1){
            mot_en_cours = true;
            if(pre_un == 2){
                temp += "-";
            }
            pre_un += 1;
            pre_zero = 0;
        }
        i+=1;
    }


    return traduit_final;
}