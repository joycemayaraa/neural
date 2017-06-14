#include <stdlib.h>
#include <stdio.h>
#include "E-S_dados.h"

void lerArquivo(int dados[]){ //editar vet pra arvore 2-3-4
    FILE *arq;
    int i = 0;
    if(!(arq = fopen("dados.txt", "r"))){
        printf("Erro de arquivo\n");
        exit(0);
    }
    while( !feof(arq)){
        fscanf(arq, "%d", &dados[i]);
        i++;
    }
    fclose(arq);
}
void gerarDados(){
    FILE *arq;
    arq = fopen("dados.txt", "w");
    if(arq == NULL){
        printf("Problema na abertura de arquivo\n");
        exit(0);
    }
    for(int j = 0; j < 10; j++){
        fprintf(arq, "%d\n", rand()%50+1);
    }
    fclose(arq);
    return;
}
void imprimirArvoreRB(){
    
}
void imprimirArvore234(){
    
}
