#ifndef MENUS_H
#define MENUS_H

//REGISTOS

typedef struct{
    //Calculos 
    int vencimento_liquido;
    float vencimento_iliquido, encargo_total_empresa, iva, sub_alimentacao, bonus, ss_entidade_patronal, ss_entidade_pessoal;
} Calculo;

//funções

//Menus
void menu();
void menu_gestao_funcionarios();
void menu_gestao_tabelas();

//funções do menu dos funcionarios 
//void add_funcionario();
void remover_funcionario();
void editar_funcionario();

//funções do menu das tabelas 
void add_criterio();
void criar_criterio();

//funçao das listagens
void print_listagem();
    
#endif 

