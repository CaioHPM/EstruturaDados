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

void excluirMusica(Musica *playlist[], int quantidadeMusicas){
    char comparador[100];
    int cont = 0, indicador = 0;

    printf("Digite o nome do artista ou da musica:");
    scanf("%s", comparador);

    while (cont <= quantidadeMusicas)
    {
        if (strcmp(comparador, playlist[cont]->nomeMusica) || strcmp(comparador, playlist[cont]->artista))
        {
            indicador = cont;

            printf("Artista/Musica removido com sucesso.");

            if (cont == quantidadeMusicas)
            {
                playlist[cont - 1]->proximo = &playlist[0];
                playlist[0]->anterior = &playlist[cont - 1];
            }
            else if (cont == 0)
            {
                playlist[quantidadeMusicas]->proximo = &playlist[1];
                playlist[1]->anterior = &playlist[quantidadeMusicas];
            }
            
            else
            {
                playlist[cont - 1]->proximo = &playlist[cont + 1];
                playlist[cont + 1]->anterior = &playlist[cont - 1];
            }
            
        }
        if (indicador <= cont)
        {
            playlist[cont] = playlist[cont + 1];
            playlist[quantidadeMusicas] = NULL;
        }
        
        cont++;
    }
    quantidadeMusicas--;
    atualizarArquivo(playlist, quantidadeMusicas);
}

void buscarMusica(Musica *playlist[], int quantidadeMusicas){
    char comparador[100];
    int cont = 0;

    printf("Digite o nome do artista ou da musica:");
    scanf("%s", comparador);

    while (cont <= quantidadeMusicas)
    {
        if (strcmp(comparador, playlist[cont]->nomeMusica) || strcmp(comparador, playlist[cont]->artista))
        {
            printf("==============================================================================\n");
            printf("Artista/Musica encontrado com sucesso.\n");
            printf("É a musica da posição %d da sua playlist.\n", &cont + 1);
            printf("Artista: %s, Musica: %s.", playlist[cont]->artista, playlist[cont]->nomeMusica);
            printf("==============================================================================\n");

        }
        cont++;
    }
}

void mostrarOrdemCadastrada(Musica *playlist, int quantidadeMusicas){

    printf("================================================================\n");

    for (int i = 0; i <= quantidadeMusicas; i++)
    {
        printf("Artista: %s, Musica: %s.\n", playlist[i].artista, playlist[i].nomeMusica);
        if (quantidadeMusicas != i)
        {
            printf("---------------------------------------------------\n");   
        }
    }
    printf("================================================================\n");

}

int compararMusicas(const void *a, const void *b) {
    Musica *musicaA = (Musica *)a;
    Musica *musicaB = (Musica *)b;
    return strcasecmp(musicaA->nomeMusica, musicaB->nomeMusica);
}

void mostrarOrdemAlfabetica(Musica listaMusicas[], int quantidadeMusicas) {

    Musica listaTemporaria[500];

    for(int cont = 0; cont < quantidadeMusicas; cont++) {
        listaTemporaria[cont] = listaMusicas[cont];
    }

    qsort(listaTemporaria, quantidadeMusicas, sizeof(Musica), compararMusicas);

    printf("================================================================\n");
    printf("\nPlaylist em ordem alfabetica:\n");
    printf("================================================================\n");
    for (int cont = 0; cont <= quantidadeMusicas; cont++) {
        printf("Artista: %s, Musica: %s\n", listaTemporaria[cont].artista, listaTemporaria[cont].nomeMusica);
        if (cont != quantidadeMusicas)
        {
            printf("---------------------------------------------------\n");
        }
    }
    printf("================================================================\n");
}

void proximaMusica(Musica **musicaTocando) {
    *musicaTocando = (*musicaTocando)->proximo;
}

void musicaAnterior(Musica **musicaTocando) {
    *musicaTocando = (*musicaTocando)->anterior;
}

int main(){
    Musica *playlist[50];
    Musica *musicaTocando;
    int quantidadeMusicas = 0, opcao = 0;
    
    criarLista(playlist);

    musicaTocando = playlist[0];

    while (opcao != 8)
    {
        printf("\nMusica que está tocando: %s\n", musicaTocando->nomeMusica);
        printf("---------------------------------------------------\n");

        printf("Digite 1 para exibir a playlist pela ordem de cadastro\n");
        printf("Digite 2 para exibir a playlist ordenada pelo nome das músicas\n");
        printf("Digite 3 para inserir novas músicas\n");
        printf("Digite 4 para remover uma música\n");
        printf("Digite 5 para busca por uma música\n");
        printf("Digite 6 para avançar para próxima música\n");
        printf("Digite 7 para retornar a música anterior\n");
        printf("---------------------------------------------------\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            mostrarOrdemCadastrada(playlist, quantidadeMusicas);
            break;
        case 2:
            mostrarOrdemAlfabetica(playlist, quantidadeMusicas);
            break;
        case 3:
            inserirMusica(playlist, quantidadeMusicas);
            break;
        case 4:
            excluirMusica(playlist, quantidadeMusicas);
            break;
        case 5:
            buscarMusica(playlist, quantidadeMusicas);
            break;
        case 6:
            proximaMusica(musicaTocando);
            break;
        case 7:
            musicaAnterior(musicaTocando);
            break;
        case 8:
            printf("Obrigado por usar este programa.");
            break;
        default:
            printf("O numero digitado não representa nenhuma das opções anteriores.");
            break;
        }
    }
    
    return 0;
}