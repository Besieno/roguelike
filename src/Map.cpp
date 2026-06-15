#include "Map.h"

#include <array>

namespace Rogue
{
    namespace
    {
        using LevelRows = std::array<std::string, MapHeight>;

        LevelRows levelOne()
        {
            return {
                "##########################",
                "#P....#.....T......#....>#",
                "#.##..#.#######.##.#.##..#",
                "#..#..#....K..#....#..#..#",
                "##.#..#######.#######.#.##",
                "#..#......#....T....#.#..#",
                "#.######..#.#####...#.#..#",
                "#....N....#.....#...#....#",
                "#######.#######.#.####D###",
                "#.....#.....S...#........#",
                "#.###.#.#####.######.###.#",
                "#...#.#.....#....H...#...#",
                "###.#.#####.#######.###.##",
                "#...#.....#.....H...#....#",
                "#.#######.#####.#####.##.#",
                "#.....T.......#.......K..#",
                "#....O........#.....O....#",
                "##########################"
            };
        }

        LevelRows levelTwo()
        {
            return {
                "##########################",
                "#P.....#......#.....T...>#",
                "#.###..#.####.#.#######..#",
                "#...#..#....#.#.....K.#..#",
                "###.#.#####.#.#####.#.#.##",
                "#...#.....#.#.....#.#.#..#",
                "#.#######.#.#####.#.#.##.#",
                "#.....N...#...S...#.#....#",
                "#####.#######.#####.######",
                "#...#.....T...#.....#....#",
                "#.#.#####.#####.###.#.##.#",
                "#.#.....#.....#...#...##.#",
                "#.#####.#####.###.####D#.#",
                "#.....#.....#...#.....H..#",
                "###.#.#####.###.########.#",
                "#...#.....#.....#....K...#",
                "#.....A...O...H.....O....#",
                "##########################"
            };
        }

        LevelRows levelThree()
        {
            return {
                "##########################",
                "#P....#.....T......#....R#",
                "#.##..#.#######.##.#.##..#",
                "#..#..#....K..#....#..#..#",
                "##.#..#######.#######.#.##",
                "#..#......#....T....#.#..#",
                "#.######..#.#####...#.#..#",
                "#....N....#.....#...#....#",
                "#######.#######.#.####D###",
                "#.....#.....S...#........#",
                "#.###.#.#####.######.###.#",
                "#...#.#.....#....H...#...#",
                "###.#.#####.#######.###.##",
                "#...#.....#.......B.#....#",
                "#.#######.#####.#####.##.#",
                "#.....T.......#.......K..#",
                "#....O........#.....O....#",
                "##########################"
            };
        }

        void applyRows(Map& map, const LevelRows& rows, Player& player, std::vector<Item>& items, std::vector<NPC>& npcs)
        {
            for (int y = 0; y < MapHeight; ++y)
            {
                for (int x = 0; x < MapWidth; ++x)
                {
                    char symbol = rows[y][x];
                    Vec2i pos {x, y};
                    TileType tile = TileType::Floor;

                    if (symbol == '#')
                    {
                        tile = TileType::Wall;
                    }
                    else if (symbol == 'D')
                    {
                        tile = TileType::DoorClosed;
                    }
                    else if (symbol == 'T')
                    {
                        tile = TileType::Trap;
                    }
                    else if (symbol == 'O')
                    {
                        tile = TileType::Obstacle;
                    }
                    else if (symbol == '>')
                    {
                        tile = TileType::Exit;
                    }
                    else if (symbol == 'R')
                    {
                        tile = TileType::Exit;
                    }
                    else if (symbol == '~')
                    {
                        tile = TileType::Water;
                    }

                    setTile(map, pos, tile);

                    if (symbol == 'P')
                    {
                        player.position = pos;
                    }
                    else if (symbol == 'K')
                    {
                        items.push_back(makeItem(ItemType::Key, pos));
                    }
                    else if (symbol == 'H')
                    {
                        items.push_back(makeItem(ItemType::HealthPotion, pos));
                    }
                    else if (symbol == 'S')
                    {
                        items.push_back(makeItem(ItemType::Sword, pos));
                    }
                    else if (symbol == 'A')
                    {
                        items.push_back(makeItem(ItemType::Shield, pos));
                    }
                    else if (symbol == 'R')
                    {
                        items.push_back(makeItem(ItemType::Relic, pos));
                    }
                    else if (symbol == 'N')
                    {
                        NPC npc;
                        npc.position = pos;
                        npc.type = (map.level == 2) ? NPCType::Healer : NPCType::Guide;
                        npc.name = (map.level == 2) ? "Curandeira Mira" : "Arqueologo Ivo";
                        npc.dialog = (map.level == 2)
                            ? "Mira cura voce e alerta: monstros tambem ativam armadilhas."
                            : "Ivo abre uma passagem antiga e entrega uma dica sobre chaves.";
                        npcs.push_back(npc);
                    }
                }
            }
        }
    }

    void initializeMap(Map& map, int width, int height)
    {
        map.width = width;
        map.height = height;
        map.tiles.assign(width * height, Tile {});
    }

    Tile* tileAt(Map& map, Vec2i position)
    {
        if (!inBounds(map, position))
        {
            return nullptr;
        }
        return &map.tiles[position.y * map.width + position.x];
    }

    const Tile* tileAt(const Map& map, Vec2i position)
    {
        if (!inBounds(map, position))
        {
            return nullptr;
        }
        return &map.tiles[position.y * map.width + position.x];
    }

