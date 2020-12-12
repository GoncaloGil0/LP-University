#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pedir_info.h"
#include "menus.h"
//#include "processar_info.h"


//FUNÇOES


//CLEAN BUFFER

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//OBTER NUMEROS

int obterInt(int min, int max, char *texto) {
    int valor;
    printf(texto);
    while (scanf("%d", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//OBTER STRINGS

void obterString(char *string, unsigned int tamanho, char *texto) {
    printf(texto);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

//OBTER DOUBLES

double obterNum(double min, double max, char *texto) {
    double valor;
    printf(texto);
    while (scanf("%lf", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}



//PROCURAR FUNCIONARIO

int procurarFuncionario(Funcionarios funcionarios, int codigo) {
    int i;
    for (i = 0; i < funcionarios.contador; i++) {
        if (funcionarios.funcionario_array[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}



//INPUTS DO FUNCIONARIO
int addFuncionario(Funcionarios *funcionarios, int codigo) {


    //VARIAVEIS LOCAIS
    int est_civil, cargo;
    char saida;

    

    //ASSOCIAR CODIGO
    funcionarios->funcionario_array[funcionarios->contador].codigo = codigo;



    //OBTER NOME
    obterString(funcionarios->funcionario_array[funcionarios->contador].nome, MAX_NOME, OBTER_NOME);



    //OBTER NUMERO TELEMOVEL
    double numero_tlm = obterNum(MIN_NUM_TELE, MAX_NUM_TELE, OBTER_NUM_TELE);
    funcionarios->funcionario_array[funcionarios->contador].numero_tlm = numero_tlm;



    //OBTER ESTADO CIVIL
    do {
        puts(OBTER_EST_CIVIL);
        scanf("%d", &est_civil);
    } while (est_civil > 3 || est_civil < 0);
    funcionarios->funcionario_array[funcionarios->contador].est_civil = est_civil;
    cleanInputBuffer();



    //OBTER NUMERO FILHOS
    puts(OBTER_NUM_FILHOS);
    scanf("%d", &funcionarios->funcionario_array[funcionarios->contador].numero_filhos);
    cleanInputBuffer();



    //OBTER CARGO NA EMPRESA
    do {
        puts(OBTER_CARGO);
        scanf("%d", &cargo);
    } while (cargo > 2 || cargo < 0);
    funcionarios->funcionario_array[funcionarios->contador].cargo = cargo;
    cleanInputBuffer();



    //OBTER SALARIO
    puts(OBTER_SALARIO);
    scanf("%f", &funcionarios->funcionario_array[funcionarios->contador].valor_hora);
    cleanInputBuffer();



    //OBTER SUBSIDIO ALIMENTACAO
    puts(OBTER_SUB_ALI);
    scanf("%f", &funcionarios->funcionario_array[funcionarios->contador].valor_sub_ali);
    cleanInputBuffer();



    //OBTER DATA NASCIMENTO
    puts(OBTER_DATA_NASC);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.dia = obterInt(MIN_MES, MAX_MES, OBTER_MES);
    funcionarios->funcionario_array[funcionarios->contador].nascimento.dia = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);



    //OBTER DATA ENTRADA
    puts(OBTER_DATA_ENT);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.dia = obterInt(MIN_MES, MAX_MES, OBTER_MES);
    funcionarios->funcionario_array[funcionarios->contador].entrada_emp.dia = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);



    //VERIFICAR SE CONTINUA NA EMPRESA
    do {
        printf("\nContinua na empresa (s/n)?: ");
        scanf(" %c", &saida);
    } while (saida != 'n' && saida != 's');
    cleanInputBuffer();



    //OBTER DATA SAIDA
    if (saida == 'n') {
        puts(OBTER_DATA_SAIDA);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.dia = obterInt(MIN_DIA, MAX_DIA, OBTER_DIA);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.dia = obterInt(MIN_MES, MAX_MES, OBTER_MES);
        funcionarios->funcionario_array[funcionarios->contador].saida_emp.dia = obterInt(MIN_ANO, MAX_ANO, OBTER_ANO);
    } else {
        // temos de atribuir um valor a data quando ele ainda esta na empresa para podermos fazer os calculos dps
    }



    //TORNAR FUNCIONARIO ATIVO
    //funcionarios->funcionario_array[funcionarios->contador].ativo = 1;



    //INCREMENTAR CONTADOR
    return funcionarios->contador++;
}




//VERIFICAR SE PODE ADICIONAR FUNCIONARIO OU SEJA SE JA EXISTE 
int verifFuncionario (Funcionarios funcionarios, int codigo) {
    if (procurarFuncionario(funcionarios, codigo) != -1) {
        return -1;
    }
    addFuncionario(&funcionarios, codigo);
}



//VERIFICAR SE LISTA DE FUNCIONARIOS ESTA CHEIA

int addFuncionarios(Funcionarios funcionarios) {
    if (funcionarios.contador < MAX_FUNCIONARIOS) {
        if (verifFuncionario(funcionarios, obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO)) == -1) {
            puts(FUNC_EXISTENTE);
            return 1;
        }
    } else {
        puts(LISTA_CHEIA);
        return -1;
    }
}



//VERIFICAR SE PODE EDITAR FUNCIONARIO

void editarFuncionarios(Funcionarios *funcionarios) {
    int codigo = obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO);
    int numero = procurarFuncionario(*funcionarios, codigo);
    if ( numero != -1) {
        addFuncionario( &funcionarios->funcionario_array[numero], codigo);
    } else {
        puts(FUNC_INEXISTENTE);
    }
}




//REMOVER FUNCIONARIOS

void removerFuncionarios(Funcionarios *funcionarios) {
    int i, numero = procurarFuncionario(*funcionarios, obterInt(MIN_CODIGO, MAX_CODIGO, OBTER_CODIGO));
    if (numero != -1) {
        i = numero;
        //funcionarios->funcionario_array[i].ativo = 0;
        puts(SUCESSO);
    } else {
        puts(FUNC_INEXISTENTE);
    }
}



//OBTER NUMERO DE DIAS NO MES

int obterNumDias(char *texto) {
    int valor;
    printf(texto);
    scanf("%d", &valor);
    return valor;
    cleanInputBuffer();
}



//VERIFICAR SOMA DOS DIAS

int verificacaoDias(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, Mes *mes) {
    int soma = dias_compl + dias_meios + dias_fds + dias_faltas;
    if (soma>*(mes--)) { //para assinalar pela contagem do array da enum, pois ninguem vais escrever 0 para janeiro por exemplo
        puts(DIAS_MAIOR_MES);
        return -1;
    }
    return 0;
}



//CALCULAR SALARIOS

void calcSalarial(Funcionarios *funcionarios) {
    do {
        funcionarios->funcionario_array[funcionarios->contador].mes = obterNumDias(OBTER_NUM_MES); //se o mes mudar, o resto nao muda pois nao?
        funcionarios->funcionario_array[funcionarios->contador].dias_compl = obterNumDias(OBTER_DIAS_COMPL);
        funcionarios->funcionario_array[funcionarios->contador].dias_meios = obterNumDias(OBTER_DIAS_MEIOS);
        funcionarios->funcionario_array[funcionarios->contador].dias_fds = obterNumDias(OBTER_DIAS_FDS);
        funcionarios->funcionario_array[funcionarios->contador].dias_faltas = obterNumDias(OBTER_DIAS_FALTAS);
    } while (verificacaoDias(funcionarios->funcionario_array[funcionarios->contador].dias_compl,
            funcionarios->funcionario_array[funcionarios->contador].dias_meios,
            funcionarios->funcionario_array[funcionarios->contador].dias_fds,
            funcionarios->funcionario_array[funcionarios->contador].dias_faltas,
            &funcionarios->funcionario_array[funcionarios->contador].mes)
            == -1);
}
