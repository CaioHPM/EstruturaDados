#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Musica{
    char artista[100];
    char nomeMusica[100];
    struct Musica* proximo;
    struct Musica* anterior;

}Musica;

void criarLista(Musica *playlist[]){
    char linha[300];
    char *divisor;  
    int numeroMusica = 0;
    FILE *arq = fopen("musicas.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
    while ( fgets(linha, 300, arq) != NULL)     
    {
        divisor = strtok(linha, ";");
        if (divisor)
        {
            strcpy(playlist[numeroMusica]->artista, linha);
            divisor = strtok(linha, "\n");   
            if (divisor)
            {
                strcpy(playlist[numeroMusica]->nomeMusica, linha);
            }
        }
        numeroMusica += 1;
    }
    fclose(arq);
}

int main(){
    Musica *playlist[50];

    
    criarLista(playlist);


    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", playlist[i]->artista);
    }
    





    return 0;
}