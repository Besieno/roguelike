#pragma once

#include "Utils.h"

#include <raylib.h>
#include <string>

namespace Rogue
{
    enum class EnemyType
    {
        Wanderer,
        Hunter,
        Brute,
        Boss
    };

    struct Enemy
    {
        EnemyType type = EnemyType::Wanderer;
        Vec2i position {0, 0};
        int hp = 8;
        int maxHp = 8;
        int attack = 3;
        int defense = 0;
        int xpReward = 5;
        int scoreReward = 30;
        bool alive = true;
        bool enraged = false;
    };

    Enemy makeEnemy(EnemyType type, Vec2i position);
    std::string enemyName(EnemyType type);
    Color enemyColor(EnemyType type);
    bool isBoss(const Enemy& enemy);
}
