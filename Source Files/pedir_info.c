// Codigo dedicado a todas as funções para pedir informação ao user 

#include <stdio.h>
#include <stdlib.h>
#include "pedir_info.h"

    void lerData (Data *data) {
        scanf("%d.%d.%d", &data->dia,&data->mes,&data->ano);
    }
    
    void lerFuncionario (Funcionario *funcionario) {
        printf("\nCódigo: ");
        scanf("%d", &funcionario->codigo);
        printf("\nNome: ");
        scanf("%s", funcionario->nome);
        printf("\nNumero de telemovel: ");
        scanf("%d", &funcionario->numero_tlm);
        printf("\nEstado civil [0-Casado 1-Solteiro 2-Divorciado 3-Viúvo]: ");
        scanf("%d", &funcionario->est_civil);
        printf("\nNumero de filhos no agregado familiar: ");
        scanf("%d", &funcionario->numero_filhos);
        printf("\nCargo na empresa [0-Empregado 1-Chefe 2-Administrador]: ");
        scanf("%d", &funcionario->cargo);
        printf("\nSalário por hora: ");
        scanf("%f", &funcionario->valor_hora);
        printf("\nValor do subsídio de alimentação: ");
        scanf("%f", &funcionario->valor_sub_ali);
        printf("\nData de nascimento (00.00.0000): ");
        lerData(&funcionario->nascimento);
        printf("\nData de entrada na empresa (00.00.0000): ");
        lerData(&funcionario->entrada_emp);
        //(uma biblio que indique a saida da empresa) &funcionario->saida_emp;
        //falta o numero de horas
    }
