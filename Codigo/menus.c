/* 
 * Ficheiro que contem todas os menus do programa
 * @file menus.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

//MENU PRINCIPAL
/**
 * Menu principal que mostra as principais opçoes de funçoes do programa a haver com calculos salariais, funcionarios, gestao de tabelas, guardar e eliminar info, listagens ou sair do programa
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void menu(Empresa *arrayRH, Lista_calc *conta, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {

    switch (obterInt(0, 7, FORMATO_MENU_PRINCIPAL)) {

        case 1:
            menu_calc_salarial(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            break;
        case 2:
            menu_gestao_funcionarios(arrayRH);
            break;
        case 3:
            menu_gestao_tabelas_IRS(dois_titulares, unico_titular, nao_casado);
            break;
        case 4:
            menu_gestao_SS(taxa);
            break;
        case 5:
            menu_listagens(arrayRH, salarios, conta);
            break;
        case 6:
            logs("GUARDAR INFORMAÇÃO");
            puts("");
            guardar(arrayRH, conta, dois_titulares, unico_titular, nao_casado, taxa, salarios);
            break;
        case 7:
            limpar_memoria(arrayRH, conta, salarios);
            break;
        case 0:
            if (obterResposta(QUESTAO_GUARDAR) == 1) {
                logs("SAIR E GUARDAR");
                guardar(arrayRH, conta, dois_titulares, unico_titular, nao_casado, taxa, salarios);
                puts("");
            } else {
                logs("SAIR SEM GUARDAR");
            }
            freeMemoria(arrayRH, conta, salarios, dois_titulares, unico_titular, nao_casado, taxa);
            printf(APLICACAO_TERMINADA);
            exit(0);
    }
}

//MENU MANUAL OU FICHEIRO CALCULO SALARIAL
/**
 * Menu de calculo salarial, permite introduzir dados, ver os salarios ou fazer os processamentos
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void menu_calc_salarial(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {

    switch (obterInt(0, 3, FORMATO_MENU_CALC_SALARIAL)) {
        case 1:
            menu_add_salarios(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            break;
        case 2:
            menu_mostrar_salarios(conta, salarios);
            break;
        case 3:
            menu_Calculo_salarial(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            break;
        case 0:
            break;
    }
}

//MENU CALCULOS SALARIAIS
/**
 * Menu dos processamentos salariais permitindo fazer de todos os conjuntos de dados ou so de um certo mes
 * Pede qual açao prefere e indica "acao" 1 para todos os processamentos ou 0 para um ficheiro especifico
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void menu_Calculo_salarial(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {

    switch (obterInt(0, 2, FORMATO_MENU_CALCULO_SALARIAL)) {
        case 1:
            logs("PROCESSAMENTO SALARIAL (TODOS)");
            puts(TITULO_SALARIOS_PROC);
            processamento(salarios, arrayRH, conta, taxa, dois_titulares, unico_titular, nao_casado, 1);
            break;
        case 2:
            logs("PROCESSAMENTO SALARIAL (POR MES)");
            puts(TITULO_SALARIOS_PROC);
            processamento(salarios, arrayRH, conta, taxa, dois_titulares, unico_titular, nao_casado, 0);
            break;
        case 0:
            break;
    }
}

//MENU MOSTRAR SALARIOS
/**
 * Menu que permite visualizar os dados de salarios, tanto os por processar como os ja processados
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void menu_mostrar_salarios(Lista_calc *conta, Lista_salarios *salarios) {

    switch (obterInt(0, 2, FORMATO_MENU_MOSTRAR_SALARIOS)) {
        case 1:
            logs("MOSTRAR SALARIOS POR PROCESSAR");
            puts("\n+ SALARIOS POR PROCESSAR +");
            if (conta->contador == 0) {
                printf("\n+ Não existem salarios para processar +\n");
            } else {
                for (int x = 0; x < conta->contador; x++) {
                    if (conta->dados_calculo_array[x].estado != 1) {
                        printf(FORMATO_MOSTRAR_SALARIOS, conta->dados_calculo_array[x].codigo,
                                conta->dados_calculo_array[x].ano,
                                conta->dados_calculo_array[x].mes,
                                conta->dados_calculo_array[x].dias_compl,
                                conta->dados_calculo_array[x].dias_meios,
                                conta->dados_calculo_array[x].dias_fds,
                                conta->dados_calculo_array[x].dias_faltas,
                                estadoToString(conta->dados_calculo_array[x].estado));
                    }
                }
            }
            break;
        case 2:
            logs("MOSTRAR TODOS OS SALARIOS PROCESSADOS");
            puts("\n+ SALARIOS PROCESSADOS +");
            if (salarios->contador == 0) {
                puts("\n+ Nao existem salarios processados +");
            } else {
                for (int x = 0; x < salarios->contador; x++) {
                    printf(FORMATO_MOSTRAR_SALARIOS_TODOS,
                            salarios->calculo_array[x].codigo,
                            salarios->calculo_array[x].venc_iliquido,
                            salarios->calculo_array[x].bonus,
                            salarios->calculo_array[x].sub_ali,
                            salarios->calculo_array[x].ss_ent_patronal,
                            salarios->calculo_array[x].ss_ent_pessoal,
                            salarios->calculo_array[x].irs,
                            salarios->calculo_array[x].venc_liquido,
                            salarios->calculo_array[x].encargo_total_emp);
                }
            }
            break;
        case 0:
            break;
    }
}

//MENU ADICIONAR DADOS SALARIOS
/**
 * Menu que permite adicionar os dados para salarios ou por ficheiro ou manualmente por inputs
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void menu_add_salarios(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {

    switch (obterInt(0, 2, FORMATO_MENU_ADD_SALARIOS)) {
        case 1:
            logs("CALCULO SALARIAL (Manual)");
            puts("\n+ CALCULO SALARIAL +");
            verificacaoFuncionariosCalculo(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            break;
        case 2:
            logs("CALCULO SALARIAL (Ficheiro)");
            importar_salarios_doc(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            break;
        case 0:
            break;
    }
}

//MENU MANUAL OU FICHEIRO FUNCIONARIO
/**
 * Menu que permite adicionar os funcionarios ou por ficheiro ou manualmente por inputs
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void menu_tipo_add_funcionarios(Empresa *arrayRH) {

    switch (obterInt(0, 2, FORMATO_MENU_TIPO_ADD_FUNCIONARIOS)) {
        case 1:
            logs("ADICIONAR FUNCIONARIO (Manual)");
            puts("\n+ DADOS FUNCIONARIO +");
            verificacaoAddFuncionarios(arrayRH);
            break;
        case 2:
            logs("ADICIONAR FUNCIONARIO (Ficheiro)");
            importar_users_doc(arrayRH);
            break;
        case 0:
            break;
    }
}

//MENU FUNCIONARIOS MANUAL
/**
 * Menu de gestao dos funcionarios, mostrando as opçoes de adicionar, editar, remover ou ver todos em memoria
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void menu_gestao_funcionarios(Empresa *arrayRH) {

    switch (obterInt(0, 4, FORMATO_MENU_GESTAO_FUNCIONARIOS)) {
        case 1:
            menu_tipo_add_funcionarios(arrayRH);
            break;
        case 2:
            logs("EDITAR FUNCIONARIO ");
            puts("\n+ EDITAR FUNCIONARIO +");
            verificacaoEditarFuncionarios(arrayRH);
            break;
        case 3:
            logs("REMOVER FUNCIONARIO ");
            puts("\n+ REMOVER FUNCIONARIO +");
            removerFuncionario(arrayRH);
            break;
        case 4:
            logs("VER TODOS FUNCIONARIOS");
            puts("\n+ TODOS OS FUNCIONARIOS +");
            if (arrayRH->contador == 0) {
                puts("| + Não existem utilizadores +");
            } else {
                for (int x = 0; x != arrayRH->contador; x++) {
                    if (arrayRH->funcionarios_array[x].ativo == 1 && arrayRH->funcionarios_array[x].saida_emp.dia != 0) {
                        printf(FORMATO_MOSTRAR_USERS, arrayRH->funcionarios_array[x].codigo,
                                arrayRH->funcionarios_array[x].nome,
                                arrayRH->funcionarios_array[x].numero_tlm,
                                est_civilToString(arrayRH->funcionarios_array[x].est_civil),
                                arrayRH->funcionarios_array[x].titulares,
                                arrayRH->funcionarios_array[x].numero_filhos,
                                arrayRH->funcionarios_array[x].cargo,
                                arrayRH->funcionarios_array[x].valor_hora,
                                arrayRH->funcionarios_array[x].valor_sub_ali,
                                arrayRH->funcionarios_array[x].nascimento.dia,
                                arrayRH->funcionarios_array[x].nascimento.mes,
                                arrayRH->funcionarios_array[x].nascimento.ano,
                                arrayRH->funcionarios_array[x].entrada_emp.dia,
                                arrayRH->funcionarios_array[x].entrada_emp.mes,
                                arrayRH->funcionarios_array[x].entrada_emp.ano,
                                arrayRH->funcionarios_array[x].saida_emp.dia,
                                arrayRH->funcionarios_array[x].saida_emp.mes,
                                arrayRH->funcionarios_array[x].saida_emp.ano,
                                ativoToString(arrayRH->funcionarios_array[x].ativo));
                    } else {
                        printf(FORMATO_MOSTRAR_USERS_EMPRESA, arrayRH->funcionarios_array[x].codigo,
                                arrayRH->funcionarios_array[x].nome,
                                arrayRH->funcionarios_array[x].numero_tlm,
                                est_civilToString(arrayRH->funcionarios_array[x].est_civil),
                                arrayRH->funcionarios_array[x].titulares,
                                arrayRH->funcionarios_array[x].numero_filhos,
                                arrayRH->funcionarios_array[x].cargo,
                                arrayRH->funcionarios_array[x].valor_hora,
                                arrayRH->funcionarios_array[x].valor_sub_ali,
                                arrayRH->funcionarios_array[x].nascimento.dia,
                                arrayRH->funcionarios_array[x].nascimento.mes,
                                arrayRH->funcionarios_array[x].nascimento.ano,
                                arrayRH->funcionarios_array[x].entrada_emp.dia,
                                arrayRH->funcionarios_array[x].entrada_emp.mes,
                                arrayRH->funcionarios_array[x].entrada_emp.ano,
                                ativoToString(arrayRH->funcionarios_array[x].ativo));
                        
                    }
                }
            }
        case 0:
            break;
    }
}

//MENU TABELAS IRS
/**
 * Menu em relaçao às tabelas de IRS, para poder alterar, adicionar ou apagar criterios e mostrar tabelas
 * 
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void menu_gestao_tabelas_IRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {

    switch (obterInt(0, 4, FORMATO_MENU_GESTAO_TABELAS_IRS)) {
        case 1:
            logs("ALTERAR CRITERIO IRS");
            puts("\n+ ALTERAR CRITERIO +");
            alterarCriterioIRS(dois_titulares, unico_titular, nao_casado);
            break;
        case 2:
            logs("ADICIONAR CRITERIO IRS");
            puts("\n+ ADICIONAR CRITERIO +");
            addCriterioIRS(dois_titulares, unico_titular, nao_casado);
            break;
        case 3:
            logs("APAGAR CRITERIO IRS");
            puts("\n+ APAGAR CRITERIO +");
            apagarCriterioIRS(dois_titulares, unico_titular, nao_casado);
            break;
        case 4:
            logs("MOSTRAR TABELAS IRS");
            puts("\n+ MOSTRAR TABELAS +");
            mostrarTabelas(dois_titulares, unico_titular, nao_casado);
            break;
        case 0:
            break;
    }
}

//MENU TAXAS SS
/**
 * Mdenu de opçoes em relaçao às taxas de SS, permitindo alterar, adicionar ou remover valores ou mostrar todos
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void menu_gestao_SS(Tabela_SS *taxa) {

    switch (obterInt(0, 4, FORMATO_MENU_GESTAO_SS)) {
        case 1:
            logs("ALTERAR CRITERIO SS");
            puts("\n+ ALTERAR CRITERIO +");
            alterarCriterioSS(taxa);
            break;
        case 2:
            logs("MOSTRAR TODAS AS TAXAS SS");
            puts("\n+ MOSTRAR TODAS AS TAXAS +");
            mostrarSS(taxa);
            break;
        case 3:
            logs("ADICIONAR CRITERIO SS");
            puts("\n+ ADICIONAR CRITERIO +");
            addCriterioSS(taxa);
            break;
        case 4:
            logs("REMOVER CRITERIO SS");
            puts("\n+ REMOVER CRITERIO +");
            removerCriterioSS(taxa);
            break;
        case 0:
            break;
    }
}

//MENU LISTAGENS
/**
 * Menu sobre as listagens
 * 1 - mostra funcionários que ja sairam da empresa, ou seja com data de saída de valores diferentes de 0
 * 2 - mostra somatório de todos os encargos da empresa nos salários processados
 * 3 - mostra somatório de todos os descontos para a SS que a empresa pagou nos salários processados
 * 4 - mostra funcionarios removidos, ou seja em que ativo se encontra a 0
 * 5 - cria ficheiros de texto para o utilizador saber toda a informaçao guardada em memoria
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 * @param conta tem o array de memoria dos dados salariais
 */
