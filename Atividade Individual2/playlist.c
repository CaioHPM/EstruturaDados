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

void inserirMusica(Musica *playlist[], int quantidadeMusicas){
    quantidadeMusicas ++;

    printf("Digite o nome do artista:");
    scanf("%s", playlist[quantidadeMusicas]->artista);
    printf("Digite o nome da musica:");
    scanf("%s", playlist[quantidadeMusicas]->nomeMusica);

    playlist[quantidadeMusicas - 1]->proximo = &playlist[quantidadeMusicas];
    playlist[quantidadeMusicas]->proximo = &playlist[0];
    playlist[0]->anterior = &playlist[quantidadeMusicas];

    atualizarArquivo(playlist, quantidadeMusicas);

}

void excluirMusica(Musica *playlist[], int quantidadeMusica){
    char comparador[100];
    int cont = 0;

    printf("Digite o nome do artista ou da musica:");
    scanf("%s", comparador);

    while (cont <= quantidadeMusica)
    {
        if (strcmp(comparador, playlist[cont]->nomeMusica) || strcmp(comparador, playlist[cont]->artista))
        {
            if (cont == quantidadeMusica)
            {
                playlist[cont - 1]->proximo = &playlist[0];
                playlist[0]->anterior = &playlist[cont - 1];
            }
            else if (cont == 0)
            {
                playlist[quantidadeMusica]->proximo = &playlist[1];
            }
            
            else
            {
                playlist[cont - 1]->proximo = &playlist[cont + 1];
                playlist[cont + 1]->anterior = &playlist[cont - 1];
            }
            
        }
        cont++;
    }
    
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