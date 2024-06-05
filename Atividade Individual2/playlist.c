#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Musica{
    char artista[100];
    char nomeMusica[100];
    int numeroMusica;
    struct Musica* proximo;
    struct Musica* anterior;

}Musica;

void criarLista(Musica *playlist[]){
    char linha[300];
    char *divisor;  
    int cont = 0;

    FILE *arq = fopen("musicas.txt", "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while ( fgets(linha, 300, arq) != NULL)     
    {
        if (cont == 0)
        {
            playlist[cont]->anterior = NULL;
        }
        else
        {
            playlist[cont]->anterior = &playlist[cont - 1];
        }
        

        playlist[cont]->numeroMusica = cont;
        divisor = strtok(linha, ";");
        if (divisor)
        {
            strcpy(playlist[cont]->artista, linha);
            divisor = strtok(linha, "\n");   
            if (divisor)
            {
                strcpy(playlist[cont]->nomeMusica, linha);
            }
        }
        cont += 1;
    }

    playlist[0]->anterior = &playlist[cont];
    playlist[cont-1]->proximo = &playlist[0];

    fclose(arq);
}

void atualizarArquivo(Musica *playlist[], int quantidadeMusicas){
    int i = 0;

    FILE *arq = fopen("musicas.txt", "w");
    if (arq == NULL)
    {
        return;
    }

    while (i <= quantidadeMusicas)
    {
        
        printf(playlist[i]->artista);
        printf(";");
        printf(playlist[i]->nomeMusica);

        i++;
    }

    fclose(arq);
}

int main(){
    Musica *playlist[50];
    int quantidadeMusicas = 0;
    
    criarLista(playlist);


    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", playlist[i]->artista);
    }
    





    return 0;
}