#include "UI.h"

#include <raylib.h>

#include <array>

namespace Rogue
{
    namespace
    {
        const Color Background {18, 20, 26, 255};
        const Color Panel {30, 34, 43, 255};
        const Color TextMain {232, 236, 245, 255};
        const Color TextMuted {166, 174, 190, 255};
        const Color Accent {92, 211, 164, 255};

        Rectangle tileRect(Vec2i pos)
        {
            return Rectangle {
                static_cast<float>(pos.x * TileSize),
                static_cast<float>(pos.y * TileSize),
                static_cast<float>(TileSize),
                static_cast<float>(TileSize)
            };
        }

        void drawTextLine(const std::string& text, int x, int y, int size, Color color)
        {
            DrawText(text.c_str(), x, y, size, color);
        }

        void drawWrappedHelp(const std::vector<std::string>& lines)
        {
            int y = 150;
            for (const std::string& line : lines)
            {
                drawTextLine(line, 110, y, 20, TextMain);
                y += 30;
            }
            drawTextLine("ESC volta ao menu.", 110, ScreenHeight - 70, 20, Accent);
        }

        void drawEntityCircle(Vec2i pos, Color color, const char* label)
        {
            int cx = pos.x * TileSize + TileSize / 2;
            int cy = pos.y * TileSize + TileSize / 2;
            DrawCircle(cx, cy, TileSize * 0.34f, color);
            DrawText(label, cx - 5, cy - 8, 16, BLACK);
        }
    }

    void drawGame(const Map& map, const Player& player, const std::vector<Enemy>& enemies, const std::vector<Item>& items, const std::vector<NPC>& npcs, const std::string& message)
    {
        ClearBackground(Background);

        for (int y = 0; y < map.height; ++y)
        {
            for (int x = 0; x < map.width; ++x)
            {
                Vec2i pos {x, y};
                const Tile* tile = tileAt(map, pos);
                Rectangle rect = tileRect(pos);

                if (tile == nullptr || !tile->explored)
                {
                    DrawRectangleRec(rect, BLACK);
                    continue;
                }

                Color color = tileColor(tile->type, tile->trapActive);
                if (!tile->visible)
                {
                    color = Color {
                        static_cast<unsigned char>(color.r / 3),
                        static_cast<unsigned char>(color.g / 3),
                        static_cast<unsigned char>(color.b / 3),
                        255
                    };
                }

                DrawRectangleRec(rect, color);
                DrawRectangleLines(x * TileSize, y * TileSize, TileSize, TileSize, Color {21, 23, 29, 255});
            }
        }

        for (const Item& item : items)
        {
            const Tile* tile = tileAt(map, item.position);
            if (!item.collected && tile != nullptr && tile->visible)
            {
                Color color = itemColor(item.type);
                Rectangle rect = tileRect(item.position);
                DrawRectangleRounded(Rectangle {rect.x + 8, rect.y + 8, 16, 16}, 0.25f, 4, color);
            }
        }

        for (const NPC& npc : npcs)
        {
            const Tile* tile = tileAt(map, npc.position);
            if (tile != nullptr && tile->visible)
            {
                drawEntityCircle(npc.position, Color {87, 189, 198, 255}, "N");
            }
        }

        for (const Enemy& enemy : enemies)
        {
            const Tile* tile = tileAt(map, enemy.position);
            if (enemy.alive && tile != nullptr && tile->visible)
            {
                drawEntityCircle(enemy.position, enemyColor(enemy.type), isBoss(enemy) ? "B" : "E");
                DrawRectangle(enemy.position.x * TileSize + 5, enemy.position.y * TileSize + 27, 22, 3, Color {45, 12, 16, 255});
                int hpWidth = static_cast<int>(22.0f * enemy.hp / enemy.maxHp);
                DrawRectangle(enemy.position.x * TileSize + 5, enemy.position.y * TileSize + 27, hpWidth, 3, Color {234, 77, 97, 255});
            }
        }

        drawEntityCircle(player.position, Color {99, 170, 255, 255}, "@");

        DrawRectangle(MapWidth * TileSize, 0, ScreenWidth - MapWidth * TileSize, ScreenHeight, Panel);
        drawTextLine("Roguelike", HudX, 24, 28, TextMain);
        drawTextLine(map.title, HudX, 58, 18, Accent);
        drawTextLine("Nivel da masmorra: " + intToString(map.level), HudX, 88, 18, TextMuted);

        DrawRectangle(HudX, 126, 220, 18, Color {75, 28, 38, 255});
        int hpWidth = static_cast<int>(220.0f * player.hp / player.maxHp);
        DrawRectangle(HudX, 126, hpWidth, 18, Color {224, 72, 92, 255});
        drawTextLine("HP " + intToString(player.hp) + "/" + intToString(player.maxHp), HudX + 8, 125, 18, WHITE);

        drawTextLine("Nivel: " + intToString(player.level), HudX, 168, 18, TextMain);
        drawTextLine("XP: " + intToString(player.xp) + "/" + intToString(player.xpToNext), HudX, 196, 18, TextMain);
        drawTextLine("Pontos: " + intToString(calculateFinalScore(player)), HudX, 224, 18, TextMain);
        drawTextLine("Chaves: " + intToString(player.keys) + "  Pocoes: " + intToString(player.potions), HudX, 252, 18, TextMain);

        drawTextLine("Atributos", HudX, 298, 20, Accent);
        drawTextLine("Forca: " + intToString(player.attributes.strength), HudX, 330, 18, TextMuted);
        drawTextLine("Vitalidade: " + intToString(player.attributes.vitality), HudX, 356, 18, TextMuted);
        drawTextLine("Defesa: " + intToString(player.attributes.defense), HudX, 382, 18, TextMuted);
        drawTextLine("Agilidade: " + intToString(player.attributes.agility), HudX, 408, 18, TextMuted);

        drawTextLine("Controles", HudX, 462, 20, Accent);
        drawTextLine("WASD/setas: mover", HudX, 494, 17, TextMuted);
        drawTextLine("Espaco: atacar", HudX, 518, 17, TextMuted);
        drawTextLine("E: falar/interagir", HudX, 542, 17, TextMuted);
        drawTextLine("H: usar pocao", HudX, 566, 17, TextMuted);
        drawTextLine("ESC: pausar", HudX, 590, 17, TextMuted);

        DrawRectangle(HudX, 632, 300, 52, Color {21, 24, 31, 255});
        drawTextLine(message, HudX + 10, 648, 16, TextMain);
    }

