// Função para iniciar a batalha entre o jogador e o oponente
int batalha_total(Pokemon jogador_pokemon, Pokemon oponente_pokemon){
    const char *cor_j = cor_pokemon(jogador_pokemon);
    const char *cor_o = cor_pokemon(oponente_pokemon);
    int jogador_max_vida = jogador_pokemon.vida;
    int oponente_max_vida = oponente_pokemon.vida;

    const char* cor_vida_jogador;
    const char* cor_vida_oponente;
    
    printf(Negrito Cinza"\n\nBarry%s te desafia para uma batalha pokemon! Vamos Lutar!\n" Resetar, Resetar);
    linhaDeCarregamento();
    printf("\nRival %sBarry%s manda %s%s%s para batalhar!" Resetar, Negrito Cinza, Resetar, cor_o, oponente_pokemon.nome, Resetar);
    printf("\nVoce manda %s%s%s!\n" Resetar, cor_j, jogador_pokemon.nome, Resetar);

  // Codigo da batalha
    int escolha;
    char desistir;
    while(jogador_pokemon.vida > 0 || oponente_pokemon.vida > 0){
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
        
        printf("\nSua vida: %s%d" Resetar, cor_vida_jogador, jogador_pokemon.vida);
        printf(" || Vida do Oponente: %s%d" Resetar, cor_vida_oponente, oponente_pokemon.vida);
        
        printf(Negrito "\n1- Ataque Normal \n2- Ataque Especial (%d usos restantes) \n3- Curar (%d usos restantes) \n4- Desistir \nSua escolha: " Resetar, jogador_pokemon.qtd_especial, jogador_pokemon.qtd_cura);
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            oponente_pokemon.vida -= jogador_pokemon.ataque;
            printf("Voce realiza um ataque e causa um pouco de dano ao seu oponente!\n");
            break;
        case 2:
            if(jogador_pokemon.qtd_especial > 0){
                oponente_pokemon.vida -= jogador_pokemon.ataque_especial;
                jogador_pokemon.qtd_especial -= 1;
                printf("Voce realiza um ataque especial e causa bastante dano ao seu oponente!\n");
                break;
            }else{
                printf("Voce tenta utilizar um ataque especial, mas nao consegue mais.\n");
                continue;
            }
        case 3:
            if(jogador_pokemon.qtd_cura <= 0){
                printf("Voce tenta se curar, mas nao consegue mais.\n");
                continue;
            }else if(jogador_pokemon.vida = jogador_max_vida){
                printf("Voce tenta se curar, mas sua vida ja esta cheia.\n");
                continue;
            }else if(jogador_pokemon.vida + jogador_pokemon.cura >= jogador_max_vida){
                jogador_pokemon.vida = jogador_max_vida;
                jogador_pokemon.qtd_cura -= 1;
                printf("Voce se cura, recuperando sua vida totalmente!\n");
                break;
            }else{
                jogador_pokemon.vida += jogador_pokemon.cura;
                jogador_pokemon.qtd_cura -= 1;
                printf("Voce se cura, recuperando um pouco de vida!\n");
                break;
            }
        case 4:
            printf("\nDeseja desistir(s/n)? ");
            scanf(" %c", &desistir);
            
            if(desistir == 's'){
                printf("\nVoce %sdesistiu%s da batalha contra %sBarry%s!" Resetar, Cinza, Resetar, Negrito Cinza, Resetar);
                return 0;
            }else if(desistir == 'n'){
                printf("Voce pensa em desistir mas acaba continuando a batalha.\n");
                continue;
            }
        default:
            printf("Escolha invalida! Tente novamente.\n");
            continue;
        }  
        
        if(jogador_pokemon.vida <= 0){
            printf("\nVoce %sperdeu%s a batalha contra %sBarry%s!" Resetar, Vermelho, Resetar, Negrito Cinza, Resetar);
            return 0;
        }
        if(oponente_pokemon.vida <= 0){
            printf("\nVoce %sganhou%s a batalha contra %sBarry%s!" Resetar, Verde, Resetar, Negrito Cinza, Resetar);
            return 0;
        }
    }
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

    batalha_total(jogador_pokemon, oponente_pokemon); // Batalha e seus resultados

    printf(Roxo "\nParabens %s%s!%s Esse foi somente o inicio da incrivel jornada que te aguarda! Esperamos que tenha gostado." Resetar, Resetar, jogador.nome, Roxo);

    return 0;
}