# Roguelike C++ - prototipo grafico de referencia

Este repositorio contem um prototipo completo de estudo para o trabalho T3 - Roguelike - 2026 da disciplina Algoritmos e Programacao II.

Importante: esta branch `prototype/graphical-reference` e uma versao de referencia pessoal para estudo, comparacao e visualizacao de arquitetura. Ela nao deve ser entregue como trabalho final sem entendimento, adaptacao e reimplementacao propria do grupo.

## Biblioteca grafica

O pedido original dava preferencia a SFML. Nesta maquina, SFML nao estava instalado, mas Raylib estava disponivel no MSYS2 UCRT64 e foi validado com `g++`. Por isso o prototipo usa **Raylib**, uma biblioteca grafica simples para C/C++ que compila bem no Windows e mantem o projeto didatico.

Nao foram usados Unity, Unreal, Godot, IA generativa, APIs externas, Python no jogo ou engine grande.

## Como compilar no Windows

Caminho testado nesta maquina:

1. Instale o MSYS2: https://www.msys2.org/
2. Abra o terminal **UCRT64** do MSYS2.
3. Instale compilador e Raylib, se ainda nao tiver:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib
```

4. No PowerShell, a partir da raiz do projeto, rode:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\build_windows.ps1
```

O executavel sera gerado em:

```text
build/roguelike.exe
```

O script tambem copia `libraylib.dll` para `build/` quando ela existe no MSYS2.

## Alternativa com CMake

O projeto inclui `CMakeLists.txt`, mas o CMake nao estava instalado nesta maquina durante a validacao. Se voce instalar CMake, pode tentar:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

## Como executar

Depois de compilar:

```powershell
.\build\roguelike.exe
```

## Controles

- `WASD` ou setas: mover
- `Espaco`: atacar inimigo adjacente
- `E`: conversar/interagir com NPC adjacente
- `H`: usar pocao de vida
- `ESC`: pausar ou voltar
- `Enter`: selecionar opcao do menu
- Esquerda/direita no menu: trocar dificuldade
- `1`, `2`, `3`, `4`: distribuir atributos ao subir de nivel

## Mecanicas implementadas

- Menu funcional com iniciar, como jogar, itens, pontuacao e sair
- Jogo 2D top-down em grade
- Movimento em quatro direcoes
- Colisao com paredes, portas fechadas, agua e obstaculos
- Portas abertas com chaves
- Itens: pocao, chave, espada, escudo, power-up e reliquia
- Inimigos diferentes: errante, perseguidor, brutamontes e boss
- IA simples: movimento aleatorio e perseguicao por distancia
- Sistema de combate com dano, defesa, acerto e esquiva
- Armadilhas que causam dano e se desativam
- Armadilhas tambem podem ser ativadas por inimigos
- Fog of war: preto para nunca explorado, escuro para ja explorado fora da visao
- HUD com HP, nivel, XP, pontuacao, chaves, pocoes e atributos
- XP, subida de nivel e distribuicao de atributos
- Atributos impactam dano, vida maxima, defesa, acerto, esquiva e frequencia de turnos rapidos
- NPCs com dialogo e alteracao real do mapa
- Boss final que altera a arena ao ficar com pouca vida
- Condicao de derrota por HP zero
- Condicao de vitoria ao derrotar o boss e alcancar a saida final
- Musica ambiente de suspense em loop
- Dificuldades Facil, Medio e Dificil com impacto real em HP, pocoes, inimigos, armadilhas e ritmo dos turnos

## Estrutura de pastas

```text
roguelike/
|-- CMakeLists.txt
|-- README.md
|-- build_windows.ps1
|-- assets/
|   |-- sprites/
|   |-- fonts/
|   `-- sounds/
|       `-- dungeon_ambience.wav
|-- docs/
|   |-- arquitetura.md
|   |-- checklist_pdf.md
|   `-- defesa_estudo.md
|-- src/
|   |-- Combat.h / Combat.cpp
|   |-- Enemy.h / Enemy.cpp
|   |-- Game.h / Game.cpp
|   |-- Item.h / Item.cpp
|   |-- Map.h / Map.cpp
|   |-- NPC.h / NPC.cpp
|   |-- Player.h / Player.cpp
|   |-- UI.h / UI.cpp
|   `-- Utils.h / Utils.cpp
`-- main.cpp
```

## Observacoes para estudo

Leia primeiro:

- `docs/checklist_pdf.md`: criterio por criterio do PDF
- `docs/defesa_estudo.md`: explicacao didatica para estudar o codigo
- `docs/arquitetura.md`: relacao entre os modulos

TODOs futuros possiveis, sem implementar agora:

- Geracao procedural avancada de mapas
- Boss adaptativo
- Inimigos com comportamento treinado
- NPCs com dialogos externos
- Balanceamento automatico de dificuldade
