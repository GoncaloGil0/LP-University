/*
 *  Projeto de Laboratórios de Programação
 *      Programa de cálculo de salários
 */


#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main() {
    
    //Declaração de variaveis
    int codigo, numero_tlf, numero_filhos;
    char nome[50];
    enum estadoCivil{ solteiro, casado, viuvo, divorciado };
    enum cargo{ empregado = 40, chefe = 60, administrador = 80}; //esses valores sao o pagamento por dia? mas nos vamos ter de gerir por horas, dividimos tipo 40/8?
    float sub_alimentacao;
    
    //escolha do menu
    switch (menu()) { //foi criada uma função menu que retorna a opção do menu
        
        case 1:
            printf("f1");
            break;
        case 2:
            printf("f2");
            break;
        case 3:
            printf("f3");
            break;
        case 4:
            printf("f4");
            break;
        case 5:
            printf("f5");
            break;
        case 6:
            printf("f6");
            break;
        case 7:
            printf("f7");
            break;
        case 8:
            printf("A aplicação foi terminada com sucesso");
            exit (0);
        default:
            printf("Opção Inválida"); // não é necessário devido ao "do {} while" acima
    }
    
    
    return (0);
}

