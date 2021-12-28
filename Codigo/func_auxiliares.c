/* 
 * Ficheiro que contem todas as funções auxiliares do codigo
 *  @file func_auxiliares.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "pedir_info.h"
#include "menus.h"
#include "ficheiros.h"
#include "processar_info.h"
#include "func_auxiliares.h"

//FUNÇOES
//SABER PARTES DA DATA 
/**
 * Descobre o valor atual dos parametros de tempo
 * 
 * @param pedido valor da informaçao que se quer oter
 * @return do valor atual do parametro pedido
 */
int defineData(int pedido) {

    struct tm *data;
    time_t tempo;

    time(&tempo);
    data = localtime(&tempo);

    switch (pedido) {
        case 1:
            return (data->tm_mday); //retorna o dia caso receba o numero 1
        case 2:
            return (data->tm_mon + 1); // retorna o mes caso receba o numero 2
        case 3:
            return (data->tm_year + 1900); // retorna o ano caso receba o numero 3
        case 4:
            return (data->tm_hour); // retorna a hora caso receba o numero 4
        case 5:
            return (data->tm_min); // retorna o min caso receba o numero 5
        case 6:
            return (data->tm_sec); // // retorna o segundo caso receba o numero 6
    }
}

// SABER ANO
/**
 * Pede o ano para uma data, tendo em conta o ano máximo (corrente)
 * 
 * @param TEXTO string do que pedir ao utilizador
 * @return do ano aceite
 */
int saberAno(char *TEXTO) {
    int ano = obterInt(MIN_ANO, defineData(3), TEXTO);
    return ano;
}

// SABER MES
/**
 * Pede o mes de uma data, tendo em conta o mes máximo que pode ser aceite dependendo do ano
 * 
 * @param TEXTO string do que pedir ao utilizador
 * @param ano do mes em questao
 * @return do mes aceite
 */
int saberMes(char *TEXTO, int ano) {
    int mes;
    if (ano == defineData(3)) {
        mes = obterInt(MIN_MES, defineData(2), TEXTO);
    } else {
        mes = obterInt(MIN_MES, MAX_MES, TEXTO);
    }

    return mes;
}

// SABER DIA
/**
 * Pede o dia de uma data, tendo em conta o máximo de dias que o mes daquele ano pode ter
 * 
 * @param TEXTO string do que pedir ao utilizador
 * @param ano do dia em questao
 * @param mes do dia em questao
 * @return do dia aceite
 */
int saberDia(char *TEXTO, int ano, int mes) {
    return (obterInt(MIN_DIA, saberDiaMax(ano, mes), TEXTO));
}

// SABER DIA MAX
/**
 * Verifica o numero maximo de dias que um certo mes pode ter dependendo do ano, tendo em conta anos bissextos e datas atuais
 * 
 * @param ano do mes em questao
 * @param mes que se quer saber o numero maximo de dias
 * @return numero maximo de dias que o mes do ano passados pode ter
 */
