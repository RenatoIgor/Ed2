#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "compartimento_hash.h"
#define M 113
#define Z 83

void iniciaTabela(struct Empregado lista[]){
	int i = 0;

	for(; i < M; i++){
		strcpy( lista[i].nome, " ");
		lista[i].indice = -1; 
		lista[i].codEmpregado = -1;
		lista[i].sal = 0;
		lista[i].idade = 0;
		lista[i].num_dependentes = 0;
	}	
}


void iniciaTabelaDependentes(struct  Dependente listaDependente[]){

	int i = 0;

	for(; i < M; i++){
		strcpy( listaDependente[i].nomeDependente, " ");
		listaDependente[i].indiceDependente = -1; 
		listaDependente[i].codEmpregado = 0;
		listaDependente[i].codDependente = -1;
		listaDependente[i].idadeDependente = 0;
	}
}


int compararEMPREGADO(struct Empregado x, struct Empregado y){

	if(!strcmp(x.nome , y.nome) && x.codEmpregado == y.codEmpregado)
	{	return 1;}

	return 0;

}

void ajustar_nome(char nome []){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula


   	int i = 0;

   	while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}

}

int funcao_hash(int cod){ // retorna posicao nas tabelas, fora da zona colisao
   return cod % Z;
}

void inserirEMPREGADO(struct Empregado lista[], int codEmpregado, float salario , int anos , char nome[]) {//cadastra um empregado
   
	struct Empregado *empregadoy;
   	empregadoy = (struct Empregado*) malloc(sizeof(struct Empregado));
   	empregadoy->codEmpregado = codEmpregado;  
   	empregadoy->idade = anos;
   	empregadoy->sal = salario;

   	int i = 0;

   	while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}

   	strcpy(empregadoy->nome, nome);     

   	//calcula a funcao hash 
   	int endereco = funcao_hash(codEmpregado);
   	//se nao estiver vazia, testo o proximo espaco da tabela
 	/*  while(lista[endereco].codEmpregado != -1) {//trata colisao por adjacencia
      //vai pro proximo endereco
      ++endereco;
		//calcula o mod
	endereco %= M;}*/

   	if(lista[endereco].codEmpregado != -1){
   		/*if(clientey->codEmpregado == lista[endereco].codEmpregado){printf("Erro! codigo já existente!\n");return;}*/
   		if(empregadoy->codEmpregado == lista[endereco].codEmpregado){
   			printf("CODIGO FUNCIONARIO INVALIDO\n");
   			return;
   		}
   		endereco = Z;  
  	}

   	while(lista[endereco].codEmpregado != -1){
 	/*	if(clientey->codEmpregado == lista[endereco].codEmpregado){printf("Erro! codigo já existente!\n");return;}*/
   		if(empregadoy->codEmpregado == lista[endereco].codEmpregado){
   			printf("CODIGO FUNCIONARIO INVALIDO\n");
   			return;
   		}
		++endereco;
		//calcula o mod 

		endereco %= M;
   }

   empregadoy->indice = endereco;
   strcpy(lista[endereco].nome , empregadoy->nome);
   lista[endereco].codEmpregado = empregadoy->codEmpregado;
   lista[endereco].indice = empregadoy->indice;
   lista[endereco].sal = empregadoy->sal;
   lista[endereco].idade = empregadoy->idade;
  

}

void gravar(struct Empregado lista[]){

   FILE * arq;
   arq = fopen("Empregado.dat","w+b");

   int i = 0;
   while(i<M){
      fwrite(&lista[i], sizeof(struct Empregado), 1, arq);
      i++;
   }

   fclose(arq);
}


void ler(struct Empregado lista[]){//exibe a lista completa

   puts("\n");

   FILE *arq;
   arq=fopen("Empregado.dat", "r+b");
   if(arq == NULL){
      printf("arquivo inexistente\n" );
      return;
   }

   int temp = -1;
   int i = 0;
   struct Empregado clientex;
   struct Empregado tab[M];

   printf("Funcionarios->\n");
   while(!feof(arq)){

      fread(&clientex, sizeof(struct Empregado), 1, arq);
      tab[i] = clientex;

      if(i + 1 == M){i--;}i++;

      temp = clientex.codEmpregado; //nao repetir impressao do ultimo registro
   }

   printf("(NOME, IDADE, SALARIO, INDICE, COD_EMPREGADO)\n\n");
   for(i = 0; i < M; i++){
     	strcpy(lista[i].nome , tab[i].nome);
      	lista[i].codEmpregado = tab[i].codEmpregado;
      	lista[i].indice = tab[i].indice;
      	lista[i].sal = tab[i].sal;
      	lista[i].idade = tab[i].idade;
        
        if(lista[i].codEmpregado != -1){
            printf("%s   %d   %.2f   %d  %d\n",lista[i].nome, lista[i].idade, lista[i].sal, lista[i].indice, lista[i].codEmpregado);
        }
   }

   fclose(arq);

   puts("\n");

}