    void drawMenu(MenuScreen screen, int selectedIndex, const Player& player)
    {
        ClearBackground(Background);
        drawTextLine("Roguelike - referencia grafica", 110, 70, 34, TextMain);
        drawTextLine("Ruinas de Aster: recupere a reliquia antes que o guardiao desperte.", 110, 112, 20, TextMuted);

        if (screen == MenuScreen::Main || screen == MenuScreen::Pause)
        {
            const std::array<std::string, 5> options {
                "Iniciar jogo",
                "Como jogar",
                "Itens",
                "Pontuacao",
                "Sair"
            };
            int y = 190;
            for (int i = 0; i < static_cast<int>(options.size()); ++i)
            {
                Color color = (i == selectedIndex) ? Accent : TextMain;
                std::string prefix = (i == selectedIndex) ? "> " : "  ";
                drawTextLine(prefix + options[i], 140, y, 26, color);
                y += 44;
            }
            if (screen == MenuScreen::Pause)
            {
                drawTextLine("Jogo pausado. Enter na primeira opcao continua.", 140, 440, 20, TextMuted);
            }
            return;
        }

        if (screen == MenuScreen::HowTo)
        {
            drawWrappedHelp({
                "Explore a masmorra em turnos. Cada movimento pode fazer os inimigos agirem.",
                "Bata em inimigos adjacentes com Espaco ou andando contra eles.",
                "Portas fechadas precisam de chave. NPCs podem abrir passagem ou curar.",
                "A fog of war mostra apenas o que voce ja explorou e o que esta visivel agora.",
                "Venca chegando ao ultimo nivel e derrotando o Guardiao Final."
            });
        }
        else if (screen == MenuScreen::Items)
        {
            drawWrappedHelp({
                "Pocao de vida: coletada no mapa e usada com H.",
                "Chave: abre portas fechadas ao tentar atravessa-las.",
                "Espada: aumenta o dano de ataque.",
                "Escudo: aumenta defesa e reduz dano recebido.",
                "Cristal de poder: concede XP para subir de nivel."
            });
        }
        else if (screen == MenuScreen::Scoring)
        {
            drawWrappedHelp({
                "Pontuacao soma inimigos derrotados, boss, itens, andares alcancados e vida restante.",
                "Movimentos, pocoes usadas e armadilhas ativadas reduzem a pontuacao final.",
                "A pontuacao aparece no HUD e tambem na tela final.",
                "Formula no codigo: Player.cpp, funcao calculateFinalScore."
            });
        }
        else if (screen == MenuScreen::GameOver)
        {
            drawTextLine("Fim de jogo", 110, 170, 36, Color {224, 72, 92, 255});
            drawTextLine("Pontuacao final: " + intToString(calculateFinalScore(player)), 110, 230, 26, TextMain);
            drawTextLine("Enter volta ao menu.", 110, 290, 22, Accent);
        }
        else if (screen == MenuScreen::Victory)
        {
            drawTextLine("Vitoria!", 110, 170, 42, Accent);
            drawTextLine("O Guardiao caiu e a reliquia foi recuperada.", 110, 230, 24, TextMain);
            drawTextLine("Pontuacao final: " + intToString(calculateFinalScore(player)), 110, 270, 26, TextMain);
            drawTextLine("Enter volta ao menu.", 110, 330, 22, Accent);
        }
    }

    void drawLevelUp(const Player& player, const std::string& message)
    {
        ClearBackground(Background);
        drawTextLine("Subiu de nivel!", 120, 90, 38, Accent);
        drawTextLine("Pontos para distribuir: " + intToString(player.pendingAttributePoints), 120, 145, 24, TextMain);
        drawTextLine("1 - Forca: mais dano", 150, 220, 24, TextMain);
        drawTextLine("2 - Vitalidade: mais HP maximo", 150, 260, 24, TextMain);
        drawTextLine("3 - Defesa: reduz dano recebido", 150, 300, 24, TextMain);
        drawTextLine("4 - Agilidade: acerto, esquiva e turnos rapidos", 150, 340, 24, TextMain);
        drawTextLine(message, 120, 420, 20, TextMuted);
    }
}