int saberDiaMax(int ano, int mes) {
    int dia;
    int meses[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((ano % 4) == 0) { //bissextos 
        if (ano == defineData(3) && mes == defineData(2)) {
            dia = defineData(1);
        } else if (ano == defineData(3) && mes != 2) {
            dia = meses[mes];
        } else if (ano == defineData(3) && mes == 2) {
            dia = meses[mes] + 1;
        } else if (ano != defineData(3) && mes == 2) {
            dia = meses[mes] + 1;
        } else if (ano != defineData(3) && mes != 2) {
            dia = meses[mes];
        }
    } else { // nao bissextos 
        if (ano == defineData(3) && mes == defineData(2)) {
            dia = defineData(1);
        } else if (ano == defineData(3) && mes != 2) {
            dia = meses[mes];
        } else if (ano == defineData(3) && mes == 2) {
            dia = meses[mes];
        } else if (ano != defineData(3) && mes == 2) {
            dia = meses[mes];
        } else if (ano != defineData(3) && mes != 2) {
            dia = meses[mes];
        }
    }
    return dia;
}

//CLEAN BUFFER
/**
 * Limpa todo o buffer do sistema sempre que forem pedidos valores ao utilizador
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

//OBTER NUMEROS INTERIOS
/**
 * Pede um valor integer ao utilizador ate se encontrar entre os limites
 * 
 * @param min valor minimo
 * @param max valor maximo
 * @param texto string para pedir um valor ao utilizador
 * @return valor integer aceite do utilizador
 */
int obterInt(int min, int max, char *texto) {
    int valor;
    printf(texto);
    while (scanf(" %d", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//OBTER NUMEROS INTEIROS SEM MAXIMOS
/**
 * Pede um valor integer ao utilizador ate se encontrar acima dum minimo
 * 
 * @param min valor minimo
 * @param texto string para pedir um valor ao utilizador
 * @return valor integer aceite do utilizador
 */
int obterIntMin(int min, char *texto) {
    int valor;
    printf(texto);
    while (scanf(" %d", &valor) != 1 || valor < min) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//OBTER NUMEROS DECIMAIS
/**
 * Pede um valor float ao utilizador ate se encontrar entre os limites
 * 
 * @param min valor minimo
 * @param max valor maximo
 * @param mensagem string para pedir um valor ao utilizador
 * @return valor float aceite do utilizador
 */
float obterFloat(float min, float max, char *mensagem) {
    float numero;
    printf(mensagem);
    while (scanf(" %f", &numero) != 1 || numero < min || numero > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(mensagem);
    }
    cleanInputBuffer();
    return numero;
}

//OBTER STRINGS
/**
 * Pede uma string ao utilizador
 * 
 * @param string pointer para onde string será guardada
 * @param tamanho maximo da string a pedir
 * @param texto string para pedir uma string ao utilizador
 */
void obterString(char *string, unsigned int tamanho, char *texto) {
    int invalido, i;
    unsigned int len;
    do {
        invalido = 0;
        printf(texto);
        if (fgets(string, tamanho, stdin) != NULL) {
            len = strlen(string) - 1;
            if (string[len] == '\n') {
                string[len] = '\0';
            }
        }
    } while (invalido == 1);
}

//OBTER LONG
/**
 * Pede um valor long ao utilizador ate se encontrar entre os limites
 * 
 * @param min valor minimo
 * @param max valor maximo
 * @param texto string para pedir um valor ao utilizador
 * @return valor long aceite do utilizador
 */
long obterLong(long min, long max, char *texto) {
    long valor;
    printf(texto);
    while (scanf("%ld", &valor) != 1 || valor < min || valor > max) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(texto);
    }
    cleanInputBuffer();
    return valor;
}

//OBTER RESPOSTA
/**
 * Questiona o utilizador com uma pergunta de sim ou nao
 * 
 * @param pergunta string de questão a fazer ao utilizador
 * @return valor correspondente a resposta do utilizador (1 ou -1)
 */
int obterResposta(char *pergunta) {
    char resposta;
    printf(pergunta);
    scanf(" %c", &resposta);
    while (resposta != 's' && resposta != 'S' && resposta != 'n' && resposta != 'N') {
        cleanInputBuffer();
        puts(ERRO_RESPOSTA);
        printf(pergunta);
        scanf(" %c", &resposta);
    }
    puts("");
    if (resposta == 's' || resposta == 'S') {
        return 1;
    } else {
        return -1;
    }
    cleanInputBuffer();
}

//LIMPAR STRINGS
/**
 * Usada para limpar uma string
 * 
 * @param s string a libertar
 * @return da string
 */
char * limparString(char *s) {
    s[0]='\0';
    return s;
}

//CONVERSAO PARA STRING DO EST CIVIL
/**
 * Corresponde uma posiçao da enumeraçao do tipo Est_Civil a uma palavra
 * 
 * @param tipo valor da posiçao numa enumeração
 * @return palavra para a posicao recebida
 */
char *est_civilToString(Est_Civil tipo) {
    switch (tipo) {
        case CASADO:
            return "Casado";
            break;
        case SOLTEIRO:
            return "Solteiro";
            break;
        case DIVORCIADO:
            return "Divorciado";
            break;
        case VIUVO:
            return "Viúvo";
            break;
    }
}

//CONVERSAO PARA STRING DO PROCESSADO
/**
 * Corresponde aos valores de proc dos dados salariais uma palavra
 * 
 * @param proc valor a corresponder texto
 * @return palavra para o valor recebido
 */
char *estadoToString(int proc) {
    if (proc == 0) {
        return "Nao processado";
    } else if (proc == 1) {
        return "Processado";
    } else if (proc == -1) {
        return "Dados Incorretos";
    } else {
        return"ERRO";
    }
}

//CONVERSAO PARA STRING DO ATIVO
/**
 * Corresponde aos valores de ativo do funcionario uma palavra
 * 
 * @param ativo valor a corresponder texto
 * @return palavra para o valor recebido
 */
char *ativoToString(int ativo) {
    if (ativo == 0) {
        return "Removido";
    } else if (ativo == 1) {
        return "Ativo";
    } else if (ativo == -1) {
        return "Nao aceite";
    } else {
        return"ERRO";
    }
}

//PROCURAR FUNCIONARIO
/**
 * Encontra se o funcionario existe ou nao no array de memoria
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param codigo do funcionario a procurar
 * @return do index do funcionario no array de memoria ou -1 se nao existir funcionario
 */
int procurarFuncionario(Empresa *arrayRH, int codigo) {
    int i;
    for (i = 0; i < arrayRH->contador; i++) {
        if (arrayRH->funcionarios_array[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

//LIMPAR ARRAYS DE MEMORIA
/**
 * Liberta e apaga os apontadores de array de memoria
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 * @param conta tem o array de memoria dos dados salariais
 * @param salarios tem o array de memoria da tabela de processamentos salariais
 * @param dois_titulares tem o array de memoria da tabela de IRS de dois titulares
 * @param unico_titular tem o array de memoria da tabela de IRS de um titular
 * @param nao_casado tem o array de memoria da tabela de IRS de nao casado
 * @param taxa tem o array de memoria das taxas de SS
 */
void freeMemoria(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Tabela_SS *taxa) {
     
    arrayRH->funcionarios_array = NULL;
    free(arrayRH->funcionarios_array);

    conta->dados_calculo_array = NULL;
    free(conta->dados_calculo_array);

    salarios->calculo_array = NULL;
    free(salarios->calculo_array);
    
    dois_titulares->tabela = NULL;
    free(dois_titulares->tabela);
    
    unico_titular->tabela = NULL;
    free(unico_titular->tabela);
    
    nao_casado->tabela = NULL;
    free(nao_casado->tabela);
   
    taxa->taxa_array = NULL;
    free(taxa->taxa_array);

}

//ADICIONAR MEMORIA DINAMICA
/**
 * Adiciona um espaço de memoria ao array dos funcionarios
 * 
 * @param arrayRH tem o array de memoria dos funcionarios
 */
void addMemoriaFunc(Empresa *arrayRH){
    
    Funcionario *temp = (Funcionario*) realloc(arrayRH->funcionarios_array, (arrayRH->contador * sizeof (Funcionario)) + sizeof (Funcionario));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    arrayRH->funcionarios_array = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria ao array dos dados salarios
 * 
 * @param conta tem o array de memoria dos dados salariais
 */
void addMemoriaDadosCalc(Lista_calc *conta){
    Conta *temp = (Conta*) realloc(conta->dados_calculo_array, conta->contador * sizeof (Conta) + sizeof (Conta));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    conta->dados_calculo_array = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria ao array dos salarios processados
 * 
 * @param conta tem o array de memoria dos salarios
 */
void addMemoriaProcess(Lista_salarios *salarios){

    Calculo *temp = (Calculo*) realloc(salarios->calculo_array, salarios->contador * sizeof (Calculo) + sizeof (Calculo));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    } else {
    }
    salarios->calculo_array = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria a tabela dos dois titulares
 * 
 * @param dois_titulares tem o array de memoria da tabela dos dois titulares
 */
void addMemoriaDoisTitulares(Tabelas *dois_titulares){
    IRS *temp = (IRS*) realloc(dois_titulares->tabela, dois_titulares->contador * sizeof (IRS) + sizeof (IRS));
    
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    dois_titulares->tabela = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria a tabela do unico titular
 * 
 * @param dois_titulares tem o array de memoria da tabela dos dois titulares
 */
void addMemoriaUnicoTitular(Tabelas *unico_titular){
    IRS *temp = (IRS*) realloc(unico_titular->tabela, unico_titular->contador * sizeof (IRS) + sizeof (IRS));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    unico_titular->tabela = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria a tabela dos nao casados
 * 
 * @param nao_casado tem o array de memoria da tabela dos nao casado
 */
void addMemoriaNaoCasado(Tabelas *nao_casado){
    IRS *temp = (IRS*) realloc(nao_casado->tabela, nao_casado->contador * sizeof (IRS) + sizeof (IRS));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    nao_casado->tabela = temp;
    temp = NULL;
    free(temp);
}

/**
 * Adiciona um espaço de memoria a tabela de taxas de SS
 * 
 * @param taxa tem o array de memoria das taxas de SS
 */
void addMemoriaTaxas(Tabela_SS *taxa){
    Taxas *temp = (Taxas*) realloc(taxa->taxa_array, taxa->contador * sizeof (Taxas) + sizeof (Taxas));
    if (temp == NULL) {
        puts(ERRO_MEMORIA);
    }
    taxa->taxa_array = temp;
    temp = NULL;
    free(temp);
}

//ENCONTRAR POSICAO DE TAXAS SS
/**
 * encontra a posicao das taxas de um certo cargo na memoria
 * 
 * @param cargo a procurar por
 * @param taxa tem o array de memoria das taxas de SS
 * @return posiçao dos valores corretos na memoria ou -1 se nao existir
 */
int posicaoTaxa(char *cargo, Tabela_SS *taxa){
    for (int x=0; x!=taxa->contador;x++){
        if (strcmp(cargo, taxa->taxa_array[x].cargo) == 0){
            return x;
            break;
        }
    }
    return -1;
}