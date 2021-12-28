#ifndef FICHEIROS_H
#define FICHEIROS_H

//NOME DOS DOCUMENTOS PASTA PROGRAMA
#define FILENAME_USERS "PROGRAMA\\USERS\\users.bin"
#define FILENAME_SALARIOS "PROGRAMA\\SALARIOS\\salarios.bin"
#define FILENAME_DEPENDENTE_CASADO_DOIS_TITULARES "PROGRAMA\\TABELAS_RETENCAO_IRS\\DEPENDENTE_CASADO_DOIS_TITULARES_bin"
#define FILENAME_DEPENDENTE_CASADO_UNICO_TITULAR "PROGRAMA\\TABELAS_RETENCAO_IRS\\DEPENDENTE_CASADO_UNICO_TITULAR_bin"
#define FILENAME_DEPENDENTE_NAO_CASADO "PROGRAMA\\TABELAS_RETENCAO_IRS\\DEPENDENTE_NAO_CASADO_bin"
#define FILENAME_SS "PROGRAMA\\SEGURANCA_SOCIAL\\TAXAS.bin"
#define FILENAME_SALARIOS_PROCESSADOS "PROGRAMA\\CALCULO\\SALARIOS_PROCESSADOS_bin"

//NOME DOS DOCUMENTOS PASTA UTILIZADOR
#define FILENAME_USERS_TEXTO "UTILIZADOR\\TEXT_FILES\\FUNCIONARIOS_TEXTO.txt"
#define FILENAME_SALARIOS_TEXTO "UTILIZADOR\\TEXT_FILES\\SALARIOS_TEXTO.txt"
#define FILENAME_CALCULOS_TEXTO "UTILIZADOR\\TEXT_FILES\\CALCULOS_TEXTO.txt"
#define FILENAME_LOG "LOGS\\logs.bin"
#define FILENAME_USERS_DOC "UTILIZADOR\\FUNCIONARIOS\\funcionarios.txt"
#define FILENAME_SALARIOS_DOC "UTILIZADOR\\SALARIOS\\"

//TIPO DE FORMATO DE LEITURA 
#define FORMATO_USERS "%d %[^ ] %ld %d %d %d %[^ ] %f %f %d %d %d %d %d %d %d %d %d %d "
#define FORMATO_SALARIOS "%d %d %d %d %d %d %d"
#define FORMATO_SS "%f %f %f %f %f %f"
#define FORMATO_TABELA "%d %f %f %f %f %f %f"

//TIPO DE FORMATO DE ESCRITA
#define FORMATO_USERS_TEXTO "%d %s %ld %d %d %d %s %0.2f %0.2f %d %d %d %d %d %d %d %d %d\n"
#define FORMATO_SALARIOS_TEXTO "%d %d %d %d %d %d %d %d\n"
#define FORMATO_CALCULOS_TEXTO "%d %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f\n"
#define FORMATO_LOGS "DIA: %d-%02d-%02d HORA: %02d:%02d:%02d | %s\n"