void buscarNomeEMPREGADO(char nome[],struct Empregado lista[]){


	printf("\n\t\tEMPREGADOS\n\n");

	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0;


   	while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 

   	char substring[50];
   	strcpy(substring,nome);
   	char *aux;

	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      aux = strstr(tmp[i].nome,substring);

		if(aux != NULL){
			lista[j] = tmp[i];
			printf("\nNOME:  %s\n",lista[j].nome);
			printf("Salario: %.2f  Idade: %d  Posicao: %d\n",  lista[j].sal, lista[j].idade, lista[j].indice);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe ,%s nao encontrado!\n",nome );
	}

	fclose(arq);


}


void buscarIdadeEMPREGADO(int anos_idade, struct Empregado lista[]){

	printf("\n\t\tEMPREGADOS\n\n");

	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 

   	//char substring[50];
   	//strcpy(substring,nome);
   	//char *aux;

	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      //aux = strstr(tmp[i].nome,substring);

		if(tmp[i].idade >= anos_idade){
			lista[j] = tmp[i];
			printf("\nNOME:  %s\n",lista[j].nome);
			printf("Salario: %.2f  Idade: %d  Posicao: %d\n",  lista[j].sal, lista[j].idade, lista[j].indice);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe , nao existem funcionarios!\n" );
	}

	fclose(arq);
}

void buscarSalarioEMPREGADO(float salarioAtual, struct Empregado lista[]){

	printf("\n\t\tEMPREGADOS\n\n");

	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 


	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      //aux = strstr(tmp[i].nome,substring);

		if(tmp[i].sal >= salarioAtual){
			lista[j] = tmp[i];
			printf("\nNOME:  %s\n",lista[j].nome);
			printf("Salario: %.2f  Idade: %d  Posicao: %d\n",  lista[j].sal, lista[j].idade, lista[j].indice);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe , nao existem funcionarios!\n" );
	}

	fclose(arq);

}

void buscarNumDependentesEMPREGADO(int qnt_dependentes, struct Empregado lista[]){

	printf("\n\t\tEMPREGADOS\n\n");

	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 

	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      //aux = strstr(tmp[i].nome,substring);

		if(tmp[i].num_dependentes == qnt_dependentes && strlen(tmp[i].nome) != 1){
			lista[j] = tmp[i];
			printf("\nNOME:  %s\n",lista[j].nome);
			printf("Salario: %.2f  Idade: %d  Posicao: %d\n",  lista[j].sal, lista[j].idade, lista[j].indice);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe , nao existem funcionarios!\n" );
	}

	fclose(arq);

}



