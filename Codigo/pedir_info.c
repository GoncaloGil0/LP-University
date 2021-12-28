/* 
 * Ficheiro que contem todas as funções responsaveis por pedir informação ao utilizador
 * @file pedir_info.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

//ADICIONAR DO FUNCIONARIO
/**
 * Pede e guarda toda a informação referente aos utilizadores manualmente
 * 
 * @param arrayRH tem o array de memoria onde vao ser guardados os dados
 * @param codigo necessario para pesquisa do funcionario
 */
void addFuncionario(Empresa *arrayRH, int codigo) {

    //VARIAVEIS LOCAIS
    int est_civil, mes, ano, dia;
    
    //ASSOCIAR CODIGO
    arrayRH->funcionarios_array[arrayRH->contador].codigo = codigo;

    //OBTER NOME
    obterString(arrayRH->funcionarios_array[arrayRH->contador].nome, MAX_NOME, OBTER_NOME);

    //OBTER NUMERO TELEMOVEL
    arrayRH->funcionarios_array[arrayRH->contador].numero_tlm = obterLong(MIN_NUM_TELE, MAX_NUM_TELE, OBTER_NUM_TELE);

    //OBTER ESTADO CIVIL
    est_civil = obterInt(0, 3, OBTER_EST_CIVIL);
    arrayRH->funcionarios_array[arrayRH->contador].est_civil = est_civil;
    if (est_civil == 0) {
        arrayRH->funcionarios_array[arrayRH->contador].titulares = obterInt(1, 2, OBTER_TITULARES);
    } else {
        arrayRH->funcionarios_array[arrayRH->contador].titulares = 0;
    }

    //OBTER NUMERO FILHOS
    arrayRH->funcionarios_array[arrayRH->contador].numero_filhos = obterIntMin(0, OBTER_NUM_FILHOS);
    
    //OBTER CARGO NA EMPRESA
    obterString(arrayRH->funcionarios_array[arrayRH->contador].cargo, MAX_CARGO, OBTER_CARGO);

    //OBTER SALARIO
    arrayRH->funcionarios_array[arrayRH->contador].valor_hora = obterIntMin(1, OBTER_VALOR_HORA);

    //OBTER SUBSIDIO ALIMENTACAO
    arrayRH->funcionarios_array[arrayRH->contador].valor_sub_ali = obterIntMin(0, OBTER_SUB_ALI);

    //OBTER DATA NASCIMENTO
    puts(OBTER_DATA_NASC);
    ano = saberAno(OBTER_ANO);
    while ((defineData(3) - ano) < 18) {
        puts(DATA_IVALIDA_MENOR);
        ano = saberAno(OBTER_ANO);
    }
    if ((defineData(3) - ano) == 18) {
        do {
            mes = saberMes(OBTER_MES, ano);
        } while (mes > defineData(2));
    } else {
        mes = saberMes(OBTER_MES, ano);
    }
    if (((defineData(3) - ano) == 18) && (mes == defineData(2))) {
        do {
            dia = saberDia(OBTER_DIA, ano, mes);
        } while (dia > defineData(1));
    } else {
        dia = saberDia(OBTER_DIA, ano, mes);
    }
    arrayRH->funcionarios_array[arrayRH->contador].nascimento.ano = ano;
    arrayRH->funcionarios_array[arrayRH->contador].nascimento.mes = mes;
    arrayRH->funcionarios_array[arrayRH->contador].nascimento.dia = dia;


    //OBTER DATA ENTRADA
    puts(OBTER_DATA_ENT);
    ano = saberAno(OBTER_ANO);
    while ((ano - arrayRH->funcionarios_array[arrayRH->contador].nascimento.ano) < 18) {
        puts(DATA_IVALIDA_MENOR);
        ano = saberAno(OBTER_ANO);
    }
    if ((ano - arrayRH->funcionarios_array[arrayRH->contador].nascimento.ano) == 18) {
        mes = saberMes(OBTER_MES, ano);
        while (mes < arrayRH->funcionarios_array[arrayRH->contador].nascimento.mes) {
            puts(DATA_IVALIDA_MENOR);
            mes = saberMes(OBTER_MES, ano);
        }
    } else {
        mes = saberMes(OBTER_MES, ano);
    }
    if (((ano - arrayRH->funcionarios_array[arrayRH->contador].nascimento.ano) == 18) && (mes == arrayRH->funcionarios_array[arrayRH->contador].nascimento.mes)) {
        dia = saberDia(OBTER_DIA, ano, mes);
        while (dia < arrayRH->funcionarios_array[arrayRH->contador].nascimento.dia) {
            puts(DATA_IVALIDA_MENOR);
            dia = saberDia(OBTER_DIA, ano, mes);
        }
    } else {
        dia = saberDia(OBTER_DIA, ano, mes);
    }
    arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.ano = ano;
    arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.mes = mes;
    arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.dia = dia;

    //OBTER DATA SAIDA
    if (obterResposta("| \n| Continua na empresa (s/n)? ") == -1) {
        puts(OBTER_DATA_SAIDA);
        do {
            ano = saberAno(OBTER_ANO);
        } while (ano < arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.ano);

        if (ano == arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.ano) {
            do {
                mes = saberMes(OBTER_MES, ano);
            } while (mes < arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.mes);
        } else {
            mes = saberMes(OBTER_MES, ano);
        }
        if (ano == arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.ano && mes == arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.mes) {
            do {
                dia = saberDia(OBTER_DIA, ano, mes);
            } while (dia < arrayRH->funcionarios_array[arrayRH->contador].entrada_emp.dia);
        } else {
            dia = saberDia(OBTER_DIA, ano, mes);
        }
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.ano = ano;
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.mes = mes;
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.dia = dia;
    } else {
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.ano = 0;
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.mes = 0;
        arrayRH->funcionarios_array[arrayRH->contador].saida_emp.dia = 0;
    }
    //TORNAR FUNCIONARIO ATIVO
    arrayRH->funcionarios_array[arrayRH->contador].ativo = 1;
    //INCREMENTAR CONTADOR
    arrayRH->contador++;  
    addMemoriaFunc(arrayRH);
}

