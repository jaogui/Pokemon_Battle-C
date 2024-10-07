// Regiao de Sinnoh, Professor Rowan

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_vida 150
typedef enum { FOGO, AGUA, PLANTA } Tipo;

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

typedef struct {
    char nome[50];
    int vitorias;
    int derrotas;
} Jogador;

Pokemon escolher_oponente_pokemon(Pokemon jogador_pokemon){

    Pokemon oponente_pokemon;
    do{
        oponente_pokemon = pokemons[rand() % 3];
    }while(strcmp(oponente_pokemon.nome, jogador_pokemon.nome) == 0);

    return oponente_pokemon;
}

int main(){
    srand(time(NULL));

    //Teste da função escolher_oponente_pokemon
    Pokemon jogador_pokemon = {"Chimchar", max_vida, 20, 10, 35, 2, FOGO}; // Pokemon do jogador hipotetico para teste
    Pokemon oponente_pokemon = escolher_oponente_pokemon(jogador_pokemon);
    printf("\nPokemon do jogador: %s", jogador_pokemon.nome);
    printf("\nPokemon do oponente: %s", oponente_pokemon.nome);

    return 0;
}