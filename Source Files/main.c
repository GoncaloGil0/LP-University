/*
 *  Projeto de Laboratórios de Programação
 *      Programa de cálculo de salários
 */

#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "pedir_info.h"
#include "processar_info.h"

int main() {
    
    //Variaveis
    char resposta;
    
    //Registos
    Calculo calculo;
    
    do{
    menu();
    
    printf("Deseja continuar no programa [s/n]?\n");
    scanf(" %c", &resposta);
    
    
    } while (resposta != 'n');
    
    
    return (0);
}

