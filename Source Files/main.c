#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
//#include "processar_info.h"



int main() {

    //VARIAVEIS
    char resposta;

    
    //CHAMAR MENU
    do {
        menu();

        printf("Deseja continuar no programa [s/n]?\n");
        scanf(" %c", &resposta);


    } while (resposta != 'n');


    return (0);
}

