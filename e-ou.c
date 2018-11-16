#include <stdlib.h>
#include <stdio.h>

#define LIMITE_EPOCAS 10	// Número limite de épocas para o neurônio aprender. 

int contErroIndividualOu = 0; // Contagem da ocorrência de erros. Quando a execução do neurônio para todas as entradas gerar erroIndividual igual a 0 ocorre o fim do loop. 
int contErroIndividualE = 0; // Contagem da ocorrência de erros. Quando a execução do neurônio para todas as entradas gerar erroIndividual igual a 0 ocorre o fim do loop. 

int contNumeroEpocasOu = 0; 
int contNumeroEpocasE = 0; 

// Funções
double calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos);
double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada); 
void calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada); 

int main () {  
// VARIÁVEIS 
	double matEntrada[4][3] = { {0, 0, -1}, 
								{0, 1, -1}, 
								{1, 0, -1}, 
								{1, 1, -1} }; 
	double vetEntradaAux[3] = {-30, -30, -30}; // Vetor auxiliar que receberá cada uma das linhas da matriz que contém os dados de entrada. -30 são valores arbitrários de inicialização.
	
	int limiarTheta_Ou = 0; 
	int limiarTheta_E = 1; 

	double vetSaidaDesejadaOu[4] = {0, 1, 1, 1};
	double vetSaidaDesejadaE[4] = {0, 0, 0, 1}; 
	double vetPesosW[3] = {0.7, -0.3, 0.4};  

	double nivelAtivacaoNet = 0; 
	double erroIndividual = 0; 
	double taxaAprendizagemN = 1.414213562; // Considera-se a taxa (ou ritmo) de aprendizado igual à raiz quadrada de dois. Escolha arbitrária, mas recomenda-se um valor pequeno. 
	
	int j = 0; // Iterador. Atua na correspondência entre cada linha da matriz e a posição do vetor de saídas (que dá o valor de saída desejado àquela entrada). 
	int k = 0; // Iterador. Atua no loop que atribui cada uma das linhas da matriz de entrada de dados para um vetor auxiliar. 

	int escolha = 0; 

// MENU
	do {

		printf("\t====================================\n");
		printf("\t|        NEURÔNIO ARTIFICIAL       |\n");
		printf("\t|----------------------------------|\n");
		printf("\t| Escolha uma opção:               |\n");
		printf("\t|                                  |\n");
		printf("\t| [1] Resolver porta lógica OU     |\n");
		printf("\t| [2] Resolver porta lógica E;     |\n");
		printf("\t| [3]Finalizar && Sair.            |\n");
		printf("\t|                                  |\n");
		printf("\t====================================\n");
		
		scanf ("%d", &escolha); // Lê a opção escolhida pelo usuário.

		switch(escolha) {
			case 1: // Resolver OU

				while (contNumeroEpocasOu < LIMITE_EPOCAS || (contErroIndividualOu == 4)) { // Define uma quantidade máxima de épocas para treinar o neurônio.
					for (j = 0; j < 4; j++) { // Loop responsável por executar o neurônio para cada uma de suas entradas (para cada um dos 4 vetores (j = 0, j = 1, j = 3) temporários de entrada). 
						
						for(k = 0; k < 3; k++) {
							vetEntradaAux[k] = matEntrada[j][k];
							printf("Vetor de entrada %d: %.2f\n", k, vetEntradaAux[k]);
						}
						// calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos)
						nivelAtivacaoNet = calcula_NivelAtivacao(vetEntradaAux, vetPesosW); 
						printf("Nível ativação: %.5f\n", nivelAtivacaoNet);

						// double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada)
						erroIndividual = funcaoAtivacao_LimiarAbruptoSimples(limiarTheta_Ou, vetSaidaDesejadaOu, j, nivelAtivacaoNet, vetEntradaAux); 
						printf("Erro individual: %.5f\n", erroIndividual);

						// Correção do erro
						if(erroIndividual != 0) {
							// Chama função que corrige os pesos: calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada); 
							calcula_novosPesos(vetPesosW, taxaAprendizagemN, erroIndividual, vetEntradaAux);
							// Incrementa contador de erros
							contErroIndividualOu = 0; 
						} else { // contErroIndividualOu será igual a 4 se não houver erro para todas as entradas do neurônio
							contErroIndividualOu++; 
						}

						if(j == 3 && contErroIndividualOu < 4){
							contErroIndividualOu = 0;
						}
						printf("Executou o neurônio para a entrada %d de 4.\n\n", j+1);

					}
					contNumeroEpocasOu++;					 
				}

				printf("\nNúmero de épocas executadas: %d\n", contNumeroEpocasOu);
				//printf("\nContagem Erro individual: %d\n", contErroIndividualOu);

				break; 
			case 2: // Resolver E

				while (contNumeroEpocasE < LIMITE_EPOCAS /*|| contErroIndividualE > 0*/) { // Define uma quantidade máxima de épocas para treinar o neurônio.
					for (j = 0; j < 4; j++) { // Loop responsável por executar o neurônio para cada uma de suas entradas (para cada um dos 4 vetores (j = 0, j = 1, j = 3) temporários de entrada). 
						
						for(k = 0; k < 3; k++) {
							vetEntradaAux[k] = matEntrada[j][k];
							printf("Vetor de entrada %d: %.2f\n", k, vetEntradaAux[k]);
						}
						// calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos)
						nivelAtivacaoNet = calcula_NivelAtivacao(vetEntradaAux, vetPesosW); 
						printf("Nível ativação: %.5f\n", nivelAtivacaoNet);

						// double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada)
						erroIndividual = funcaoAtivacao_LimiarAbruptoSimples(limiarTheta_E, vetSaidaDesejadaE, j, nivelAtivacaoNet, vetEntradaAux); 
						printf("Erro individual: %.5f\n", erroIndividual);

						// Correção do erro
						if(erroIndividual != 0) {
							// Chama função que corrige os pesos: calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada); 
							calcula_novosPesos(vetPesosW, taxaAprendizagemN, erroIndividual, vetEntradaAux);
							 
						} else { // Não houve erro na execução do neurônio
							contErroIndividualOu++; 
						}

						printf("Executou o neurônio para a entrada %d de 4.\n\n", j+1);

					}
					contNumeroEpocasE++; 
				}

				//printf("\nNúmero de épocas executadas: %d\n", contNumeroEpocasOu);
				//printf("\nContagem Erro individual: %d\n", contErroIndividualOu);

				break;
			case 3: // Finalizar e sair. 
					printf("===============================================================================\n");
					printf("| - Desenvolvido por:                                                         |\n");
					printf("|       Gabriel Félix Ramos,                                                  |\n");
					printf("|       Joyce Mayara Almeida.                                                 |\n");
					printf("|                                                                             |\n");
					printf("| - Disciplina: CIC260 - Inteligência Artificial.                             |\n");
					printf("| - Professora: Isabela Drummond Neves.                                       |\n");
					printf("| - Semestre: 2018.2.                                                         |\n");
					printf("| - Para melhor visualização, executar no terminal com os seguintes comandos: |\n");
					printf("|                                                                             |\n");
					printf("|    $ gcc e-ou.c -o e-ou                                                     |\n");
					printf("|    $ ./e-ou                                                                 |\n");
					printf("===============================================================================\n");

					exit(1); /* Termina a execução do programa.  */
					break; 

				default: 
					printf("[X] Insira uma opção válida! \n");
		}

	} while (escolha); 

	return 0;
} // Fim da função principal.

double calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos) {
	double nivelAtivacao = 0; 
	int i = 0;
	double posicaoVetEntrada = 0;
	double posicaoVetPeso = 0;

	for(i = 0; i < 3; i++) {
		posicaoVetEntrada = *(pVetEntrada + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de entrada. 
		posicaoVetPeso = *(pVetPesos + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de pesos.

		// Calcula a soma ponderada das entradas do neurônio pelo peso de cada entrada.
		nivelAtivacao += posicaoVetEntrada * posicaoVetPeso;
	}

	return nivelAtivacao; 
} // Fim de calcula_NivelAtivacao

// Limiar é recebido por parâmetro pois é variável de acordo com a função lógica implementada pelo neurônio. E => limiar = 1. OU => limiar = 0.
double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada) { 
	// Calcula o valor de saída real do neurônio usando a função de limiar abrupto simples
	int saidaCalculada = -10; // -10 é um valor arbitrário de inicialização. 
	double erroIndividual = -20; // -20 é um valor arbitrário de inicialização.
	/* Para cada vetor auxiliar de entrada (ou cada linha da matriz de entradas) corresponde um valor de uma posição do vetor de saída (que contém a saída desejada). 
		Por exemplo, a entrada do neurônio formada pela linha 0 da matriz de entrada tem como saída desejada o valor que está na posição 0 do vetor de saídas; a linha 1 da matriz
	corresponde à posição 1 do vetor de saídas desejadas e assim sucessivamente. Por isso: valorSaidaDesejada = *(pVetSaidaDesejada + pPosicaoVetSaidas_j);
	*/
	double valorSaidaDesejada = *(pVetSaidaDesejada + pPosicaoVetSaidas_j); 

	// Aprendizado supervisionado: comparação entre o valor de saída calculado e o valor de saída desejado (esperado)
	if(pNivelAtivacao > pLimiar) {
		saidaCalculada = 1;
	} else {
		saidaCalculada = 0; 
	}

	erroIndividual = valorSaidaDesejada - saidaCalculada; 

	return erroIndividual; 
} // Fim de funcaoAtivacao_LimiarAbruptoSimples

void calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada) {
	double vetAuxNovosPesos[4]; 
	double posicaoVetEntrada = 0;
	double posicaoVetPeso = 0;
	int i = 0; // Iterador. 
	int j = 0; // Iterador. 

	// Fórmula de correção do erro: w = wi + taxa_aprendizagem * erroIndividual * vetorDeEntrada
	for(i = 0; i < 4; i++) {
		posicaoVetEntrada = *(pVetEntrada + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de entrada. 
		posicaoVetPeso = *(pVetPesos + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de pesos.

		*(vetAuxNovosPesos + i) = posicaoVetPeso + (pTaxaAprendizagem * pErroIndividual + posicaoVetEntrada); 		 
	}

	// Loop que copia os pesos do vetor auxiliar para o vetor de pesos, atualizando-o. 
	printf("Correção de pesos executada. Vetor de pesos novo: ");
	for(j = 0; j < 4; j++) {
		*(pVetPesos + j) = *(vetAuxNovosPesos + j);
		printf("%.2f\t", *(pVetPesos + j));
	}
	printf("\n");

} // Fim de calcula_novosPesos

// SE ELE NÃO CORRIGE OS PESOS PARA TODAS AS ENTRADAS, SIGNIFICA QUE NÃO HÁ ERROS INDIVIDUAIS MAIS E O NEURÔNIO APRENDEU CORRETAMENTE. O.O