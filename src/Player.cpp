#include "Player.h"

#include <algorithm>

namespace Rogue
{
    Player createPlayer()
    {
        Player player;
        recalculatePlayerStats(player);
        player.hp = player.maxHp;
        return player;
    }

    void recalculatePlayerStats(Player& player)
    {
        // Atributos alteram mecanicas reais: vitalidade aumenta vida maxima.
        player.maxHp = std::max(20, 24 + player.attributes.vitality * 5 + player.difficultyHpBonus);
        if (player.hp > player.maxHp)
        {
            player.hp = player.maxHp;
        }
    }

    int playerAttackPower(const Player& player)
    {
        int weaponBonus = player.hasSword ? 4 : 0;
        return 4 + player.attributes.strength * 2 + weaponBonus;
    }

    int playerDefensePower(const Player& player)
    {
        int shieldBonus = player.hasShield ? 3 : 0;
        return player.attributes.defense * 2 + shieldBonus;
    }

    int playerAccuracyPercent(const Player& player)
    {
        return clampInt(70 + player.attributes.agility * 4, 70, 95);
    }

    int playerDodgePercent(const Player& player)
    {
        return clampInt(6 + player.attributes.agility * 3, 6, 40);
    }

    bool addExperience(Player& player, int amount)
    {
        player.xp += amount;
        bool leveled = false;
        while (player.xp >= player.xpToNext)
        {
            player.xp -= player.xpToNext;
            player.level += 1;
            player.pendingAttributePoints += 2;
            player.xpToNext += 8 + player.level * 3;
            player.score += 100;
            recalculatePlayerStats(player);
            player.hp = player.maxHp;
            leveled = true;
        }
        return leveled;
    }

    bool usePotion(Player& player, std::string& message)
    {
        if (player.potions <= 0)
        {
            message = "Voce nao tem pocoes.";
            return false;
        }
        if (player.hp >= player.maxHp)
        {
            message = "Sua vida ja esta cheia.";
            return false;
        }

        player.potions -= 1;
        player.potionsUsed += 1;
        player.hp = std::min(player.maxHp, player.hp + 14 + player.attributes.vitality);
        player.score -= 5;
        message = "Pocao usada. Vida recuperada.";
        return true;
    }

    void applyAttributePoint(Player& player, int option, std::string& message)
    {
        if (player.pendingAttributePoints <= 0)
        {
            return;
        }

        if (option == 1)
        {
            player.attributes.strength += 1;
            message = "Forca aumentada: dano maior.";
        }
        else if (option == 2)
        {
            player.attributes.vitality += 1;
            int oldMax = player.maxHp;
            recalculatePlayerStats(player);
            player.hp += player.maxHp - oldMax;
            message = "Vitalidade aumentada: vida maxima maior.";
        }
        else if (option == 3)
        {
            player.attributes.defense += 1;
            message = "Defesa aumentada: dano recebido menor.";
        }
        else if (option == 4)
        {
            player.attributes.agility += 1;
            message = "Agilidade aumentada: acerto, esquiva e turnos rapidos melhores.";
        }
        else
        {
            return;
        }

        player.pendingAttributePoints -= 1;
    }

    int calculateFinalScore(const Player& player)
    {
        int score = player.score;
        score += player.enemiesDefeated * 45;
        score += player.bossesDefeated * 400;
        score += player.itemsCollected * 20;
        score += player.deepestLevel * 120;
        score += player.hp * 4;
        score -= player.moves / 2;
        score -= player.potionsUsed * 10;
        score -= player.trapsTriggered * 15;
        return std::max(0, score);
    }
}
