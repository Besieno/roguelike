#include "NPC.h"

#include "Item.h"
#include "Map.h"

namespace Rogue
{
    NPC* findAdjacentNpc(std::vector<NPC>& npcs, Vec2i playerPosition)
    {
        for (NPC& npc : npcs)
        {
            if (manhattanDistance(npc.position, playerPosition) == 1)
            {
                return &npc;
            }
        }
        return nullptr;
    }

    void interactWithNpc(Player& player, Map& map, NPC& npc, std::vector<Item>& items, std::string& message)
    {
        if (npc.type == NPCType::Guide)
        {
            if (!npc.talked)
            {
                openSecretPassage(map);
                player.keys += 1;
                player.score += 35;
                npc.talked = true;
                message = npc.name + ": passagem aberta e uma chave entregue.";
            }
            else
            {
                message = npc.name + ": procure a escada depois da porta.";
            }
        }
        else if (npc.type == NPCType::Healer)
        {
            if (!npc.talked)
            {
                player.hp = player.maxHp;
                items.push_back(makeItem(ItemType::HealthPotion, {npc.position.x + 1, npc.position.y}));
                npc.talked = true;
                message = npc.name + ": vida restaurada e uma pocao deixada no chao.";
            }
            else
            {
                message = npc.name + ": cuidado, alguns inimigos desativam armadilhas ao pisar.";
            }
        }
    }
}
