#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int menu(){
    
    int opcao;

    do {
        printf("\n+ MENU +\n");
        printf("| 1) Carregar dados\n");
        printf("| 2) Guardar dados\n");
        printf("| 3) Listgem 1\n");
        printf("| 4) Listgem 2\n");
        printf("| 5) Listgem 3\n");
        printf("| 6) Listgem 4\n");
        printf("| 7) Listgem 5\n");
        printf("| 8) Sair\n");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while ( opcao < 1 || opcao > 8);

    return (opcao);
    
}