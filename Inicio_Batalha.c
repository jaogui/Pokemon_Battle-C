// Função para iniciar a batalha entre o jogador e o oponente
int batalha_total(Pokemon jogador_pokemon, Pokemon oponente_pokemon) {
    const char *cor_j = cor_pokemon(jogador_pokemon);
    const char *cor_o = cor_pokemon(oponente_pokemon);
    int jogador_max_vida = jogador_pokemon.vida;
    int oponente_max_vida = oponente_pokemon.vida;

    const char* cor_vida_jogador;
    const char* cor_vida_oponente;
  
    if(jogador_pokemon.vida > jogador_max_vida / 2){
      cor_vida_jogador = Negrito Verde;
    }else if(jogador_pokemon.vida > jogador_max_vida / 4){
      cor_vida_jogador = Negrito Amarelo;
    }else{
      cor_vida_jogador = Negrito Vermelho;
    }
  
    if(oponente_pokemon.vida > oponente_max_vida / 2){
      cor_vida_oponente = Negrito Verde;
    }else if(oponente_pokemon.vida > oponente_max_vida / 4){
      cor_vida_oponente = Negrito Amarelo;
    }else{
      cor_vida_oponente = Negrito Vermelho;
    }
  
    printf(Negrito Cinza"\n\nBarry%s te desafia para uma batalha pokemon! Vamos Lutar!\n" Resetar, Resetar);
    linhaDeCarregamento();
    printf("\nRival %sBarry%s manda %s%s%s para batalhar!" Resetar, Negrito Cinza, Resetar, cor_o, oponente_pokemon.nome, Resetar);
    printf("\nVoce manda %s%s%s!" Resetar, cor_j, jogador_pokemon.nome, Resetar);
    
    
  // Codigo da batalha
    while(jogador_pokemon.vida > 0 || oponente_pokemon.vida > 0){
        printf("\nSua vida: %s%d" Resetar, cor_vida_jogador, jogador_pokemon.vida);
        printf(" || Vida do Oponente: %s%d" Resetar, cor_vida_oponente, oponente_pokemon.vida);
            
        switch (escolher_ataque(jogador_pokemon))
        {
        case 1:
            oponente_pokemon.vida -= jogador_pokemon.ataque;
            printf("%s%s%s realiza um ataque normal e causa %s%s%s de dano ao seu oponente!" 
            Resetar, cor_j, jogador_pokemon.nome, Resetar, Negrito Cinza, jogador_pokemon.ataque, Resetar);
            break;
        case 2:
            if(jogador_pokemon.qtd_especial > 0){
                oponente_pokemon.vida -= jogador_pokemon.ataque_especial;
                jogador_pokemon.qtd_especial -= 1;
                printf("%s%s%s realiza um ataque especial e causa %s%s%s de dano ao seu oponente!" 
                Resetar, cor_j, jogador_pokemon.nome, Resetar, cor_j, jogador_pokemon.ataque, Resetar);
                break;
            }else{
                printf("%s%s%s nao pode mais utilizar ataques especiais, tente outra coisa." Resetar, cor_j, jogador_pokemon.nome, Resetar);
            }
        case 3:
            if(jogador_pokemon.qtd_especial > 0){
                jogador_pokemon.vida += jogador_pokemon.cura;
                jogador_pokemon.qtd_cura -= 1;
                printf("%s%s%s realiza um ataque normal e da %s%s%s de dano ao seu oponente!" 
                Resetar, cor_j, jogador_pokemon.nome, Resetar, Negrito Cinza, jogador_pokemon.ataque, Resetar);
                break;
            }else{
                printf("%s%s%s nao pode mais utilizar curas, tente outra coisa." Resetar, cor_j, jogador_pokemon.nome, Resetar);
            }
        default:
            break;
        }

    }
      
  // Fim da batalha
    for(int i = 0; i < sizeof(pokemons) / sizeof(pokemons[0]); i++){ // Recuperar a vida dos pokemons depois da batalha
        if(strcmp(jogador_pokemon.nome, pokemons[i].nome) == 0){
            jogador_pokemon = pokemons[i];
        }
        if(strcmp(oponente_pokemon.nome, pokemons[i].nome) == 0){
            oponente_pokemon = pokemons[i];
        }
    }
}

int escolher_ataque(Pokemon jogador_pokemon){
    int escolha;
    printf(Negrito "\n1- Ataque Normal \n2- Ataque Especial (%d usos restantes)\n3- Curar (%d usos restantes)" Resetar, jogador_pokemon.qtd_especial, jogador_pokemon.qtd_cura);
    scanf("\nSua escolha: %d", &escolha);
    getchar();
  
    return escolha;
}

int main() {
    srand(time(NULL));

    Jogador jogador;
    Pokemon jogador_pokemon;
    
    boasVindas(&jogador);     

    if(verificarJogadorExistente(&jogador)){
        jogador_pokemon = link_jogador_pokemon(&jogador);
        printf(Roxo "\nBem-vindo de volta, %s%s!%s Seu Pokemon %s%s%s estava esperando por voce!" Resetar, Resetar, jogador.nome, Roxo, cor_pokemon(jogador_pokemon),jogador.jogador_pokemon, Resetar Roxo);
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

    switch (
        batalha_total(jogador_pokemon, oponente_pokemon)) // Batalha e seus resultados
    {
    case 0:
    // Provisorio
        printf("\nFIM POR ENQUANTO!"); 
    // Correto
        // printf("\nVoce %sperdeu%s a batalha contra %sBarry%s!" Resetar, Vermelho, Resetar, Negrito Cinza, Resetar); 
        break;
    case 1:
        printf("\nVoce %sganhou%s a batalha contra %sBarry%s!" Resetar, Verde, Resetar, Negrito Cinza, Resetar);
        break;
    case 2:
        printf("\nVoce %sdesistiu%s da batalha contra %sBarry%s!" Resetar, Cinza,Resetar, Negrito Cinza, Resetar);
        break;
    default:
        break;
    }

    return 0;
}