//TIPO DE FORMATO PARA MOSTRAR O QUE FOI GUARDADO
#define FORMATO_MOSTRAR_SALARIOS "| Codigo: %d | Ano: %d | Mes: %d | Dias Completos: %d | Meios dias: %d | Fins de semana: %d | Faltas: %d | Estado: %s\n"
#define FORMATO_MOSTRAR_USERS "\n+ FUNCIONARIO +\n| Codigo: %d \n| Nome: %s \n| Numero de telemovel: %ld \n| Estado civil: %s \n| Numero de titulares: %d \n| Numero de filhos: %d \n| Cargo: %s \n| Valor hora: %0.2f \n| Subsidio de alimentação: %0.2f \n| Data de nascimento: %d-%d-%d \n| Data de entrada na empresa: %d-%d-%d \n| Data de saida da empresa: %d-%d-%d \n| Estado: %s \n"
#define FORMATO_MOSTRAR_USERS_EMPRESA "\n+ FUNCIONARIO +\n| Codigo: %d \n| Nome: %s \n| Numero de telemovel: %ld \n| Estado civil: %s \n| Numero de titulares: %d \n| Numero de filhos: %d \n| Cargo: %s \n| Valor hora: %0.2f \n| Subsidio de alimentação: %0.2f \n| Data de nascimento: %d-%d-%d \n| Data de entrada na empresa: %d-%d-%d \n| Estado: %s \n"
#define FORMATO_CRITERIOS "| 1) Geral entidade patronal: %0.2f \n| 2) Geral Trabalhador: %0.2f \n| 3) Chefia entidade patronal: %0.2f \n| 4) Chefia trabalhador: %0.2f \n| 0) Sair \n"
#define FORMATO_MOSTRAR_TABELAS "| %d %0.3f %0.3f %0.3f %0.3f %0.3f %0.3f \n"
#define FORMATO_MENU_ALTERAR_IRS "| 1) Tabela dois titulares \n| 2) Tabela unico titular \n| 3) Tabela nao casado \n| 0) sair \n| Opção: "
#define FORMATO_LISTA_FICHEIROS "\n+ FICHEIRO +\n| 1) Listagem de funcionarios \n| 2) Listagem de dados para cálculos\n| 3) Listagem de cálculos processados\n| 0) Voltar\n| Opção: "
#define FORMATO_MOSTRAR_SS "| Cargo: %s \n| Entidade patronal: %0.3f \n| Entidade trabalhadora: %0.3f \n"
#define FORMATO_MOSTRAR_SALARIOS_LISTAGENS "| Codigo: %d \n| Ano: %d \n| Mes: %d \n| Dias Completos: %d \n| Meios dias: %d \n| Fins de semana: %d \n| Faltas: %d \n| Estado: %s\n"

//MENSAGENS
#define IMPORTADA " Importada "
#define ERRO_FILE "| !Ficheiro não encontrado! "
#define SUCESSO_FILE "| Ficheiro aberto com sucesso"
#define PERGUNTA_INFO_GUARDADA "|\n| Deseja ver a informação guardada [s/n]? "
#define SUCESSO_ALTERACAO "| Alteração feita com sucesso"
#define ERRO_MEMORIA "| Problemas na memoria "
#define NAO_EXISTEM "\n+ !Nao existem %s no sistema! \n"
#define ERRO_VENCIMENTO "| !O vencimento inserido não é valido! "
#define ERRO_SS_NAO_EXISTENTE "| !Cargo nao existente nas taxas! "
#define ERRO_SS_EXISTENTE "| !Cargo ja existente nas taxas! "

//FUNÇÕES
int importar_users_sys(Empresa *arrayRH); 
int importar_salarios_sys(Lista_calc *conta); 
void importar_users_doc(Empresa *arrayRH);
void importar_salarios_doc(Lista_calc *conta, Empresa *arrayRH, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Lista_salarios *salarios);
void guardar(Empresa *arrayRH, Lista_calc *conta, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, Tabela_SS *taxa, Lista_salarios *salarios); 
void importarDoisTitulares(Tabelas *dois_titulares);
void importarUnicoTitular(Tabelas *unico_titular);
void importarNaoCasado(Tabelas *nao_casado);
void importarTablelaSS(Tabela_SS *taxa);
void logs(char *mensagem);
void alterarCriterioSS(Tabela_SS *taxa);
void mostrarSS(Tabela_SS *taxa);
void mostrarTabelas(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
void alterarCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
int verificarVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
int importar_salarios_proc_sys(Lista_salarios *salarios);
void limpar_memoria(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios);
void criarFicheirosUser(Empresa *arrayRH, Lista_calc *conta, Lista_salarios *salarios);
int verificacaoDiasDoc(int dias_compl, int dias_meios, int dias_fds, int dias_faltas, int mes, int ano);
void addCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
int posicaoVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
void apagarCriterioIRS(Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
int linhaVencimento(int tabela, int vencimento, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
void addCriterioSS(Tabela_SS *taxa);
void alterarCriterioSS(Tabela_SS *taxa);
void removerCriterioSS(Tabela_SS *taxa);

#endif /* FICHEIROS_H */

