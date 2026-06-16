# Arquitetura

## Visao geral

O projeto foi separado por responsabilidade para ficar didatico e facil de defender:

- `Game`: coordena estados, input, regras de turno e fluxo geral.
- `Map`: guarda os tiles, carrega niveis e controla fog of war.
- `Player`: guarda jogador, atributos, XP e pontuacao.
- `Enemy`: define tipos e propriedades de inimigos.
- `Item`: define itens coletaveis.
- `NPC`: define conversas e interacoes com o mapa.
- `Combat`: concentra regras de ataque, defesa, acerto e esquiva.
- `UI`: desenha mapa, entidades, HUD e menus.
- `Utils`: funcoes pequenas e tipos basicos.
- `assets/sounds`: guarda a musica ambiente usada pela Raylib.

## Relacao entre os modulos

`main.cpp` cria `Game`.

`Game` contem:

- `Map map`
- `Player player`
- `std::vector<Enemy> enemies`
- `std::vector<Item> items`
- `std::vector<NPC> npcs`

`Game` chama:

- `Map` para carregar nivel, checar tiles e atualizar fog.
- `Combat` para resolver ataques.
- `NPC` para conversas.
- `Player` para XP, atributos, pocaes e pontuacao.
- `UI` para desenhar.
- Raylib Audio para tocar musica de ambiente em loop.

## Por que separar assim

A separacao evita um arquivo gigante com tudo misturado.

Cada arquivo responde por uma pergunta:

- Onde esta o jogador? `Player`
- Que tile existe nessa posicao? `Map`
- Quanto dano um ataque causa? `Combat`
- Como desenhar o HUD? `UI`
- O que acontece quando falo com NPC? `NPC`

Isso ajuda o professor a pedir mudancas pequenas na defesa sem quebrar o projeto todo.

## Como mudar a dificuldade

A dificuldade fica no `enum class Difficulty`, em `src/Utils.h`.

Os efeitos principais ficam em `src/Game.cpp`:

- `applyDifficultyToPlayer`: altera bonus/penalidade de HP.
- `applyDifficultyToEnemies`: altera vida, ataque, defesa e inimigos extras.
- `trapDamage`: altera dano de armadilhas.
- `enemyDetectionBonus`: altera distancia de perseguicao.
- `quickTurnBase`: altera frequencia dos turnos rapidos.

Para adicionar uma nova dificuldade, crie um novo valor no enum e ajuste essas funcoes.

## Como trocar a musica

Substitua `assets/sounds/dungeon_ambience.wav` por outro arquivo WAV compatvel.

O carregamento fica em `Game::setupAudio`. A funcao procura o arquivo tanto quando o jogo roda pela raiz do projeto quanto quando roda pela pasta `build`.

## Como adicionar novos inimigos

1. Abra `src/Enemy.h`.
2. Adicione um valor em `enum class EnemyType`.
3. Abra `src/Enemy.cpp`.
4. Configure vida, ataque, defesa, XP e pontuacao em `makeEnemy`.
5. Adicione nome em `enemyName`.
6. Adicione cor em `enemyColor`.
7. Coloque o inimigo em algum nivel dentro de `Map::loadLevel`.

Se quiser comportamento diferente, altere `Game::chooseEnemyStep`.

## Como adicionar novos itens

1. Abra `src/Item.h`.
2. Adicione valor em `enum class ItemType`.
3. Configure nome, descricao e cor em `Item.cpp`.
4. Adicione a regra de coleta em `Game::collectItemsAtPlayer`.
5. Coloque o item no mapa dentro de `Map.cpp`.

## Como adicionar novas salas ou niveis

Os niveis usam arrays de texto em `Map.cpp`.

Simbolos principais:

- `#`: parede
- `.`: chao
- `P`: spawn do jogador
- `D`: porta fechada
- `T`: armadilha
- `O`: obstaculo
- `>` ou `R`: saida
- `K`: chave
- `H`: pocao
- `S`: espada
- `A`: escudo
- `N`: NPC

Cada linha deve ter exatamente `MapWidth` caracteres, e devem existir `MapHeight` linhas.

## Pontos futuros para IA/ML/Python

Nao ha IA generativa, machine learning ou Python no jogo atual. Pontos onde isso poderia entrar futuramente:

- `Game::chooseEnemyStep`: inimigos com comportamento treinado.
- `bossChangesArena`: boss adaptativo que muda arena conforme estilo do jogador.
- `Map::loadLevel`: geracao procedural avancada.
- `NPC.cpp`: dialogos dinamicos por LLM.
- `Player.cpp`: balanceamento automatico de dificuldade.

Esses pontos sao apenas TODOs conceituais. O foco desta versao e Algoritmos e Programacao II em C++.
