#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//Menus
void menu(){
    
    int opcao;

    do {
        printf("\n+ MENU +\n");
        printf("| 1) Carregar dados\n");
        printf("| 2) Guardar dados\n");
        printf("| 3) Gestão de funcionarios\n"); //criar menu para este 
        printf("| 4) Gestão das tabelas de descontos para o IRS\n");
        printf("| 5) Gestão das tabelas de descontos para a Segurança Social\n"); //menu para este tambem
        printf("| 6) Listagem 1\n");
        printf("| 7) Listagem 2\n");
        printf("| 8) Listagem 3\n");
        printf("| 9) Listagem 4\n");
        printf("| 10) Listagem 5\n");
        printf("| 0) Sair\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while ( opcao < 1 || opcao > 10);
    
    switch (opcao) { //foi criada uma função menu que retorna a opção do menu
        
        case 1:
            printf("f1");
            break;
        case 2:
            printf("f2");
            break;
        case 3:
            menu_gestao_funcionarios();
            break;
        case 4:
            menu_gestao_tabelas();
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
            printf("f8");
            break;
        case 9:
            printf("f9");
            break;
        case 10:
            printf("A aplicação foi terminada com sucesso");
            exit (0);
        default:
            printf("Opção Inválida"); // não é necessário devido ao "do {} while" acima
    }
}
void menu_gestao_funcionarios(){
    
    int opcao;

    do {
        printf("\n+ GESTÃO DE FUNCIONARIOS +\n");
        printf("| 1) Adicionar\n");
        printf("| 2) Editar\n");
        printf("| 3) Remover\n"); 
        printf("| 4) Voltar\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while ( opcao < 1 || opcao > 4);
    
    switch (opcao){
        case 1:
            add_funcionario();
            break;
        case 2:
            editar_funcionario();
            break;
        case 3:
            remover_funcionario();
            break;
        case 4:
            menu(); 
            break;
    }
}
void menu_gestao_tabelas(){
    
    int opcao;

    do {
        printf("\n+ GESTÃO DAS TABELAS DE DESCONTOS PARA A SEGURANÇA SOCIAL +\n");
        printf("| 1) Criar criterio\n");
        printf("| 2) Adicionar criterio\n");
        printf("| 3) Voltar\n"); 
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while ( opcao < 1 || opcao > 3);

    
    switch (opcao){
        case 1:
            criar_criterio();
            break;
        case 2:
            add_criterio();
            break;
        case 3:
            menu();    
            break;
    }
}

//Funções do menu dos funcionarios
void add_funcionario(){ printf("Add user");}
void remover_funcionario(){  printf("Remover user");}
void editar_funcionario(){ printf("Editar user");}

//Funções do menu das tabelas 
void add_criterio(){printf("Add Criterio");}
void criar_criterio(){printf("Criar criterio");}
