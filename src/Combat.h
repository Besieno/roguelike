#pragma once

#include "Enemy.h"
#include "Player.h"

#include <string>

namespace Rogue
{
    bool playerAttacksEnemy(Player& player, Enemy& enemy, std::string& message);
    bool enemyAttacksPlayer(const Enemy& enemy, Player& player, std::string& message);
}
