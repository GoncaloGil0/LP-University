#ifndef PROCESSAR_INFO_H
#define PROCESSAR_INFO_H

//CONSTANTES 
#define TEMPO_MAXIMO 47
#define IDADE_MAXIMA 65

//FORMATOS DE TEXTO
#define FORMATO_MOSTRAR_SALARIOS_TODOS "\n+VENCIMENTO+\n| Codigo: %d \n| Vencimento iliquido: %0.1f \n| Bonus: %0.1f \n| Sub. Alimentação: %0.1f \n| Segurança Social Entidade patronal: %0.1f \n| Segurança Social Entidade pessoal: %0.1f \n| IRS: %0.1f \n| Vencimento Liquido: %0.1f\n| Encargo Total da empresa: %0.1f \n"
#define FORMATO_GUARDAR_DOC_SALARIOS "\n+VENCIMENTO+\n| Nome: %s \n| Codigo: %d \n| Data: %d/%d \n| Vencimento iliquido: %0.1f \n| Bonus: %0.1f \n| Sub. Alimentação: %0.1f \n| Segurança Social Entidade patronal: %0.1f \n| Segurança Social Entidade pessoal: %0.1f \n| IRS: %0.1f \n| Vencimento Liquido: %0.1f\n| Encargo Total da empresa: %0.1f \n"

//FICHEIROS
#define FILENAME_RELATORIOS "UTILIZADOR\\RELATORIOS\\RELATORIO.txt"

//PERGUNTAS
#define PERGUNTA_VER_SALARIOS "| Deseja ver todos os salarios processados [s/n]? "

//INFORMAÇÃO
#define TITULO_SALARIOS_PROC "\n+ SALARIOS CALCULADOS +"

//MENSAGENS (ERRO OU SUCESSO)
#define ERRO_DATABASE "| O Codigo nº %d não se encontra no database \n"
#define ERRO_NAO_SALARIOS "| Não existem salarios para processar \n"
#define INFO_SALARIOS_PROC "| Foram processados %d salarios \n"

//FUNÇÕES
float saberSS(int entidade, int codigo, Empresa *arrayRH, Tabela_SS *taxa);
float saberIRS(int vencimento, int codigo, Empresa *arrayRH, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado);
void processamento(Lista_salarios *salarios, Empresa *arrayRH, Lista_calc *dados_salariais, Tabela_SS *taxa, Tabelas *dois_titulares, Tabelas *unico_titular, Tabelas *nao_casado, int acao);
float saberBonus(Empresa *arrayRH, Lista_calc *conta, int posicao, int dia_max, int x);

#endif /* PROCESSAR_INFO_H */