//VERIFICAR SE FUNCIONARIO JA EXISTE 
/**
 * Verifica se funcionario ja existe na base de dados ou nao para poder ser adicionado
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void verificacaoAddFuncionarios(Empresa *arrayRH) {
    int codigo;
    while (1) {
        codigo = obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO);
        if (procurarFuncionario(arrayRH, codigo) != -1) {
            printf(FUNC_EXISTENTE);
            break;
        } else {
            addFuncionario(arrayRH, codigo);
            break;
        }
    }
}

// FAZER A ALTERAÇAO DOS DADOS DO FUNCIONARIO 
/**
 * Edita a informação de um funcionário escolhida
 * 
 * @param arrayRH tem array de memoria onde se encontram os funcionarios
 * @param posicao index da posicao do funcionario no array de memoria
 * @param opcao que o funcionario escolheu editar do funcionario
 */
void editarFuncionario(Empresa *arrayRH, int posicao, int opcao) {

    int dia, mes, ano;
    char resposta, cargo[MAX_CARGO];
    
    do {
        switch (opcao) {
            case 1:
                //ALTERAR TELEMOVEL
                arrayRH->funcionarios_array[posicao].numero_tlm = obterLong(MIN_NUM_TELE, MAX_NUM_TELE, OBTER_NUM_TELE);
                break;
            case 2:
                //ALTERAR ESTADO CIVIL
                arrayRH->funcionarios_array[posicao].est_civil = obterInt(0, 3, OBTER_EST_CIVIL);
                cleanInputBuffer();
                break;
            case 3:
                // ALTERAR NUMERO DE FILHOS
                arrayRH->funcionarios_array[posicao].numero_filhos = obterIntMin(0, OBTER_NUM_FILHOS);
                break;
            case 4:
                limparString(arrayRH->funcionarios_array[posicao].cargo); 
                
                // ALTERAR CARGO
                obterString(cargo, MAX_CARGO, OBTER_CARGO);
                strcpy(arrayRH->funcionarios_array[posicao].cargo, "");
                strcat(arrayRH->funcionarios_array[posicao].cargo, cargo);

                cleanInputBuffer();
                break;
            case 5:
                // ALTERAR VALOR HORA
                arrayRH->funcionarios_array[posicao].valor_hora = obterIntMin(0, OBTER_VALOR_HORA);
                break;
            case 6:
                // ALTERAR VALOR HORA ALIMENTACAO
                arrayRH->funcionarios_array[posicao].valor_sub_ali = obterIntMin(0, OBTER_SUB_ALI);
                break;
            case 7:
                // ALTERAR DATA DE SAIDA DA EMPRESA
                puts(OBTER_DATA_SAIDA);
                ano = saberAno(OBTER_ANO);
                mes = saberMes(OBTER_MES, ano);
                dia = saberDia(OBTER_DIA, ano, mes);
                arrayRH->funcionarios_array[posicao].saida_emp.ano = ano;
                arrayRH->funcionarios_array[posicao].saida_emp.mes = mes;
                arrayRH->funcionarios_array[posicao].saida_emp.dia = dia;
                break;
            case 0:
                break;
        }
        if (opcao != 0) {
            resposta = obterResposta("|\n| Deseja fazer mais alterações [s/n]?");
            if (resposta == 1) {
                opcao = obterInt(0, 7, "|\n| Digite o que quer editar: ");
            }
        } else {
            break;
        }
    } while (resposta == 's');
}

