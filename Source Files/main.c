/*
 *  Projeto de Laboratórios de Programação
 *      Programa de cálculo de salários
 */


#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    
    //Variaveis
    char resposta;
    
    //Registos
    Data data[8];
    Funcionario_info funcionario_info;
    Calculo calculo;
    
    do{
    menu();
    
    printf("Deseja continuar no programa [s/n]?\n");
    scanf(" %c", &resposta);
    
    
    } while (resposta != 'n');
    
    
    return (0);
}