    bool inBounds(const Map& map, Vec2i position)
    {
        return position.x >= 0 && position.y >= 0 && position.x < map.width && position.y < map.height;
    }

    bool isSolidTile(TileType type)
    {
        return type == TileType::Wall || type == TileType::DoorClosed || type == TileType::Obstacle || type == TileType::Water;
    }

    bool canCreatureWalkOn(const Map& map, Vec2i position)
    {
        const Tile* tile = tileAt(map, position);
        return tile != nullptr && !isSolidTile(tile->type);
    }

    void setTile(Map& map, Vec2i position, TileType type)
    {
        Tile* tile = tileAt(map, position);
        if (tile == nullptr)
        {
            return;
        }
        tile->type = type;
        tile->trapActive = (type == TileType::Trap);
    }

    Color tileColor(TileType type, bool trapActive)
    {
        switch (type)
        {
            case TileType::Floor: return Color {42, 44, 52, 255};
            case TileType::Wall: return Color {92, 96, 112, 255};
            case TileType::DoorClosed: return Color {137, 89, 55, 255};
            case TileType::DoorOpen: return Color {92, 64, 44, 255};
            case TileType::Obstacle: return Color {96, 82, 75, 255};
            case TileType::Trap: return trapActive ? Color {155, 54, 68, 255} : Color {55, 52, 58, 255};
            case TileType::Exit: return Color {68, 156, 114, 255};
            case TileType::Water: return Color {48, 91, 130, 255};
            case TileType::Rubble: return Color {103, 91, 83, 255};
        }
        return DARKGRAY;
    }

    char tileGlyph(TileType type)
    {
        switch (type)
        {
            case TileType::Floor: return '.';
            case TileType::Wall: return '#';
            case TileType::DoorClosed: return '+';
            case TileType::DoorOpen: return '/';
            case TileType::Obstacle: return 'O';
            case TileType::Trap: return '^';
            case TileType::Exit: return '>';
            case TileType::Water: return '~';
            case TileType::Rubble: return '%';
        }
        return '?';
    }

    void updateFogOfWar(Map& map, Vec2i center)
    {
        for (Tile& tile : map.tiles)
        {
            tile.visible = false;
        }

        for (int y = center.y - VisionRadius; y <= center.y + VisionRadius; ++y)
        {
            for (int x = center.x - VisionRadius; x <= center.x + VisionRadius; ++x)
            {
                Vec2i pos {x, y};
                if (!inBounds(map, pos) || manhattanDistance(center, pos) > VisionRadius)
                {
                    continue;
                }
                Tile* tile = tileAt(map, pos);
                if (tile != nullptr)
                {
                    tile->visible = true;
                    tile->explored = true;
                }
            }
        }
    }

    void loadLevel(Map& map, int level, Player& player, std::vector<Enemy>& enemies, std::vector<Item>& items, std::vector<NPC>& npcs)
    {
        initializeMap(map, MapWidth, MapHeight);
        map.level = level;
        map.bossArenaChanged = false;
        enemies.clear();
        items.clear();
        npcs.clear();

        if (level == 1)
        {
            map.title = "Entrada das ruinas";
            applyRows(map, levelOne(), player, items, npcs);
            enemies.push_back(makeEnemy(EnemyType::Wanderer, {5, 5}));
            enemies.push_back(makeEnemy(EnemyType::Hunter, {19, 4}));
            enemies.push_back(makeEnemy(EnemyType::Wanderer, {22, 14}));
            items.push_back(makeItem(ItemType::PowerUp, {7, 16}));
        }
        else if (level == 2)
        {
            map.title = "Galeria inundada";
            applyRows(map, levelTwo(), player, items, npcs);
            enemies.push_back(makeEnemy(EnemyType::Hunter, {12, 4}));
            enemies.push_back(makeEnemy(EnemyType::Wanderer, {18, 10}));
            enemies.push_back(makeEnemy(EnemyType::Brute, {8, 15}));
            items.push_back(makeItem(ItemType::PowerUp, {3, 16}));
        }
        else
        {
            map.title = "Camara do guardiao";
            applyRows(map, levelThree(), player, items, npcs);
            enemies.push_back(makeEnemy(EnemyType::Hunter, {5, 15}));
            enemies.push_back(makeEnemy(EnemyType::Brute, {20, 12}));
            enemies.push_back(makeEnemy(EnemyType::Boss, {18, 13}));
            items.push_back(makeItem(ItemType::PowerUp, {10, 16}));
        }

        updateFogOfWar(map, player.position);
        player.deepestLevel = std::max(player.deepestLevel, level);
    }

    void openSecretPassage(Map& map)
    {
        // Exemplo pedido no enunciado: um NPC modifica o mapa abrindo passagem.
        for (int y = 7; y <= 8; ++y)
        {
            setTile(map, {7, y}, TileType::Floor);
        }
        setTile(map, {8, 8}, TileType::DoorOpen);
    }

    void bossChangesArena(Map& map)
    {
        if (map.bossArenaChanged)
        {
            return;
        }
        map.bossArenaChanged = true;
        setTile(map, {15, 13}, TileType::Trap);
        setTile(map, {16, 13}, TileType::Trap);
        setTile(map, {17, 13}, TileType::Trap);
        setTile(map, {20, 13}, TileType::Rubble);
    }
}
