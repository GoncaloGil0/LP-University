/* 
 * Ficheiro que contem todas as funções necessarias para o processamento salarial
 * @file processar_info.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

//SABER TAXA DA SS
/**
 * Encontra o valor correto das deduçoes para SS para aplicar no processamento dependendo do cargo
 * 
 * @param entidade para que se precisa do valor de SS
 * @param codigo do funcionario
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @return o valor de SS correspondente à entidade e ao cargo
 */
float saberSS(int entidade, int codigo, Empresa *arrayRH, Tabela_SS *taxa) {
    int posicao_taxa = posicaoTaxa(arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].cargo, taxa);
    
    if (posicao_taxa == -1 && entidade == 0){
        return (taxa->taxa_array[0].empregadora);
    } else if (posicao_taxa != -1 && entidade == 0) {
        return (taxa->taxa_array[posicao_taxa].empregadora);
    } else if (posicao_taxa == -1 && entidade == 1){
        return (taxa->taxa_array[0].trabalhador);
    } else if (posicao_taxa != -1 && entidade == 1) {
        return (taxa->taxa_array[posicao_taxa].trabalhador);
    } else {
        puts("ERRO");
    }
        
}

//SABER TAXA DO IRS
/**
 * Encontra o valor correto da taxa de IRS para aplicar no processamento
 * 
 * @param vencimento o salario liquido do funcionario
 * @param codigo do funcionario
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @return o valor da taxa de IRS correspondente ao vencimento
 */
float saberIRS(int vencimento, int codigo, Empresa *arrayRH, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int posicao = procurarFuncionario(arrayRH, codigo);

    if (arrayRH->funcionarios_array[posicao].titulares == 1) { //unico titular
        for (int i = 0; i < unico_titular->contador; i++) {
            if ((unico_titular->tabela[i].vencimento < vencimento && vencimento < unico_titular->tabela[i + 1].vencimento) || vencimento == unico_titular->tabela[i + 1].vencimento) {

                switch (arrayRH->funcionarios_array[posicao].numero_filhos) {
                    case 0:
                        return (unico_titular->tabela[i+1].filho_zero);
                        break;
                    case 1:
                        return (unico_titular->tabela[i+1].filho_um);
                        break;
                    case 2:
                        return (unico_titular->tabela[i+1].filho_dois);
                        break;
                    case 3:
                        return (unico_titular->tabela[i+1].filho_tres);
                        break;
                    case 4:
                        return (unico_titular->tabela[i+1].filho_quatro);
                        break;
                    default:
                        return (unico_titular->tabela[i+1].filho_cinco);
                        break;
                }
                break;
            }
        }
    } else if (arrayRH->funcionarios_array[posicao].titulares == 2) { //dois titulares

        for (int i = 0; i < dois_titulares->contador; i++) {

            if ((dois_titulares->tabela[i].vencimento < vencimento && vencimento < dois_titulares->tabela[i + 1].vencimento) || vencimento == dois_titulares->tabela[i + 1].vencimento) {

                switch (arrayRH->funcionarios_array[posicao].numero_filhos) {
                    case 0:
                        return (dois_titulares->tabela[i+1].filho_zero);
                        break;
                    case 1:
                        return (dois_titulares->tabela[i+1].filho_um);
                        break;
                    case 2:
                        return (dois_titulares->tabela[i+1].filho_dois);
                        break;
                    case 3:
                        return (dois_titulares->tabela[i+1].filho_tres);
                        break;
                    case 4:
                        return (dois_titulares->tabela[i+1].filho_quatro);
                        break;
                    default:
                        return (dois_titulares->tabela[i+1].filho_cinco);
                        break;
                }
            }
        }
    } else { //nao casado
        for (int i = 0; i < nao_casado->contador; i++) {

            if ((nao_casado->tabela[i].vencimento < vencimento && vencimento < nao_casado->tabela[i + 1].vencimento) || vencimento == nao_casado->tabela[i + 1].vencimento) {

                switch (arrayRH->funcionarios_array[posicao].numero_filhos) {
                    case 0:
                        return (nao_casado->tabela[i+1].filho_zero);
                        break;
                    case 1:
                        return (nao_casado->tabela[i+1].filho_um);
                        break;
                    case 2:
                        return (nao_casado->tabela[i+1].filho_dois);
                        break;
                    case 3:
                        return (nao_casado->tabela[i+1].filho_tres);
                        break;
                    case 4:
                        return (nao_casado->tabela[i+1].filho_quatro);
                        break;
                    default:
                        return (nao_casado->tabela[i+1].filho_cinco);
                        break;
                }
            }
        }
    }
}

