/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Sofia
 *
 * Created on 08 November 2020, 19:11
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int cifra, i;
    char nome[10];
    printf("diga o seu nome: ");
    scanf("%s", nome);
    printf("diga o ultimo digito do seu aniversario: ");
    scanf("%d", &cifra);
    printf("o seu nome na verdade é: ");
    for ( i=0 ; nome[i]!='\0' ; i++) {
        if ( nome[i]>=97 && nome[i]<=122) {
            if ( nome[i]+cifra>122) {
                nome[i]-=26;
            }
        }
        else {
            if ( nome[i]+cifra>90) {
                nome[i]-=26;
            }
        }
        printf("%c", nome[i]+cifra);
    }
    
    return (EXIT_SUCCESS);
}

