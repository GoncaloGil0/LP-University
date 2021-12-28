#ifndef FUNC_AUXILIARES_H
#define FUNC_AUXILIARES_H

#define QUESTAO_GUARDAR "\n+ Deseja guardar os dados [s/n]? "
#define APLICACAO_TERMINADA "\n+ A aplicação foi terminada com sucesso"

int defineData(int pedido);
void cleanInputBuffer();
int obterInt(int min, int max, char *texto);
float obterFloat(float min, float max, char *texto);
void obterString(char *string, unsigned int tamanho, char *texto);
long obterLong(long min, long max, char *texto);
int obterResposta(char *pergunta);
char * limparString(char *s);
int saberDiaMax(int ano, int mes);
int saberDia(char *TEXTO, int ano, int mes);
int saberMes(char *TEXTO, int ano);
int saberAno(char *TEXTO);
char *est_civilToString(Est_Civil tipo);
char *estadoToString(int proc);
char *ativoToString(int ativo);
int obterIntMin(int min, char *texto);
int procurarFuncionario(Empresa *arrayRH, int codigo);
void freeMemoria(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Tabela_SS *taxas);
void addMemoriaFunc(Empresa *arrayRH);
void addMemoriaDadosCalc(Lista_calc *conta);
void addMemoriaProcess(Lista_salarios *salarios);
void addMemoriaDoisTitulares(Tabelas *dois_titulares);
void addMemoriaUnicoTitular(Tabelas *unico_titular);
void addMemoriaNaoCasado(Tabelas *nao_casado);
void addMemoriaTaxas(Tabela_SS *taxa);
int posicaoTaxa(char *cargo, Tabela_SS *taxa);

#endif /* FUNC_AUXILIARES_H */