// MOSTRAR OS DADOS DO FUNCIONARIO 
/**
 * Mostra a informação guardada em memória do funcionario
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param posicao index do funcionario no arrya de memoria
 * @return opcao da informaçao a editar do funcionario 
 */
int infoFuncionario(Empresa *arrayRH, int posicao) {
    int opcao;
    printf("%s%s\n", OBTER_NOME, arrayRH->funcionarios_array[posicao].nome);
    printf("%s%ld\n", OBTER_NUM_TELE, arrayRH->funcionarios_array[posicao].numero_tlm);
    printf("%s%s\n", EST_CIVIL, est_civilToString(arrayRH->funcionarios_array[posicao].est_civil));
    printf("%s%d\n", OBTER_NUM_FILHOS, arrayRH->funcionarios_array[posicao].numero_filhos);
    printf("%s%s\n", OBTER_CARGO, arrayRH->funcionarios_array[posicao].cargo);
    printf("%s%.2f euros\n", OBTER_VALOR_HORA, arrayRH->funcionarios_array[posicao].valor_hora);
    printf("%s%.2f euros\n", OBTER_SUB_ALI, arrayRH->funcionarios_array[posicao].valor_sub_ali);
    printf("%s%d.%d.%d\n", OBTER_DATA_NASC, arrayRH->funcionarios_array[posicao].nascimento.dia, arrayRH->funcionarios_array[posicao].nascimento.mes, arrayRH->funcionarios_array[posicao].nascimento.ano);
    printf("%s%d-%d-%d\n", OBTER_DATA_ENT, arrayRH->funcionarios_array[posicao].entrada_emp.dia, arrayRH->funcionarios_array[posicao].entrada_emp.mes, arrayRH->funcionarios_array[posicao].entrada_emp.ano);
    if (arrayRH->funcionarios_array[posicao].saida_emp.dia != 0) { // se o funcionario ja nao estiver na empresa
        printf("%s%d-%d-%d\n", OBTER_DATA_SAIDA, arrayRH->funcionarios_array[posicao].saida_emp.dia, arrayRH->funcionarios_array[posicao].saida_emp.mes, arrayRH->funcionarios_array[posicao].saida_emp.ano);
    }
    do {
        puts("\n| Escolha o parametro que deseja alterar:");
        puts("| 1) Numero de telemovel");
        puts("| 2) Estado Civil");
        puts("| 3) Numero de filhos");
        puts("| 4) Cargo");
        puts("| 5) Valor hora");
        puts("| 6) Valor hora subsidio de alimentação");
        puts("| 7) Data de saida da empresa");
        puts("| 0) Voltar");
        printf("| Opção: ");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 7);

    editarFuncionario(arrayRH, posicao, opcao);

    return (opcao);

}