void remover(char nome[], int codEmpregado){

	printf("\t\tREMOVER FUNCIONARIO\n\n");

	int casou = 0;
	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	FILE *arqDep;
	arqDep = fopen("Dependente.dat","r+b");

	if(arqDep == NULL){
		printf("arquivo inexistente\n");
		return;
	}
	
	

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0 , j = funcao_hash(codEmpregado);
	iniciaTabela(tmp);


	struct Dependente tab[M];
	struct Dependente y;
	iniciaTabelaDependentes(tab);


	while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}

   	i = 0;


	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	}

	rewind(arq);

	i = 0;
	while(!feof(arqDep)){
		
		fread(&y,sizeof(struct Dependente),1,arqDep);
		tab[i] = y;

		if(i + 1 == M){i--;};
		i++;

	}

	i = 0;
	strcpy( y.nomeDependente, " ");
	y.indiceDependente = -1; 
	y.codEmpregado = 0;
	y.codDependente = -1;
	y.idadeDependente = 0;

	if(strcmp(tmp[j].nome,nome) == 0  && codEmpregado == tmp[j].codEmpregado){//busca no endereco hash
		
		fseek(arq,j*sizeof(struct Empregado) ,SEEK_SET);
		iniciaTabela(tmp);
		fwrite(&tmp[j],sizeof(struct Empregado),1,arq);
		//rewind(arq);	
		printf("%s Excluido com sucesso!\n",nome );
		fclose(arq);

		while(i < M){

			if(tab[i].codEmpregado == codEmpregado)
			{
				fseek(arqDep,i*sizeof(struct Dependente),SEEK_SET);
				fwrite(&y,sizeof(struct Dependente),1,arqDep);		
			}i++;
			rewind(arqDep);
		}
		fclose(arqDep);
		return;
	}

   	else{//busca na zona de colisao
   		i = 0;
   		for(i = Z ;i < M; i++)
      	{
      		if(strcmp(tmp[i].nome,nome) == 0  && codEmpregado == tmp[i].codEmpregado){
      			fseek(arq,i*sizeof(struct Empregado),SEEK_SET);
      			iniciaTabela(tmp);
				fwrite(&tmp[j],sizeof(struct Empregado),1,arq);
		//rewind(arq);	
				printf("%s Excluido com sucesso!\n",nome );
				fclose(arq);

			int k = 0;
			while(k < M){

			if(tab[k].codEmpregado == codEmpregado)
			{
				
				fseek(arqDep,k*sizeof(struct Dependente),SEEK_SET);
				fwrite(&y,sizeof(struct Dependente),1,arqDep);
			}k++;
		}
		fclose(arqDep);
				return;
      		}
      	}
   	}
   	printf("Empregado nao pertence ao banco de registros!\n");
	fclose(arq);


}

void alterarRegistroEmpregado(struct Empregado lista[], char nome[], int codEmpregado){


	printf("\t\tALTERAR DADOS EMPREGADO\n\n");
	int i = 0;
	int casou = 0,op = 0;
	char newNome[50];
	int newIdade;
	float newSalario;
	
	while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}

	printf("CODIGO: %d   \tNOME: %s\n\n",codEmpregado,nome );

   	int j = 0;
   	j = funcao_hash(codEmpregado);


	if(strcmp(lista[j].nome,nome) == 0  && codEmpregado == lista[j].codEmpregado){//busca no endereco hash
	
		casou = 1;
		printf("Empregado Encontrado.\n");

		printf("\nAlterar dados:\n\n");
		printf("1   -Nome\n");
		printf("2   -Idade\n");
		printf("3   -Salario\n");
		printf("N/A -Voltar\n");
		scanf("%d",&op);

		switch(op){

			case 1:
				printf("NOME:\n");
				scanf(" %s",newNome);
				i=0;
				while(i < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula
					newNome[i] = tolower(newNome[i]);
					if(i == 0 || newNome[i-1] == ' '){
						newNome[i] = toupper(newNome[i]);
					}
					i++;
				}

				strcpy(lista[j].nome,newNome);
				break;

			case 2:
				printf("IDADE:\n");
				scanf("%d",&newIdade);

				lista[j].idade = newIdade;
				break;

			case 3:
				printf("SALARIO\n");
				scanf("%f",&newSalario);
				lista[j].sal = newSalario;
				break;

			default:
				break;

		}
		return;
	}


	else{//busca na zona de colisao
		i = 0; 

		for(i = Z; i < M; i++){
			if(strcmp(lista[i].nome,nome) == 0  && codEmpregado == lista[i].codEmpregado){
					casou = 1;
					printf("Empregado Encontrado.\n");

					printf("\nAlterar dados:\n\n");
					printf("1   -Nome\n");
					printf("2   -Idade\n");
					printf("3   -Salario\n");
					printf("N/A -Voltar\n");
					scanf("%d",&op);

					switch(op){

						case 1:
							printf("NOME:\n");
							scanf(" %s",newNome);
							j=0;
							while(j < strlen(nome)){//Formata o nome completo do Empregado ex: aNa PauLA -> Ana Paula
								newNome[j] = tolower(newNome[j]);
								if(j == 0 || newNome[j-1] == ' '){
									newNome[j] = toupper(newNome[j]);
								}
								j++;
							}

							strcpy(lista[i].nome,newNome);
							break;

						case 2:
							printf("IDADE:\n");
							scanf("%d",&newIdade);

							lista[i].idade = newIdade;
							break;

						case 3:
							printf("SALARIO\n");
							scanf("%f",&newSalario);
							lista[i].sal = newSalario;
							break;

						default:
							break;

					}
					return;
			}	
		}


	}


	printf("EMPREGADO NAO ENCONTRADO.\n\n");

	

}

