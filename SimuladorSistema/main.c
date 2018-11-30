#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

#define MENU_PRINCIPAL 0
#define MENU_EMPREGADO 1
#define MENU_DEPENDENTE 2
#define MENUBUSCA_EMPREGADO 11
#define MENUBUSCA_DEPENDENTE 21

#define SAIR 3

int menuAtual = MENU_PRINCIPAL;
int proximoMenu = MENU_PRINCIPAL;

struct Empregado tab[M];
struct Empregado buscaNome[M];
struct Dependente tabDependente[M];


void menuPrincipal();
void menuEmpregado();
void menuDependente();
void submenuEmpregado();
void submenuDependente();

int main(void){
 	
 	iniciaTabela(tab);
  	//gravar(tab);	
  	iniciaTabelaDependentes(tabDependente);
 	//gravarTabelaDEPENDENTES(tabDependente);

  int sair = 0;

  while (!sair)
  {printf("\n\t\t<======= SIMULADOR DE CONSULTA =======>\n\n");
    menuAtual = proximoMenu;
    switch (menuAtual)
    {
      case MENU_PRINCIPAL:
        menuPrincipal();
        break;

      case MENU_EMPREGADO:
        menuEmpregado();
        break;

      case MENU_DEPENDENTE:
        menuDependente();
        break;

      case MENUBUSCA_EMPREGADO:
        submenuEmpregado();
        break;  

      case MENUBUSCA_DEPENDENTE:
        submenuDependente();
        break;

      default:
        sair = 1;
        break;
    }
    
  }

	return 0;
}

void menuPrincipal()
{
  printf("Menu Principal\n");
  printf("1 - Empregado\n");
  printf("2 - Dependente\n");
  printf("3 - Sair\n");

  int escolhaMENU_PRINCIPAL;

  scanf("%d", &escolhaMENU_PRINCIPAL);

  switch (escolhaMENU_PRINCIPAL)
  {
    case 1:
      // menu empregado
      proximoMenu = MENU_EMPREGADO;
      //system("clear");
      break;
    case 2:
      // menu dependente
      proximoMenu = MENU_DEPENDENTE;
      //system("clear");
      break;
    default:
      proximoMenu = SAIR;
      break;
  }
}


void submenuEmpregado(){

  ////system("clear");
  printf("\t\tPROCURAR EMPREGADO(OPCOES)->\n\n");
  printf("1 - Nome(Completo)\n");
  printf("2 - Idade\n");
  printf("3 - Salario Mensal\n");
  printf("4 - Numero de dependentes\n");
  printf("5 - Voltar\n");



  int escolha;
  int n_dependentes;
  int cod;
  int idade;
  float salario;
  char nome[50];
  
  scanf("%d",&escolha);

  switch (escolha)
  {

    case 1:
      ////system("clear");
      printf("\t\tBUSCA POR NOMES\n\n");
      printf("Nome: ");
      scanf(" %s", nome);

      buscarNomeEMPREGADO(nome,tab);
      break;

    case 2:
     // //system("clear");
      printf("\t\tBUSCA POR IDADE\n\n");
      printf("Maiores de: ");
      scanf("%d",&idade);

      buscarIdadeEMPREGADO(idade,tab);
      break;

    case 3:
      ////system("clear");
      printf("\t\tBUSCA POR SALARIO\n\n");
      printf("Salario  maior que: ");
      scanf("%f",&salario);

      buscarSalarioEMPREGADO(salario,tab);
      break;

    case 4:

      printf("\t\tBUSCA POR NUMERO DEPENDENTES\n\n");
      printf("NUMERO DEPENDENTES: ");
      scanf("%d",&n_dependentes);

      buscarNumDependentesEMPREGADO(n_dependentes, tab);
      break;  

    default:
      proximoMenu = MENU_EMPREGADO;
      ////system("clear");
      break;
  }

}

