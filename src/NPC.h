#pragma once

#include "Player.h"
#include "Utils.h"

#include <string>
#include <vector>

namespace Rogue
{
    struct Map;
    struct Item;

    enum class NPCType
    {
        Guide,
        Healer
    };

    struct NPC
    {
        NPCType type = NPCType::Guide;
        Vec2i position {0, 0};
        std::string name = "NPC";
        std::string dialog = "";
        bool talked = false;
    };

    NPC* findAdjacentNpc(std::vector<NPC>& npcs, Vec2i playerPosition);
    void interactWithNpc(Player& player, Map& map, NPC& npc, std::vector<Item>& items, std::string& message);
}
