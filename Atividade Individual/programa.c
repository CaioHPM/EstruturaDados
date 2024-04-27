#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTISTAS 100
#define MAX_NOME 100
#define MAX_TIPO_MUSICAL 100
#define MAX_ORIGEM 100
#define MAX_ALBUNS 100
#define MAX_NOME_ARQUIVO 30

typedef struct {
    char nome[MAX_NOME];
    char tipoMusc[MAX_TIPO_MUSICAL];
    char lugarOrigem[MAX_ORIGEM];
    char listaAlbuns[MAX_ALBUNS][MAX_NOME];
    int numAlbuns;
} Artista;

typedef enum {
    INSERIR_ARTISTA = 1,
    REMOVER_ARTISTA,
    EDITAR_ARTISTA,
    BUSCAR_ARTISTA,
    BUSCAR_ALBUM,
    SAIR
} OpcaoInicio;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void iniciarLista(Artista listaArtistas[], int *posArtista) {
    FILE *arquivo = fopen("Artista.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, " %[^\n]", listaArtistas[*posArtista].nome) != EOF) {
        fscanf(arquivo, " %[^\n]", listaArtistas[*posArtista].tipoMusc);
        fscanf(arquivo, " %[^\n]", listaArtistas[*posArtista].lugarOrigem);
        limparBuffer();

        listaArtistas[*posArtista].numAlbuns = 0;
        while (1) {
            fscanf(arquivo, " %[^\n]", listaArtistas[*posArtista].listaAlbuns[listaArtistas[*posArtista].numAlbuns]);
            listaArtistas[*posArtista].numAlbuns++;
            if (strcmp(listaArtistas[*posArtista].listaAlbuns[listaArtistas[*posArtista].numAlbuns - 1], "==========") == 0) {
                break;
            }
        }
        listaArtistas[*posArtista].numAlbuns -= 1;
        (*posArtista)++;
    }

    fclose(arquivo);
}

void reescreverLista(Artista listaArtistas[], int quantidadeArtistas) {
    FILE *arquivo = fopen("Artista.txt", "w+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < quantidadeArtistas; i++) {
        fprintf(arquivo, "%s\n", listaArtistas[i].nome);
        fprintf(arquivo, "%s\n", listaArtistas[i].tipoMusc);
        fprintf(arquivo, "%s\n", listaArtistas[i].lugarOrigem);
        for (int j = 0; j < listaArtistas[i].numAlbuns; j++) {
            fprintf(arquivo, "%s\n", listaArtistas[i].listaAlbuns[j]);
        }
        fprintf(arquivo, "==========\n");
    }

    fclose(arquivo);
}

