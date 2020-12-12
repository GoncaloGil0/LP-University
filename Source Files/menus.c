#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
//#include "processar_info.h"


//VARIAVEIS APOIO
Funcionarios funcionarios = {.contador = 0};

//MENU PRINCIPAL
void menu() {

    int opcao;

    do {
        printf("\n+ MENU +\n");
        printf("| 1) Carregar dados\n");
        printf("| 2) Guardar dados\n");
        printf("| 3) Gestão de funcionarios\n"); 
        printf("| 4) Gestão das tabelas de descontos para o IRS\n");
        printf("| 5) Gestão das tabelas de descontos para a Segurança Social\n");
        printf("| 6) Listagem 1\n");
        printf("| 7) Listagem 2\n");
        printf("| 8) Listagem 3\n");
        printf("| 9) Listagem 4\n");
        printf("| 10) Listagem 5\n");
        printf("| 0) Sair\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 10);

    switch (opcao) {

        case 1:
            //printf("f1");
            break;
        case 2:
            //printf("f2");
            break;
        case 3:
            menu_gestao_funcionarios();
            break;
        case 4:
            menu_gestao_tabelas();
            break;
        case 5:
            menu_gestao_tabelas();
            break;
        case 6:
            //print_listagem();
            break;
        case 7:
            //print_listagem();
            break;
        case 8:
            //print_listagem();
            break;
        case 9:
            //print_listagem();
            break;
        case 10:
            //print_listagem();
        case 0:
            printf("A aplicação foi terminada com sucesso");
            exit(0);
        default:
            printf("Opção Inválida");
    }
}

//MENU FUNCIONARIOS
void menu_gestao_funcionarios() {

    int opcao;

    do {
        printf("\n+ GESTÃO DE FUNCIONARIOS +\n");
        printf("| 1) Adicionar\n");
        printf("| 2) Editar\n");
        printf("| 3) Remover\n");
        printf("| 0) Voltar\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 4);

    switch (opcao) {
        case 1:
            addFuncionarios( funcionarios );
            break;
        case 2:
            editarFuncionarios( &funcionarios );
            break;
        case 3:
            removerFucionarios(&funcionarios);
            break;
        case 0:
            menu();
            break;
    }
}

//MENU TABELAS
void menu_gestao_tabelas() {

    int opcao;

    do {
        printf("\n+ GESTÃO DAS TABELAS DE DESCONTOS PARA O IRS E SEGURANÇA SOCIAL +\n");
        printf("| 1) Criar criterio\n");
        printf("| 2) Adicionar criterio\n");
        printf("| 0) Voltar\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 3);


    switch (opcao) {
        case 1:
            //criar_criterio();
            break;
        case 2:
            //add_criterio();
            break;
        case 0:
            menu();
            break;
    }
}
