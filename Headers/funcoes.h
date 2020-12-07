#ifndef FUNCOES_H
#define FUNCOES_H

//REGISTOS 
typedef struct data {
   int dia, mes, ano;
} Data;

typedef struct {
    //informação a guardar referente ao funcionario
    int codigo, numero_tlm, numero_filhos, valor_hora, valor_sub_alimentacao;
    char nome[20], estado_civil[15], cargo[15], data_nascimento[10], data_entrada_empresa[10], data_saida_empresa[10];
} Funcionario_info;

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
void add_funcionario();
void remover_funcionario();
void editar_funcionario();

//funções do menu das tabelas 
void add_criterio();
void criar_criterio();
#endif 