void inserirArtista(Artista listaArtistas[], int *posArtista) {
    FILE *arquivo = fopen("Artista.txt", "a");
    if (arquivo == NULL) {
        printf("Erro para abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    limparBuffer();
    printf("\nNome do artista: ");
    fgets(listaArtistas[*posArtista].nome, sizeof(listaArtistas[*posArtista].nome), stdin);
    listaArtistas[*posArtista].nome[strcspn(listaArtistas[*posArtista].nome, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posArtista].nome);

    printf("Tipo musical: ");
    fgets(listaArtistas[*posArtista].tipoMusc, sizeof(listaArtistas[*posArtista].tipoMusc), stdin);
    listaArtistas[*posArtista].tipoMusc[strcspn(listaArtistas[*posArtista].tipoMusc, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posArtista].tipoMusc);

    printf("lugar de Origem: ");
    fgets(listaArtistas[*posArtista].lugarOrigem, sizeof(listaArtistas[*posArtista].lugarOrigem), stdin);
    listaArtistas[*posArtista].lugarOrigem[strcspn(listaArtistas[*posArtista].lugarOrigem, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posArtista].lugarOrigem);

    int numAlbuns = 0;
    do {
        printf("Digite o nome do álbum (ou '0' para finalizar): ");
        fgets(listaArtistas[*posArtista].listaAlbuns[numAlbuns], sizeof(listaArtistas[*posArtista].listaAlbuns[numAlbuns]), stdin);
        listaArtistas[*posArtista].listaAlbuns[numAlbuns][strcspn(listaArtistas[*posArtista].listaAlbuns[numAlbuns], "\n")] = '\0';
        fprintf(arquivo, "%s\n", listaArtistas[*posArtista].listaAlbuns[numAlbuns]);
        numAlbuns++;
    } while (strcmp(listaArtistas[*posArtista].listaAlbuns[numAlbuns - 1], "0") != 0 && numAlbuns < MAX_ALBUNS);

    listaArtistas[*posArtista].numAlbuns = numAlbuns - 1;

    fclose(arquivo);
    (*posArtista)++;
}

void removerArtista(Artista listaArtistas[], int *posArtista, char nomeArtista[]) {
    int indice = -1;

    for (int i = 0; i < *posArtista; i++) {
        if (strcmp(nomeArtista, listaArtistas[i].nome) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < *posArtista - 1; i++) {
            listaArtistas[i] = listaArtistas[i + 1];
        }
        (*posArtista)--;

        reescreverLista(listaArtistas, *posArtista);

        printf("Artista removido com sucesso.\n");
    } else {
        printf("Artista não encontrado.\n");
    }
}

void editarArtista(Artista *artista) {
    printf("Novo nome: ");
    fgets(artista->nome, sizeof(artista->nome), stdin);
    artista->nome[strcspn(artista->nome, "\n")] = '\0';

    printf("Novo tipo musical: ");
    fgets(artista->tipoMusc, sizeof(artista->tipoMusc), stdin);
    artista->tipoMusc[strcspn(artista->tipoMusc, "\n")] = '\0';

    printf("Nova lugar de Origem: ");
    fgets(artista->lugarOrigem, sizeof(artista->lugarOrigem), stdin);
    artista->lugarOrigem[strcspn(artista->lugarOrigem, "\n")] = '\0';
}

void buscarAlbum(Artista listaArtistas[], int quanArtistas, char nomeAlbum[]) {
    int encontrado = 0;

    for (int i = 0; i < quanArtistas; i++) {
        for (int j = 0; j < listaArtistas[i].numAlbuns; j++) {
            if (strcmp(nomeAlbum, listaArtistas[i].listaAlbuns[j]) == 0) {
                printf("O album foi %s encontrado e foi feito pelo artista: %s\n", nomeAlbum, listaArtistas[i].nome);
                encontrado = 1;
            }
        }
    }

    if (!encontrado) {
        printf("O album não foi encontrado.\n");
    }
}

void buscarBinario(Artista listaArtistas[], int inicio, int fim, char nomeArtista[]) {
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int comparacao = strcmp(listaArtistas[meio].nome, nomeArtista);

        if (comparacao == 0) {
            printf("Artista: %s\n", listaArtistas[meio].nome);
            printf("Tipo musical: %s\n", listaArtistas[meio].tipoMusc);
            printf("Origem: %s\n", listaArtistas[meio].lugarOrigem);
            for (int i = 0; i < listaArtistas[meio].numAlbuns; i++) {
                printf("Álbum %d: %s\n", i + 1, listaArtistas[meio].listaAlbuns[i]);
            }
            return;
        }

        if (comparacao > 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("O artista não foi encontrado.\n");
}

OpcaoInicio mostrarInicio() {
    int escolha;
    printf("==================== Inicio ====================\n");
    printf("[1] Inserir novo artista\n");
    printf("[2] Remover artista\n");
    printf("[3] Editar artista\n");
    printf("[4] Buscar binaria pelo artista\n");
    printf("[5] Buscar sequencial pelo album\n");
    printf("[6] Sair\n");
    printf("===============================================\n");
    printf("Digite uma opção: ");
    scanf("%d", &escolha);
    limparBuffer();
    return (OpcaoInicio)escolha;
}

int main() {
    Artista listaArtistas[MAX_ARTISTAS];
    int posArtista = 0;
    char nomeArtista[MAX_NOME];
    char nomeAlbum[MAX_NOME];

    iniciarLista(listaArtistas, &posArtista);

    OpcaoInicio opcao;
    do {
        opcao = mostrarInicio();
        switch (opcao) {
            case INSERIR_ARTISTA:
                inserirArtista(listaArtistas, &posArtista);
                break;
            case REMOVER_ARTISTA:
                printf("Digite o nome do artista que você deseja excluir: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                removerArtista(listaArtistas, &posArtista, nomeArtista);
                break;
            case EDITAR_ARTISTA:
                printf("Digite o nome do artista que você deseja editar: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                for (int i = 0; i < posArtista; i++) {
                    if (strcmp(nomeArtista, listaArtistas[i].nome) == 0) {
                        editarArtista(&listaArtistas[i]);
                        reescreverLista(listaArtistas, posArtista);
                        printf("Artista editado com sucesso.\n");
                        break;
                    }
                }
                break;
            case BUSCAR_ARTISTA:
                printf("Digite o nome do artista que você deseja buscar: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                buscarBinario(listaArtistas, 0, posArtista - 1, nomeArtista);
                break;
            case BUSCAR_ALBUM:
                printf("Digite o nome do álbum que você deseja buscar: ");
                fgets(nomeAlbum, sizeof(nomeAlbum), stdin);
                nomeAlbum[strcspn(nomeAlbum, "\n")] = '\0';
                buscarAlbum(listaArtistas, posArtista, nomeAlbum);
                break;
            case SAIR:
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != SAIR);

    return 0;
}
