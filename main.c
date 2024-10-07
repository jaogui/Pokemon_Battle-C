// Regiao de Sinnoh, Professor Rowan
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define max_vida 150
typedef enum { FOGO, AGUA, PLANTA } Tipo;

// Definicões de cores para o terminal (USE SEMPRE O RESETAR DEPOIS )
#define Resetar "\033[0m"
#define Vermelho "\033[31m"
#define Verde "\033[32m"
#define Azul "\033[34m"
#define Roxo "\033[35m"
#define Negrito "\033[1m"

// Struct com todos os dados do jogador e de seu pokemon
typedef struct {
    char nome[50];
    int vida;
    int ataque;
    int ataque_especial; 
    int quant_ataque_especial; 
    int cura;
    int quant_cura;
    Tipo tipo;
} Pokemon;

// Pokemons disponiveis
Pokemon pokemons[3] = {
    {"Chimchar", max_vida, 20, 35, 3, 10, 3, FOGO},
    {"Turtwig", max_vida, 15, 30, 3, 10, 3, PLANTA},
    {"Piplup", max_vida, 18, 32, 3, 10, 3, AGUA}
};

// Estrutura para armazenar o jogador e seu pokemon escolhido
typedef struct {
    char nome[50];
    char jogador_pokemon[50];
} Jogador;

void linhaDeCarregamento() {
    printf(Verde "Carregando" Resetar);
    for (int i = 0; i < 3; i++) {
        printf(Verde "." Resetar);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

// Verifica se o jogador ja jogou antes
int verificarJogadorExistente(Jogador *jogador){
    Jogador jogadorExistente;
    FILE *arquivo = fopen("jogador.bin", "rb");
    if(arquivo == NULL){
        return 0;
    }

    while(fread(&jogadorExistente, sizeof(Jogador), 1, arquivo)){
        printf("Lendo jogador: %s, Pokemon: %s\n" Resetar, jogadorExistente.nome, jogadorExistente.jogador_pokemon);

        if(strcmp(jogadorExistente.nome, jogador->nome) == 0){
            strcpy(jogador->jogador_pokemon, jogadorExistente.jogador_pokemon);
            fclose(arquivo);

            return 1; 
        }
    }

    fclose(arquivo);
    return 0; 
}

// Função para mostrar o menu de boas vindas e perguntar o nome
void boasVindas(Jogador *jogador){
    printf(Negrito Azul "Bem-vindo ao mundo de Pokemon!" Resetar "\n");
    printf(Negrito Azul"Vamos comecar. Primeiro, voce precisa falar com uma pessoa, so um momento.\n");
    linhaDeCarregamento();
    printf(Roxo "...\n" Resetar);
    printf(Roxo "Ola, sou o professor Rowan, parece que voce acabou de chegar em Sinnoh." Resetar "\n");
    printf(Roxo "Para comecar, por favor, me diga o seu nome: "Resetar);
    fgets(jogador->nome, 50, stdin);
    jogador->nome[strcspn(jogador->nome, "\n")] = 0; 
}

// Função para escolher o pokemon inicial
void escolherPokemon(Jogador *jogador){
    int escolha = 0;

    do{
        printf(Roxo "\nOtimo, %s! Prazer em conhece-lo!\n" Resetar, jogador->nome);
        printf(Roxo "\n%s, agora escolha seu Pokemon inicial. Lembre-se, ele sera seu companheiro para uma longa jornada cheia de aventuras!\n", jogador->nome);
        printf(Negrito Vermelho "1. Chimchar\n" Resetar);
        printf(Negrito Verde "2. Turtwig\n" Resetar);
        printf(Negrito Azul "3. Piplup\n" Resetar);
        printf(Negrito "Escolha um companheiro (1-3): " Resetar);
        scanf("%d", &escolha);
        getchar();  

        switch(escolha){
            case 1:
                strcpy(jogador->jogador_pokemon, Negrito Vermelho "Chimchar");
                break;
            case 2:
                strcpy(jogador->jogador_pokemon, Negrito Verde "Turtwig");
                break;
            case 3:
                strcpy(jogador->jogador_pokemon, Negrito Azul "Piplup");
                break;
            default:
                printf(Vermelho "Escolha invalida! Por favor, escolha novamente.\n" Resetar);
                escolha = 0;  
        }
    }while(escolha == 0);

    printf(Roxo "\nParabens, %s! Voce escolheu %s%s como seu primeiro Pokemon, excelente escolha!\n" Resetar, jogador->nome, jogador->jogador_pokemon, Resetar Roxo);
}

// Função para salvar os dados do jogador em um arquivo binario
void salvarJogador(Jogador *jogador){
    FILE *arquivo = fopen("jogador.bin", "ab"); 
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    fwrite(jogador, sizeof(Jogador), 1, arquivo);
    fclose(arquivo);

    printf("\nDados salvos com sucesso!\n");
}

Pokemon escolher_oponente_pokemon(Pokemon jogador_pokemon){
    
    Pokemon oponente_pokemon;
    do{
        oponente_pokemon = pokemons[rand() % 3];
    }while(strcmp(oponente_pokemon.nome, jogador_pokemon.nome) == 0);

    return oponente_pokemon;
}

Pokemon link_jogador_pokemon(Jogador *jogador){
    Pokemon jogador_pokemon;

    for(int i = 0; i < sizeof(pokemons) / sizeof(pokemons[0]); i++){
        if(strcmp(jogador->jogador_pokemon, pokemons[i].nome) == 0){
            jogador_pokemon = pokemons[i];
            return jogador_pokemon;
        }
    }
    Pokemon vazio = {"", 0, 0, 0, 0, 0, 0, FOGO};
    return vazio;

}

int main(){
    srand(time(NULL));

    Jogador jogador;

    boasVindas(&jogador);     

    // Verificar se jogador já existe
    if(verificarJogadorExistente(&jogador)){
        printf(Roxo "Bem-vindo de volta, %s! Seu Pokemon %s%s estava esperando por voce!\n" Resetar, jogador.nome, jogador.jogador_pokemon, Resetar Roxo);
    }else{
        escolherPokemon(&jogador); 
        salvarJogador(&jogador);    
    }

    Pokemon jogador_pokemon = link_jogador_pokemon(&jogador);     

    // Erro no codigo: o pokemon do jogador nunca está sendo encontrado pela função link_jogador_pokemon(), arrumar futuramente

    if(strlen(jogador_pokemon.nome) == 0){
        printf("Erro: Pokemon do jogador nao encontrado.\n");
        return 1;
    }

    Pokemon oponente_pokemon = escolher_oponente_pokemon(jogador_pokemon);

    //Teste da função escolher_oponente_pokemon
    printf("\nPokemon do jogador: %s", jogador_pokemon.nome);
    printf("\nPokemon do oponente: %s", oponente_pokemon.nome);

    return 0;
}