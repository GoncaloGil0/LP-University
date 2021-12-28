/* 
 * @author Grupo 12
 * @file main.c 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

/**
 * Função principal do programa, inicializa todos os arrays de memoria, importa a informação da utilização anterior e abre os menus 
 */
int main() {
    
    //VARIAVEIS E MEMORIAS DINAMICAS 
    Empresa arrayRH;
    arrayRH.contador = 0;
    arrayRH.funcionarios_array = (Funcionario*) malloc (sizeof (Funcionario));
    if (arrayRH.funcionarios_array == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Lista_calc conta;
    conta.contador = 0;
    conta.dados_calculo_array = (Conta*) malloc (sizeof (Conta));
    if (conta.dados_calculo_array == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Tabelas dois_titulares;
    dois_titulares.contador = 0;
    dois_titulares.tabela = (IRS*) malloc (sizeof(IRS));
    if (dois_titulares.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Tabelas unico_titular;
    unico_titular.contador = 0;
    unico_titular.tabela = (IRS*) malloc (sizeof(IRS));
    if (unico_titular.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Tabelas nao_casado;
    nao_casado.contador = 0;
    nao_casado.tabela = (IRS*) malloc (sizeof(IRS));
    if (nao_casado.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Lista_salarios salarios;
    salarios.contador = 0;
    salarios.calculo_array = (Calculo*) malloc (sizeof(Calculo));
    if (salarios.calculo_array == NULL) {
        puts(ERRO_MEMORIA);
    }
    
    Tabela_SS taxa;
    taxa.contador = 0;
    taxa.taxa_array = (Taxas*) malloc (sizeof(Taxas));
    if (taxa.taxa_array == NULL) {
        puts(ERRO_MEMORIA);
    }
    

    printf("| INFORMAÇÕES DO SISTEMA: \n");
    printf("| Numero de users em memoria: %d \n", importar_users_sys(&arrayRH));
    printf("| Numero de salarios em memoria: %d \n", importar_salarios_sys(&conta));
    printf("| Numero de salarios processados em memoria: %d \n", importar_salarios_proc_sys(&salarios));
    printf("| Tabela IRS Dois Titulares: ");
    importarDoisTitulares(&dois_titulares);
    printf("| Tabela IRS Unico Titular: ");
    importarUnicoTitular(&unico_titular);
    printf("| Tabela IRS Nao Casado: ");
    importarNaoCasado(&nao_casado);
    printf("| Tabela Segurança Social: ");
    importarTablelaSS(&taxa);
    printf("\n");
      
    //CHAMAR MENU
    do {
        menu(&arrayRH, &conta, &taxa, &dois_titulares, &unico_titular, &nao_casado, &salarios);
    } while (obterResposta("\n+ Deseja continuar no programa [s/n]? ") == 1);

    if (obterResposta(QUESTAO_GUARDAR) == 1) {
        logs("SAIR E GUARDAR");
        guardar(&arrayRH, &conta, &dois_titulares, &unico_titular, &nao_casado, &taxa, &salarios); 
        printf(APLICACAO_TERMINADA);
    } else {
        logs("SAIR SEM GUARDAR");
        printf(APLICACAO_TERMINADA);
    }
    
    freeMemoria(&arrayRH, &conta, &salarios, &dois_titulares, &unico_titular, &nao_casado, &taxa);
    
    return (0);
}
