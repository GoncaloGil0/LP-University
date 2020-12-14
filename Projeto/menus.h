#ifndef MENUS_H
#define MENUS_H


//REGISTOS

//CALCULO
typedef struct{ 
    int venc_liquido;
    float venc_iliquido, encargo_total_emp, iva, sub_ali, bonus, ss_ent_patronal, ss_ent_pessoal;
} Calculo;


//FUNÇOES

//MENUS
void menu();
void menu_gestao_funcionarios();
void menu_gestao_tabelas();
void menu_listagens();

//MENU FUNCIONARIOS 
void add_funcionario();
//void remover_funcionario(); //esta no pedir info
//void editar_funcionario(); //esta no pedir info

//MENU TABELAS 
//void add_criterio();
//void criar_criterio();

//LISTAGENS
//void print_listagem();
    
#endif