//VERIFICAR SE PODE EDITAR FUNCIONARIO
/**
 * Verifica se o funcionario existe na base de dados e está ativo para poder ser editado
 * Permite adicionar funcionario se nao existir na base de dados
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void verificacaoEditarFuncionarios(Empresa *arrayRH) {

    int codigo = obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO), posicao = procurarFuncionario(arrayRH, codigo);

    if (posicao != -1 && arrayRH->funcionarios_array[posicao].ativo == 1) {
        infoFuncionario(arrayRH, posicao);
    } else if (posicao != -1 && arrayRH->funcionarios_array[posicao].ativo != 1) {
        puts(ERRO_FUNCIONARIO);
        if (obterResposta("| Deseja adicionar um funcionário [s/n]?") == 1) {
            verificacaoAddFuncionarios(arrayRH);
        }
    } else {
        puts(FUNC_INEXISTENTE);
        if (obterResposta("| Deseja adicionar um funcionário com esse codigo [s/n]?") == 1) {
            cleanInputBuffer();
            addFuncionario(arrayRH, codigo);
        }
    }
}

//REMOVER FUNCIONARIOS
/**
 * remove funcionarios passando a “ativo” para 0;
 * 
 * @param arrayRH tem o array de memoria onde se encontram os funcionarios guardados
 */
void removerFuncionario(Empresa *arrayRH) {
    int i = procurarFuncionario(arrayRH, obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO));
    if (i != -1 && arrayRH->funcionarios_array[i].ativo == 1) {
        arrayRH->funcionarios_array[i].ativo = 0;
        puts(SUCESSO);
    } else if (i != -1 && arrayRH->funcionarios_array[i].ativo == 0) {
        printf(ERRO_REMOVIDO);
    } else {
        puts(FUNC_INEXISTENTE);
    }
}

//VERIFICAR SOMA DOS DIAS
/**
 * Verifica se o numero total de dias passados corresponde ao numero maximo de dias do mes
 * 
 * @param dias_compl numero de dias completos para adicionar
 * @param dias_meios numero de dias meio completos para adicionar
 * @param dias_fds numero de dias ao fim de semana para adicionar
 * @param dias_faltas numero de dias faltados para adicionar
 * @param mes do calculo salarial
 * @param ano do calculo salarial
 * @return valor 1 se total de dias nao corresponder com o mes
 */
int verificacaoDias(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, int mes, int ano) {

    if ((dias_compl + dias_meios + dias_fds + dias_faltas) > saberDiaMax(ano, mes)) {
        puts(DIAS_MAIOR_MES);
        return 1;
    }
    if ((dias_compl + dias_meios + dias_fds + dias_faltas) < saberDiaMax(ano, mes)) {
        puts(DIAS_FALTA_MES);
        return 1;
    }
}

//CALCULAR SALARIOS
/**
 * /**
 * Pede toda a informação referente aos dados salariais de um funcionario manualmente
 * Guarda a informaçao no array de memoria dos dados salariais
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param codigo do funcionario para identificacao nos arrays de memoria
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 * os ultimos 5 parametros sao necessarios para outra funcao
 */
