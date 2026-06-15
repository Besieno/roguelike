#include "Enemy.h"

namespace Rogue
{
    Enemy makeEnemy(EnemyType type, Vec2i position)
    {
        Enemy enemy;
        enemy.type = type;
        enemy.position = position;

        if (type == EnemyType::Wanderer)
        {
            enemy.maxHp = 9;
            enemy.attack = 3;
            enemy.defense = 0;
            enemy.xpReward = 5;
            enemy.scoreReward = 30;
        }
        else if (type == EnemyType::Hunter)
        {
            enemy.maxHp = 12;
            enemy.attack = 4;
            enemy.defense = 1;
            enemy.xpReward = 7;
            enemy.scoreReward = 45;
        }
        else if (type == EnemyType::Brute)
        {
            enemy.maxHp = 22;
            enemy.attack = 6;
            enemy.defense = 2;
            enemy.xpReward = 12;
            enemy.scoreReward = 70;
        }
        else if (type == EnemyType::Boss)
        {
            enemy.maxHp = 72;
            enemy.attack = 8;
            enemy.defense = 3;
            enemy.xpReward = 30;
            enemy.scoreReward = 400;
        }

        enemy.hp = enemy.maxHp;
        return enemy;
    }

    std::string enemyName(EnemyType type)
    {
        switch (type)
        {
            case EnemyType::Wanderer: return "Errante";
            case EnemyType::Hunter: return "Perseguidor";
            case EnemyType::Brute: return "Brutamontes";
            case EnemyType::Boss: return "Guardiao Final";
        }
        return "Inimigo";
    }

    Color enemyColor(EnemyType type)
    {
        switch (type)
        {
            case EnemyType::Wanderer: return Color {228, 96, 93, 255};
            case EnemyType::Hunter: return Color {255, 133, 51, 255};
            case EnemyType::Brute: return Color {160, 76, 58, 255};
            case EnemyType::Boss: return Color {115, 31, 61, 255};
        }
        return RED;
    }

    bool isBoss(const Enemy& enemy)
    {
        return enemy.type == EnemyType::Boss;
    }
}
