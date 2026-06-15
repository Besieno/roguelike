#include "Item.h"

namespace Rogue
{
    Item makeItem(ItemType type, Vec2i position)
    {
        Item item;
        item.type = type;
        item.position = position;
        return item;
    }

    std::string itemName(ItemType type)
    {
        switch (type)
        {
            case ItemType::HealthPotion: return "Pocao de vida";
            case ItemType::Key: return "Chave";
            case ItemType::Sword: return "Espada";
            case ItemType::Shield: return "Escudo";
            case ItemType::PowerUp: return "Cristal de poder";
            case ItemType::Relic: return "Reliquia antiga";
        }
        return "Item";
    }

    std::string itemDescription(ItemType type)
    {
        switch (type)
        {
            case ItemType::HealthPotion: return "Cura parte da vida ao apertar H.";
            case ItemType::Key: return "Abre portas fechadas.";
            case ItemType::Sword: return "Aumenta o dano do jogador.";
            case ItemType::Shield: return "Aumenta defesa e reduz dano.";
            case ItemType::PowerUp: return "Concede XP e ajuda a subir de nivel.";
            case ItemType::Relic: return "Objetivo final protegido pelo chefe.";
        }
        return "";
    }

    Color itemColor(ItemType type)
    {
        switch (type)
        {
            case ItemType::HealthPotion: return Color {224, 72, 92, 255};
            case ItemType::Key: return Color {245, 197, 66, 255};
            case ItemType::Sword: return Color {185, 204, 220, 255};
            case ItemType::Shield: return Color {82, 151, 255, 255};
            case ItemType::PowerUp: return Color {171, 93, 255, 255};
            case ItemType::Relic: return Color {255, 245, 170, 255};
        }
        return WHITE;
    }
}