void inserirDependente(struct Dependente tabela[],struct Empregado lista[], int codDependente, int codEmpregado, char nome[] , int idade){

	// Modificar a funcao para garantir codigo unico para empregado
	int casou = 0;
	FILE *arqEmpregado;
	arqEmpregado = fopen("Empregado.dat","r+b");
	if(arqEmpregado == NULL){

		printf("Nao existem empregados no banco de dados\n");
		return;
	}

   struct Dependente *clientey;
   clientey = (struct Dependente*) malloc(sizeof(struct Dependente));
   clientey->codDependente = codDependente;  
   clientey->codEmpregado = codEmpregado;
   clientey->idadeDependente = idade;

   int i = 0;

   while(i < strlen(nome)){

   	nome[i] = tolower(nome[i]);
   	if(i == 0 || nome[i-1] == ' '){
   		nome[i] = toupper(nome[i]);
   	}
   	i++;
   }

   strcpy(clientey->nomeDependente, nome);  

  	struct Empregado tmp[M];
	struct Empregado x;

	int j = funcao_hash(codEmpregado); i = 0;
	iniciaTabela(tmp);
	while(!feof(arqEmpregado)){
		
		fread(&x,sizeof(struct Empregado),1,arqEmpregado);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	}


	if(codEmpregado == tmp[j].codEmpregado){//busca no endereco hash

		casou = 1;
	}

   	else{//busca na zona de colisao
   		for(i = Z ;i < M; i++)
      	{
      		if(codEmpregado == tmp[i].codEmpregado){

				casou = 1 ;
      		}
      	}
   	}
   

   if(casou == 1){

   //calcula a funcao hash 
   int endereco = funcao_hash(codDependente);


  	if(tabela[endereco].codDependente != -1){
   		if(clientey->codDependente == tabela[endereco].codDependente){
   			printf("Erro! CODIGO INVALIDO!\n");
   			return;
   		}

   	endereco = Z;
   
  	}
   	while(tabela[endereco].codDependente != -1){
 		if(clientey->codDependente == tabela[endereco].codDependente){
   			printf("Erro! CODIGO INVALIDO!\n");
   			return;
   		}


 		++endereco;
		
     	 //calcula o mod
     	 endereco %= M;
   }

   clientey->indiceDependente = endereco;
   strcpy(tabela[endereco].nomeDependente , clientey->nomeDependente);
   tabela[endereco].codEmpregado = clientey->codEmpregado;
   tabela[endereco].indiceDependente = clientey->indiceDependente;
   tabela[endereco].codDependente = clientey->codDependente;
   tabela[endereco].idadeDependente = clientey->idadeDependente;
  
}

	if(casou == 0){
		printf("Nao exixte empregados registrados no banco de dados!\n");
	}

	fclose(arqEmpregado);

}


void gravarTabelaDEPENDENTES(struct Dependente tabela[]){
   FILE * arq;
   arq = fopen("Dependente.dat","w+b");

   int i = 0;
   while(i<M){
      fwrite(&tabela[i], sizeof(struct Dependente), 1, arq);
      i++;
   }

   fclose(arq);
}


void lerTabelaDEPENDENTES(struct Dependente tabela[]){

	puts("\n");

   FILE *arq;
   arq=fopen("Dependente.dat", "r+b");
   if(arq == NULL){
      printf("arquivo inexistente\n" );
      return;
   }

   int temp = -1;
   int i = 0;
   struct Dependente clientex;
   struct Dependente lista[M];

   printf("Dependentes->\n");
   while(!feof(arq)){

      fread(&clientex, sizeof(struct Dependente), 1, arq);
      lista[i] = clientex;

      if(i + 1 == M){i--;}i++;

      temp = clientex.codDependente; //nao repetir impressao do ultimo registro
   }

   printf("(NOME, IDADE, COD_DEPENDENTE, INDICE, COD_EMPREGADO)\n\n");
   for(i = 0; i < M; i++){
     	strcpy(tabela[i].nomeDependente , lista[i].nomeDependente);
      	tabela[i].codEmpregado = lista[i].codEmpregado;
      	tabela[i].indiceDependente = lista[i].indiceDependente;
      	tabela[i].codDependente = lista[i].codDependente;
      	tabela[i].idadeDependente = lista[i].idadeDependente;
        
        if(tabela[i].codDependente != -1){
            printf("%s   %d   %d   %d  %d\n",tabela[i].nomeDependente, tabela[i].idadeDependente, tabela[i].codDependente, tabela[i].indiceDependente, tabela[i].codEmpregado);
        }
   }

   fclose(arq);

   puts("\n");
}

