#pragma once

#include "Utils.h"

#include <string>

namespace Rogue
{
    struct Attributes
    {
        int strength = 2;
        int vitality = 2;
        int defense = 1;
        int agility = 1;
    };

    struct Player
    {
        Vec2i position {1, 1};
        int level = 1;
        int xp = 0;
        int xpToNext = 12;
        int hp = 34;
        int maxHp = 34;
        int keys = 0;
        int potions = 0;
        int pendingAttributePoints = 0;
        bool hasSword = false;
        bool hasShield = false;
        Attributes attributes;

        int moves = 0;
        int score = 0;
        int itemsCollected = 0;
        int potionsUsed = 0;
        int trapsTriggered = 0;
        int enemiesDefeated = 0;
        int bossesDefeated = 0;
        int deepestLevel = 1;
    };

    Player createPlayer();
    void recalculatePlayerStats(Player& player);
    int playerAttackPower(const Player& player);
    int playerDefensePower(const Player& player);
    int playerAccuracyPercent(const Player& player);
    int playerDodgePercent(const Player& player);
    bool addExperience(Player& player, int amount);
    bool usePotion(Player& player, std::string& message);
    void applyAttributePoint(Player& player, int option, std::string& message);
    int calculateFinalScore(const Player& player);
}
