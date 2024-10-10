// Função para iniciar a batalha entre o jogador e o oponente
void iniciarBatalha(Pokemon *jogador_pokemon, Pokemon *oponente_pokemon) {
    printf(Roxo "\nA batalha começou!\n" Resetar);
    printf(Negrito Verde "Seu Pokemon: %s\n" Resetar, jogador_pokemon->nome);
    printf(Negrito Vermelho "Pokemon oponente: %s\n" Resetar, oponente_pokemon->nome);
    
    int turno = 1;
    while(jogador_pokemon->vida > 0 && oponente_pokemon->vida > 0) {
        printf(Negrito "\nTurno %d\n" Resetar, turno);

        // Jogador ataca primeiro
        oponente_pokemon->vida -= jogador_pokemon->ataque;
        printf(Verde "%s atacou %s! Vida restante do oponente: %d\n" Resetar, jogador_pokemon->nome, oponente_pokemon->nome, oponente_pokemon->vida);
        
        if (oponente_pokemon->vida <= 0) {
            printf(Verde "\nParabéns! Você derrotou o %s!\n" Resetar, oponente_pokemon->nome);
            break;
        }

        // Oponente contra-ataca
        jogador_pokemon->vida -= oponente_pokemon->ataque;
        printf(Vermelho "%s atacou %s! Sua vida restante: %d\n" Resetar, oponente_pokemon->nome, jogador_pokemon->nome, jogador_pokemon->vida);

        if (jogador_pokemon->vida <= 0) {
            printf(Vermelho "\nVocê foi derrotado pelo %s.\n" Resetar, oponente_pokemon->nome);
            break;
        }

        turno++;
    }
}

int main() {
    srand(time(NULL));

    Jogador jogador;
    Pokemon jogador_pokemon;
    
    boasVindas(&jogador);     

    if(verificarJogadorExistente(&jogador)){
        jogador_pokemon = link_jogador_pokemon(&jogador); 
    } else {
        escolherPokemon(&jogador); 
        salvarJogador(&jogador);   
        jogador_pokemon = link_jogador_pokemon(&jogador); 
    }    

    if(strlen(jogador_pokemon.nome) == 0) {
        printf("Erro: Pokemon do jogador nao encontrado.\n");
        return 1;
    }

    Pokemon oponente_pokemon = escolher_oponente_pokemon(jogador_pokemon);

    // Inicia a batalha
    iniciarBatalha(&jogador_pokemon, &oponente_pokemon);

    return 0;
}
