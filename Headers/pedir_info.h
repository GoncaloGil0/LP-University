// Codigo dedicado a todas as funções para pedir informação ao user 

#ifndef PEDIR_INFO_H
#define PEDIR_INFO_H

typedef enum {
    CASADO, SOLTEIRO, DIVORCIADO, VIUVO
} Est_Civil;

typedef enum {
    EMPREGADO, CHEFE, ADMINISTRADOR
} Cargo;
    
typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    int codigo, numero_tlm, numero_filhos;
    char nome[50];
    Est_Civil est_civil;
    Cargo cargo;
    float valor_hora, valor_sub_ali;
    Data nascimento, entrada_emp, saida_emp;
    //falta o numero de horas
    //integers para o processamento salarial
    int dias_compl, dias_meios, dias_fds, dias_faltas; 
} Funcionario;


void lerData (Data *data);
void lerFuncionario (Funcionario *funcionario);

#endif /* PEDIR_INFO_H */

