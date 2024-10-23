#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int vida;
    int ataque;
    int ataque_especial;
    int quant_ataque_especial;
    int cura;
    int quant_cura;
} Pokemon;

// Função para inicializar o histórico no início da batalha
void iniciar_historico(const Pokemon *jogador_pokemon, const Pokemon *oponente_pokemon) {
    FILE *arquivo = fopen("historico.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de historico.\n");
        return;
    }

    fprintf(arquivo, "========================\n");
    fprintf(arquivo, " BATALHA POKÉMON INICIADA\n");
    fprintf(arquivo, "========================\n");
    fprintf(arquivo, "Jogador: %s\n", jogador_pokemon->nome);
    fprintf(arquivo, "Oponente: %s\n\n", oponente_pokemon->nome);
    fclose(arquivo);
}

// Função para salvar detalhes de um ataque no histórico
void salvar_ataque(const char *atacante, const char *alvo, int dano, int vida_restante) {
    FILE *arquivo = fopen("historico.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de historico.\n");
        return;
    }

    fprintf(arquivo, "----------------------------------\n");
    fprintf(arquivo, "ATAQUE: %s atacou %s\n", atacante, alvo);
    fprintf(arquivo, "Dano causado: %d\n", dano);
    fprintf(arquivo, "Vida restante de %s: %d\n", alvo, vida_restante);
    fprintf(arquivo, "----------------------------------\n\n");
    fclose(arquivo);
}

// Função para salvar detalhes de uma cura no histórico
void salvar_cura(const char *pokemon, int cura, int vida_restante) {
    FILE *arquivo = fopen("historico.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de historico.\n");
        return;
    }

    fprintf(arquivo, "----------------------------------\n");
    fprintf(arquivo, "CURA: %s usou uma poção\n", pokemon);
    fprintf(arquivo, "Cura realizada: %d\n", cura);
    fprintf(arquivo, "Vida atual de %s: %d\n", pokemon, vida_restante);
    fprintf(arquivo, "----------------------------------\n\n");
    fclose(arquivo);
}

// Função para finalizar o histórico ao término da batalha
void finalizar_historico(const char *vencedor) {
    FILE *arquivo = fopen("historico.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de historico.\n");
        return;
    }

    fprintf(arquivo, "========================\n");
    fprintf(arquivo, " BATALHA FINALIZADA\n");
    fprintf(arquivo, " Vencedor: %s\n", vencedor);
    fprintf(arquivo, "========================\n");
    fclose(arquivo);
}