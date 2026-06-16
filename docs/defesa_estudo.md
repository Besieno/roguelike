# Defesa de estudo

Este documento explica o prototipo como material de estudo para defesa. A ideia e entender as partes, nao decorar.

## Structs principais

- `Vec2i` em `src/Utils.h`: guarda coordenadas inteiras `x` e `y` na grade.
- `Attributes` em `src/Player.h`: guarda forca, vitalidade, defesa e agilidade.
- `Player` em `src/Player.h`: guarda posicao, HP, XP, inventario, atributos e contadores de pontuacao.
- `Enemy` em `src/Enemy.h`: guarda tipo, posicao, vida, ataque, defesa, recompensa e estado vivo.
- `Item` em `src/Item.h`: guarda tipo, posicao e se ja foi coletado.
- `Tile` em `src/Map.h`: guarda tipo do bloco, fog of war e se a armadilha esta ativa.
- `Map` em `src/Map.h`: guarda largura, altura, nivel, titulo e vetor de tiles.
- `NPC` em `src/NPC.h`: guarda tipo, posicao, nome, dialogo e se ja falou.

## Para que serve cada arquivo

- `main.cpp`: ponto de entrada. Cria `Rogue::Game` e chama `run()`.
- `Game.h/cpp`: loop principal, estados do jogo, input, troca de nivel e regras gerais.
- `Map.h/cpp`: mapa, tiles, fog of war, layouts dos niveis e alteracoes do cenario.
- `Player.h/cpp`: dados do jogador, atributos, XP, level up, pocao e pontuacao.
- `Enemy.h/cpp`: tipos de inimigo, valores iniciais, nomes e cores.
- `Item.h/cpp`: tipos de item, nomes, descricoes e cores.
- `Combat.h/cpp`: calculo de ataque, defesa, acerto, esquiva e morte de inimigo.
- `NPC.h/cpp`: procura NPC adjacente e aplica interacoes.
- `UI.h/cpp`: desenho do mapa, HUD, menus, telas de ajuda e level up.
- `Utils.h/cpp`: funcoes pequenas reaproveitadas, como distancia e aleatoriedade.

## Loop principal

O loop fica em `Game::run`:

1. Abre a janela Raylib.
2. Enquanto a janela esta aberta, chama `update()`.
3. Comeca desenho com `BeginDrawing()`.
4. Chama `draw()`.
5. Finaliza com `EndDrawing()`.

O estado atual (`GameState`) decide se o jogo atualiza menu, gameplay, level up, vitoria ou derrota.

## Audio

`Game::setupAudio` inicializa o dispositivo de audio da Raylib, carrega `assets/sounds/dungeon_ambience.wav`, define volume baixo e deixa a musica em loop.

`Game::updateAudio` chama `UpdateMusicStream` a cada frame. Isso e necessario em Raylib para musicas streamadas continuarem tocando.

`Game::shutdownAudio` descarrega a musica e fecha o dispositivo de audio ao sair.

## Dificuldade

A dificuldade fica em `Difficulty`, definido em `Utils.h`.

O menu permite alternar entre:

- `Facil`: mais HP, uma pocao inicial, inimigos mais fracos e armadilhas menos punitivas.
- `Medio`: valores base.
- `Dificil`: menos HP, inimigos mais fortes, inimigos extras, armadilhas mais fortes e menos turnos rapidos.

As principais funcoes sao:

- `cycleDifficulty`: troca a dificuldade no menu.
- `applyDifficultyToPlayer`: aplica bonus/penalidade de HP.
- `applyDifficultyToEnemies`: ajusta vida, ataque, defesa e adiciona inimigos extras no dificil.
- `trapDamage`: muda dano de armadilha conforme dificuldade.
- `enemyDetectionBonus`: muda distancia de perseguicao.
- `quickTurnBase`: muda a frequencia dos turnos rapidos por agilidade.

## Renderizacao

`UI::drawGame` desenha:

1. Tiles do mapa.
2. Itens visiveis.
3. NPCs visiveis.
4. Inimigos visiveis.
5. Jogador.
6. HUD lateral.

Como a Raylib usa double buffering, a tela nao deve piscar. A cena inteira e redesenhada a cada frame.

## Colisao

A colisao principal esta em `Game::movePlayer` e usa `isSolidTile`.

Tiles solidos:

- `Wall`
- `DoorClosed`
- `Obstacle`
- `Water`

Se o jogador tenta entrar em porta fechada, `openDoorOrBlockMessage` verifica se existe chave. Se existir, muda o tile para `DoorOpen`.

