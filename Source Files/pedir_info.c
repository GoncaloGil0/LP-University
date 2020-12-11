// Codigo dedicado a todas as funções para pedir informação ao user 

//Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//headers
#include "pedir_info.h"
#include "menus.h"
#include "processar_info.h"

//constantes
#define VALOR_INVALIDO " ! Valor inválido ! "
#define NOME_INVALIDO " ! Nome inválido ! "

//funções
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void lerData (Data *data) {
    scanf("%d.%d.%d", &data->dia, &data->mes, &data->ano);
}

void addFuncionario (Funcionario *funcionario) {
    char nome[50], saida;
    int est_civil, cargo;
    
    printf("\nCódigo: ");
    //scanf("%d", &funcionario->codigo); 
    
    printf("\nNome: ");
    //scanf(" %s", funcionario->nome);    

    printf("\nNumero de telemovel: ");
    
    double max = 969999999;
    double min = 911111111;

    obter_num(min, max);//&funcionario->numero_tlm = ao que a função retorna

    
    do {
    printf("\nEstado civil [0-Casado 1-Solteiro 2-Divorciado 3-Viúvo]: "); 
    scanf("%d", &est_civil); 
    } while ( est_civil > 3 || est_civil < 0 );
    
    //&funcionario->est_civil = est_civil
    
    printf("\nNumero de filhos no agregado familiar: ");
    scanf("%d", &funcionario->numero_filhos);
    
    do {
    printf("\nCargo na empresa [0-Empregado 1-Chefe 2-Administrador]: ");
    scanf("%d", &cargo);
    } while ( cargo > 2 || cargo < 0 );
    
    //&funcionario->cargo = cargo
    
    printf("\nSalário por hora: ");
    scanf("%f", &funcionario->valor_hora);
    
    printf("\nValor do subsídio de alimentação: ");
    scanf("%f", &funcionario->valor_sub_ali);
    
    printf("\nData de nascimento (dd.mm.aaaa): ");
    lerData(&funcionario->nascimento); //temos de fazer a verificação se a data e valida 
    
    printf("\nData de entrada na empresa (dd.mm.aaaa): ");
    lerData(&funcionario->entrada_emp); //temos de fazer a verificação se a data e valida 
    
    do {
    printf("\nContinua na empresa (s/n) ? ");
    scanf(" %c", &saida);
    
    } while ( saida != 'n' && saida != 's');
    
    if (saida == 'n') {
        printf("\nData de saida da empresa (dd.mm.aaaa): ");
        lerData(&funcionario->saida_emp); //temos de fazer a verificação se a data e valida 
    } else {
        // temos de atribuir um valor a data quando ele ainda esta na empresa 
        // para podermos fazer os calculos dps
    }

}

void calcSalarial (Funcionario *funcionario) {
    // e para cada data verificar se os 4 parametros somados não dao superiores ao numero de dias nesse mes   
    printf("\nMês: ");
    scanf("%d", &funcionario->mes);
    printf("\nNumero de dias completos trabalhados: ");
    scanf("%d", &funcionario->dias_compl);
    printf("\nNumero de meios dias trabalhados: ");
    scanf("%d", &funcionario->dias_meios);
    printf("\nNumero de dias trabalhados ao fim de semana: ");
    scanf("%d", &funcionario->dias_fds);
    printf("\nNumero de dias faltados: ");
    scanf("%d", &funcionario->dias_faltas);
}

double obter_num(double min, double max) {
    double valor;
    while (scanf("%lf", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf("Digite um valor: ");
    }
    cleanInputBuffer();
    return valor;
}
