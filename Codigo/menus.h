#ifndef MENUS_H
#define MENUS_H

#define FORMATO_MENU_PRINCIPAL "+ MENU +\n| 1) Cálculo salarial\n| 2) Gestão de funcionarios\n| 3) Gestão das tabelas de descontos para o IRS\n| 4) Gestão das taxas da segurança social\n| 5) Listagens \n| 6) Guardar dados em memoria\n| 7) Apagar dados em memoria\n| 0) Sair\n| Opção: "
#define FORMATO_MENU_CALC_SALARIAL "\n+ CÁLCULO SALARIAL +\n| 1) Introduzir dados\n| 2) Ver salarios (por processar e processados)\n| 3) Fazer o calculo salarial \n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_CALCULO_SALARIAL "\n+ PROCESSAMENTO SALARIAL + \n| 1) Todos em memoria \n| 2) Salarios escolhidos por mes e ano \n| 0) Sair \n| Opção: "
#define FORMATO_MENU_MOSTRAR_SALARIOS "\n+ CÁLCULO SALARIAL +\n| 1) Ver todos os salarios por processar\n| 2) Ver todos os salarios processados \n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_ADD_SALARIOS "\n+ INTRODUZIR DADOS PARA O CALCULO SALARIAL +\n| 1) Manualmente\n| 2) Ficheiro\n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_TIPO_ADD_FUNCIONARIOS "\n+ ADICIONAR FUNCIONARIO +\n| 1) Manualmente\n| 2) Ficheiro\n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_GESTAO_FUNCIONARIOS "\n+ GESTÃO DE FUNCIONARIOS +\n| 1) Adicionar\n| 2) Editar\n| 3) Remover\n| 4) Ver todos\n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_GESTAO_TABELAS_IRS "\n+ GESTÃO DAS TABELAS DE DESCONTOS PARA O IRS +\n| 1) Alterar criterio\n| 2) Adicionar criterio\n| 3) Apagar criterio\n| 4) Mostrar tabelas\n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_GESTAO_SS "\n+ GESTÃO DAS TAXAS DA SEGURANÇA SOCIAL +\n| 1) Alterar criterio\n| 2) Mostrar todas as taxas\n| 3) Adicionar criterio\n| 4) Remover criterio\n| 0) Voltar\n| Opção: "
#define FORMATO_MENU_LISTAGENS "\n+ MENU LISTAGENS +\n| 1) Mostrar ex-funcionarios\n| 2) Total gasto pela empresa \n| 3) Total gasto pela empresa em impostos\n| 4) Mostrar funcionarios removidos\n| 5) Criar ficheiros\n| 0) Voltar\n| Opção: "


//MENUS
void menu(Empresa *arrayRH, Lista_calc *conta, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void menu_calc_salarial(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void menu_tipo_add_funcionarios( Empresa *arrayRH );
void menu_gestao_funcionarios(Empresa *arrayRH);
void menu_gestao_tabelas_IRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *array_tres);
void menu_gestao_SS(Tabela_SS *taxa );
void menu_listagens(Empresa *arrayRH, Lista_salarios *salarios, Lista_calc *conta);
void menu_mostrar_salarios(Lista_calc *conta, Lista_salarios *salarios);
void menu_add_salarios(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void menu_Calculo_salarial(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);

//MOSTRAR
void mostrarUsers(Empresa *arrayRH);

#endif
