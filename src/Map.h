#pragma once

#include "Enemy.h"
#include "Item.h"
#include "NPC.h"
#include "Player.h"
#include "Utils.h"

#include <raylib.h>
#include <string>
#include <vector>

namespace Rogue
{
    enum class TileType
    {
        Floor,
        Wall,
        DoorClosed,
        DoorOpen,
        Obstacle,
        Trap,
        Exit,
        Water,
        Rubble
    };

    struct Tile
    {
        TileType type = TileType::Floor;
        bool explored = false;
        bool visible = false;
        bool trapActive = false;
    };

    struct Map
    {
        int width = MapWidth;
        int height = MapHeight;
        int level = 1;
        std::string title = "Entrada das ruinas";
        bool bossArenaChanged = false;
        std::vector<Tile> tiles;
    };

    void initializeMap(Map& map, int width, int height);
    Tile* tileAt(Map& map, Vec2i position);
    const Tile* tileAt(const Map& map, Vec2i position);
    bool inBounds(const Map& map, Vec2i position);
    bool isSolidTile(TileType type);
    bool canCreatureWalkOn(const Map& map, Vec2i position);
    void setTile(Map& map, Vec2i position, TileType type);
    Color tileColor(TileType type, bool trapActive);
    char tileGlyph(TileType type);
    void updateFogOfWar(Map& map, Vec2i center);
    void loadLevel(Map& map, int level, Player& player, std::vector<Enemy>& enemies, std::vector<Item>& items, std::vector<NPC>& npcs);
    void openSecretPassage(Map& map);
    void bossChangesArena(Map& map);
}
