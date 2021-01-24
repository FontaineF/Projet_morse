//Fait la synthèse de morse_to_tab et tab_to_txt pour décoder le message morse

#include "tab_to_txt.h"

void saisie_m(){
    printf("\t\t\t* Decodage d'un texte morse *\n\n");
    
    int* valeur = decoder();

    std::cout << "Une fois décodé, votre message devient : " << std::endl;
    
    std::cout << "  ->  " << translation(valeur) << std::endl;

    std::cout << std::endl;
}