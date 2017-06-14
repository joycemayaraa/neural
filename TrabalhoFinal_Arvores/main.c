#include <stdio.h>
#include <stdlib.h>

int main() {
    int flagMenu = 0, escolha1 = 0, escolha2 = 0;
    
    while(flagMenu == 0){
        printf("1. Inserir novo elemento na árvore 2-3-4\n");
        printf("2. Remover elemento da árvore 2-3-4\n");
        printf("3. Imprimir árvore 2-3-4\n");
        printf("4. Converter em uma árvore rubro-negra\n");
        printf("5. Sair\n");
        scanf("%d", &escolha1);
        
        switch(escolha1){
            case 1:
                //Função que insere elemento na 2-3-4
                break;
            case 2:
                //Função que remove elemento da 2-3-4
                break;
            case 3:
                //Função que imprime a arvore 2-3-4
                break;
            case 4:
                //Chama a função que converte
                system("clear");
                flagMenu = 1;
                break;
            case 5:
                exit(1);
                break;
        }
        while(flagMenu == 1){
            printf("1. Inserir novo elemento na árvore Rubro-Negra\n");
            printf("2. Remover elemento da árvore Rubro-Negra\n");
            printf("3. Imprimir árvore Rubro-Negra\n");
            printf("4. Converter em uma árvore 2-3-4\n");
            printf("5. Sair\n");
            scanf("%d", &escolha2);
        
        switch(escolha2){
            case 1:
                //Função que insere elemento na rubro-negra
                break;
            case 2:
                //Função que remove elemento na rubro-negra
                break;
            case 3:
                //Função que imprime a rubro-negra
                break;
            case 4:
                //Chama a função que converte    
                system("clear");
                flagMenu = 0;
                break;
            case 5:
                exit(1);
                escolha1 = 5;
                break;
            }
        }
    }
    return 0;
}