## Movimento

O input de movimento fica em `pressedMoveKey`, dentro de `Game.cpp`.

`Game::movePlayer` recebe um `Vec2i delta`, soma com a posicao atual e decide:

- Se ha inimigo no destino, ataca.
- Se ha NPC, bloqueia e manda usar `E`.
- Se ha parede/obstaculo, bloqueia.
- Se ha porta com chave, abre.
- Se e livre, move o jogador.

## Combate

O combate fica em `Combat.cpp`.

`playerAttacksEnemy(Player& player, Enemy& enemy, std::string& message)` usa referencias porque precisa alterar jogador e inimigo reais.

O dano do jogador considera:

- Forca
- Espada
- Defesa do inimigo
- Pequena variacao aleatoria

O inimigo usa `enemyAttacksPlayer`, e o dano recebido considera:

- Ataque do inimigo
- Defesa do jogador
- Escudo
- Chance de esquiva pela agilidade

## IA simples dos inimigos

A funcao `Game::chooseEnemyStep` decide o movimento:

- `Wanderer`: escolhe direcao aleatoria.
- `Hunter`: persegue quando esta perto.
- `Brute`: e resistente e tende a se aproximar.
- `Boss`: persegue de longe e altera a arena quando fica com metade da vida.

`Game::moveEnemy` tambem impede inimigo de atravessar parede, porta, obstaculo, NPC ou outro inimigo.

## Fog of war

O fog of war fica em `updateFogOfWar`.

Cada `Tile` tem:

- `explored`: ja foi visto alguma vez.
- `visible`: esta dentro da visao atual.

Na UI:

- Nao explorado: preto.
- Explorado, mas fora da visao: cor escurecida.
- Visivel: cor normal.

## XP e level up

`addExperience(Player& player, int amount)` soma XP.

Quando `xp >= xpToNext`:

- Aumenta `level`.
- Ganha 2 pontos de atributo.
- Aumenta o XP necessario para o proximo nivel.
- Restaura a vida.

`Game::updateLevelUp` le teclas:

- `1`: forca
- `2`: vitalidade
- `3`: defesa
- `4`: agilidade

## Pontuacao

A pontuacao final fica em `calculateFinalScore`:

- Soma inimigos derrotados.
- Soma boss derrotado.
- Soma itens coletados.
- Soma andares alcancados.
- Soma vida restante.
- Desconta movimentos.
- Desconta pocoes usadas.
- Desconta armadilhas ativadas.

O HUD mostra essa pontuacao em tempo real.

## NPCs e alteracoes no mapa

`interactWithNpc` altera o jogo:

- O guia abre uma passagem com `openSecretPassage(map)` e entrega chave.
- A curandeira restaura vida e deixa uma pocao no mapa.

Outras alteracoes:

- Jogador abre portas com chave.
- Armadilhas desativam depois de serem acionadas.
- Inimigos tambem podem acionar armadilhas.
- Boss chama `bossChangesArena(map)` ao ficar enfurecido.

## Referencias

Exemplos:

- `Player& player`: usado quando a funcao altera o jogador real.
- `Map& map`: usado para alterar tiles do mapa real.
- `Enemy& enemy`: usado para reduzir HP do inimigo real.
- `std::string& message`: usado para devolver mensagem sem retorno extra.

Referencia evita copia desnecessaria e deixa claro que a funcao modifica o objeto original.

## Ponteiros

Exemplos:

- `Tile* tileAt(Map& map, Vec2i position)`
- `Enemy* Game::enemyAt(Vec2i position)`
- `Enemy* Game::adjacentEnemy()`
- `NPC* findAdjacentNpc(...)`

O ponteiro pode ser `nullptr`. Isso e util para dizer "nao encontrei nada" sem criar objeto falso.

## Mudancas simples que o professor poderia pedir

- Aumentar dano da espada: altere `playerAttackPower` em `Player.cpp`.
- Criar novo inimigo: adicione valor em `EnemyType`, configure `makeEnemy` e cor/nome.
- Criar novo item: adicione valor em `ItemType`, nome/cor e regra em `collectItemsAtPlayer`.
- Mudar raio de visao: altere `VisionRadius` em `Utils.h`.
- Mudar pontuacao: altere `calculateFinalScore` em `Player.cpp`.
- Adicionar sala: edite os arrays de texto em `Map.cpp`.
- Fazer armadilha dar mais dano: altere `applyCurrentTileEffects` em `Game.cpp`.
- Fazer NPC dar item diferente: altere `interactWithNpc` em `NPC.cpp`.
