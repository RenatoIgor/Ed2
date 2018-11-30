#include <stdio.h> //para reconhecer o tipo FILE, caso nao, declararia void ler();

struct Empregado
{	
	int num_dependentes;
	int indice;
	int codEmpregado;
	int idade;
	float sal;
	char nome[50];
};

struct Dependente
{	
	int indiceDependente;
	int codDependente;
	int codEmpregado;
	int idadeDependente;
	char nomeDependente[50];
};

// FUNCOES EMPREGADO
int funcao_hash(int cod);
int compararEMPREGADO(struct Empregado x, struct Empregado y);
void inserirEMPREGADO(struct Empregado lista[], int codEmpregado, float salario, int anos, char nome[]);
//void buscar(char nome[], int codEmpregado);
void buscarCod(struct Empregado lista[]);
void buscarNomeEMPREGADO(char nome[],struct Empregado lista[]);
void buscarIdadeEMPREGADO(int anos_idade, struct Empregado lista[]);
void buscarSalarioEMPREGADO(float salarioAtual, struct Empregado lista[]);
void buscarNumDependentesEMPREGADO(int qnt_dependentes, struct Empregado lista[]);
void alterarRegistroEmpregado(struct Empregado lista[], char nome[] , int codEmpregado);

void remover(char nome[], int codEmpregado);
void gravar(struct Empregado lista[]);
void ler(struct Empregado lista[]);

//**********************************************************************************************************************************//

// FUNCOES DEPENDENTES
void inserirDependente(struct Dependente tabela[],struct Empregado lista[], int codDependente, int codEmpregado, char nome[], int idade);
//void buscarDependente(char nome[], int codDependente);
void buscarNomeDependente(char nome[],struct Dependente tabela[]);
void buscarIdadeDependente(int anos_idade, struct Dependente tabela[]);
void buscarDependente_NomeEmpregado(char nomeEmpregado[],struct Dependente tabela[], struct Empregado lista[]);
void alterarRegistroDependente(struct Dependente tabela[], char nome[] , int codDependente);


void gravarTabelaDEPENDENTES(struct Dependente tabela[]);
void lerTabelaDEPENDENTES(struct Dependente tabela[]);
void removerDependente(char nome[], int codDependente);

/*
void removerDependente(char nome[], int codDependente);
void gravarTabelaDEPENDENTES(struct Dependente tabela[]);
void lerTabelaDEPENDENTES(struct Dependente tabela[]);*/