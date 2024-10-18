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

    iniciar_historico(&jogador_pokemon, &oponente_pokemon);
        
  // Codigo da batalha
    int escolha_j;
    int escolha_o;
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
        
        printf(Negrito "\n1- Ataque Normal \n2- Ataque Especial (%d usos restantes) \n3- Usar pocao de cura (%d usos restantes) \n4- Desistir \nSua escolha: " Resetar, jogador_pokemon.qtd_especial, jogador_pokemon.qtd_cura);
        scanf("%d", &escolha_j);

        // Ataque do jogador
        switch (escolha_j)
        {
        case 1:
            oponente_pokemon.vida -= jogador_pokemon.ataque;
            printf("Voce realiza um ataque e causa um pouco de dano ao seu oponente!\n");
            salvar_ataque(jogador_pokemon.nome, oponente_pokemon.nome, jogador_pokemon.ataque, oponente_pokemon.vida - jogador_pokemon.ataque);
            break;
        case 2:
            if(jogador_pokemon.qtd_especial > 0){
                oponente_pokemon.vida -= jogador_pokemon.ataque_especial;
                jogador_pokemon.qtd_especial -= 1;
                printf("Voce realiza um ataque especial e causa bastante dano ao seu oponente!\n");
                salvar_ataque(jogador_pokemon.nome, oponente_pokemon.nome, jogador_pokemon.ataque_especial, oponente_pokemon.vida - jogador_pokemon.ataque_especial);
                break;
            }else{
                printf("Voce tenta utilizar um ataque especial, mas nao consegue mais.\n");
                continue;
            }
        case 3:
            if(jogador_pokemon.qtd_cura <= 0){
                printf("Voce tenta usar uma pocao, mas nao tem mais nenhuma.\n");
                continue;
            }else if(jogador_pokemon.vida == jogador_max_vida){
                printf("Voce tenta usar uma pocao, mas sua vida ja esta cheia.\n");
                continue;
            }else if(jogador_pokemon.vida + jogador_pokemon.cura >= jogador_max_vida){
                salvar_cura(jogador_pokemon.nome, jogador_max_vida - jogador_pokemon.vida, jogador_max_vida);
                jogador_pokemon.vida = jogador_max_vida;
                jogador_pokemon.qtd_cura -= 1;
                printf("Voce usa uma pocao, recuperando sua vida totalmente!\n");
                
                break;
            }else{
                jogador_pokemon.vida += jogador_pokemon.cura;
                jogador_pokemon.qtd_cura -= 1;
                printf("Voce usa uma pocao, recuperando um pouco de vida!\n");
                salvar_cura(jogador_pokemon.nome, jogador_pokemon.cura, jogador_pokemon.vida);
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
        
        if(oponente_pokemon.vida <= 0){
            printf("\nVoce %sganhou%s a batalha contra %sBarry%s!" Resetar, Verde, Resetar, Negrito Cinza, Resetar);
            finalizar_historico(jogador_pokemon.nome);
            return 0;
        }

        // Ataque do oponente
        while(1){
            escolha_o = rand() % 3;
            if(escolha_o == 0){
                jogador_pokemon.vida -= oponente_pokemon.ataque;
                printf("Seu oponente realiza um ataque e causa um pouco de dano!\n");
                salvar_ataque(oponente_pokemon.nome, jogador_pokemon.nome, oponente_pokemon.ataque, jogador_pokemon.vida - oponente_pokemon.ataque);
                break;
            }else if(escolha_o == 1 && oponente_pokemon.qtd_especial > 0){
                jogador_pokemon.vida -= oponente_pokemon.ataque_especial;
                oponente_pokemon.qtd_especial -= 1;
                printf("Seu oponente realiza um ataque especial e causa bastante dano!\n");
                salvar_ataque(oponente_pokemon.nome, jogador_pokemon.nome, oponente_pokemon.ataque_especial, jogador_pokemon.vida - oponente_pokemon.ataque_especial);
                break;
            }else if(escolha_o == 2 && oponente_pokemon.qtd_cura > 0 && oponente_pokemon.vida <= max_vida - oponente_pokemon.cura){
                oponente_pokemon.vida += oponente_pokemon.cura;
                oponente_pokemon.qtd_cura -= 1;
                printf("Seu oponente usa uma pocao, recuperando um pouco de vida!\n");
                salvar_cura(oponente_pokemon.nome, oponente_pokemon.cura, oponente_pokemon.vida);
                break;
            }
        }
        
        if(jogador_pokemon.vida <= 0){
            printf("\nVoce %sperdeu%s a batalha contra %sBarry%s!" Resetar, Vermelho, Resetar, Negrito Cinza, Resetar);
            finalizar_historico(oponente_pokemon.nome);
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