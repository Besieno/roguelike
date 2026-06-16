#pragma once

#include <string>

namespace Rogue
{
    constexpr int TileSize = 32;
    constexpr int MapWidth = 26;
    constexpr int MapHeight = 18;
    constexpr int ScreenWidth = 1180;
    constexpr int ScreenHeight = 720;
    constexpr int HudX = MapWidth * TileSize + 24;
    constexpr int VisionRadius = 5;
    constexpr int MaxDungeonLevel = 3;

    struct Vec2i
    {
        int x = 0;
        int y = 0;
    };

    enum class Difficulty
    {
        Easy,
        Medium,
        Hard
    };

    bool operator==(Vec2i a, Vec2i b);
    bool operator!=(Vec2i a, Vec2i b);
    Vec2i operator+(Vec2i a, Vec2i b);

    int manhattanDistance(Vec2i a, Vec2i b);
    int clampInt(int value, int minValue, int maxValue);
    int randomInt(int minValue, int maxValue);
    bool percentChance(int percent);
    std::string intToString(int value);
    std::string difficultyName(Difficulty difficulty);
    std::string difficultyDescription(Difficulty difficulty);
}