void menuEmpregado()
{
  ////system("clear");
  printf("\nMenu Empregado->\n");
  printf("1 - Cadastrar empregado\n");
  printf("2 - Procurar empregado\n");
  printf("3 - Excluir empregado\n");
  printf("4 - Listar empregados\n");
  printf("5 - Alterar Registro\n");
  printf("6 - Voltar\n");

  int escolha;
  int opcao;
  scanf("%d", &escolha);


  char nome[50];
  int cod;
  int idade;
  float salario;

  switch (escolha)
  {
    case 2:
      // procurar empregado
      proximoMenu = MENUBUSCA_EMPREGADO;
      ////system("clear");
      break;
    case 1:
      // cadastrar empregado
      //system("clear");
      printf("Nome: ");
      scanf(" %[^\n]s",nome);

      printf("Codigo: ");
      scanf("%d", &cod);

      printf("Salario: ");
      scanf("%f", &salario);

      printf("Idade: ");
      scanf("%d", &idade);

      inserirEMPREGADO(tab, cod, salario, idade, nome);
      gravar(tab);
      //system("clear");
      break;
    case 3:
      // excluir empregado
      //system("clear");
      printf("Inserir nome e codigo do empregado\n\n");
      printf("Nome(completo): ");
      scanf(" %[^\n]s", nome);

      printf("Codigo: ");
      scanf("%d", &cod);

      remover(nome, cod);

      //system("clear");
      break;

    case 4:
      //lista todos os registros para debug
      //system("clear");
      printf("Lendo...\n");
      ler(tab);
      break;  

    case 5://alterar registro

      printf("Inserir nome e codigo do empregado\n\n");
      printf("Nome(completo): ");
      scanf(" %[^\n]s", nome);

      printf("Codigo: ");
      scanf("%d", &cod);
      alterarRegistroEmpregado(tab,nome, cod);
      gravar(tab);
      //system("clear");
      break;

    case 6:
      proximoMenu = MENU_PRINCIPAL;
      ////system("clear");
    default:
      printf("Comando Invalido\n");
      system("clear");
      break;
  }
}


void submenuDependente(){
  
  printf("OPCAO BUSCA->\n");
  printf("1 - Nome\n");
  printf("2 - Idade\n");
  printf("3 - Nome Empregado\n");
  printf("4 - Voltar\n");



  int escolha;
  int cod;
  int idade;
 // float salario;
  char nome[50];
  
  scanf("%d",&escolha);

  switch (escolha)
  {
    case 1:
      //system("clear");
      printf("Nome: ");
      scanf(" %s", nome);

      buscarNomeDependente(nome,tabDependente);
      break;

    case 2:
      //system("clear");
      printf("Maiores de: ");
      scanf("%d",&idade);

      buscarIdadeDependente(idade,tabDependente);
      break;

      case 3:
      //system("clear");
      printf("Nome empregado: ");
      scanf(" %s",nome);

      buscarDependente_NomeEmpregado(nome,tabDependente,tab);
      break;

    case 4:
      break;  
    default:
      proximoMenu = MENU_DEPENDENTE;
      system("clear");
      break;
  }

}

void menuDependente()
{
  printf("Menu Dependente\n");
  printf("1 - Cadastrar dependente\n");
  printf("2 - Procurar dependente\n");
  printf("3 - Excluir dependente\n");
  printf("4 - Listar dependentes\n");
  printf("5 - Alterar Registro\n");
  printf("6 - Voltar\n");

  int escolha;
  char nome[50];
  int codDependente;
  int cod;
  int idade;


  scanf("%d", &escolha);

  switch (escolha)
  {

    case 2:
      // procurar dependente
      proximoMenu = MENUBUSCA_DEPENDENTE;
      //system("clear");
    /*  printf("Nome: ");
      scanf(" %s", nome);

      buscarNomeDependente(nome,tabDependente);*/
   

      break;

    case 1:
      // cadastrar dependente
      //system("clear");
      printf("Nome: ");
      scanf(" %[^\n]s",nome);

      printf("Codigo Empregado: ");
      scanf("%d", &cod);

      printf("Codigo Dependente: ");
      scanf("%d", &codDependente);

      printf("Idade: ");
      scanf("%d", &idade);

      inserirDependente(tabDependente, tab, codDependente, cod, nome , idade);
      gravarTabelaDEPENDENTES(tabDependente);
      //system("clear");
 
      break;

    case 3:
      // excluir dependente
      //system("clear");
      printf("Inserir nome e codigo do dependente\n\n");
      printf("Nome(completo): ");
      scanf(" %[^\n]s", nome);

      printf("Codigo: ");
      scanf("%d", &codDependente);

      removerDependente(nome, codDependente);
      break;

    case 4:
      //system("clear");
      printf("Lendo...\n");
      lerTabelaDEPENDENTES(tabDependente);
      break; 

    case 5:
    //alterar registro
      printf("Inserir nome e codigo do empregado\n\n");
      printf("Nome(completo): ");
      scanf(" %[^\n]s", nome);

      printf("Codigo: ");
      scanf("%d", &cod);

      alterarRegistroDependente(tabDependente,  nome, codDependente);
      gravarTabelaDEPENDENTES(tabDependente);
      break;
    default:
      proximoMenu = MENU_PRINCIPAL;
      //system("clear");
      break;
  }
}
