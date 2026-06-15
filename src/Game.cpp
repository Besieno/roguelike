#include "Game.h"

#include "Combat.h"
#include "UI.h"

#include <raylib.h>

#include <algorithm>
#include <ctime>

namespace Rogue
{
    namespace
    {
        Vec2i directions[4] = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };

        bool pressedMoveKey(Vec2i& delta)
        {
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
            {
                delta = {0, -1};
                return true;
            }
            if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
            {
                delta = {0, 1};
                return true;
            }
            if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
            {
                delta = {-1, 0};
                return true;
            }
            if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
            {
                delta = {1, 0};
                return true;
            }
            return false;
        }
    }

    Game::Game()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        player = createPlayer();
        initializeMap(map, MapWidth, MapHeight);
    }

    void Game::run()
    {
        SetConfigFlags(FLAG_VSYNC_HINT);
        InitWindow(ScreenWidth, ScreenHeight, "Roguelike - referencia de estudo");
        SetTargetFPS(60);

        while (!WindowShouldClose() && !shouldClose)
        {
            update();
            BeginDrawing();
            draw();
            EndDrawing();
        }

        CloseWindow();
    }

    void Game::startNewGame()
    {
        player = createPlayer();
        currentLevel = 1;
        message = "As ruinas despertam. Encontre a reliquia.";
        loadCurrentLevel();
        state = GameState::Playing;
    }

    void Game::loadCurrentLevel()
    {
        loadLevel(map, currentLevel, player, enemies, items, npcs);
        message = "Nivel " + intToString(currentLevel) + ": " + map.title;
    }

    void Game::update()
    {
        if (state == GameState::MainMenu || state == GameState::HowTo || state == GameState::ItemsHelp || state == GameState::ScoringHelp || state == GameState::Paused || state == GameState::GameOver || state == GameState::Victory)
        {
            updateMenu();
        }
        else if (state == GameState::Playing)
        {
            updatePlaying();
        }
        else if (state == GameState::LevelUp)
        {
            updateLevelUp();
        }
    }

    void Game::draw() const
    {
        if (state == GameState::Playing || state == GameState::Paused)
        {
            drawGame(map, player, enemies, items, npcs, message);
            if (state == GameState::Paused)
            {
                DrawRectangle(0, 0, ScreenWidth, ScreenHeight, Color {0, 0, 0, 130});
                DrawText("Pausado - ESC volta ao jogo", 340, 320, 30, WHITE);
            }
        }
        else if (state == GameState::MainMenu)
        {
            drawMenu(MenuScreen::Main, menuIndex, player);
        }
        else if (state == GameState::HowTo)
        {
            drawMenu(MenuScreen::HowTo, menuIndex, player);
        }
        else if (state == GameState::ItemsHelp)
        {
            drawMenu(MenuScreen::Items, menuIndex, player);
        }
        else if (state == GameState::ScoringHelp)
        {
            drawMenu(MenuScreen::Scoring, menuIndex, player);
        }
        else if (state == GameState::LevelUp)
        {
            drawLevelUp(player, message);
        }
        else if (state == GameState::GameOver)
        {
            drawMenu(MenuScreen::GameOver, menuIndex, player);
        }
        else if (state == GameState::Victory)
        {
            drawMenu(MenuScreen::Victory, menuIndex, player);
        }
    }

    void Game::updateMenu()
    {
        if (state == GameState::HowTo || state == GameState::ItemsHelp || state == GameState::ScoringHelp)
        {
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_ENTER))
            {
                state = GameState::MainMenu;
            }
            return;
        }

        if (state == GameState::GameOver || state == GameState::Victory)
        {
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
            {
                state = GameState::MainMenu;
                menuIndex = 0;
            }
            return;
        }

        if (state == GameState::Paused)
        {
            if (IsKeyPressed(KEY_ESCAPE))
            {
                state = GameState::Playing;
            }
            return;
        }

        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        {
            menuIndex = (menuIndex + 4) % 5;
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        {
            menuIndex = (menuIndex + 1) % 5;
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (menuIndex == 0)
            {
                startNewGame();
            }
            else if (menuIndex == 1)
            {
                state = GameState::HowTo;
            }
            else if (menuIndex == 2)
            {
                state = GameState::ItemsHelp;
            }
            else if (menuIndex == 3)
            {
                state = GameState::ScoringHelp;
            }
            else if (menuIndex == 4)
            {
                shouldClose = true;
            }
        }
    }

    void Game::updatePlaying()
    {
        if (IsKeyPressed(KEY_ESCAPE))
        {
            state = GameState::Paused;
            return;
        }

        if (IsKeyPressed(KEY_H))
        {
            if (usePotion(player, message))
            {
                afterPlayerAction();
            }
            return;
        }

        if (IsKeyPressed(KEY_E))
        {
            NPC* npc = findAdjacentNpc(npcs, player.position);
            if (npc != nullptr)
            {
                interactWithNpc(player, map, *npc, items, message);
                afterPlayerAction();
            }
            else
            {
                message = "Nao ha NPC adjacente.";
            }
            return;
        }

        if (IsKeyPressed(KEY_SPACE))
        {
            Enemy* enemy = adjacentEnemy();
            if (enemy != nullptr)
            {
                playerAttacksEnemy(player, *enemy, message);
                removeDeadEnemies();
                afterPlayerAction();
            }
            else
            {
                message = "Nenhum inimigo adjacente para atacar.";
            }
            return;
        }

        Vec2i delta;
        if (pressedMoveKey(delta))
        {
            movePlayer(delta);
        }
    }

    void Game::updateLevelUp()
    {
        if (IsKeyPressed(KEY_ONE))
        {
            applyAttributePoint(player, 1, message);
        }
        else if (IsKeyPressed(KEY_TWO))
        {
            applyAttributePoint(player, 2, message);
        }
        else if (IsKeyPressed(KEY_THREE))
        {
            applyAttributePoint(player, 3, message);
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
            applyAttributePoint(player, 4, message);
        }

        if (player.pendingAttributePoints <= 0)
        {
            state = GameState::Playing;
            message = "Atributos aplicados. Continue explorando.";
        }
    }

    void Game::movePlayer(Vec2i delta)
    {
        Vec2i target = player.position + delta;

        Enemy* enemy = enemyAt(target);
        if (enemy != nullptr)
        {
            playerAttacksEnemy(player, *enemy, message);
            removeDeadEnemies();
            afterPlayerAction();
            return;
        }

        if (isOccupiedByNpc(target))
        {
            message = "NPC bloqueia o caminho. Aperte E para conversar.";
            return;
        }

        const Tile* targetTile = tileAt(map, target);
        if (targetTile == nullptr)
        {
            return;
        }

        if (targetTile->type == TileType::DoorClosed)
        {
            openDoorOrBlockMessage(target);
            if (tileAt(map, target)->type == TileType::DoorClosed)
            {
                return;
            }
        }
        else if (isSolidTile(targetTile->type))
        {
            message = "Parede ou obstaculo bloqueando.";
            return;
        }

        player.position = target;
        player.moves += 1;
        collectItemsAtPlayer();
        applyCurrentTileEffects();
        int levelBeforeExit = currentLevel;
        tryUseExit();
        if (state == GameState::Victory || state == GameState::GameOver)
        {
            return;
        }
        updateFogOfWar(map, player.position);
        if (currentLevel != levelBeforeExit)
        {
            return;
        }
        afterPlayerAction();
    }

    void Game::afterPlayerAction()
    {
        if (player.hp <= 0)
        {
            state = GameState::GameOver;
            message = "Voce caiu nas ruinas.";
            return;
        }

        if (player.pendingAttributePoints > 0)
        {
            state = GameState::LevelUp;
            return;
        }

        // Agilidade tambem impacta frequencia: em alguns turnos rapidos os inimigos nao agem.
        int quickTurnEvery = std::max(3, 8 - player.attributes.agility);
        bool quickTurn = (player.moves > 0 && player.moves % quickTurnEvery == 0);
        if (quickTurn)
        {
            message += " Sua agilidade deu um turno rapido.";
        }
        else
        {
            updateEnemies();
        }

        if (player.hp <= 0)
        {
            state = GameState::GameOver;
            message = "Voce caiu nas ruinas.";
        }
    }

    void Game::updateEnemies()
    {
        for (Enemy& enemy : enemies)
        {
            if (!enemy.alive)
            {
                continue;
            }

            if (manhattanDistance(enemy.position, player.position) == 1)
            {
                enemyAttacksPlayer(enemy, player, message);
                continue;
            }

            if (isBoss(enemy) && enemy.hp <= enemy.maxHp / 2 && !enemy.enraged)
            {
                enemy.enraged = true;
                enemy.attack += 2;
                bossChangesArena(map);
                message = "O Guardiao altera a arena e desperta novas armadilhas.";
            }

            moveEnemy(enemy, chooseEnemyStep(enemy));
        }
        removeDeadEnemies();
        updateFogOfWar(map, player.position);
    }

    void Game::moveEnemy(Enemy& enemy, Vec2i delta)
    {
        Vec2i target = enemy.position + delta;
        if (target == player.position)
        {
            enemyAttacksPlayer(enemy, player, message);
            return;
        }
        if (!canCreatureWalkOn(map, target) || isOccupiedByEnemy(target) || isOccupiedByNpc(target))
        {
            return;
        }

        enemy.position = target;

        Tile* tile = tileAt(map, enemy.position);
        if (tile != nullptr && tile->type == TileType::Trap && tile->trapActive)
        {
            tile->trapActive = false;
            tile->type = TileType::Floor;
            enemy.hp -= 6;
            message = enemyName(enemy.type) + " ativou e desarmou uma armadilha.";
            if (enemy.hp <= 0)
            {
                enemy.alive = false;
                player.score += enemy.scoreReward / 2;
                bool leveled = addExperience(player, enemy.xpReward / 2);
                if (leveled)
                {
                    message += " Voce ganhou XP suficiente para subir de nivel.";
                }
            }
        }
    }

    Vec2i Game::chooseEnemyStep(const Enemy& enemy) const
    {
        if (enemy.type == EnemyType::Wanderer)
        {
            return directions[randomInt(0, 3)];
        }

        int detection = isBoss(enemy) ? 12 : 7;
        if (manhattanDistance(enemy.position, player.position) > detection && enemy.type != EnemyType::Brute)
        {
            return directions[randomInt(0, 3)];
        }

        Vec2i best {0, 0};
        int bestDistance = manhattanDistance(enemy.position, player.position);
        for (Vec2i dir : directions)
        {
            Vec2i candidate = enemy.position + dir;
            int distance = manhattanDistance(candidate, player.position);
            if (distance < bestDistance && canCreatureWalkOn(map, candidate) && !isOccupiedByEnemy(candidate))
            {
                best = dir;
                bestDistance = distance;
            }
        }

        if (best.x == 0 && best.y == 0)
        {
            return directions[randomInt(0, 3)];
        }
        return best;
    }

    bool Game::isOccupiedByEnemy(Vec2i position) const
    {
        for (const Enemy& enemy : enemies)
        {
            if (enemy.alive && enemy.position == position)
            {
                return true;
            }
        }
        return false;
    }

    bool Game::isOccupiedByNpc(Vec2i position) const
    {
        for (const NPC& npc : npcs)
        {
            if (npc.position == position)
            {
                return true;
            }
        }
        return false;
    }

    Enemy* Game::enemyAt(Vec2i position)
    {
        for (Enemy& enemy : enemies)
        {
            if (enemy.alive && enemy.position == position)
            {
                return &enemy;
            }
        }
        return nullptr;
    }

    Enemy* Game::adjacentEnemy()
    {
        for (Enemy& enemy : enemies)
        {
            if (enemy.alive && manhattanDistance(enemy.position, player.position) == 1)
            {
                return &enemy;
            }
        }
        return nullptr;
    }

    void Game::collectItemsAtPlayer()
    {
        for (Item& item : items)
        {
            if (item.collected || item.position != player.position)
            {
                continue;
            }

            item.collected = true;
            player.itemsCollected += 1;
            player.score += 20;

            if (item.type == ItemType::HealthPotion)
            {
                player.potions += 1;
                message = "Pocao coletada.";
            }
            else if (item.type == ItemType::Key)
            {
                player.keys += 1;
                message = "Chave coletada.";
            }
            else if (item.type == ItemType::Sword)
            {
                player.hasSword = true;
                message = "Espada equipada: dano aumentado.";
            }
            else if (item.type == ItemType::Shield)
            {
                player.hasShield = true;
                message = "Escudo equipado: defesa aumentada.";
            }
            else if (item.type == ItemType::PowerUp)
            {
                bool leveled = addExperience(player, 10);
                message = "Cristal absorvido: XP +10.";
                if (leveled)
                {
                    message += " Voce subiu de nivel.";
                }
            }
            else if (item.type == ItemType::Relic)
            {
                message = "A reliquia vibra. Derrote o Guardiao para sair.";
            }
        }
    }

    void Game::applyCurrentTileEffects()
    {
        Tile* tile = tileAt(map, player.position);
        if (tile == nullptr)
        {
            return;
        }

        if (tile->type == TileType::Trap && tile->trapActive)
        {
            tile->trapActive = false;
            tile->type = TileType::Floor;
            player.hp -= std::max(2, 9 - playerDefensePower(player));
            player.trapsTriggered += 1;
            message = "Armadilha ativada e desarmada.";
        }
    }

    void Game::tryUseExit()
    {
        const Tile* tile = tileAt(map, player.position);
        if (tile == nullptr || tile->type != TileType::Exit)
        {
            return;
        }

        bool bossAlive = false;
        for (const Enemy& enemy : enemies)
        {
            if (enemy.alive && isBoss(enemy))
            {
                bossAlive = true;
            }
        }

        if (currentLevel >= MaxDungeonLevel)
        {
            if (bossAlive)
            {
                message = "A saida esta selada enquanto o Guardiao vive.";
            }
            else
            {
                player.score += 600;
                state = GameState::Victory;
            }
            return;
        }

        currentLevel += 1;
        player.score += 120;
        loadCurrentLevel();
    }

    void Game::removeDeadEnemies()
    {
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy)
        {
            return !enemy.alive;
        }), enemies.end());
    }

    void Game::openDoorOrBlockMessage(Vec2i target)
    {
        if (player.keys <= 0)
        {
            message = "Porta trancada. Procure uma chave.";
            return;
        }

        player.keys -= 1;
        player.score += 25;
        setTile(map, target, TileType::DoorOpen);
        message = "Porta aberta com uma chave.";
    }
}
