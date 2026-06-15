#include "Combat.h"

#include "Utils.h"

#include <algorithm>

namespace Rogue
{
    bool playerAttacksEnemy(Player& player, Enemy& enemy, std::string& message)
    {
        if (!enemy.alive)
        {
            return false;
        }

        if (!percentChance(playerAccuracyPercent(player)))
        {
            message = "Voce errou o ataque contra " + enemyName(enemy.type) + ".";
            return false;
        }

        int rawDamage = playerAttackPower(player) + randomInt(0, 3);
        int damage = std::max(1, rawDamage - enemy.defense);
        enemy.hp -= damage;
        message = "Voce causou " + intToString(damage) + " de dano em " + enemyName(enemy.type) + ".";

        if (enemy.hp <= 0)
        {
            enemy.alive = false;
            player.enemiesDefeated += 1;
            player.score += enemy.scoreReward;
            if (isBoss(enemy))
            {
                player.bossesDefeated += 1;
            }
            bool leveled = addExperience(player, enemy.xpReward);
            message = enemyName(enemy.type) + " derrotado! XP +" + intToString(enemy.xpReward) + ".";
            if (leveled)
            {
                message += " Voce subiu de nivel.";
            }
        }

        return true;
    }

    bool enemyAttacksPlayer(const Enemy& enemy, Player& player, std::string& message)
    {
        if (!enemy.alive)
        {
            return false;
        }

        if (percentChance(playerDodgePercent(player)))
        {
            message = "Voce esquivou de " + enemyName(enemy.type) + ".";
            return false;
        }

        int rawDamage = enemy.attack + randomInt(0, 3);
        int damage = std::max(1, rawDamage - playerDefensePower(player));
        player.hp -= damage;
        message = enemyName(enemy.type) + " causou " + intToString(damage) + " de dano.";
        return true;
    }
}
