#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTISTAS 100
#define MAX_NOME 100
#define MAX_TIPO_MUSICAL 100
#define MAX_NATURALIDADE 100
#define MAX_ALBUNS 100
#define MAX_NOME_ARQUIVO 30

typedef struct {
    char nome[MAX_NOME];
    char tipoMusc[MAX_TIPO_MUSICAL];
    char naturalidade[MAX_NATURALIDADE];
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

void iniciarLista(Artista listaArtistas[], int *posicaoArtista) {
    FILE *arquivo = fopen("Artista.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(arquivo, " %[^\n]", listaArtistas[*posicaoArtista].nome) != EOF) {
        fscanf(arquivo, " %[^\n]", listaArtistas[*posicaoArtista].tipoMusc);
        fscanf(arquivo, " %[^\n]", listaArtistas[*posicaoArtista].naturalidade);
        limparBuffer();

        listaArtistas[*posicaoArtista].numAlbuns = 0;
        while (1) {
            fscanf(arquivo, " %[^\n]", listaArtistas[*posicaoArtista].listaAlbuns[listaArtistas[*posicaoArtista].numAlbuns]);
            listaArtistas[*posicaoArtista].numAlbuns++;
            if (strcmp(listaArtistas[*posicaoArtista].listaAlbuns[listaArtistas[*posicaoArtista].numAlbuns - 1], "==========") == 0) {
                break;
            }
        }
        listaArtistas[*posicaoArtista].numAlbuns -= 1;
        (*posicaoArtista)++;
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
        fprintf(arquivo, "%s\n", listaArtistas[i].naturalidade);
        for (int j = 0; j < listaArtistas[i].numAlbuns; j++) {
            fprintf(arquivo, "%s\n", listaArtistas[i].listaAlbuns[j]);
        }
        fprintf(arquivo, "==========\n");
    }

    fclose(arquivo);
}

void inserirArtista(Artista listaArtistas[], int *posicaoArtista) {
    FILE *arquivo = fopen("Artista.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    limparBuffer();
    printf("\nNome do artista: ");
    fgets(listaArtistas[*posicaoArtista].nome, sizeof(listaArtistas[*posicaoArtista].nome), stdin);
    listaArtistas[*posicaoArtista].nome[strcspn(listaArtistas[*posicaoArtista].nome, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posicaoArtista].nome);

    printf("Tipo musical: ");
    fgets(listaArtistas[*posicaoArtista].tipoMusc, sizeof(listaArtistas[*posicaoArtista].tipoMusc), stdin);
    listaArtistas[*posicaoArtista].tipoMusc[strcspn(listaArtistas[*posicaoArtista].tipoMusc, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posicaoArtista].tipoMusc);

    printf("Naturalidade: ");
    fgets(listaArtistas[*posicaoArtista].naturalidade, sizeof(listaArtistas[*posicaoArtista].naturalidade), stdin);
    listaArtistas[*posicaoArtista].naturalidade[strcspn(listaArtistas[*posicaoArtista].naturalidade, "\n")] = '\0';
    fprintf(arquivo, "%s\n", listaArtistas[*posicaoArtista].naturalidade);

    int numAlbuns = 0;
    do {
        printf("Digite o nome do álbum (ou '0' para finalizar): ");
        fgets(listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns], sizeof(listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns]), stdin);
        listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns][strcspn(listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns], "\n")] = '\0';
        fprintf(arquivo, "%s\n", listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns]);
        numAlbuns++;
    } while (strcmp(listaArtistas[*posicaoArtista].listaAlbuns[numAlbuns - 1], "0") != 0 && numAlbuns < MAX_ALBUNS);

    listaArtistas[*posicaoArtista].numAlbuns = numAlbuns - 1;

    fclose(arquivo);
    (*posicaoArtista)++;
}

void removerArtista(Artista listaArtistas[], int *posicaoArtista, char nomeArtista[]) {
    int indice = -1;

    for (int i = 0; i < *posicaoArtista; i++) {
        if (strcmp(nomeArtista, listaArtistas[i].nome) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < *posicaoArtista - 1; i++) {
            listaArtistas[i] = listaArtistas[i + 1];
        }
        (*posicaoArtista)--;

        reescreverLista(listaArtistas, *posicaoArtista);

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

    printf("Nova naturalidade: ");
    fgets(artista->naturalidade, sizeof(artista->naturalidade), stdin);
    artista->naturalidade[strcspn(artista->naturalidade, "\n")] = '\0';
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
            printf("Origem: %s\n", listaArtistas[meio].naturalidade);
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
    int posicaoArtista = 0;
    char nomeArtista[MAX_NOME];
    char nomeAlbum[MAX_NOME];

    iniciarLista(listaArtistas, &posicaoArtista);

    OpcaoInicio opcao;
    do {
        opcao = mostrarInicio();
        switch (opcao) {
            case INSERIR_ARTISTA:
                inserirArtista(listaArtistas, &posicaoArtista);
                break;
            case REMOVER_ARTISTA:
                printf("Digite o nome do artista que você deseja excluir: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                removerArtista(listaArtistas, &posicaoArtista, nomeArtista);
                break;
            case EDITAR_ARTISTA:
                printf("Digite o nome do artista que você deseja editar: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                for (int i = 0; i < posicaoArtista; i++) {
                    if (strcmp(nomeArtista, listaArtistas[i].nome) == 0) {
                        editarArtista(&listaArtistas[i]);
                        reescreverLista(listaArtistas, posicaoArtista);
                        printf("Artista editado com sucesso.\n");
                        break;
                    }
                }
                break;
            case BUSCAR_ARTISTA:
                printf("Digite o nome do artista que você deseja buscar: ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                buscarBinario(listaArtistas, 0, posicaoArtista - 1, nomeArtista);
                break;
            case BUSCAR_ALBUM:
                printf("Digite o nome do álbum que você deseja buscar: ");
                fgets(nomeAlbum, sizeof(nomeAlbum), stdin);
                nomeAlbum[strcspn(nomeAlbum, "\n")] = '\0';
                buscarAlbum(listaArtistas, posicaoArtista, nomeAlbum);
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
