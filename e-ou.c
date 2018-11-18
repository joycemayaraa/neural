#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Funções
double calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos);
double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada); 
void calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada); 

int main () {  
// VARIÁVEIS 
	double matEntrada[4][3] = { {0, 0, 1}, 
								{0, 1, 1}, 
								{1, 0, 1}, 
								{1, 1, 1} }; 
	double vetEntradaAux[3] = {-30, -30, -30}; // Vetor auxiliar que receberá cada uma das linhas da matriz que contém os dados de entrada. -30 são valores arbitrários de inicialização.
	
	int limiarTheta_Ou = 0; 
	int limiarTheta_E = 1; 

	double vetSaidaDesejadaOu[4] = {0, 1, 1, 1};
	double vetSaidaDesejadaE[4] = {0, 0, 0, 1}; 
	double vetPesosW[3] = {0.7, -0.3, 0.4};  

	double nivelAtivacaoNet = 0; 
	double erroIndividual = 0; 
	double taxaAprendizagemN = 1.414213562; //Considera-se a taxa (ou ritmo) de aprendizado igual à raiz quadrada de dois. Escolha arbitrária, mas recomenda-se um valor pequeno. 
	
	int i = 0; // Iterador. 
	int j = 0; // Iterador. Atua na correspondência entre cada linha da matriz e a posição do vetor de saídas (que dá o valor de saída desejado àquela entrada). 
	int k = 0; // Iterador. Atua no loop que atribui cada uma das linhas da matriz de entrada de dados para um vetor auxiliar. Índice para as linhas. 

	int limite_epocas = 20;	// Número limite de épocas para o neurônio aprender. 

	int contErroIndividualOu = 0; // Contagem da ocorrência de erros.  
	int contErroIndividualE = 0; // Contagem da ocorrência de erros.  

	int contTotalErroIndividualOu = 0; // Contagem total da ocorrência de erros.  
	int contTotalErroIndividualE = 0; // Contagem total da ocorrência de erros.

	int contNumeroEpocasOu = 0; 
	int contNumeroEpocasE = 0;

	int escolha = 0; 

	struct timeval inicio, fim;
	double tempoExecucaoOU = 0;
	double tempoExecucaoE = 0;
	double ti = 0, tf = 0;

// MENU
	do {

		printf("\t====================================\n");
		printf("\t|        NEURÔNIO ARTIFICIAL       |\n");
		printf("\t|----------------------------------|\n");
		printf("\t| Escolha uma opção:               |\n");
		printf("\t|                                  |\n");
		printf("\t| [1] Resolver porta lógica OU     |\n");
		printf("\t| [2] Resolver porta lógica E;     |\n");
		printf("\t| [3] Finalizar && Sair.           |\n");
		printf("\t|                                  |\n");
		printf("\t====================================\n");
		
		scanf ("%d", &escolha); 


		switch(escolha) {
			case 1: // Resolver OU
				printf("\n");
				printf("Insira o limite máximo de épocas: ");
				scanf("%d", &limite_epocas);
				printf("\n");

				gettimeofday(&inicio, NULL); // Inicia contagem do tempo de execução 


				for (i = 0; i < 3; i++) {
					printf("Insira posição %d de 3 do vetor de pesos: ", i+1);
					scanf("%lf", &vetPesosW[i]);					
				}
				printf("\n");

				while (contNumeroEpocasOu < limite_epocas) { // Define uma quantidade máxima de épocas para treinar o neurônio.

					if ((contErroIndividualOu == 4)) { // Não há erro para todas as entradas do neurônio. Aprendizado do neurônio completo. 
                        break;
                    }

                    if (contNumeroEpocasOu == limite_epocas) { // Não há erro para todas as entradas do neurônio. Aprendizado do neurônio completo. 
                         printf("Número máximo de épocas atingido.\n");
                         break;
                    }


                    // Loop responsável por executar o neurônio para cada uma de suas entradas (para cada um dos 4 vetores temporários de entrada (j = 0, j = 1, j = 3)). 
					for (j = 0; j < 4; j++) { 
						
						// Loop copia para o vetEntradaAux cada uma das 4 entradas do neurônio, a cada iteração do loop. Cada entrada é uma das linhas da matriz de entradas do neurônio: k representa a linha a ser copiada, l as colunas.  
						printf("Vetor de entrada %d: [", j+1);
						for(k = 0; k < 3; k++) { 
							vetEntradaAux[k] = matEntrada[j][k];
							printf("  %.2f  ", vetEntradaAux[k]);
						}
						printf("]\n");

						// Calcula o nível de ativação do neurônio
						nivelAtivacaoNet = calcula_NivelAtivacao(vetEntradaAux, vetPesosW); 
						printf("Nível ativação: %.5f\n", nivelAtivacaoNet);

						// Calcula o erro individual da entrada sob análise 
						erroIndividual = funcaoAtivacao_LimiarAbruptoSimples(limiarTheta_Ou, vetSaidaDesejadaOu, j, nivelAtivacaoNet, vetEntradaAux); 
						printf("Erro individual: %.5f\n", erroIndividual);

						
						if(erroIndividual != 0) {  // Existe diferença entre a saída (calculada) do neurônio e a saída desejada: existe erro. 
							// Correção do erro: Chama função que corrige os pesos do neurônio para reduzir o erro na próxima execução das entradas. 
                            calcula_novosPesos(vetPesosW, taxaAprendizagemN, erroIndividual, vetEntradaAux);
                            printf("Executou o neurônio para a entrada %d de 4. Continuando execução com novo vetor de pesos.\n\n", j + 1);
                            /////printf("Executou o neurônio para a entrada %d de 4. Reiniciando execução com novo vetor de pesos.\n\n", j + 1); // Se j for reiniciado para -1, usar esse print: 
                            ////j = -1; // Reinicia o iterador para que o novo vetor de pesos seja aplicado a todas as entradas, desde o início. 
                            contErroIndividualOu = 0; // Reinicia a contagem. 
                            contTotalErroIndividualOu++; 
                            
						} else { // Não houve erro na execução do neurônio
							// Armazena o número de vezes em que as entradas não apresentou erro: será igual a 4 se não houver erro para todas as entradas do neurônio (Nesse caso, o aprendizado do neurônio está completo e pode-se interromper o loop while). 
							contErroIndividualOu++; 
                            printf("Executou o neurônio para a entrada %d de 4.\n\n", j + 1); 
						}

						if(j == 3 && contErroIndividualOu < 4){
							contErroIndividualOu = 0;
						}
							
					}
					contNumeroEpocasOu++;
										 
				} 

				// Finaliza contagem do tempo de execução
				gettimeofday(&fim, NULL);
				tf = (double) fim.tv_usec + ( (double)fim.tv_sec * (1000000.0) );
				ti = (double) inicio.tv_usec + ( (double)inicio.tv_sec * (1000000.0) );
				tempoExecucaoOU = (tf - ti) / 1000; //milisegundos
				
				printf("Número de épocas executadas: %d\n", contNumeroEpocasOu);
				printf("Total de ocorrência de erros: %d\n", contTotalErroIndividualOu);
				printf("Tempo de execução da resolução da porta OU: %.5f milisegundos\n\n", tempoExecucaoOU);

				break; 

			case 2: // Resolver E
				printf("\n");
				printf("Insira o limite máximo de épocas: ");
				scanf("%d", &limite_epocas);
				printf("\n");

				gettimeofday(&inicio, NULL); // Inicia contagem do tempo de execução

				for (i = 0; i < 3; i++) {
					printf("Insira posição %d de 3 do vetor de pesos: ", i+1);
					scanf("%lf", &vetPesosW[i]);					
				}
				printf("\n"); 

				while (contNumeroEpocasE < limite_epocas) { // Define uma quantidade máxima de épocas para treinar o neurônio.

					if ((contErroIndividualE == 4)) { // Não há erro para todas as entradas do neurônio. Aprendizado do neurônio completo. 
                        break;
                    }

                    if (contNumeroEpocasE == limite_epocas) { // Não há erro para todas as entradas do neurônio. Aprendizado do neurônio completo. 
                         printf("Número máximo de épocas atingido.\n");
                         break;
                    }


                    // Loop responsável por executar o neurônio para cada uma de suas entradas (para cada um dos 4 vetores temporários de entrada (j = 0, j = 1, j = 3)). 
					for (j = 0; j < 4; j++) { 
						
						// Loop copia para o vetEntradaAux cada uma das 4 entradas do neurônio, a cada iteração do loop. Cada entrada é uma das linhas da matriz de entradas do neurônio: k representa a linha a ser copiada, l as colunas.  
						printf("Vetor de entrada %d: [", j+1);
						for(k = 0; k < 3; k++) { 
							vetEntradaAux[k] = matEntrada[j][k];
							printf("  %.2f  ", vetEntradaAux[k]);
						}
						printf("]\n");

						// Calcula o nível de ativação do neurônio
						nivelAtivacaoNet = calcula_NivelAtivacao(vetEntradaAux, vetPesosW); 
						printf("Nível ativação: %.5f\n", nivelAtivacaoNet);

						// Calcula o erro individual da entrada sob análise 
						erroIndividual = funcaoAtivacao_LimiarAbruptoSimples(limiarTheta_E, vetSaidaDesejadaE, j, nivelAtivacaoNet, vetEntradaAux); 
						printf("Erro individual: %.5f\n", erroIndividual);

						
						if(erroIndividual != 0) {  // Existe diferença entre a saída (calculada) do neurônio e a saída desejada: existe erro. 
							// Correção do erro: Chama função que corrige os pesos do neurônio para reduzir o erro na próxima execução das entradas. 
                            calcula_novosPesos(vetPesosW, taxaAprendizagemN, erroIndividual, vetEntradaAux);
                            printf("Executou o neurônio para a entrada %d de 4. Continuando execução com novo vetor de pesos.\n\n", j + 1);
                            /////printf("Executou o neurônio para a entrada %d de 4. Reiniciando execução com novo vetor de pesos.\n\n", j + 1); // Se j for reiniciado para -1, usar esse print: 
                            ////j = -1; // Reinicia o iterador para que o novo vetor de pesos seja aplicado a todas as entradas, desde o início. 
                            contErroIndividualE = 0; // Reinicia a contagem. 
                            contTotalErroIndividualE++; 
                            
						} else { // Não houve erro na execução do neurônio
							// Armazena o número de vezes em que as entradas não apresentou erro: será igual a 4 se não houver erro para todas as entradas do neurônio (Nesse caso, o aprendizado do neurônio está completo e pode-se interromper o loop while). 
							contErroIndividualE++; 
                            printf("Executou o neurônio para a entrada %d de 4.\n\n", j + 1); 
						}

						if(j == 3 && contErroIndividualE < 4){
							contErroIndividualE = 0;
						}
							
					}
					contNumeroEpocasE++;
										 
				} 

				// Finaliza contagem do tempo de execução
				gettimeofday(&fim, NULL);
				tf = (double) fim.tv_usec + ( (double)fim.tv_sec * (1000000.0) );
				ti = (double) inicio.tv_usec + ( (double)inicio.tv_sec * (1000000.0) );
				tempoExecucaoE = (tf - ti) / 1000; //milisegundos

				printf("Número de épocas executadas: %d\n", contNumeroEpocasE);
				printf("Total de ocorrência de erros: %d\n", contTotalErroIndividualE);
				printf("Tempo de execução da resolução da porta E: %.5f milisegundos\n\n", tempoExecucaoE);

				break;
			case 3: // Finalizar e sair. 
					printf("===============================================================================\n");
					printf("| - Desenvolvido por:                                                         |\n");
					printf("|       Gabriel Félix Ramos,                                                  |\n");
					printf("|       Joyce Mayara Almeida.                                                 |\n");
					printf("|                                                                             |\n");
					printf("| - Disciplina: CIC260 - Inteligência Artificial.                             |\n");
					printf("| - Professora: Isabela Neves Drummond.                                       |\n");
					printf("| - Semestre: 2018_2.                                                         |\n");
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

/* Função que calcula o nível de ativação do neurônio. */
double calcula_NivelAtivacao(double* pVetEntrada, double* pVetPesos) {
	double nivelAtivacao = 0; 
	int i = 0;
	double posicaoVetEntrada = 0;
	double posicaoVetPeso = 0;

	for(i = 0; i < 3; i++) {
		posicaoVetEntrada = *(pVetEntrada + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de entrada. 
		posicaoVetPeso = *(pVetPesos + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de pesos.

		// Calcula o nível de ativação: a soma ponderada das entradas do neurônio pelo peso de cada entrada.
		nivelAtivacao += posicaoVetEntrada * posicaoVetPeso;
	}

	return nivelAtivacao; 
} // Fim de calcula_NivelAtivacao


/***
** 		Função que implementa a função de limiar (ou de ativação) do neurônio. Ela calcula o estado final (ou a saída) do neurônio, determinando o 
** quanto o nível de ativação do neurônio está abaixo ou acima de um valor de limiar. Objetiva definir a ativação do neurônio. 
** 		A função é do tipo função de limiar abrupto simples, em que uma ativação acima de limiar resulta em um valor de saída 1, ou no caso contrário, de 0.  
** 		O valor do Limiar é recebido por parâmetro, pois é variável de acordo com a função lógica implementada pelo neurônio. E => limiar = 1. OU => limiar = 0.
***/
double funcaoAtivacao_LimiarAbruptoSimples(int pLimiar, double* pVetSaidaDesejada, int pPosicaoVetSaidas_j, double pNivelAtivacao, double* pVetEntrada) { 
	int saidaCalculada = -10; // -10 é um valor arbitrário de inicialização. 
	double erroIndividual = -20; // -20 é um valor arbitrário de inicialização.
	int valorSaidaDesejada = -30; 

	if(pNivelAtivacao > pLimiar) {
		saidaCalculada = 1;
	} else {
		saidaCalculada = 0; 
	}

	printf("Saída Calculada: %d\n", saidaCalculada);
	/* Para cada vetor auxiliar de entrada (ou cada linha da matriz de entradas) corresponde um valor de uma posição do vetor de saída (que contém a saída desejada). 
		Por exemplo, a entrada do neurônio formada pela linha 0 da matriz de entrada tem como saída desejada o valor que está na posição 0 do vetor de saídas; a linha 1 da matriz
	corresponde à posição 1 do vetor de saídas desejadas e assim sucessivamente. Por isso: valorSaidaDesejada = *(pVetSaidaDesejada + pPosicaoVetSaidas_j);
	*/
	valorSaidaDesejada = *(pVetSaidaDesejada + pPosicaoVetSaidas_j);
	printf("Saída Desejada: %d\n", valorSaidaDesejada);

	/*
	Implementação do aprendizado supervisionado: É fornecido ao neurônio o resultado correto (saída desejada). 
	Se ocorre uma diferença entre o valor da saída calculada e o valor de saída desejado, essa diferença forma o erro individual. 
	Se o erro individual for diferente de zero, o neurônio, então, modificará seus pesos de modo a reduzir esse erro na próxima execução. 
	*/
	erroIndividual = valorSaidaDesejada - saidaCalculada; 

	return erroIndividual; 
} // Fim de funcaoAtivacao_LimiarAbruptoSimples


/* Função que modifica os pesos do neurônio de modo a reduzir o erro apresentado na execução da entrada. */
void calcula_novosPesos(double* pVetPesos, double pTaxaAprendizagem, double pErroIndividual, double* pVetEntrada) {
	double vetAuxNovosPesos[3]; 
	double posicaoVetEntrada = 0;
	double posicaoVetPeso = 0;
	int i = 0; // Iterador. 
	int j = 0; // Iterador. 

	// Fórmula de correção do erro: w = wi + taxa_aprendizagem * erroIndividual * vetorDeEntrada
	for(i = 0; i <  3; i++) {
		posicaoVetEntrada = *(pVetEntrada + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de entrada. 
		
		posicaoVetPeso = *(pVetPesos + i); // Conforme a execução do loop, recebe o conteúdo da 1ª, 2ª e 3ª posições do vetor de pesos.
		printf("Posição %d -> vet Entrada: %.2f\tvet Peso: %.2f\n", i, posicaoVetEntrada, posicaoVetPeso);

		*(vetAuxNovosPesos + i) = posicaoVetPeso + (pTaxaAprendizagem * pErroIndividual * posicaoVetEntrada); // Preenche o vetor com os novos pesos, posição por posição.		 
	}

	// Loop que copia os pesos do vetor auxiliar para o vetor de pesos, atualizando-o. 
	printf("Correção de pesos executada. Vetor de pesos novo: [");
	for(j = 0; j < 3; j++) {
		*(pVetPesos + j) = *(vetAuxNovosPesos + j);
		printf("  %.2f  ", *(pVetPesos + j));
	}
	printf("]\n");

} // Fim de calcula_novosPesos

// SE ELE NÃO CORRIGE OS PESOS PARA TODAS AS ENTRADAS, SIGNIFICA QUE NÃO HÁ MAIS ERROS INDIVIDUAIS E O NEURÔNIO APRENDEU CORRETAMENTE. 