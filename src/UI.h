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
    enum class MenuScreen
    {
        Main,
        HowTo,
        Items,
        Scoring,
        Pause,
        GameOver,
        Victory,
        LevelUp
    };

    void drawGame(const Map& map, const Player& player, const std::vector<Enemy>& enemies, const std::vector<Item>& items, const std::vector<NPC>& npcs, const std::string& message);
    void drawMenu(MenuScreen screen, int selectedIndex, const Player& player);
    void drawLevelUp(const Player& player, const std::string& message);
}
