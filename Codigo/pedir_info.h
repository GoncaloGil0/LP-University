#ifndef PEDIR_INFO_H
#define PEDIR_INFO_H

//CONSTANTES
#define MAX_CODIGO 9999
#define MIN_CODIGO 1
#define OBTER_CODIGO "| Código: "

#define MAX_CARGO 50
#define MAX_NOME  50
#define OBTER_NOME "| Nome: "

#define MAX_NUM_TELE 969999999
#define MIN_NUM_TELE 910000000
#define OBTER_NUM_TELE "| Número de telemóvel: "

#define EST_CIVIL "| Estado civil: "
#define OBTER_EST_CIVIL "| Estado civil [0-Casado 1-Solteiro 2-Divorciado 3-Viuvo]: "
#define OBTER_TITULARES "| Numero de titulares: "
#define OBTER_NUM_FILHOS "| Número de filhos: "
#define OBTER_CARGO "| Cargo na empresa: "
#define OBTER_VALOR_HORA "| Valor por hora: "
#define OBTER_SUB_ALI "| Subsidio de alimentação: "

#define MIN_DIA 1
#define MAX_MES 12
#define MIN_MES 1
#define MIN_ANO 1950

#define OBTER_DATA_NASC "| Data de nascimento: "
#define OBTER_DATA_ENT "| Data de entrada na empresa: "
#define OBTER_DATA_SAIDA "| Data de saída da empresa: "

#define OBTER_DIA "| Dia: "
#define OBTER_MES "| Mes: "
#define OBTER_ANO "| Ano: "

#define TITLE_CALC "| Insira os dados para o calculo\n"
#define OBTER_NUM_ANO "| Ano: "
#define OBTER_NUM_MES "| Mes: "
#define OBTER_DIAS_COMPL "| Numero de dias completos trabalhados: "
#define OBTER_DIAS_MEIOS "| Numero de meios dias trabalhados: "
#define OBTER_DIAS_FDS "| Numero de dias trabalhados ao fim de semana: "
#define OBTER_DIAS_FALTAS "| Numero de dias de faltas: "
#define MIN_DIAS_TRABALHO 0

#define VALOR_INVALIDO "| !VALOR INVALIDO! "
#define NOME_INVALIDO "| !NOME INVALIDO!\n"
#define FUNC_EXISTENTE "| !FUNCIONARIO JÁ EXISTENTE!\n"
#define LISTA_CHEIA "| !LISTA CHEIA!\n"
#define DIAS_MAIOR_MES "| !DIAS ULTRAPASSAM OS DIAS DO MES!\n"
#define DIAS_FALTA_MES "| !NUMERO DE DIAS INCORRETO!\n"
#define FUNC_INEXISTENTE "| !FUNCIONARIO INEXISTÊNTE!\n"
#define DATA_IVALIDA_MENOR "| !DATA INVALIDA (MENOR DE IDADE)!"
#define DATA_INVALIDA_SALARIO "| !O FUNCIONARIO NAO SE ENCONTRA NA EMPRESA NESSE %s!\n"
#define FUNC_REMOVIDO "| !FUNCIONARIO ENCONTRA-SE REMOVIDO!\n"

#define SUCESSO "| Operação realizada com sucesso\n"
#define ERRO "| !Algo deu errado!\n"
#define ERRO_RESPOSTA "| !Resposta invalida!\n"
#define ERRO_FUNCIONARIO "| !Funcionário inacessível!\n"
#define ERRO_REMOVIDO "| !Funcionário já removido!\n"
//REGISTOS

//ESTADO CIVIL
typedef enum {
    CASADO, SOLTEIRO, DIVORCIADO, VIUVO
} Est_Civil;

//DATAS
typedef struct {
    int dia, mes, ano;
} Data;

//FUNCIONARIO INFO
typedef struct {
    long numero_tlm;
    int codigo, numero_filhos, titulares;
    char nome[MAX_NOME], cargo[MAX_CARGO];
    Est_Civil est_civil;
    
    float valor_hora, valor_sub_ali;
    Data nascimento, entrada_emp, saida_emp;
    int ativo; // 0 = ativo e 1 = inativo
} Funcionario;

//ARRAY FUNCIONARIOS
typedef struct {
    int contador;
    Funcionario *funcionarios_array;
} Empresa;

//CACLCULO SALARIAL
typedef struct {
    int codigo, dias_compl, dias_meios, dias_fds, dias_faltas, mes, ano, estado; //estado==1 ja foi processado, estado==0 nao foi ainda
} Conta;

//ARRAY CALCULOS
typedef struct {
    int contador;
    Conta *dados_calculo_array;
} Lista_calc;

//TADELAS IRS
typedef struct {
    float filho_zero, filho_um, filho_dois, filho_tres, filho_quatro, filho_cinco;
    int vencimento;
} IRS;

//ESTRUTURA DAS LISTAS DO IRS
typedef struct{
    int contador;
    IRS *tabela;
} Tabelas;

//TAXAS SS
typedef struct {
    float empregadora, trabalhador;
    char cargo[MAX_CARGO];
} Taxas;

typedef struct{
    int contador;
    Taxas *taxa_array;
} Tabela_SS;

//CALCULO
typedef struct{ 
    int codigo;
    float venc_liquido, venc_iliquido, encargo_total_emp, irs, sub_ali, bonus, ss_ent_patronal, ss_ent_pessoal;
} Calculo;

typedef struct{ 
    int contador;
    Calculo *calculo_array;
} Lista_salarios;

//FUNÇÕES

void verificacaoAddFuncionarios(Empresa *arrayRH);
void verificacaoEditarFuncionarios(Empresa *arrayRH);
int verificacaoDias(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, int mes, int ano);
void verificacaoFuncionariosCalculo(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void editarFuncionario(Empresa *arrayRH, int posicao, int opcao);
int infoFuncionario(Empresa *arrayRH, int posicao);
void removerFuncionario(Empresa * arrayRH);
void addSalarios(Lista_calc *conta, int codigo, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void addFuncionario(Empresa *arrayRH, int codigo);

#endif
