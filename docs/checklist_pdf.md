# Checklist do PDF

Status usado: implementado, parcial ou nao implementado.

| Criterio do PDF | Status | Arquivo/funcao | Observacoes |
|---|---|---|---|
| Jogo otimizado, sem atrasos excessivos, jogador move sem bugs | Implementado | `Game::run`, `Game::movePlayer` | Raylib a 60 FPS, mapa pequeno em grade e logica por turnos. |
| Jogo nao pisca nem desloca blocos incoerentes | Implementado | `UI::drawGame` | Renderizacao redesenha a cena completa por frame com double buffering da Raylib. |
| Design caprichado e visual consistente | Implementado | `UI.cpp`, `Item.cpp`, `Enemy.cpp`, `Map.cpp` | Paleta fixa, HUD lateral, formas geometricas e cores por entidade. |
| Menu funcional com como jogar, itens e pontuacao | Implementado | `Game::updateMenu`, `UI::drawMenu` | Inclui iniciar, como jogar, itens, pontuacao e sair. |
| Jogador se move para todas as direcoes | Implementado | `pressedMoveKey`, `Game::movePlayer` | WASD e setas. |
| Jogador bloqueado por paredes | Implementado | `isSolidTile`, `Game::movePlayer` | Bloqueia paredes, portas fechadas, agua e obstaculos. |
| Diferentes tipos de inimigos com movimento aleatorio/perseguicao e colisao | Implementado | `Enemy.cpp`, `Game::chooseEnemyStep`, `Game::moveEnemy` | Errante aleatorio, perseguidor, brutamontes resistente e boss. |
| Vitoria ao chegar ao ultimo nivel e derrotar chefe final | Implementado | `Game::tryUseExit` | Saida final fica selada enquanto o boss esta vivo. |
| Itens pelo mapa, chaves, portas e pocoes | Implementado | `Map::loadLevel`, `Game::collectItemsAtPlayer`, `Game::openDoorOrBlockMessage` | Tambem ha espada, escudo, power-up e reliquia. |
| Derrota quando vida chega a zero | Implementado | `Game::afterPlayerAction`, `Game::updateEnemies` | Estado muda para `GameOver`. |
| Mapa comecando escuro e abrindo com exploracao | Implementado | `updateFogOfWar`, `UI::drawGame` | Nunca explorado fica preto; explorado fora da visao fica escuro. |
| Sistema de batalha | Implementado | `Combat.cpp`, `Game::movePlayer`, `Game::updatePlaying` | Ataque adjacente por Espaco ou andando contra inimigo. |
| Pontuacao e vida exibidas em tela | Implementado | `UI::drawGame`, `calculateFinalScore` | HUD mostra HP e pontuacao em tempo real. |
| Armadilhas no mapa | Implementado | `TileType::Trap`, `Game::applyCurrentTileEffects`, `Game::moveEnemy` | Armadilhas causam dano e sao desativadas. |
| Pontos de experiencia e personagem sobe de nivel | Implementado | `addExperience` | XP vem de inimigos e power-ups. |
| Atributos distribuidos ao subir de nivel | Implementado | `Game::updateLevelUp`, `applyAttributePoint` | Tela propria usa teclas 1 a 4. |
| Atributos impactam armadura, acerto, dano, esquiva, vida e velocidade/frequencia | Implementado | `Player.cpp`, `Game::afterPlayerAction` | Forca, vitalidade, defesa e agilidade alteram mecanicas reais. |
| Historia e NPCs | Implementado | `README.md`, `NPC.cpp`, `UI::drawMenu` | Historia simples das Ruinas de Aster e NPCs com dialogo. |
| Mapa sofre alteracoes por NPCs, mobs e jogador | Implementado | `openSecretPassage`, `bossChangesArena`, `Game::moveEnemy`, `Game::openDoorOrBlockMessage` | NPC abre passagem, jogador abre porta, armadilha desativa, boss altera arena. |
| Boss final | Implementado | `EnemyType::Boss`, `Map::loadLevel`, `Game::tryUseExit` | Boss com mais vida, dano e mudanca de arena. |
| Feedback sonoro/ambientacao extra | Implementado | `Game::setupAudio`, `assets/sounds/dungeon_ambience.wav` | Musica ambiente de suspense em loop usando Raylib audio. |
| Dificuldade configuravel extra | Implementado | `Game::cycleDifficulty`, `Game::applyDifficultyToPlayer`, `Game::applyDifficultyToEnemies` | Facil, Medio e Dificil afetam HP, pocoes, inimigos, armadilhas e ritmo. |
| Uso de struct | Implementado | `Vec2i`, `Player`, `Attributes`, `Enemy`, `Item`, `Tile`, `Map`, `NPC` | Structs concentram os dados principais do jogo. |
| Sub-rotinas com parametros e referencias corretos | Implementado | `Player&`, `Map&`, `Enemy&`, `NPC&` em varios arquivos | Funcoes recebem referencias quando precisam alterar estado. |
| Ponteiros e referencias | Implementado | `tileAt`, `enemyAt`, `adjacentEnemy`, `findAdjacentNpc` | Ponteiros indicam "encontrado ou nao encontrado" sem copiar objetos. |
| Boa segmentacao de sub-rotinas e tecnicas | Implementado | `src/*.cpp` | Codigo separado por responsabilidade: jogo, mapa, combate, UI, jogador, inimigos, itens e NPC. |

## Pontos parciais intencionais

- Os mapas sao fixos, porque o PDF permite mapa fixo. Geracao procedural fica como melhoria futura.
- Os assets sao placeholders geometricos, sem sprites externos. Isso mantem o projeto compilavel sem arquivos binarios.
- Sons nao foram implementados, pois nao aparecem como criterio obrigatorio do PDF.
