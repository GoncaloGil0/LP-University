/* 
 * Ficheiro que contem todas as funções relacionadas com o uso de ficheiros
 * @file ficheiros.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

//IMPORTAR USERS DOCUMENTO DO SISTEMA
/**
 * Importa para a memória todos os utilizadores do ficheiro 
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @return numero de funcionarios inseridos
 */
int importar_users_sys(Empresa *arrayRH) {
    int n = 0;
    FILE *ficheiro_users;

    ficheiro_users = fopen(FILENAME_USERS, "rb");
    if (ficheiro_users == NULL) {
        return (0);
    } else {
        while (fread(&arrayRH->funcionarios_array[arrayRH->contador], sizeof (Funcionario), 1, ficheiro_users)) {
            arrayRH->contador++;
            n++;
            addMemoriaFunc(arrayRH);
        }
    }

    fclose(ficheiro_users);
    return (n);
}

//IMPORTAR SALARIOS PROCESSADOS DOCUMENTO DO SISTEMA
/**
 * Importa para a memória todos os salarios ja processados do ficheiro 
 * 
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 * @return numero de processamentos inseridos
 */
int importar_salarios_proc_sys(Lista_salarios *salarios) {
    int n = 0;
    FILE *ficheiro_salarios_proc;

    ficheiro_salarios_proc = fopen(FILENAME_SALARIOS_PROCESSADOS, "rb");
    if (ficheiro_salarios_proc == NULL) {
        return (0);
    } else {
        while (fread(&salarios->calculo_array[salarios->contador], sizeof (Calculo), 1, ficheiro_salarios_proc)) {
            salarios->contador++;
            n++;
            addMemoriaProcess(salarios);
        }
    }

    fclose(ficheiro_salarios_proc);
    return (n);
}

//IMPORTAR SALARIOS DOCUMENTO DO SISTEMA
/**
 * Importa para a memória todos os dados salariais do ficheiro 
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @return numero de dados salariais inseridos
 */
int importar_salarios_sys(Lista_calc *conta) {
    int n;

    Conta *temp;
    FILE *ficheiro_salarios;

    ficheiro_salarios = fopen(FILENAME_SALARIOS, "rb");
    if (ficheiro_salarios == NULL) {
        return (0);
    } else {
        while (fread(&conta->dados_calculo_array[conta->contador], sizeof (Conta), 1, ficheiro_salarios)) {
            conta->contador++;
            n++;
            addMemoriaDadosCalc(conta);
        }
    }
    fclose(ficheiro_salarios);
    return (n);
}

