#include "Utils.h"

#include <algorithm>
#include <cstdlib>
#include <string>

namespace Rogue
{
    bool operator==(Vec2i a, Vec2i b)
    {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(Vec2i a, Vec2i b)
    {
        return !(a == b);
    }

    Vec2i operator+(Vec2i a, Vec2i b)
    {
        return {a.x + b.x, a.y + b.y};
    }

    int manhattanDistance(Vec2i a, Vec2i b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

    int clampInt(int value, int minValue, int maxValue)
    {
        return std::max(minValue, std::min(value, maxValue));
    }

    int randomInt(int minValue, int maxValue)
    {
        if (maxValue <= minValue)
        {
            return minValue;
        }
        return minValue + (std::rand() % (maxValue - minValue + 1));
    }

    bool percentChance(int percent)
    {
        return randomInt(1, 100) <= clampInt(percent, 0, 100);
    }

    std::string intToString(int value)
    {
        return std::to_string(value);
    }

    std::string difficultyName(Difficulty difficulty)
    {
        switch (difficulty)
        {
            case Difficulty::Easy: return "Facil";
            case Difficulty::Medium: return "Medio";
            case Difficulty::Hard: return "Dificil";
        }
        return "Medio";
    }

    std::string difficultyDescription(Difficulty difficulty)
    {
        switch (difficulty)
        {
            case Difficulty::Easy:
                return "Mais vida, menos dano e inimigos mais lentos.";
            case Difficulty::Medium:
                return "Equilibrado para estudar as mecanicas.";
            case Difficulty::Hard:
                return "Menos folga, inimigos fortes e mais pressao.";
        }
        return "";
    }
}