void menu_listagens(Empresa *arrayRH, Lista_salarios *salarios, Lista_calc *conta) {
    float soma = 0, n = 0;

    switch (obterInt(0, 5, FORMATO_MENU_LISTAGENS)) {
        case 1:
            logs("LISTAGEM DE EX FUNCIONARIOS");
            if (arrayRH->contador == 0) {
                puts("| Não foram adicionados funcionarios");
            } else {
                printf("\n+ LISTAGEM DE EX FUNCIONARIOS +");
                for (int i = 0; i < arrayRH->contador; i++) {
                    if (arrayRH->funcionarios_array[i].saida_emp.ano != 0) {
                        printf("\n| Código %d ", arrayRH->funcionarios_array[i].codigo);
                    }
                    n++;
                }
            }
            if (n == 0) {
                puts("\n+ Não exitem funcionarios fora da empresa");
            }
            break;
        case 2:
            logs("TOTAL GASTO PELA EMPRESA");
            if (salarios->contador == 0) {
                puts("| Não foram processados salarios");
            } else {
                for (int x = 0; x < salarios->contador; x++) {
                    soma = soma + salarios->calculo_array[x].encargo_total_emp;
                }
                printf("\n+ GASTO PELA EMPRESA: %0.2f +", soma);
            }
            break;
        case 3:
            logs("TOTAL GASTO PELA EMPRESA EM IMPOSTOS");
            if (salarios->contador == 0) {
                puts("| Não foram processados salarios");
            } else {
                for (int x = 0; x < salarios->contador; x++) {
                    soma = soma + salarios->calculo_array[x].ss_ent_patronal;
                }
                printf("\n+ GASTO PELA EMPRESA EM IMPOSTOS: %0.2f +", soma);
            }
            break;
        case 4:
            logs("LISTAGEM DE FUNCIONARIOS REMOVIDOS");
            if (arrayRH->contador == 0) {
                puts("| Não foram adicionados funcionarios");
            } else {
                printf("\n+ LISTAGEM DE FUNCIONARIOS REMOVIDOS +");
                for (int i = 0; i < arrayRH->contador; i++) {
                    if (arrayRH->funcionarios_array[i].ativo == 0) {
                        printf("\n| Código %d ", arrayRH->funcionarios_array[i].codigo);
                        n++;
                    }
                }
            }
            if (n == 0) {
                puts("\n| Não existem funcionarios removidos");
            }
            break;
        case 5:
            criarFicheirosUser(arrayRH, conta, salarios);
            break;
        case 0:
            break;
    }
}