void addSalarios(Lista_calc *conta, int codigo, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {
    int ano, mes, dias_compl, dias_meios, dias_fds, dias_faltas, ano_saida, mes_saida, dia_saida;

    if (arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].saida_emp.ano == 0) {
        ano_saida = defineData(3);
        mes_saida = defineData(2);
        dia_saida = defineData(1);
    } else {
        ano_saida = arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].saida_emp.ano;
        mes_saida = arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].saida_emp.mes;
        dia_saida = arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].saida_emp.dia;
    }
    puts(TITLE_CALC);
    ano = saberAno(OBTER_NUM_ANO);
    while (ano < arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].entrada_emp.ano || ano > ano_saida) {
        printf(DATA_INVALIDA_SALARIO, "ANO");
        ano = saberAno(OBTER_NUM_ANO);
    }
    mes = saberMes(OBTER_NUM_MES, ano);
    if (ano == ano_saida) {
        while (mes > mes_saida) {
            printf(DATA_INVALIDA_SALARIO, "MES");
            mes = saberMes(OBTER_NUM_MES, ano);
        }
    } else if (ano == arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].entrada_emp.ano) {
        while (mes < arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].entrada_emp.mes) {
            printf(DATA_INVALIDA_SALARIO, "MES");
            mes = saberMes(OBTER_NUM_MES, ano);
        }
    }
    printf("| Máximo de dias: %d\n", saberDiaMax(ano, mes));
    do {
        dias_compl = obterInt(MIN_DIAS_TRABALHO, saberDiaMax(ano, mes), OBTER_DIAS_COMPL);
        dias_meios = obterInt(MIN_DIAS_TRABALHO, saberDiaMax(ano, mes) - dias_compl, OBTER_DIAS_MEIOS);
        dias_fds = obterInt(MIN_DIAS_TRABALHO, 10, OBTER_DIAS_FDS);
        dias_faltas = obterInt(MIN_DIAS_TRABALHO, saberDiaMax(ano, mes) - (dias_compl + dias_meios + dias_fds), OBTER_DIAS_FALTAS);
    } while (verificacaoDias(dias_compl, dias_meios, dias_fds, dias_faltas, mes, ano) == 1);

    conta->dados_calculo_array[conta->contador].codigo = codigo;
    conta->dados_calculo_array[conta->contador].ano = ano;
    conta->dados_calculo_array[conta->contador].mes = mes;
    conta->dados_calculo_array[conta->contador].dias_compl = dias_compl;
    conta->dados_calculo_array[conta->contador].dias_meios = dias_meios;
    conta->dados_calculo_array[conta->contador].dias_fds = dias_fds;
    conta->dados_calculo_array[conta->contador].dias_faltas = dias_faltas;
    conta->dados_calculo_array[conta->contador].estado = 0;

    puts(SUCESSO);
    (conta->contador)++;
    
    addMemoriaDadosCalc(conta);

    if (obterResposta("| Deseja fazer o processamento salarial [s/n]? ") == 1) {
        menu_Calculo_salarial(conta, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
    }
}

//VERIFICAR EXISTENCIA DO FUNCIONARIO PARA CALCULO
/**
 * Verifica se o funcionario existe na base de dados e está ativo para se adicionar os dados do seu salario
 * 
 * @param conta tem o array de memoria dos dados salariais
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param taxa tem o array de memoria das taxas de SS
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 */
void verificacaoFuncionariosCalculo(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios) {
    int codigo = obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO);
    if (procurarFuncionario(arrayRH, codigo) != -1 && arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].ativo == 1) {
        addSalarios(conta, codigo, arrayRH, taxa, dois_titulares, unico_titular, nao_casado, salarios);
    } else if (procurarFuncionario(arrayRH, codigo) == -1) {
        puts(FUNC_INEXISTENTE);
        if (obterResposta("\n| Deseja adicionar o funcionário com esse codigo [s/n]?") == 1) {
            addFuncionario(arrayRH, codigo);
        }
    } else if (procurarFuncionario(arrayRH, codigo) != -1 && arrayRH->funcionarios_array[procurarFuncionario(arrayRH, codigo)].ativo != 1) {
        puts(FUNC_REMOVIDO);
    }
}