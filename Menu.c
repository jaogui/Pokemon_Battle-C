#include <stdio.h>
#include <string.h>

// Estrutura para armazenar o jogador e seu Pokémon escolhido
typedef struct {
    char nome[50];
    char pokemonEscolhido[20];
} Jogador;

// Função para mostrar o menu de boas-vindas e perguntar o nome
void boasVindas(Jogador *jogador) {
    printf("Bem-vindo ao mundo de Pokemon, vamos comecar. Primeiro voce precisa falar com uma pessoa, so um momento.\n");
    printf("...\n");
    printf("...\n");
    printf("...\n");
    printf("Ola, sou o professor Rowan, parece que voce acabou de chegar em Sinnoh, para comecar por favor, me diga o seu nome: ");
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0; // Remover a nova linha capturada pelo fgets
}

// Função para escolher o Pokémon inicial
void escolherPokemon(Jogador *jogador) {
    int escolha = 0;

    do {
        printf("\nMuito bem, %s! Agora escolha seu Pokemon inicial, lembre-se, ele sera seu companheiro para uma longa jornada repleta de aventuras.\n", jogador->nome);
        printf("1. Chimchar\n");
        printf("2. Turtwig\n");
        printf("3. Piplup\n");
        printf("Escolha um companheiro (1-3): ");
        scanf("%d", &escolha);
        getchar();  // Consumir o '\n' deixado pelo scanf

        switch (escolha) {
            case 1:
                strcpy(jogador->pokemonEscolhido, "Chimchar");
                break;
            case 2:
                strcpy(jogador->pokemonEscolhido, "Turtwig");
                break;
            case 3:
                strcpy(jogador->pokemonEscolhido, "Piplup");
                break;
            default:
                printf("Escolha invalida! Por favor, escolha novamente.\n");
                escolha = 0;  
        }
    } while (escolha == 0);

    printf("\nParabens, %s! Você escolheu %s como seu primeiro Pokemon, boa escolha!\n", jogador->nome, jogador->pokemonEscolhido);
}

// Função para salvar os dados do jogador em um arquivo binário
void salvarJogador(Jogador *jogador) {
    FILE *arquivo = fopen("jogador.bin", "wb"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    // Escrever os dados da estrutura no arquivo
    fwrite(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);

    printf("\nDados salvos com sucesso!\n");
}

// Função principal
int main() {
    Jogador jogador;

    boasVindas(&jogador);        
    escolherPokemon(&jogador);   
    salvarJogador(&jogador);     

    return 0;
}
