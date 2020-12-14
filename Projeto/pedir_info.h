#ifndef PEDIR_INFO_H
#define PEDIR_INFO_H


//CONSTANTES
#define MAX_FUNCIONARIOS 5 //pequeno por agora para testes

#define MAX_CODIGO 1000
#define MIN_CODIGO 0
#define OBTER_CODIGO "Código: "

#define MAX_NOME  50
#define OBTER_NOME "Nome: "

#define MAX_NUM_TELE 969999999
#define MIN_NUM_TELE 910000000
#define OBTER_NUM_TELE "Número de telemóvel: "

#define EST_CIVIL "Estado civi: "
#define CARGO "Cargo na empresa: "
#define OBTER_EST_CIVIL "Estado civil [0-Casado 1-Solteiro 2-Divorciado 3-Viúvo]: "
#define OBTER_NUM_FILHOS "Número de filhos: "
#define OBTER_CARGO "Cargo na empresa [0-Empregado 1-Chefe 2-Administrador]: "
#define OBTER_SALARIO "Salário por hora: "
#define OBTER_SUB_ALI "Subsídio de alimentação: "

#define MAX_DIA 31
#define MIN_DIA 1
#define MAX_MES 12
#define MIN_MES 1
#define MAX_ANO 2020 //temos de usar algo que define o ano em que tamos (acho)
#define MIN_ANO 1950

#define OBTER_DATA_NASC "Data de nascimento: "
#define OBTER_DATA_ENT "Data de entrada na empresa: "
#define OBTER_DATA_SAIDA "Data de saída da empresa: "

#define OBTER_DIA "Dia: "
#define OBTER_MES "Mes: "
#define OBTER_ANO "Ano: "

#define OBTER_NUM_MES "Numero do mes: "
#define OBTER_DIAS_COMPL "Numero de dias completos trabalhados: "
#define OBTER_DIAS_MEIOS "Numero de dias completos trabalhados: "
#define OBTER_DIAS_FDS "Numero de dias completos trabalhados: "
#define OBTER_DIAS_FALTAS "Numero de dias completos trabalhados: "

#define VALOR_INVALIDO " ! Valor inválido ! "
#define NOME_INVALIDO " ! Nome inválido ! "
#define FUNC_EXISTENTE " ! Funcionário já existente ! "
#define LISTA_CHEIA " ! Lista cheia ! "
#define DIAS_MAIOR_MES " ! Dias ultrapassam dias do mes ! "
#define FUNC_INEXISTENTE " ! Funcionario não existe ! "

#define SUCESSO "Operação realizada com sucesso"


//REGISTOS

//ESTADO CIVIL
typedef enum {
    CASADO, SOLTEIRO, DIVORCIADO, VIUVO
} Est_Civil;

//CARGO EMPRESA
typedef enum {
    EMPREGADO, CHEFE, ADMINISTRADOR
} Cargo;

//MES
typedef enum {
    JANEIRO=31,FEVEREIRO=28,MAR�O=31,ABRIL=30,MAIO=31,JUNHO=30,JULHO=31,AGOSTO=31,SETEMBRO=30,OUTUBRO=31,NOVEMBRO=30,DEZEMBRO=31
} Mes;
    
//DATAS
typedef struct {
    int dia, mes, ano;
} Data;

//FUNCIONARIO
typedef struct {
    //user info
    int codigo, numero_tlm, numero_filhos;
    char nome[MAX_NOME];
    Est_Civil est_civil;
    Cargo cargo;
    float valor_hora, valor_sub_ali;
    Data nascimento, entrada_emp, saida_emp;    
    
    //integers para o processamento salarial
    Mes mes;
    int dias_compl, dias_meios, dias_fds, dias_faltas; 
    
    //ativo ou nao
    //int ativo = 0; //da erro nao sei porque ainda
} Funcionario;

//ARRAY FUNCIONARIOS + CONTADOR
typedef struct {
    int contador;
    Funcionario funcionario_array[MAX_FUNCIONARIOS];
} Funcionarios;


//FUN�OES
int define_data(int pedido);
char *data_completa();
void cleanInputBuffer();
int obter_int(int min, int max, char *texto);
void obter_string(char *string, unsigned int tamanho, char *texto);
double obter_num(double min, double max, char *texto);
int addFuncionario(Funcionarios *funcionarios, int codigo);
int procurarFuncionario(Funcionarios funcionarios, int codigo);
int verificarFuncionario(Funcionarios funcionarios, int codigo);
int verificacao_addFuncionarios(Funcionarios funcionarios);
void editarFuncionario(Funcionarios *funcionarios, int posicao, int opcao);
int infoFuncionario(Funcionarios funcionarios, int posicao);
void verificacao_editarFuncionarios(Funcionarios *funcionarios);
void removerFuncionario(Funcionarios * funcionarios);
int obterNumDias(char *texto);
int verificacaoDias(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, Mes * mes);
void calcSalarial(Funcionarios * funcionarios);

#endif
