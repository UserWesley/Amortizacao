
/* Autor : Wesley Almeida da Silva
Data Inicio : 13/10/2017
Data Fim : 21/10/2017
Linguagem de Programação : C
Desenvolvido no NANO, para GNU/LINUX Debian

Descrição : Este programa foi desenvolvido, para calcular as principais tabelas de sistema de emprestimos ( SAC, PRICE,SACRE e o Americano),
cabe ressaltar que não se aplica ao mercado real, tendo em vista, que não estamos levando em consideração a inflação do mercado.

Observação : A inclusão da biblioteca stdlib.h, se deve ao fato da portabilidade para o windows, no entanto caracteres com acentuação
ou ç, ficaram ilegiveis

*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Declaração das Funções
void calcularSistemaSAC(double,double,int);
void calcularSistemaPRICE(double,double,int);
void calcularSistemaAmericano(double,double,int);
void calcularSistemaSACRE(double,double,int);
void dadosIniciais();
void menu(double,double,int);
void verificaValores(double,double,int);

//Função Principal onde contém as principais funções
void main(){

	int escolha = 0;

	printf("\n\n-------------------------Inicio----------------------------------");

	do{

		printf("\n\nBem Vindo\n\n");
		printf("1 - Sistema de Amortização.\n");
		printf("2 - Sair");

		printf("\n\nDigite sua escolha : ");
		scanf("%d",&escolha);

		switch(escolha){

			case 1 : printf("\nIniciar"); dadosIniciais();
				break;

			case 2 : printf("\nObrigado.\n");
				exit(0);

			default : printf("\nEsta opção não existe.\n");
		}

	}while(escolha != 2);
}

//Função que irá receber os dados iniciais
void dadosIniciais(){

	double divida;
	//Periodo em meses
	int periodo;
	double taxaJuros;

	divida = 0;
	periodo = 0;
	taxaJuros = 0;

	printf("\n\n-------------------------Inserção de Valores----------------------------------");


	printf("\n\n - Dados Iniciais -");

	printf("\nDigite o valor do emprestimo : ");
	scanf("%lf",&divida);

	printf("\nTaxa de Juros (Convertido - Exemplo 3% = 0.03) : ");
	scanf("%lf",&taxaJuros);

	printf("\nPeríodo (em meses) : ");
	scanf("%d",&periodo);

	verificaValores(divida, taxaJuros, periodo);

	printf("\n-------------------------------------------------------------\n");

	menu(divida, taxaJuros, periodo);
}

//Função de menu - Escolha do sistema de amortização
void menu(double divida, double taxaJuros, int periodo){

	//Teste
	//verificaValores(divida,taxaJuros,periodo);

	int escolha;

	do {

		escolha = 0;

		printf("\n--------------------------Escolha de Amortização------------------------------");

		printf("\n\nEscolha o sistema de Amortização :");
		printf("\n\n1 - Sistema SAC\n");
		printf("2 - Sistema PRICE\n");
		printf("3 - Sistema Americano\n");
		printf("4 - Sistema SACRE\n");
		printf("5 - Varificar Valores\n");
		printf("6 - Voltar\n\n");

		printf("\n\n Digite sua Escolha :");

		scanf("%d",&escolha);

		printf("\n--------------------------------------------------------------\n\n");

		switch(escolha){

			case 1 : calcularSistemaSAC(divida, taxaJuros, periodo);
			break;

			case 2 : calcularSistemaPRICE(divida, taxaJuros, periodo);
			break;

			case 3 : calcularSistemaAmericano(divida, taxaJuros, periodo);
			break;

			case 4 : calcularSistemaSACRE(divida, taxaJuros, periodo);
			break;

			case 5 : verificaValores(divida, taxaJuros, periodo);
			break;

			case 6 : printf("\nMenu Principal\n"); main();
			break;

			default : printf("\nEscolha uma opção entre 1 e 6.\n\n");
		}

	}while(escolha!=6);
}

//Função de calcular o sistema SAC
void calcularSistemaSAC(double divida, double taxaJuros, int periodo){

	//Testes
	//printf("SAC");
	//verificaValores(divida,taxaJuros,periodo);

	//Variáveis locais
	double amortizacao = (divida / periodo);
	double tabelaDivida = divida;
	double juros = 0;
	double prestacao = 0;
	double valorPago = 0;
	double jurosPago = 0;
	int linha = 0;
	int coluuna = 0;
	
	printf("\n\n\n-----------------------------------------------------------\n\n");
	printf("\t Tabela SAC\n");

	//Cabeçalho da tabela
	printf("Índice da tabela SAC");
	printf("\n\nPeríodo | Amortização | Divida | Juros | Prestação ");

	//Construção da tabela PRICE
	printf("\n\n----------------------- Tabela SAC ----------------------------\n");

	for( linha = 1; linha <= periodo; linha++){
		for( coluna = 0; coluna <=4;coluna++){

			//Coluna - Periodo
			if(coluna == 0) {printf(" %d -",linha);}

			//Coluna - Amortização
		    else if(coluna == 1) {printf("| %2.f |", amortizacao);}

			//Coluna - Divida
			else if(coluna == 2) {
				tabelaDivida = tabelaDivida - amortizacao;
				printf("| %2.f |", tabelaDivida);}

			//Coluna - Juros
			else if(coluna == 3) {
				juros = taxaJuros * (tabelaDivida+amortizacao);
				jurosPago = jurosPago + juros;
				printf("| %2.f |", juros);
			}

			//Coluna - Prestação
			else if(coluna == 4) {
				prestacao = amortizacao + juros;
				valorPago = valorPago + prestacao;
				printf("| %2.f |", prestacao);
				printf("\n");
			}
		}
	}
	
	printf("\nValores Finais");
	printf("\n\nValor pago no final %.12lf", valorPago);
	printf("\nJuros pago no final %.12lf", jurosPago);

	printf("\n\n-------------------------Fim tabela----------------------------------");

}

//Função de calcular o sistema Price
void calcularSistemaPRICE(double divida, double taxaJuros, int periodo){

	//Teste
	//verificaValores(divida,taxaJuros,periodo);

	double periododouble = periodo;
	double prestacao = (divida * taxaJuros) /(1-(pow(1/(1+taxaJuros),periododouble)));
	double juros = 0;
	double tabelaDivida = divida;
	double amortizacao = 0;
	double valorPago = 0;
	double jurosPago = 0;
	int linha = 0;
	int coluuna = 0;
	
	printf("\n\n\n-----------------------------------------------------------\n\n");
	printf("\t Tabela PRICE\n");

	//Indice da tabela
	printf("Índice da tabela PRICE\n");
	printf("\nPeríodo | Prestação | Juros | Amortização | Divida |\n ");

	//Construção da tabela PRICE
	printf("\n-------------- Tabela PRICE ------------------\n\n");
	for( linha = 1; linha <=periodo ; linha++){
		for( coluna = 0; coluna <=4; coluna++){

			//coluna do periodo
			if(coluna == 0){printf(" %d - ", linha);}

			//coluna da prestação
			else if(coluna == 1){ 
				valorPago = valorPago + prestacao;
				printf("| %.12lf |",prestacao);
			}

			//coluna do juros
			else if(coluna == 2){
				juros = taxaJuros * tabelaDivida;
				jurosPago = jurosPago + juros;
				printf("| %.12lf |", juros);
			}

			//coluna Amortização
			else if(coluna == 3){
				amortizacao = prestacao - juros;
				printf("| %.12lf |",amortizacao);
			}

			//coluna Divida
			else if(coluna == 4){
				tabelaDivida = tabelaDivida - amortizacao;
				printf("| %.12lf |", tabelaDivida);
				printf("\n");
			}
		}
	}

	printf("\nValores Finais");
	printf("\n\nValor pago no final %.12lf", valorPago);
	printf("\nJuros pago no final %.12lf", jurosPago);

	printf("\n\n-------------------------Fim tabela----------------------------------");

}

//Função de calcular o sistema Americano
void calcularSistemaAmericano(double divida, double taxaJuros, int periodo){

	//Teste
	//printf("Americano");
	//verificaValores(divida,taxaJuros,periodo);

	int amortizacao = 0;
	double prestacao = divida * taxaJuros;
	double juros = prestacao;
	double valorPago = 0;
	double jurosPago = 0;
	int linha = 0;
	int coluna = 0;
	
	printf("\n\n\n-----------------------------------------------------------\n\n");
	printf("\tTabela Americana \n");

	printf("Índice da tabela Americana.\n");
	printf("Período | Amortização | Dívida | Prestação | Juros ");

	//Construção da tabela americana
	printf("\n\n------------- Tabela Americana ---------------\n");

	for(linha = 1; linha <=periodo ; linha++){
		for(coluna = 0; coluna <=4; coluna++){

			//coluna periodo
			if(coluna == 0 ){ printf(" %d -", linha);}

			//coluna amortizacao
			else if(coluna == 1 ){ printf("| %d |", amortizacao);}

			//coluna divida
			else if(coluna == 2) { printf("| %2.f |", divida);}

			//coluna prestacao
			else if(coluna == 3) {
				valorPago = valorPago + prestacao; 
				printf("| %2.f |", prestacao);
			}

			//coluna juros
			else if(coluna == 4) {
				jurosPago = jurosPago + juros;
				printf("| %2.f |", juros);
				printf("\n");
			}
		}
	}

	printf("\nValores Finais");
	printf("\n\nValor pago no final %.12lf", valorPago);
	printf("\nJuros pago no final %.12lf", jurosPago);

	printf("\n\n-------------------------Fim tabela----------------------------------");

}

//Função de calcular o sistema SACRE
void calcularSistemaSACRE(double divida, double taxaJuros, int periodo){

	//Teste
	//printf("SACRE");
	//verificaValores(divida,taxaJuros,periodo);

	int ciclo = 0;
	int contaCiclo = 0;
	int linha = 0;
	int coluuna = 0;
	int periodoRestante = periodo;
	double amortizacao = 0;
	double juros = 0;
	double prestacao = 0;
	double tabelaDivida = divida;
	double valorPago = 0;
	double jurosPago = 0;

	printf("\n-------------------------Iniciando tabela SACRE----------------------------------\n\n");
	printf("\tTabela SACRE");

	printf("\nEm quantos ciclos será : ");
	scanf("%d", &ciclo);

	printf("índice da tabela SACRE \n");
	printf("Período | Juros | Amortização | Prestação | Dívida ");

	printf("\n\n------------------------ Tabela SACRE -----------------------\n");
	//Construção da tabela SACRE
	for( linha = 1; linha <= periodo; linha++ ){

		//Controle de ciclo
		if(contaCiclo == ciclo){
			contaCiclo = 0;
			printf("\n\tInicio de novo ciclo\n");
		}

		for( coluna = 0 ; coluna <= 4; coluna++){

			//coluna periodo
			if(coluna == 0){ printf("%d - ", linha);}

			//coluna juros
			else if(coluna == 1){
				juros = taxaJuros * tabelaDivida;
				jurosPago = jurosPago + juros;
				printf("| %.12lf |", juros);
			}

			//coluna amortização
			else if((coluna == 2) && (contaCiclo == 0)){
				amortizacao = tabelaDivida / periodoRestante;
				printf("| %.12lf |", amortizacao);
			}

			else if((coluna == 2) && (contaCiclo != 0)){
				amortizacao = prestacao - juros;
				printf("| %.12lf |", amortizacao);
			}

			//coluna prestação
			else if((coluna == 3) && (contaCiclo == 0)){
				prestacao = amortizacao + juros;
				valorPago = valorPago + prestacao;
				printf("| %.12lf |", prestacao);

			}
			else if((coluna == 3) && (contaCiclo != 0)){
				printf("| %.12lf |", prestacao);
				valorPago = valorPago + prestacao;
			}

			//coluna divida
			else if(coluna == 4){
				tabelaDivida = tabelaDivida - amortizacao;
				printf("| %.12lf |", tabelaDivida);
				printf("\n");
			}

		}
		periodoRestante--;
		contaCiclo++;
	}

	printf("\nValores Finais");
	printf("\n\nValor pago no final %.12lf", valorPago-juros);
	printf("\nJuros pago no final %.12lf", jurosPago);

	printf("\n\n-------------------------Fim tabela----------------------------------");

}

//Função de verificar os valores iniciais
void verificaValores(double divida, double taxaJuros, int periodo){

	printf("\n\n ----------------- Verificação de Valores ---------------------------");
	printf("\n\nCapital Inicial : %.12lf", divida);
	printf("\nTaxa de Juros : %.12lf", taxaJuros);
	printf("\nPeriodo : %d", periodo);
}