//IMPORTAR USERS DOCUMENTO DO UTILIZADOR
/**
 * Le e guarda a informacao de funcionarios do ficheiro de texto do utilizador
 * Mostra esses funcionarios adicionados
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void importar_users_doc(Empresa *arrayRH) {
    int n = 0, i, existente = 0;
    char buffer[250];

    Funcionario *temp;
    FILE *ficheiro_users;

    ficheiro_users = fopen(FILENAME_USERS_DOC, "r");
    if (ficheiro_users == NULL) {
        puts(ERRO_FILE);
    } else {
        while (fgets(buffer, sizeof (buffer), ficheiro_users)) {
            sscanf(buffer, FORMATO_USERS, &arrayRH->funcionarios_array[arrayRH->contador].codigo,
                    arrayRH->funcionarios_array[arrayRH->contador].nome,
                    &arrayRH->funcionarios_array[arrayRH->contador].numero_tlm,
                    &arrayRH->funcionarios_array[arrayRH->contador].est_civil,
                    &arrayRH->funcionarios_array[arrayRH->contador].titulares,
                    &arrayRH->funcionarios_array[arrayRH->contador].numero_filhos,
                    arrayRH->funcionarios_array[arrayRH->contador].cargo,
                    &arrayRH->funcionarios_array[arrayRH->contador].valor_hora,
                    &arrayRH->funcionarios_array[arrayRH->contador].valor_sub_ali,
                    &arrayRH->funcionarios_array[arrayRH->contador].nascimento.dia,
                    &arrayRH->funcionarios_array[arrayRH->contador].nascimento.mes,
                    &arrayRH->funcionarios_array[arrayRH->contador].nascimento.ano,
                    &arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.dia,
                    &arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.mes,
                    &arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.ano,
                    &arrayRH->funcionarios_array[arrayRH->contador].saida_emp.dia,
                    &arrayRH->funcionarios_array[arrayRH->contador].saida_emp.mes,
                    &arrayRH->funcionarios_array[arrayRH->contador].saida_emp.ano,
                    &arrayRH->funcionarios_array[arrayRH->contador].ativo);

            if (procurarFuncionario(arrayRH, arrayRH->funcionarios_array[arrayRH->contador].codigo) != -1) {
                arrayRH->funcionarios_array[arrayRH->contador].ativo = -1;
                existente++;
            }
            arrayRH->contador++;
            n++;
            addMemoriaFunc(arrayRH);
        }
        fclose(ficheiro_users);

        if (existente != 0) {
            printf("|\n| Foram adicionados %d funcionarios, mas %d ja existem e nao foram aceites \n", n, existente);
        } else {
            printf("|\n| Foram adicionados %d funcionarios \n", n);
        }

        if (obterResposta(PERGUNTA_INFO_GUARDADA) == 1) {

            for (int i = 0; i < n; i++) {
                printf(FORMATO_MOSTRAR_USERS, arrayRH->funcionarios_array[(arrayRH->contador - n) + i].codigo,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].nome,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].numero_tlm,
                        est_civilToString(arrayRH->funcionarios_array[(arrayRH->contador - n) + i].est_civil),
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].titulares,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].numero_filhos,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].cargo,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].valor_hora,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].valor_sub_ali,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].nascimento.dia,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].nascimento.mes,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].nascimento.ano,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].entrada_emp.dia,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].entrada_emp.mes,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].entrada_emp.ano,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].saida_emp.dia,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].saida_emp.mes,
                        arrayRH->funcionarios_array[(arrayRH->contador - n) + i].saida_emp.ano,
                        ativoToString(arrayRH->funcionarios_array[(arrayRH->contador - n) + i].ativo));
            }
        }
    }
}

//IMPORTAR SALARIOS DOCUMENTO DO UTILIZADOR
/**
 * Le e guarda a informacao de salarios do ficheiro de texto escolhido pelo utilizador
 * Mostra esses salarios adicionados
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void importar_salarios_doc(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {
    int n = 0, porAdd = 0, atencao = 0;
    char buffer[250];

    FILE *ficheiro_salarios;
    
    char filename[50], filename_final[100];

    do {
        obterString(filename, sizeof(filename), "| Digite o nome do documento a importar: ");
        strcpy(filename_final, FILENAME_SALARIOS_DOC);
        strcat(filename_final, filename);
        strcat(filename_final, ".txt");
        ficheiro_salarios = fopen(filename_final, "r");
        if (ficheiro_salarios == NULL) {
            puts(ERRO_FILE);
        } else {
            while (fgets(buffer, sizeof (buffer), ficheiro_salarios)) {
                sscanf(buffer, FORMATO_SALARIOS, &conta->dados_calculo_array[conta->contador].codigo,
                        &conta->dados_calculo_array[conta->contador].ano,
                        &conta->dados_calculo_array[conta->contador].mes,
                        &conta->dados_calculo_array[conta->contador].dias_compl,
                        &conta->dados_calculo_array[conta->contador].dias_meios,
                        &conta->dados_calculo_array[conta->contador].dias_fds,
                        &conta->dados_calculo_array[conta->contador].dias_faltas);
                if (procurarFuncionario(arrayRH, conta->dados_calculo_array[conta->contador].codigo) == -1) {
                    porAdd++;
                }
                if (verificacaoDiasDoc(conta->dados_calculo_array[conta->contador].dias_compl, conta->dados_calculo_array[conta->contador].dias_meios, conta->dados_calculo_array[conta->contador].dias_fds, conta->dados_calculo_array[conta->contador].dias_faltas, conta->dados_calculo_array[conta->contador].mes, conta->dados_calculo_array[conta->contador].ano) == 1) {
                    conta->dados_calculo_array[conta->contador].estado = -1;
                    atencao++;
                } else {
                    conta->dados_calculo_array[conta->contador].estado = 0;
                }
                (conta->contador)++;
                n++;
                addMemoriaDadosCalc(conta);
            }
            fclose(ficheiro_salarios);

            if (atencao == 0 && n != 0) {
                printf("|\n| Foram adicionados %d salarios \n", n);
            } else if (atencao != 0) {
                printf("|\n| Foram adicionados %d salarios e desses, %d sao invalidos\n", n, atencao);
            } else {
                printf("|\n| Não foram adicionados salarios \n");
            }

            if (porAdd != 0) {
                if (porAdd == 1) {
                    printf("|\n| O codigo seguinte nao tem conta criada: \n");
                } else {
                    printf("|\n| Os seguintes codigos nao têm conta criada: \n");
                }
                printf("| Codigo:");
                for (int x = 0; x != n; x++) {
                    if (procurarFuncionario(arrayRH, conta->dados_calculo_array[(conta->contador - n) + x].codigo) == -1) {
                        printf(" %d ", conta->dados_calculo_array[(conta->contador - n) + x].codigo);
                    }
                }
            }

            puts("");
            if (obterResposta(PERGUNTA_INFO_GUARDADA) == 1) {
                printf("|\n| SALARIOS ADICIONADOS: \n");
                for (int i = 0; i < n; i++) {
                    printf(FORMATO_MOSTRAR_SALARIOS, conta->dados_calculo_array[(conta->contador - n) + i].codigo,
                            conta->dados_calculo_array[(conta->contador - n) + i].ano,
                            conta->dados_calculo_array[(conta->contador - n) + i].mes,
                            conta->dados_calculo_array[(conta->contador - n) + i].dias_compl,
                            conta->dados_calculo_array[(conta->contador - n) + i].dias_meios,
                            conta->dados_calculo_array[(conta->contador - n) + i].dias_fds,
                            conta->dados_calculo_array[(conta->contador - n) + i].dias_faltas,
                            estadoToString(conta->dados_calculo_array[(conta->contador - n) + i].estado));
                }
            }

            if (obterResposta("| Deseja fazer o processamento salarial [s/n]? ") == 1) {
                menu_Calculo_salarial(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
            }
        }
    } while (ficheiro_salarios == NULL);
}

//IMPORTAR TABELA DE IRS DOIS TITULARES
/**
 * Importa para a memória a tabela de dois titulares de IRS do ficheiro 
 *  
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 */
void importarDoisTitulares(Tabelas *dois_titulares) {
    FILE *ficheiro_dois_titulares;

    ficheiro_dois_titulares = fopen(FILENAME_DEPENDENTE_CASADO_DOIS_TITULARES, "rb");
    if (ficheiro_dois_titulares == NULL) {
        puts(ERRO_FILE);
    } else {
        while (fread(&dois_titulares->tabela[dois_titulares->contador], sizeof (IRS), 1, ficheiro_dois_titulares)) {
            dois_titulares->contador++;
            addMemoriaDoisTitulares(dois_titulares);
        }
        puts(IMPORTADA);
    }
    fclose(ficheiro_dois_titulares);
}

//IMPORTAR TABELA DE IRS UM TITULAR´
/**
 * Importa para a memória a tabela de um titular de IRS do ficheiro 
 * 
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 */
void importarUnicoTitular(Tabelas *unico_titular) {
    FILE *ficheiro_unico_titular;

    ficheiro_unico_titular = fopen(FILENAME_DEPENDENTE_CASADO_UNICO_TITULAR, "rb");
    if (ficheiro_unico_titular == NULL) {
        puts(ERRO_FILE);
    } else {
        while (fread(&unico_titular->tabela[unico_titular->contador], sizeof (IRS), 1, ficheiro_unico_titular)) {
            unico_titular->contador++;
            addMemoriaUnicoTitular(unico_titular);
        }
        puts(IMPORTADA);
    }
    fclose(ficheiro_unico_titular);
}