//FAZER O CALCULO SALARIAL
/**
 * Processamento dos dados salariais
 * Guarda-los no array de memoria 
 * Adiciona o relatório sobre cada salário processado ao documento dos relatórios
 * 
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param dados_salarios tem o array de memoria dos dados salariais
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param acao valor para processamento por certo mes (0) ou todos (1)
 */
void processamento(Lista_salarios *salarios, Empresa *arrayRH, Lista_calc *dados_salarios, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, int acao) {
    //APONTADORES
    FILE *ficheiro_relatorios;

    //VARIAVEIS
    int n = 0, x, posicaoFunc, horasTrabalhadas, ano, mes;
    float ValordiasCompletos, ValordiasMeios, ValordiasFds, ValordiasCompletosAlm, ValordiaFdsAlm, ValoralimetacaoTotal, vencimentoIliquido, irs, SS_func, SS_emp, bonus, vencimentoLiquido;
    switch (acao){
        case 1: //vai processar todos
            for (x = 0; x != dados_salarios->contador; x++) {
                if (dados_salarios->dados_calculo_array[x].estado == 0 && procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo) != -1 && arrayRH->funcionarios_array[procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo)].ativo == 1) {

                    //SABER A POSIÇÃO DO FUNCIONARIO NA LISTA
                    posicaoFunc = procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo);

                    //CALCULO DAS HORAS TOTAIS TRABALHADAS
                    horasTrabalhadas = ((8 * dados_salarios->dados_calculo_array[x].dias_compl)+(4 * dados_salarios->dados_calculo_array[x].dias_meios)+(8 * dados_salarios->dados_calculo_array[x].dias_fds));

                    //CALCULAR VENCIMENTO ILIQUIDO
                    ValordiasCompletos = arrayRH->funcionarios_array[posicaoFunc].valor_hora * (8 * dados_salarios->dados_calculo_array[x].dias_compl);
                    ValordiasMeios = arrayRH->funcionarios_array[posicaoFunc].valor_hora * (4 * dados_salarios->dados_calculo_array[x].dias_meios);
                    ValordiasFds = (arrayRH->funcionarios_array[posicaoFunc].valor_hora * 1.5) * (8 * dados_salarios->dados_calculo_array[x].dias_fds);

                    ValordiasCompletosAlm = arrayRH->funcionarios_array[posicaoFunc].valor_sub_ali * dados_salarios->dados_calculo_array[x].dias_compl;
                    ValordiaFdsAlm = (arrayRH->funcionarios_array[posicaoFunc].valor_sub_ali * 1.5) * dados_salarios->dados_calculo_array[x].dias_fds;

                    ValoralimetacaoTotal = ValordiasCompletosAlm + ValordiaFdsAlm;
                    vencimentoIliquido = ValordiasCompletos + ValordiasMeios + ValordiasFds;
                    bonus = vencimentoIliquido * saberBonus(arrayRH, dados_salarios, posicaoFunc, saberDiaMax(dados_salarios->dados_calculo_array[x].ano, dados_salarios->dados_calculo_array[x].mes), x);
                    vencimentoIliquido = vencimentoIliquido + bonus;

                    //CALCULO DO IRS E SS
                    SS_func = (vencimentoIliquido * saberSS(1, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, taxa)) / 100;
                    SS_emp = (vencimentoIliquido * saberSS(0, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, taxa)) / 100;
                    irs = vencimentoIliquido * saberIRS(vencimentoIliquido, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, dois_titulares, unico_titular, nao_casado);

                    vencimentoLiquido = (vencimentoIliquido + ValoralimetacaoTotal) - (SS_func + irs);

                    //GUARDAR EM MEMORIA
                    salarios->calculo_array[salarios->contador].codigo = arrayRH->funcionarios_array[posicaoFunc].codigo;
                    salarios->calculo_array[salarios->contador].irs = irs;
                    salarios->calculo_array[salarios->contador].ss_ent_patronal = SS_emp;
                    salarios->calculo_array[salarios->contador].ss_ent_pessoal = SS_func;
                    salarios->calculo_array[salarios->contador].sub_ali = ValoralimetacaoTotal;
                    salarios->calculo_array[salarios->contador].venc_iliquido = vencimentoIliquido;
                    salarios->calculo_array[salarios->contador].venc_liquido = vencimentoLiquido;
                    salarios->calculo_array[salarios->contador].bonus = bonus;
                    salarios->calculo_array[salarios->contador].encargo_total_emp = vencimentoIliquido + SS_emp;

                    //PASSA O "PROCESSADO" PARA "1" (OU SEJA, JA ESTA PROCESSADO)
                    dados_salarios->dados_calculo_array[x].estado = 1;

                    //ADICIONA RELATORIO DOC
                    ficheiro_relatorios = fopen(FILENAME_RELATORIOS, "a");
                    if (ficheiro_relatorios == NULL) {
                        puts(ERRO_FILE);
                    } else {
                        fprintf(ficheiro_relatorios, FORMATO_GUARDAR_DOC_SALARIOS,
                                arrayRH->funcionarios_array[posicaoFunc].nome,
                                salarios->calculo_array[salarios->contador].codigo,
                                dados_salarios->dados_calculo_array[x].mes,
                                dados_salarios->dados_calculo_array[x].ano,
                                salarios->calculo_array[salarios->contador].venc_iliquido,
                                salarios->calculo_array[salarios->contador].bonus,
                                salarios->calculo_array[salarios->contador].sub_ali,
                                salarios->calculo_array[salarios->contador].ss_ent_patronal,
                                salarios->calculo_array[salarios->contador].ss_ent_pessoal,
                                salarios->calculo_array[salarios->contador].irs,
                                salarios->calculo_array[salarios->contador].venc_liquido,
                                salarios->calculo_array[salarios->contador].encargo_total_emp);
                    }
                    fclose(ficheiro_relatorios);

                    //ADICIONA AO CONTADOR
                    salarios->contador++;

                    //ADICIONA MEMORIA PARA O PROXIMO CALCULO
                    addMemoriaProcess(salarios);

                    //ADICIONA NA CONTAGEM DE ELEMENTOS LIDOS
                    n++;
                }
            }
            break;
        case 0: //vai procesar pelos anos
            ano = saberAno("| Digite o ano a processar: ");
            mes = saberMes("| Digite o mes a processar: ", ano);
            for (x = 0; x != dados_salarios->contador; x++) {
                if (dados_salarios->dados_calculo_array[x].estado == 0 && procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo) != -1 && arrayRH->funcionarios_array[procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo)].ativo == 1 && dados_salarios->dados_calculo_array[x].ano == ano && dados_salarios->dados_calculo_array[x].mes == mes ) {

                    //SABER A POSIÇÃO DO FUNCIONARIO NA LISTA
                    posicaoFunc = procurarFuncionario(arrayRH, dados_salarios->dados_calculo_array[x].codigo);

                    //CALCULO DAS HORAS TOTAIS TRABALHADAS
                    horasTrabalhadas = ((8 * dados_salarios->dados_calculo_array[x].dias_compl)+(4 * dados_salarios->dados_calculo_array[x].dias_meios)+(8 * dados_salarios->dados_calculo_array[x].dias_fds));

                    //CALCULAR VENCIMENTO ILIQUIDO
                    ValordiasCompletos = arrayRH->funcionarios_array[posicaoFunc].valor_hora * (8 * dados_salarios->dados_calculo_array[x].dias_compl);
                    ValordiasMeios = arrayRH->funcionarios_array[posicaoFunc].valor_hora * (4 * dados_salarios->dados_calculo_array[x].dias_meios);
                    ValordiasFds = (arrayRH->funcionarios_array[posicaoFunc].valor_hora * 1.5) * (8 * dados_salarios->dados_calculo_array[x].dias_fds);

                    ValordiasCompletosAlm = arrayRH->funcionarios_array[posicaoFunc].valor_sub_ali * dados_salarios->dados_calculo_array[x].dias_compl;
                    ValordiaFdsAlm = (arrayRH->funcionarios_array[posicaoFunc].valor_sub_ali * 1.5) * dados_salarios->dados_calculo_array[x].dias_fds;

                    ValoralimetacaoTotal = ValordiasCompletosAlm + ValordiaFdsAlm;
                    vencimentoIliquido = ValordiasCompletos + ValordiasMeios + ValordiasFds;
                    bonus = vencimentoIliquido * saberBonus(arrayRH, dados_salarios, posicaoFunc, saberDiaMax(dados_salarios->dados_calculo_array[x].ano, dados_salarios->dados_calculo_array[x].mes), x);
                    vencimentoIliquido = vencimentoIliquido + bonus;

                    //CALCULO DO IRS E SS
                    SS_func = (vencimentoIliquido * saberSS(1, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, taxa)) / 100;
                    SS_emp = (vencimentoIliquido * saberSS(0, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, taxa)) / 100;
                    irs = vencimentoIliquido * saberIRS(vencimentoIliquido, arrayRH->funcionarios_array[posicaoFunc].codigo, arrayRH, dois_titulares, unico_titular, nao_casado);

                    vencimentoLiquido = (vencimentoIliquido + ValoralimetacaoTotal) - (SS_func + irs);

                    //GUARDAR EM MEMORIA
                    salarios->calculo_array[salarios->contador].codigo = arrayRH->funcionarios_array[posicaoFunc].codigo;
                    salarios->calculo_array[salarios->contador].irs = irs;
                    salarios->calculo_array[salarios->contador].ss_ent_patronal = SS_emp;
                    salarios->calculo_array[salarios->contador].ss_ent_pessoal = SS_func;
                    salarios->calculo_array[salarios->contador].sub_ali = ValoralimetacaoTotal;
                    salarios->calculo_array[salarios->contador].venc_iliquido = vencimentoIliquido;
                    salarios->calculo_array[salarios->contador].venc_liquido = vencimentoLiquido;
                    salarios->calculo_array[salarios->contador].bonus = bonus;
                    salarios->calculo_array[salarios->contador].encargo_total_emp = vencimentoIliquido + SS_emp;

                    //PASSA O "PROCESSADO" PARA "1" (OU SEJA, JA ESTA PROCESSADO)
                    dados_salarios->dados_calculo_array[x].estado = 1;

                    //ADICIONA RELATORIO DOC
                    ficheiro_relatorios = fopen(FILENAME_RELATORIOS, "a");
                    if (ficheiro_relatorios == NULL) {
                        puts(ERRO_FILE);
                    } else {
                        fprintf(ficheiro_relatorios, FORMATO_GUARDAR_DOC_SALARIOS,
                                arrayRH->funcionarios_array[posicaoFunc].nome,
                                salarios->calculo_array[salarios->contador].codigo,
                                dados_salarios->dados_calculo_array[x].mes,
                                dados_salarios->dados_calculo_array[x].ano,
                                salarios->calculo_array[salarios->contador].venc_iliquido,
                                salarios->calculo_array[salarios->contador].bonus,
                                salarios->calculo_array[salarios->contador].sub_ali,
                                salarios->calculo_array[salarios->contador].ss_ent_patronal,
                                salarios->calculo_array[salarios->contador].ss_ent_pessoal,
                                salarios->calculo_array[salarios->contador].irs,
                                salarios->calculo_array[salarios->contador].venc_liquido,
                                salarios->calculo_array[salarios->contador].encargo_total_emp);
                    }
                    fclose(ficheiro_relatorios);

                    //ADICIONA AO CONTADOR
                    salarios->contador++;

                    //ADICIONA MEMORIA PARA O PROXIMO CALCULO
                    addMemoriaProcess(salarios);

                    //ADICIONA NA CONTAGEM DE ELEMENTOS LIDOS
                    n++;
                }
            }
            break;
        default:
            puts("ERRO");
            break;
    }
    
    if (n > 0) {
        if (n == 1) {
            printf("| Foi processado 1 salario \n");
        } else if (n > 1) {
            printf(INFO_SALARIOS_PROC, n);
        }
        
        if (obterResposta(PERGUNTA_VER_SALARIOS) == 1) {

            for (int x = 0; x < n; x++) {
                printf(FORMATO_MOSTRAR_SALARIOS_TODOS,
                        salarios->calculo_array[(salarios->contador - n) + x].codigo,
                        salarios->calculo_array[(salarios->contador - n) + x].venc_iliquido,
                        salarios->calculo_array[(salarios->contador - n) + x].bonus,
                        salarios->calculo_array[(salarios->contador - n) + x].sub_ali,
                        salarios->calculo_array[(salarios->contador - n) + x].ss_ent_patronal,
                        salarios->calculo_array[(salarios->contador - n) + x].ss_ent_pessoal,
                        salarios->calculo_array[(salarios->contador - n) + x].irs,
                        salarios->calculo_array[(salarios->contador - n) + x].venc_liquido,
                        salarios->calculo_array[(salarios->contador - n) + x].encargo_total_emp);
            }
        }
    } else if (n == 0) {
        printf(ERRO_NAO_SALARIOS);
    }
}

//FAZER CALCULO DO BONUS
/**
 * Calcula a percentagem de bonus para o salario a ser processado
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param posicao index do funcionario no array de memoria
 * @param dia_max numero maximo de dias que o mes pode ter
 * @param x quantos processamentos ja foram realizados
 * @return percentagem do bonus
 */
float saberBonus(Empresa *arrayRH, Lista_calc *conta, int posicao, int dia_max, int x) {
    float tempo, idade, dias, bonus;
    int dias_trab = conta->dados_calculo_array[x].dias_compl + conta->dados_calculo_array[x].dias_fds + conta->dados_calculo_array[x].dias_meios;

    tempo = 0.53 * (defineData(3) - arrayRH->funcionarios_array[posicao].entrada_emp.ano);
    idade = 0.26 * ((defineData(3) - arrayRH->funcionarios_array[posicao].nascimento.ano) - 18);
    if (dias_trab <= 22) {
        dias = 0;
    } else {
        dias = (12.5 / (dia_max - 22)) * (dias_trab - 22);
    }
    bonus = (tempo + idade + dias) / 100;
    return bonus;
}