void buscarNomeDependente(char nome[],struct Dependente tabela[]){

	printf("\n\t\tDEPENDENTES\n\n");

	FILE *arq;
	arq = fopen("Dependente.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}


	int i = 0;

   	while(i < strlen(nome)){

   		nome[i] = tolower(nome[i]);
   		if(i == 0 || nome[i-1] == ' '){
   			nome[i] = toupper(nome[i]);
   		}
   		i++;
   	}

	struct Dependente tmp[M];
	struct Dependente x;
 	i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Dependente),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 

   	char substring[50];
   	strcpy(substring,nome);
   	char *aux;

	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      aux = strstr(tmp[i].nomeDependente,substring);

		if(aux != NULL){
			tabela[j] = tmp[i];
			printf("\nNOME:  %s\n",tabela[j].nomeDependente);
			printf("COD_EMPREGADO: %d  Idade: %d  Posicao: %d\n",  tabela[j].codEmpregado, tabela[j].idadeDependente, tabela[j].indiceDependente);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe ,%s nao encontrado!\n",nome );
	}

	fclose(arq);


}

void buscarIdadeDependente(int anos_idade, struct Dependente tabela[]){

	printf("\n\t\tDEPENDENTES\n\n");

	FILE *arq;
	arq = fopen("Dependente.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Dependente tmp[M];
	struct Dependente x;
	int i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Dependente),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 


	int j = 0;
	int vazia = 1;

	printf("\n----------------------------------------\n");
	for(i = 0; i < M ; i++){
      //aux = strstr(tmp[i].nome,substring);

		if(tmp[i].idadeDependente >= anos_idade){
			tabela[j] = tmp[i];
			printf("\nNOME:  %s\n",tabela[j].nomeDependente);
			printf("Idade: %d  Posicao: %d\n", tabela[j].idadeDependente, tabela[j].indiceDependente);
			j++;
			vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe , nao existem dependentes!\n" );
	}

	fclose(arq);
}

void buscarDependente_NomeEmpregado(char nomeEmpregado[],struct Dependente tabela[], struct Empregado lista[]){

	ajustar_nome(nomeEmpregado);

	printf("\n\t\tDEPENDENTES\n\n");
	
	
	FILE *arq;
	arq = fopen("Empregado.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Empregado tmp[M];
	struct Empregado x;
	int i = 0;
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Empregado),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	} 
	
	FILE *arqDep;
	arqDep = fopen("Dependente.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Dependente tab[M];
	struct Dependente y;
	i = 0;
	while(!feof(arqDep)){

		fread(&y,sizeof(struct Dependente),1,arqDep);
		tab[i] = y;

		if(i + 1 == M){i--;};
		i++;

	}


	char substring[50];
   	strcpy(substring,nomeEmpregado);
   	char *aux;

	int j = 0, k = 0;
	int vazia = 1;
	printf("-----------------------------------------\n");
	for(i = 0; i < M ; i++){
      aux = strstr(tmp[i].nome,substring);

		if(aux != NULL){
			lista[j] = tmp[i];
			printf("\nNOME:  %s\n",lista[j].nome);
			//printf("Salario: %.2f  Idade: %d  Posicao: %d\n",  lista[j].sal, lista[j].idade, lista[j].indice)
			printf("-----------------------------------------\n");
			printf("Dependentes->\n");
			for(k = 0; k < M; k++){
				 //printf("FOR K\n");

				if(tab[k].codEmpregado == lista[j].codEmpregado){
				
					vazia = 0;
					printf("\nNOME:  %s\n",tab[k].nomeDependente);
					printf("Idade: %d  Posicao: %d\n", tab[k].idadeDependente, tab[k].indiceDependente);
				}
			}

			j++;
			//vazia = 0;
		}
	}
	printf("-----------------------------------------\n");

	if(vazia == 1){
		printf("Desculpe ,%s nao encontrado!\n",nomeEmpregado );
	}

	fclose(arq);
	fclose(arqDep);

}



void removerDependente(char nome[], int codDependente){

	ajustar_nome(nome);


	printf("\t\tREMOVER DEPENDENTE\n\n");

	int casou = 0;
	FILE *arq;
	arq = fopen("Dependente.dat","r+b");
	if(arq == NULL){
		printf("arquivo inexistente\n");
		return;
	}

	struct Dependente tmp[M];
	struct Dependente x;
	int i = 0 , j = funcao_hash(codDependente);
	iniciaTabelaDependentes(tmp);
	while(!feof(arq)){
		
		fread(&x,sizeof(struct Dependente),1,arq);
		tmp[i] = x;

		if(i + 1 == M){i--;};
		i++;

	}

	rewind(arq);

	if(strcmp(tmp[j].nomeDependente,nome) == 0  && codDependente == tmp[j].codDependente){//busca no endereco hash
		fseek(arq,j*sizeof(struct Dependente) ,SEEK_SET);
		iniciaTabelaDependentes(tmp);
		fwrite(&tmp[j],sizeof(struct Dependente),1,arq);
		//rewind(arq);	
		printf("%s Excluido com sucesso!\n",nome );
		fclose(arq);
		return;
	}

   	else{//busca na zona de colisao
   		for(i = Z ;i < M; i++)
      	{
      		if(strcmp(tmp[i].nomeDependente,nome) == 0  && codDependente == tmp[i].codDependente){
      			fseek(arq,i*sizeof(struct Dependente),SEEK_SET);
      			iniciaTabelaDependentes(tmp);
				fwrite(&tmp[j],sizeof(struct Dependente),1,arq);
		//rewind(arq);	
				printf("%s Excluido com sucesso!\n",nome );
				fclose(arq);
				return;
      		}
      	}
   	}
   	printf("Dependente nao pertence ao banco de registros!\n");
	fclose(arq);

	

}

void alterarRegistroDependente(struct Dependente tabela[], char nome[] , int codDependente){

	printf("\t\tALTERAR DADOS DEPENDENTE\n\n");
	
	int i = 0;
	int casou = 0,op = 0;
	char newNome[50];
	int newIdade;

	
	ajustar_nome(nome);

	printf("CODIGO: %d   \tNOME: %s\n\n",codDependente,nome );

   	int j = 0;
   	j = funcao_hash(codDependente);


	if(strcmp(tabela[j].nomeDependente,nome) == 0  && codDependente == tabela[j].codDependente){//busca no endereco hash
	
		casou = 1;
		printf("Dependente Encontrado.\n");

		printf("\nAlterar dados:\n\n");
		printf("1   -Nome\n");
		printf("2   -Idade\n");
		printf("N/A -Voltar\n");
		scanf("%d",&op);

		switch(op){

			case 1:
				printf("NOME:\n");
				scanf(" %s",newNome);
				i=0;
				ajustar_nome(newNome);

				strcpy(tabela[j].nomeDependente,newNome);
				break;

			case 2:
				printf("IDADE:\n");
				scanf("%d",&newIdade);

				tabela[j].idadeDependente = newIdade;
				break;

			default:
				break;

		}
		return;
	}


	else{//busca na zona de colisao
		i = 0; 

		for(i = Z; i < M; i++){
			if(strcmp(tabela[i].nomeDependente,nome) == 0  && codDependente == tabela[i].codDependente){
					casou = 1;
					printf("Dependente Encontrado.\n");

					printf("\nAlterar dados:\n\n");
					printf("1   -Nome\n");
					printf("2   -Idade\n");
					printf("N/A -Voltar\n");
					scanf("%d",&op);

					switch(op){

						case 1:
							printf("NOME:\n");
							scanf(" %s",newNome);
							j=0;
							ajustar_nome(newNome);

							strcpy(tabela[i].nomeDependente,newNome);
							break;

						case 2:
							printf("IDADE:\n");
							scanf("%d",&newIdade);

							tabela[i].idadeDependente = newIdade;
							break;


						default:
							break;

					}
					return;
			}	
		}


	}


	printf("DEPENDENTE NAO ENCONTRADO.\n\n");

	

}


//}
/*
void buscarDependente(char nome[], int codDependente);
void buscarNomeDependente(char nome[],struct Dependente lista[]);


void gravarTabelaDEPENDENTES(struct Dependente tabela[]);
void lerTabelaDEPENDENTES(struct Dependente tabela[]);
*/