//IMPORTAR TABELA DE IRS NAO CASADO
/**
 * Importa para a memória a tabela de nao casado de IRS do ficheiro 
 * 
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void importarNaoCasado(Tabelas *nao_casado) {
    FILE *ficheiro_nao_casado;

    ficheiro_nao_casado = fopen(FILENAME_DEPENDENTE_NAO_CASADO, "rb");
    if (ficheiro_nao_casado == NULL) {
        puts(ERRO_FILE);
    } else {
        while (fread(&nao_casado->tabela[nao_casado->contador], sizeof (IRS), 1, ficheiro_nao_casado)) {
            nao_casado->contador++;
            addMemoriaNaoCasado(nao_casado);
        }
        puts(IMPORTADA);
    }
    fclose(ficheiro_nao_casado);
}

//IMPORTAR TABELA SS
/**
 * Importa para a memória as taxas de segurança social do ficheiro 
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void importarTablelaSS(Tabela_SS *taxa) {

    FILE *ficheiro_SS;

    ficheiro_SS = fopen(FILENAME_SS, "r");
    if (ficheiro_SS == NULL) {
        puts(ERRO_FILE);
    } else {
        while (fread(&taxa->taxa_array[taxa->contador], sizeof (Taxas), 1, ficheiro_SS)){
            taxa->contador++;
            addMemoriaTaxas(taxa);
        }
        puts(IMPORTADA);
    }
    fclose(ficheiro_SS);

}

//GUARDAR TODOS OS DADOS EM MEMORIA
/**
 * Guarda toda a informaçao em memoria em ficheiros do sistema 
 * 
 * @param funcionarios tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param taxa tem o array de memoria das taxas de SS
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void guardar(Empresa *funcionarios, Lista_calc *conta, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Tabela_SS *taxa, Lista_salarios *salarios) {

    FILE *ficheiro_SS, *ficheiro_calculo, *ficheiro_users, *ficheiro_salarios, *ficheiro_dois_titulares, *ficheiro_um_titular, *ficheiro_nao_casado;
    printf("+ GUARDAR INFORMAÇÃO + \n");

    //GUARDAR TODOS OS USERS
    ficheiro_users = fopen(FILENAME_USERS, "wb");
    if (ficheiro_users == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int i = 0; i < funcionarios->contador; i++) {
            fwrite(&funcionarios->funcionarios_array[i], sizeof (Funcionario), 1, ficheiro_users);
        }
        printf("| Funcionarios: Guardado \n");
    }

    fclose(ficheiro_users);

    //GUARDAR TODOS OS DADOS PARA O CALC DO SALARIO
    ficheiro_salarios = fopen(FILENAME_SALARIOS, "wb");
    if (ficheiro_salarios == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int i = 0; i < conta->contador; i++) {
            fwrite(&conta->dados_calculo_array[i], sizeof (Conta), 1, ficheiro_salarios);
        }
        printf("| Salarios: Guardado \n");
    }
    fclose(ficheiro_salarios);

    //GUARDAR DADOS DO PROCESSAMENTO DE SALARIOS
    ficheiro_calculo = fopen(FILENAME_SALARIOS_PROCESSADOS, "w");
    if (ficheiro_calculo == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int y = 0; y < salarios->contador; y++) {
            fwrite(&salarios->calculo_array[y], sizeof (Calculo), 1, ficheiro_calculo);
        }
        printf("| Salarios processados: Guardado \n");
    }
    fclose(ficheiro_calculo);

    //GUARDAR TABELA DE DOIS TITULARES
    ficheiro_dois_titulares = fopen(FILENAME_DEPENDENTE_CASADO_DOIS_TITULARES, "wb");
    if (ficheiro_dois_titulares == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int i = 0; i < dois_titulares->contador; i++) {
            fwrite(&dois_titulares->tabela[i], sizeof (IRS), 1, ficheiro_dois_titulares);
        }
        printf("| Tabela IRS Dois Titulares: Guardado \n");
    }
    fclose(ficheiro_dois_titulares);

    //GUARDAR TABELA DE UNICO TITULAR
    ficheiro_um_titular = fopen(FILENAME_DEPENDENTE_CASADO_UNICO_TITULAR, "wb");
    if (ficheiro_um_titular == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int x = 0; x < unico_titular->contador; x++) {
            fwrite(&unico_titular->tabela[x], sizeof (IRS), 1, ficheiro_um_titular);
        }
        printf("| Tabela IRS Unico Titular: Guardado \n");
    }
    fclose(ficheiro_um_titular);

    //GUARDAR TABELA DE NAO CASADO
    ficheiro_nao_casado = fopen(FILENAME_DEPENDENTE_NAO_CASADO, "wb");
    if (ficheiro_nao_casado == NULL) {
        puts(ERRO_FILE);
    } else {
        for (int y = 0; y < nao_casado->contador; y++) {
            fwrite(&nao_casado->tabela[y], sizeof (IRS), 1, ficheiro_nao_casado);
        }
        printf("| Tabela IRS Nao Casado: Guardado \n");
    }
    fclose(ficheiro_nao_casado);

    //GUARDAR DADOS SEGURANCA SOCIAL
    ficheiro_SS = fopen(FILENAME_SS, "wb");
    if (ficheiro_SS == NULL) {
        puts(ERRO_FILE);
    } else {
        for(int x = 0; x != taxa->contador ; x++){
            fwrite(&taxa->taxa_array[x], sizeof(Taxas), 1,ficheiro_SS );
        }
        printf("| Tabela Segurança Social: Guardado \n");
    }
    fclose(ficheiro_SS);

}

//ALTERAR CRITERIO SS
/**
 * Altera os valores de descontos para a segurança social
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void alterarCriterioSS(Tabela_SS *taxa) {
    int n=0;
    char cargo[MAX_CARGO];
    obterString(cargo, MAX_CARGO, "| Digite o cargo das taxas a alterar: ");
    n = posicaoTaxa(cargo, taxa);
    if (n != -1){
        taxa->taxa_array[n].empregadora = obterFloat(0,100, "| Digite o novo valor para a entidade patronal: ");
        taxa->taxa_array[n].trabalhador = obterFloat(0,100, "| Digite o novo valor para a entidade trabalhadora: ");
        puts(SUCESSO_ALTERACAO);
    } else {
        puts(ERRO_SS_NAO_EXISTENTE);
    }
}

/**
 * Remove uma categoria de valores de descontos para a segurança social dependendo do cargo
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void removerCriterioSS(Tabela_SS *taxa){
    char cargo[MAX_CARGO];
    int posicao;
    
    Taxas *memoria;
    
    Tabela_SS temp;
    temp.contador = 0;
    temp.taxa_array = (Taxas*) malloc (sizeof(Taxas));
    if (temp.taxa_array == NULL) {
        puts(ERRO_MEMORIA);
    }
    obterString(cargo, MAX_CARGO, OBTER_CARGO);
    posicao = posicaoTaxa(cargo, taxa);
    
    if (posicao == -1){
        puts(ERRO_SS_NAO_EXISTENTE);
    } else if (posicao == 0){
        puts("| !IMPOSSSIVEL APAGAR ESSE CRITERIO! ");
    } else {
        for (int y = 0; y != taxa->contador; y++) {
            if (y != posicao) {
                strcpy( temp.taxa_array[temp.contador].cargo,  taxa->taxa_array[y].cargo);
                temp.taxa_array[temp.contador].empregadora = taxa->taxa_array[y].empregadora;
                temp.taxa_array[temp.contador].trabalhador = taxa->taxa_array[y].trabalhador;
                temp.contador++;
                memoria = (Taxas*) realloc(temp.taxa_array, temp.contador * sizeof (Taxas) + sizeof (Taxas));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                temp.taxa_array = memoria;
                memoria = NULL;
                free(memoria);
            }
        }
        taxa->taxa_array = temp.taxa_array;
        temp.taxa_array = NULL;
        free(temp.taxa_array);
        (taxa->contador)--; 
        puts(SUCESSO_ALTERACAO);
    }
}

//ADICIONAR CRITERIO
/**
 * Permite adicionar criterios as taxas de descontos para a SS
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void addCriterioSS(Tabela_SS *taxa) {
    char cargo[MAX_CARGO];
    obterString(cargo, MAX_CARGO, OBTER_CARGO);
    int posicao = posicaoTaxa(cargo, taxa);
    if (posicao == -1){
        strcpy( taxa->taxa_array[taxa->contador].cargo, cargo); 
        taxa->taxa_array[taxa->contador].empregadora = obterFloat(0,100, "| Digite o valor para a entidade patronal: ");
        taxa->taxa_array[taxa->contador].trabalhador = obterFloat(0,100, "| Digite o valor para a entidade trabalhadora: ");
        taxa->contador++;
        addMemoriaTaxas(taxa);
        puts(SUCESSO_ALTERACAO);
    } else {
        puts(ERRO_SS_EXISTENTE);
    }
}

//MOSTRAR TODAS AS TAXAS
/**
 * Mostra os valores das taxas para descontos para a SS em memória
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void mostrarSS(Tabela_SS *taxa) {
    for(int i=0; i != taxa->contador; i++){
        printf(FORMATO_MOSTRAR_SS, taxa->taxa_array[i].cargo, taxa->taxa_array[i].empregadora, taxa->taxa_array[i].trabalhador);
    }
}

//ALTERAR CRITERIO
/**
 * Altera os valores de descontos para o IRS de um vencimento
 * Pergunta ao utilizador o vencimento e os novos valores
 * 
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void alterarCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {

    int tabela, vencimento, num_filhos, i;
    float valor;

    tabela = obterInt(0, 3, FORMATO_MENU_ALTERAR_IRS);

    if (tabela != 0) {

        if (tabela == 1) {
            printf("\n| ALTERAÇÃO DE CRITERIO NA TABELA DE DOIS TITULARES\n");
        } else if (tabela == 2) {
            printf("\n| ALTERAÇÃO DE CRITERIO NA TABELA DE UNICO TITULAR\n");
        } else {
            printf("\n| ALTERAÇÃO DE CRITERIO NA TABELA NÃO CASADO\n");
        }

        do {
            printf("| Insira o vencimento (linha): ");
            scanf("%d", &vencimento);
        } while (verificarVencimento(tabela, vencimento, dois_titulares, unico_titular, nao_casado) != 1);

        num_filhos = obterInt(0, 5, "| Insira o numero de filhos (coluna): ");
        valor = obterInt(0, 100, "| Insira o novo valor: ");

        switch (tabela) {
            case 1:
                for (i = 0; i < dois_titulares->contador; i++) {
                    if (vencimento == dois_titulares->tabela[i].vencimento) {
                        switch (num_filhos) {
                            case 0:
                                dois_titulares->tabela[i].filho_zero = valor;
                                break;
                            case 1:
                                dois_titulares->tabela[i].filho_um = valor;
                                break;
                            case 2:
                                dois_titulares->tabela[i].filho_dois = valor;
                                break;
                            case 3:
                                dois_titulares->tabela[i].filho_tres = valor;
                                break;
                            case 4:
                                dois_titulares->tabela[i].filho_quatro = valor;
                                break;
                            default:
                                dois_titulares->tabela[i].filho_cinco = valor;
                                break;
                        }
                        break;
                    }
                }
                puts(SUCESSO_ALTERACAO);
                break;
            case 2:
                for (i = 0; i < unico_titular->contador; i++) {
                    if (vencimento == unico_titular->tabela[i].vencimento) {
                        switch (num_filhos) {
                            case 0:
                                unico_titular->tabela[i].filho_zero = valor;
                                break;
                            case 1:
                                unico_titular->tabela[i].filho_um = valor;
                                break;
                            case 2:
                                unico_titular->tabela[i].filho_dois = valor;
                                break;
                            case 3:
                                unico_titular->tabela[i].filho_tres = valor;
                                break;
                            case 4:
                                unico_titular->tabela[i].filho_quatro = valor;
                                break;
                            default:
                                unico_titular->tabela[i].filho_cinco = valor;
                                break;
                        }
                        break;
                    }
                }
                puts(SUCESSO_ALTERACAO);
                break;
            case 3:
                for (i = 0; i < nao_casado->contador; i++) {
                    if (vencimento == nao_casado->tabela[i].vencimento) {
                        switch (num_filhos) {
                            case 0:
                                nao_casado->tabela[i].filho_zero = valor;
                                break;
                            case 1:
                                nao_casado->tabela[i].filho_um = valor;
                                break;
                            case 2:
                                nao_casado->tabela[i].filho_dois = valor;
                                break;
                            case 3:
                                nao_casado->tabela[i].filho_tres = valor;
                                break;
                            case 4:
                                nao_casado->tabela[i].filho_quatro = valor;
                                break;
                            default:
                                nao_casado->tabela[i].filho_cinco = valor;
                                break;
                        }
                        break;
                    }
                }
                puts(SUCESSO_ALTERACAO);
                break;
            case 0:
                break;
        }
    }
}

//ADICIONAR CRITERIO
/**
 * Adiciona uma linha de valores de descontos para o IRS
 * Pede ao utilizador os novos valores
 * 
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void addCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int x = 0, i = 0, y = 0, posicao, tabela, vencimento;
    float filho_um, filho_dois, filho_tres, filho_quatro, filho_cinco, filho_zero;

    IRS *memoria;

    Tabelas temp;
    temp.contador = 0;
    temp.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    Tabelas temp_unico;
    temp_unico.contador = 0;
    temp_unico.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp_unico.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    Tabelas temp_nao_casado;
    temp_nao_casado.contador = 0;
    temp_nao_casado.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp_nao_casado.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    tabela = obterInt(0, 3, FORMATO_MENU_ALTERAR_IRS);

    if (tabela != 0) {

        printf("|\n| Informação a acrencentar \n");

        printf("| Digite o novo vencimento: ");
        scanf("%d", &vencimento);

        while (vencimento < 0 || posicaoVencimento(tabela, vencimento, dois_titulares, unico_titular, nao_casado) == -1) {
            puts(ERRO_VENCIMENTO);
            printf("| Digite o novo vencimento: ");
            scanf("%d", &vencimento);
        }

        filho_zero = obterFloat(0, 100, "| Digite o valor para nenhum filho: ");
        filho_um = obterFloat(0, 100, "| Digite o valor para 1 filho: ");
        filho_dois = obterFloat(0, 100, "| Digite o valor para 2 filhos: ");
        filho_tres = obterFloat(0, 100, "| Digite o valor para 3 filhos: ");
        filho_quatro = obterFloat(0, 100, "| Digite o valor para 4 filhos: ");
        filho_cinco = obterFloat(0, 100, "| Digite o valor para mais de 5 filhos: ");

        posicao = posicaoVencimento(tabela, vencimento, dois_titulares, unico_titular, nao_casado);

        switch (tabela) {
            case 1:
                logs("ADICIOAR CRITERIO - TABELA: DOIS TITULARES");
                for (x = 0; x != dois_titulares->contador; x++) {
                    if (x == posicao) {
                        temp.tabela[temp.contador].vencimento = vencimento;
                        temp.tabela[temp.contador].filho_zero = filho_zero;
                        temp.tabela[temp.contador].filho_um = filho_um;
                        temp.tabela[temp.contador].filho_dois = filho_dois;
                        temp.tabela[temp.contador].filho_tres = filho_tres;
                        temp.tabela[temp.contador].filho_quatro = filho_quatro;
                        temp.tabela[temp.contador].filho_cinco = filho_cinco;
                        temp.contador++;

                        memoria = (IRS*) realloc(temp.tabela, temp.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }

                    temp.tabela[temp.contador].vencimento = dois_titulares->tabela[x].vencimento;
                    temp.tabela[temp.contador].filho_zero = dois_titulares->tabela[x].filho_zero;
                    temp.tabela[temp.contador].filho_um = dois_titulares->tabela[x].filho_um;
                    temp.tabela[temp.contador].filho_dois = dois_titulares->tabela[x].filho_dois;
                    temp.tabela[temp.contador].filho_tres = dois_titulares->tabela[x].filho_tres;
                    temp.tabela[temp.contador].filho_quatro = dois_titulares->tabela[x].filho_quatro;
                    temp.tabela[temp.contador].filho_cinco = dois_titulares->tabela[x].filho_cinco;
                    temp.contador++;

                    memoria = (IRS*) realloc(temp.tabela, temp.contador * sizeof (IRS) + sizeof (IRS));
                    if (memoria == NULL) {
                        puts(ERRO_MEMORIA);
                    }
                    temp.tabela = memoria;
                    memoria = NULL;
                    free(memoria);
                }
                dois_titulares->tabela = temp.tabela;
                memoria = (IRS*) realloc(dois_titulares->tabela, dois_titulares->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                dois_titulares->tabela = memoria;
                memoria = NULL;
                free(memoria);
                dois_titulares->contador++;

                puts(SUCESSO_ALTERACAO);
                break;
            case 2:
                logs("ADICIOAR CRITERIO - TABELA: UNICO TITULAR");
                for (x = 0; x != unico_titular->contador; x++) {
                    if (x == posicao) {
                        temp_unico.tabela[temp_unico.contador].vencimento = vencimento;
                        temp_unico.tabela[temp_unico.contador].filho_zero = filho_zero;
                        temp_unico.tabela[temp_unico.contador].filho_um = filho_um;
                        temp_unico.tabela[temp_unico.contador].filho_dois = filho_dois;
                        temp_unico.tabela[temp_unico.contador].filho_tres = filho_tres;
                        temp_unico.tabela[temp_unico.contador].filho_quatro = filho_quatro;
                        temp_unico.tabela[temp_unico.contador].filho_cinco = filho_cinco;
                        temp_unico.contador++;

                        memoria = (IRS*) realloc(temp_unico.tabela, temp_unico.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp_unico.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }

                    temp_unico.tabela[temp_unico.contador].vencimento = unico_titular->tabela[x].vencimento;
                    temp_unico.tabela[temp_unico.contador].filho_zero = unico_titular->tabela[x].filho_zero;
                    temp_unico.tabela[temp_unico.contador].filho_um = unico_titular->tabela[x].filho_um;
                    temp_unico.tabela[temp_unico.contador].filho_dois = unico_titular->tabela[x].filho_dois;
                    temp_unico.tabela[temp_unico.contador].filho_tres = unico_titular->tabela[x].filho_tres;
                    temp_unico.tabela[temp_unico.contador].filho_quatro = unico_titular->tabela[x].filho_quatro;
                    temp_unico.tabela[temp_unico.contador].filho_cinco = unico_titular->tabela[x].filho_cinco;
                    temp_unico.contador++;

                    memoria = (IRS*) realloc(temp_unico.tabela, temp_unico.contador * sizeof (IRS) + sizeof (IRS));
                    if (memoria == NULL) {
                        puts(ERRO_MEMORIA);
                    }
                    temp_unico.tabela = memoria;
                    memoria = NULL;
                    free(memoria);
                }
                unico_titular->tabela = temp_unico.tabela;
                memoria = (IRS*) realloc(unico_titular->tabela, unico_titular->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                unico_titular->tabela = memoria;
                memoria = NULL;
                free(memoria);
                unico_titular->contador++;
                puts(SUCESSO_ALTERACAO);
                break;
            case 3:
                logs("ADICIOAR CRITERIO - TABELA: NÃO CASADO");
                for (x = 0; x != nao_casado->contador; x++) {
                    if (x == posicao) {
                        temp_nao_casado.tabela[temp_nao_casado.contador].vencimento = vencimento;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_zero = filho_zero;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_um = filho_um;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_dois = filho_dois;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_tres = filho_tres;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_quatro = filho_quatro;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_cinco = filho_cinco;
                        temp_nao_casado.contador++;

                        memoria = (IRS*) realloc(temp_nao_casado.tabela, temp_nao_casado.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp_nao_casado.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }

                    temp_nao_casado.tabela[temp_nao_casado.contador].vencimento = nao_casado->tabela[x].vencimento;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_zero = nao_casado->tabela[x].filho_zero;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_um = nao_casado->tabela[x].filho_um;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_dois = nao_casado->tabela[x].filho_dois;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_tres = nao_casado->tabela[x].filho_tres;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_quatro = nao_casado->tabela[x].filho_quatro;
                    temp_nao_casado.tabela[temp_nao_casado.contador].filho_cinco = nao_casado->tabela[x].filho_cinco;
                    temp_nao_casado.contador++;

                    memoria = (IRS*) realloc(temp_nao_casado.tabela, temp_nao_casado.contador * sizeof (IRS) + sizeof (IRS));
                    if (memoria == NULL) {
                        puts(ERRO_MEMORIA);
                    }
                    temp_nao_casado.tabela = memoria;
                    memoria = NULL;
                    free(memoria);
                }
                nao_casado->tabela = temp_nao_casado.tabela;
                memoria = (IRS*) realloc(nao_casado->tabela, nao_casado->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                nao_casado->tabela = memoria;
                memoria = NULL;
                free(memoria);
                nao_casado->contador++;
                puts(SUCESSO_ALTERACAO);
                break;
            default:
                puts(ERRO);
        }

        temp.tabela = NULL;
        free(temp.tabela);

        temp_unico.tabela = NULL;
        free(temp_unico.tabela);

        temp_nao_casado.tabela = NULL;
        free(temp_nao_casado.tabela);

        if (obterResposta("| Deseja ver as tabelas? ") == 1) {
            mostrarTabelas(dois_titulares, unico_titular, nao_casado);
        }
    }
}

//APAGAR CRITERIO IRS
/**
 * Apaga uma linha de valores de descontos para o IRS
 * Pede ao utilizador o vencimento correspondente à linha
 * 
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void apagarCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int x = 0, i = 0, y = 0, posicao, tabela, vencimento;

    IRS *memoria;

    Tabelas temp;
    temp.contador = 0;
    temp.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    Tabelas temp_unico;
    temp_unico.contador = 0;
    temp_unico.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp_unico.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    Tabelas temp_nao_casado;
    temp_nao_casado.contador = 0;
    temp_nao_casado.tabela = (IRS*) malloc(sizeof (IRS));
    if (temp_nao_casado.tabela == NULL) {
        puts(ERRO_MEMORIA);
    }

    tabela = obterInt(0, 3, FORMATO_MENU_ALTERAR_IRS);

    if (tabela != 0) {

        printf("|\n| Informação a apagar \n");
        do {
            printf("| Digite o vencimento: ");
            scanf("%d", &vencimento);
        } while (vencimento < 0 || linhaVencimento(tabela, vencimento, dois_titulares, unico_titular, nao_casado) == -1);


        posicao = linhaVencimento(tabela, vencimento, dois_titulares, unico_titular, nao_casado) - 1;

        switch (tabela) {
            case 1:
                logs("APAGAR CRITERIO - TABELA: DOIS TITULARES");
                for (x = 1; x != dois_titulares->contador; x++) {
                    if (x != posicao) {
                        temp.tabela[temp.contador].vencimento = dois_titulares->tabela[x].vencimento;
                        temp.tabela[temp.contador].filho_zero = dois_titulares->tabela[x].filho_zero;
                        temp.tabela[temp.contador].filho_um = dois_titulares->tabela[x].filho_um;
                        temp.tabela[temp.contador].filho_dois = dois_titulares->tabela[x].filho_dois;
                        temp.tabela[temp.contador].filho_tres = dois_titulares->tabela[x].filho_tres;
                        temp.tabela[temp.contador].filho_quatro = dois_titulares->tabela[x].filho_quatro;
                        temp.tabela[temp.contador].filho_cinco = dois_titulares->tabela[x].filho_cinco;
                        temp.contador++;

                        memoria = (IRS*) realloc(temp.tabela, temp.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }

                }
                dois_titulares->tabela = temp.tabela;
                memoria = (IRS*) realloc(dois_titulares->tabela, dois_titulares->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                dois_titulares->tabela = memoria;
                memoria = NULL;
                free(memoria);
                dois_titulares->contador++;

                puts(SUCESSO_ALTERACAO);
                break;
            case 2:
                logs("ADICIOAR CRITERIO - TABELA: UNICO TITULAR");
                for (x = 0; x != unico_titular->contador; x++) {
                    if (x != posicao) {
                        temp_unico.tabela[temp_unico.contador].vencimento = unico_titular->tabela[x].vencimento;
                        temp_unico.tabela[temp_unico.contador].filho_zero = unico_titular->tabela[x].filho_zero;
                        temp_unico.tabela[temp_unico.contador].filho_um = unico_titular->tabela[x].filho_um;
                        temp_unico.tabela[temp_unico.contador].filho_dois = unico_titular->tabela[x].filho_dois;
                        temp_unico.tabela[temp_unico.contador].filho_tres = unico_titular->tabela[x].filho_tres;
                        temp_unico.tabela[temp_unico.contador].filho_quatro = unico_titular->tabela[x].filho_quatro;
                        temp_unico.tabela[temp_unico.contador].filho_cinco = unico_titular->tabela[x].filho_cinco;
                        temp_unico.contador++;

                        memoria = (IRS*) realloc(temp_unico.tabela, temp_unico.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp_unico.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }
                }
                unico_titular->tabela = temp_unico.tabela;
                memoria = (IRS*) realloc(unico_titular->tabela, unico_titular->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                unico_titular->tabela = memoria;
                memoria = NULL;
                free(memoria);
                unico_titular->contador++;
                puts(SUCESSO_ALTERACAO);
                break;
            case 3:
                logs("ADICIOAR CRITERIO - TABELA: NÃO CASADO");
                for (x = 0; x != nao_casado->contador; x++) {
                    if (x != posicao) {
                        temp_nao_casado.tabela[temp_nao_casado.contador].vencimento = nao_casado->tabela[x].vencimento;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_zero = nao_casado->tabela[x].filho_zero;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_um = nao_casado->tabela[x].filho_um;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_dois = nao_casado->tabela[x].filho_dois;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_tres = nao_casado->tabela[x].filho_tres;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_quatro = nao_casado->tabela[x].filho_quatro;
                        temp_nao_casado.tabela[temp_nao_casado.contador].filho_cinco = nao_casado->tabela[x].filho_cinco;
                        temp_nao_casado.contador++;

                        memoria = (IRS*) realloc(temp_nao_casado.tabela, temp_nao_casado.contador * sizeof (IRS) + sizeof (IRS));
                        if (memoria == NULL) {
                            puts(ERRO_MEMORIA);
                        }
                        temp_nao_casado.tabela = memoria;
                        memoria = NULL;
                        free(memoria);
                    }
                }
                nao_casado->tabela = temp_nao_casado.tabela;
                memoria = (IRS*) realloc(nao_casado->tabela, nao_casado->contador * sizeof (IRS) + sizeof (IRS));
                if (memoria == NULL) {
                    puts(ERRO_MEMORIA);
                }
                nao_casado->tabela = memoria;
                memoria = NULL;
                free(memoria);
                nao_casado->contador++;
                puts(SUCESSO_ALTERACAO);
                break;
            default:
                puts(ERRO);
        }

        temp.tabela = NULL;
        free(temp.tabela);

        temp_unico.tabela = NULL;
        free(temp_unico.tabela);

        temp_nao_casado.tabela = NULL;
        free(temp_nao_casado.tabela);

        if (obterResposta("| Deseja ver as tabelas [s/n]? ") == 1) {
            mostrarTabelas(dois_titulares, unico_titular, nao_casado);
        }
    }
}

//VERIFICAR VENCIMENTO
/**
 * Verifica se o vencimento indicado da linha que se quer editar existe na tabela escolhida
 * 
 * @param tabela que se quer verificar do IRS
 * @param vencimento da linha que se quer alterar
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @return valor 1 se encontrar a linha correspondente na tabela
 */
int verificarVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int i;
    switch (tabela) {
        case 1:
            for (i = 0; i < dois_titulares->contador; i++) {
                if (vencimento == dois_titulares->tabela[i].vencimento) {
                    return (1);
                }
            }
            puts(ERRO_VENCIMENTO);
            break;
        case 2:
            for (i = 0; i < unico_titular->contador; i++) {
                if (vencimento == unico_titular->tabela[i].vencimento) {
                    return (1);
                }
            }
            puts(ERRO_VENCIMENTO);
            break;
        case 3:
            for (i = 0; i < nao_casado->contador; i++) {
                if (vencimento == nao_casado->tabela[i].vencimento) {
                    return (1);
                }
            }
            puts(ERRO_VENCIMENTO);
            break;
    }
}

//POSIÇÃO VENCIMENTO
/**
 * Localiza a posiçao na tabela de IRS a que o vencimento da nova linha a acrescentar corresponde 
 * 
 * @param tabela a fazer alteraçao
 * @param vencimento da linha a acrescentar
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @return index onde a linha a criar deve ficar na tabela escolhida
 */
int posicaoVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int i;
    switch (tabela) {
        case 1:
            for (i = 0; i < dois_titulares->contador; i++) {
                if (vencimento < dois_titulares->tabela[i + 1].vencimento && vencimento > dois_titulares->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            return (-1);
            break;
        case 2:
            for (i = 0; i < unico_titular->contador; i++) {
                if (vencimento < dois_titulares->tabela[i + 1].vencimento && vencimento > dois_titulares->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            return (-1);
            break;
        case 3:
            for (i = 0; i < nao_casado->contador; i++) {
                if (vencimento < dois_titulares->tabela[i + 1].vencimento && vencimento > dois_titulares->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            return (-1);
            break;
    }
}

//MOTRAR TODAS AS TABELAS IRS
/**
 * Mostra os valores de descontos de IRS em memória por tabelas
 * Pergunta a tabela em questao
 * 
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 */
void mostrarTabelas(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {

    switch (obterInt(0, 3, FORMATO_MENU_ALTERAR_IRS)) {
        case 1:
            logs("MOSTRAR TABELA DOIS TITULARES");
            puts("\n| TABELA DOIS TITULARES");
            for (int i = 0; i < (dois_titulares->contador) - 2; i++) {
                printf(FORMATO_MOSTRAR_TABELAS, dois_titulares->tabela[i].vencimento,
                        dois_titulares->tabela[i].filho_zero,
                        dois_titulares->tabela[i].filho_um,
                        dois_titulares->tabela[i].filho_dois,
                        dois_titulares->tabela[i].filho_tres,
                        dois_titulares->tabela[i].filho_quatro,
                        dois_titulares->tabela[i].filho_cinco);
            }
            break;
        case 2:
            logs("MOSTRAR TABELA UNICO TITULAR");
            puts("\n| TABELA UNICO TITULAR");
            for (int i = 0; i < (unico_titular->contador) - 2; i++) {
                printf(FORMATO_MOSTRAR_TABELAS, unico_titular->tabela[i].vencimento,
                        unico_titular->tabela[i].filho_zero,
                        unico_titular->tabela[i].filho_um,
                        unico_titular->tabela[i].filho_dois,
                        unico_titular->tabela[i].filho_tres,
                        unico_titular->tabela[i].filho_quatro,
                        unico_titular->tabela[i].filho_cinco);
            }
            break;
        case 3:
            logs("MOSTRAR TABELA NAO CASADO");
            puts("\n| TABELA NAO CASADO");
            for (int i = 0; i < (nao_casado->contador) - 2; i++) {
                printf(FORMATO_MOSTRAR_TABELAS, nao_casado->tabela[i].vencimento,
                        nao_casado->tabela[i].filho_zero,
                        nao_casado->tabela[i].filho_um,
                        nao_casado->tabela[i].filho_dois,
                        nao_casado->tabela[i].filho_tres,
                        nao_casado->tabela[i].filho_quatro,
                        nao_casado->tabela[i].filho_cinco);
            }
            break;
    }
}

//FAZER LOGS
/**
 * Adiciona linhas de texto num ficheiro de logs a informar a hora e data das funçoes realizadas
 * 
 * @param mensagem a escrever no ficheiro
 */
void logs(char *mensagem) {

    FILE *ficheiro_logs = fopen(FILENAME_LOG, "a");
    if (ficheiro_logs == NULL) {
        exit(EXIT_FAILURE);
    } else {
        fprintf(ficheiro_logs, FORMATO_LOGS, defineData(3), defineData(2), defineData(1), defineData(4), defineData(5), defineData(6), mensagem);
    }
    fclose(ficheiro_logs);
}

//LIMPAR MEMORIA
/**
 * Apaga a informaçao nos ficheiros de memoria do programa e nos arrays de memoria
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void limpar_memoria(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios) {

    Calculo *tempCalculo;
    Funcionario *tempFuncionarios;
    Conta *tempConta;

    printf("\n+ APAGAR TODA A INFORMAÇÃO + \n");

    if (obterResposta("| Tem a certeza que quer apagar todos os dados dos ficheiros (users, salarios, salarios processados) [s/n]? ") == 1) {
        logs("APAGAR INFORMAÇÃO");
        //APAGAR TODOS OS USERS
        FILE *ficheiro_users = fopen(FILENAME_USERS, "wb");
        if (ficheiro_users == NULL) {
            puts(ERRO_FILE);
        } else {
            printf("| Funcionarios: Apagado \n");
        }
        fclose(ficheiro_users);

        //APAGAR TODOS OS DADOS PARA O CALC DO SALARIO
        FILE *ficheiro_salarios = fopen(FILENAME_SALARIOS, "wb");
        if (ficheiro_salarios == NULL) {
            puts(ERRO_FILE);
        } else {
            printf("| Salarios: Apagado \n");
        }
        fclose(ficheiro_salarios);

        //APAGAR DADOS DO PROCESSAMENTO DE SALARIOS
        FILE *ficheiro_calculo = fopen(FILENAME_SALARIOS_PROCESSADOS, "w");
        if (ficheiro_calculo == NULL) {
            puts(ERRO_FILE);
        } else {
            printf("| Salarios processados: Apagado \n");
        }
        fclose(ficheiro_calculo);

        arrayRH->funcionarios_array = NULL;
        free(arrayRH->funcionarios_array);

        conta->dados_calculo_array = NULL;
        free(conta->dados_calculo_array);

        salarios->calculo_array = NULL;
        free(salarios->calculo_array);

        //Criar um espaço para as listas
        salarios->contador = 0;
        tempCalculo = (Calculo*) malloc(sizeof (Calculo));
        if (tempCalculo == NULL) {
            puts(ERRO_MEMORIA);
        }
        salarios->calculo_array = tempCalculo;
        tempCalculo = NULL;
        free(tempCalculo);

        arrayRH->contador = 0;
        tempFuncionarios = (Funcionario*) malloc(sizeof (Funcionario));
        if (tempFuncionarios == NULL) {
            puts(ERRO_MEMORIA);
        }
        arrayRH->funcionarios_array = tempFuncionarios;
        tempFuncionarios = NULL;
        free(tempFuncionarios);

        conta->contador = 0;
        tempConta = (Conta*) malloc(sizeof (Conta));
        if (tempConta == NULL) {
            puts(ERRO_MEMORIA);
        }
        conta->dados_calculo_array = tempConta;
        tempConta = NULL;
        free(tempConta);
    }
}

//CRIAR FICHEIROS PARA O USER
/**
 * Imprime para um documento de texto todos os dados de um array de memoria escolhido
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param salarios tem o array de memoria de processamentos salariais
 */
void criarFicheirosUser(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios) {

    FILE *ficheiro_users, *ficheiro_salarios, *ficheiro_conta;

    switch (obterInt(0, 3, FORMATO_LISTA_FICHEIROS)) {
        case 1:
            ficheiro_users = fopen(FILENAME_USERS_TEXTO, "w");
            if (ficheiro_users == NULL) {
                puts(ERRO_FILE);
            } else if (arrayRH->contador == 0) {
                printf(NAO_EXISTEM, "UTILIZADORES");
            } else {
                for (int i = 0; i < arrayRH->contador; i++) {
                    fprintf(ficheiro_users, FORMATO_MOSTRAR_USERS,
                            arrayRH->funcionarios_array[i].codigo,
                            arrayRH->funcionarios_array[i].nome,
                            arrayRH->funcionarios_array[i].numero_tlm,
                            est_civilToString(arrayRH->funcionarios_array[i].est_civil),
                            arrayRH->funcionarios_array[i].titulares,
                            arrayRH->funcionarios_array[i].numero_filhos,
                            arrayRH->funcionarios_array[i].cargo,
                            arrayRH->funcionarios_array[i].valor_hora,
                            arrayRH->funcionarios_array[i].valor_sub_ali,
                            arrayRH->funcionarios_array[i].nascimento.dia,
                            arrayRH->funcionarios_array[i].nascimento.mes,
                            arrayRH->funcionarios_array[i].nascimento.ano,
                            arrayRH->funcionarios_array[i].entrada_emp.dia,
                            arrayRH->funcionarios_array[i].entrada_emp.mes,
                            arrayRH->funcionarios_array[i].entrada_emp.ano,
                            arrayRH->funcionarios_array[i].saida_emp.dia,
                            arrayRH->funcionarios_array[i].saida_emp.mes,
                            arrayRH->funcionarios_array[i].saida_emp.ano,
                            ativoToString(arrayRH->funcionarios_array[i].ativo));
                }
                fclose(ficheiro_users);
                puts(SUCESSO);
                break;
            }
        case 2:
            ficheiro_conta = fopen(FILENAME_SALARIOS_TEXTO, "w");
            if (ficheiro_conta == NULL) {
                puts(ERRO_FILE);
            } else if (conta->contador == 0) {
                printf(NAO_EXISTEM, "SALARIOS POR PROCESSAR");
            } else {
                for (int i = 0; i < conta->contador; i++) {
                    fprintf(ficheiro_conta, FORMATO_MOSTRAR_SALARIOS_LISTAGENS,
                            conta->dados_calculo_array[i].codigo,
                            conta->dados_calculo_array[i].dias_compl,
                            conta->dados_calculo_array[i].dias_meios,
                            conta->dados_calculo_array[i].dias_fds,
                            conta->dados_calculo_array[i].dias_faltas,
                            conta->dados_calculo_array[i].ano,
                            conta->dados_calculo_array[i].mes,
                            estadoToString(conta->dados_calculo_array[i].estado));
                }
                fclose(ficheiro_conta);
                puts(SUCESSO);
                break;
            }
        case 3:
            ficheiro_salarios = fopen(FILENAME_CALCULOS_TEXTO, "w");
            if (ficheiro_salarios == NULL) {
                puts(ERRO_FILE);
            } else if (salarios->contador == 0) {
                printf(NAO_EXISTEM, "SALARIOS PROCESSADOS");
            } else {
                for (int i = 0; i < salarios->contador; i++) {
                    fprintf(ficheiro_salarios, FORMATO_MOSTRAR_SALARIOS_TODOS,
                            salarios->calculo_array[i].codigo,
                            salarios->calculo_array[i].venc_iliquido,
                            salarios->calculo_array[i].bonus,
                            salarios->calculo_array[i].sub_ali,
                            salarios->calculo_array[i].ss_ent_patronal,
                            salarios->calculo_array[i].ss_ent_pessoal,
                            salarios->calculo_array[i].irs,
                            salarios->calculo_array[i].venc_liquido,
                            salarios->calculo_array[i].encargo_total_emp);
                }
                fclose(ficheiro_salarios);
                puts(SUCESSO);
                break;
            }
        case 0:
            break;
    }
}

//VALIDAÇÃO DO SOMATORIO DOS DIAS 
/**
 * Verifica se o numero total de dias passados nos salarios por ficheiro corresponde ao numero maximo de dias do mes
 * 
 * @param dias_compl numero de dias completos para adicionar
 * @param dias_meios numero de dias meio completos para adicionar
 * @param dias_fds numero de dias ao fim de semana para adicionar
 * @param dias_faltas numero de dias faltados para adicionar
 * @param mes do calculo salarial
 * @param ano do calculo salarial
 * @return valor 1 se total de dias nao corresponder com o mes
 */
int verificacaoDiasDoc(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, int mes, int ano) {
    if (dias_compl + dias_meios + dias_fds + dias_faltas != saberDiaMax(ano, mes)) {
        return 1;
    }
}

//OBTER LINHA CORRETA DO VENCIMENTO NAS TABELAS (SO PERMITE VENCIMENTOS JA EXISTENTES NA TABELA)
/**
 * Localiza a posicao da linha de IRS a ser apagada correspondente ao vencimento dado
 * 
 * @param tabela a fazer alteraçao
 * @param vencimento da linha a apagar
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @return index da linha a apagar na tabela
 */
int linhaVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado) {
    int i;
    switch (tabela) {
        case 1:
            for (i = 0; i < dois_titulares->contador; i++) {
                if (vencimento == dois_titulares->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            puts(ERRO_VENCIMENTO);
            return (-1);
            break;
        case 2:
            for (i = 0; i < unico_titular->contador; i++) {
                if (vencimento == unico_titular->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            puts(ERRO_VENCIMENTO);
            return (-1);
            break;
        case 3:
            for (i = 0; i < nao_casado->contador; i++) {
                if (vencimento == nao_casado->tabela[i].vencimento) {
                    return (i + 1);
                }
            }
            puts(ERRO_VENCIMENTO);
            return (-1);
            break;
    }
}
