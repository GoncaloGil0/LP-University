// Codigo dedicado a todas as funções para pedir informação ao user 

#include <stdio.h>
#include <stdlib.h>
#include "pedir_info.h"

    void lerData (Data *data) {
        scanf("%d.%d.%d", &data->dia,&data->mes,&data->ano);
    }
    
    void addFuncionario (Funcionario *funcionario) {
        printf("\nCódigo: ");
        scanf("%d", &funcionario->codigo); // se desse temos de fazer a verificação de que o input é um int e não uma string ou assim
        printf("\nNome: ");
        scanf("%s", funcionario->nome); // se desse temos de fazer a verificação de que o input é uma string e não um int ou assim
        printf("\nNumero de telemovel: ");
        scanf("%d", &funcionario->numero_tlm); //temos de fazer a verificação se o numero é valido (ou seja, tenha 9 digitos)
        printf("\nEstado civil [0-Casado 1-Solteiro 2-Divorciado 3-Viúvo]: "); 
        scanf("%d", &funcionario->est_civil); //temos de fazer a verificação se o input nao é diferente daqueles 3
        printf("\nNumero de filhos no agregado familiar: ");
        scanf("%d", &funcionario->numero_filhos);
        printf("\nCargo na empresa [0-Empregado 1-Chefe 2-Administrador]: ");
        scanf("%d", &funcionario->cargo);  //temos de fazer a verificação se o input nao é diferente daqueles 3
        printf("\nSalário por hora: ");
        scanf("%f", &funcionario->valor_hora);
        printf("\nValor do subsídio de alimentação: ");
        scanf("%f", &funcionario->valor_sub_ali);
        printf("\nData de nascimento (00.00.0000): ");
        lerData(&funcionario->nascimento); //temos de fazer a verificação se a data e valida 
        printf("\nData de entrada na empresa (00.00.0000): ");
        lerData(&funcionario->entrada_emp); //temos de fazer a verificação se a data e valida 
        
        //(uma biblio que indique a saida da empresa) &funcionario->saida_emp;
        //falta o numero de horas
        // 
        // aqui podemos adicionar um if do tipo: ainda se encontra na empresa?; se sim, continua, se nao, pergunta a data de saida
    }


    void calcSalarial (Funcionario *funcionario) {
        // temos de pedir e armazenar o mes
        // e para cada data verificar se é valida e se os 4 parametros somados não dao superiores ao numero de dias nesse mes
        printf("\nNumero de dias completos trabalhados: ");
        scanf("%d", &funcionario->dias_compl);
        printf("\nNumero de meios dias trabalhados: ");
        scanf("%d", &funcionario->dias_meios);
        printf("\nNumero de dias trabalhados ao fim de semana: ");
        scanf("%d", &funcionario->dias_fds);
        printf("\nNumero de dias faltados: ");
        scanf("%d", &funcionario->dias_faltas);
    }
