#pragma once

#include "Enemy.h"
#include "Item.h"
#include "Map.h"
#include "NPC.h"
#include "Player.h"

#include <string>
#include <vector>

namespace Rogue
{
    enum class GameState
    {
        MainMenu,
        HowTo,
        ItemsHelp,
        ScoringHelp,
        Playing,
        Paused,
        LevelUp,
        GameOver,
        Victory
    };

    class Game
    {
    public:
        Game();
        void run();

    private:
        GameState state = GameState::MainMenu;
        Map map;
        Player player;
        std::vector<Enemy> enemies;
        std::vector<Item> items;
        std::vector<NPC> npcs;
        std::string message = "Explore as ruinas.";
        int currentLevel = 1;
        int menuIndex = 0;
        bool shouldClose = false;

        void startNewGame();
        void loadCurrentLevel();
        void update();
        void draw() const;
        void updateMenu();
        void updatePlaying();
        void updateLevelUp();
        void movePlayer(Vec2i delta);
        void afterPlayerAction();
        void updateEnemies();
        void moveEnemy(Enemy& enemy, Vec2i delta);
        Vec2i chooseEnemyStep(const Enemy& enemy) const;
        bool isOccupiedByEnemy(Vec2i position) const;
        bool isOccupiedByNpc(Vec2i position) const;
        Enemy* enemyAt(Vec2i position);
        Enemy* adjacentEnemy();
        void collectItemsAtPlayer();
        void applyCurrentTileEffects();
        void tryUseExit();
        void removeDeadEnemies();
        void openDoorOrBlockMessage(Vec2i target);
    };
}
