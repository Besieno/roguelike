#pragma once

#include "Utils.h"

#include <raylib.h>
#include <string>

namespace Rogue
{
    enum class ItemType
    {
        HealthPotion,
        Key,
        Sword,
        Shield,
        PowerUp,
        Relic
    };

    struct Item
    {
        ItemType type = ItemType::HealthPotion;
        Vec2i position {0, 0};
        bool collected = false;
    };

    Item makeItem(ItemType type, Vec2i position);
    std::string itemName(ItemType type);
    std::string itemDescription(ItemType type);
    Color itemColor(ItemType type);
}
