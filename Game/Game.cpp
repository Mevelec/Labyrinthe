// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Grid.h>
#include <Player.h>
#include <olConsole.h>
#include <string>

using namespace std;

static GameEngine::GridManager& g_manager = GameEngine::GridManager::getInstance();

class Demo : public olcConsoleGameEngine {
    float cam_pos_x;
    float cam_pos_y;
    float scale;
    size_t index;
    size_t indexMap;

    GameEngine::Character player;
    std::wstring IA_Name;
public :
    Demo() :
        player("rambo")
    {
        index = 0;
        scale = 10;

        g_manager.generate(L"lab1", "lab1_10x10.txt");
        g_manager.generate(L"lab2", "lab2_10x10.txt");
        g_manager.generate(L"lab3", "lab3_3x3.txt");
        g_manager.generate(L"lab4", "lab4_50x50.txt");
        g_manager.load(0);
        indexMap = 0;

        cam_pos_x = 10;
        cam_pos_y = 10;

        player.setIA(new GameEngine::IA_Left());
        IA_Name = L"IA_Left";
    }
public :
    bool OnUserCreate() {

        return true;
    }
    bool OnUserUpdate(float fElapsedTime) {
        if (m_keys[VK_LEFT].bHeld) {
            cam_pos_x -= 15.0f * fElapsedTime;
        }
        if (m_keys[VK_RIGHT].bHeld) {
            cam_pos_x += 15.0f * fElapsedTime;
        }
        if (m_keys[VK_UP].bHeld) {
            cam_pos_y -= 15.0f * fElapsedTime;
        }
        if (m_keys[VK_DOWN].bHeld) {
            cam_pos_y += 15.0f * fElapsedTime;
        }

        if (m_keys[VK_PRIOR].bHeld) {
            scale -= 10.f * fElapsedTime;
        }
        if (m_keys[VK_NEXT].bHeld) {
            scale += 10.f * fElapsedTime;
        }

        if (m_keys[VK_F1].bPressed) {
            index = 0;
        }
        else if (m_keys[VK_F2].bPressed) {
            index = 10;
        }
        else if (m_keys[VK_F3].bPressed) {
            index = 20;
        } 
        else if (m_keys[0x44].bPressed) {
            index = 11;
        } 
        else if (m_keys[0x49].bPressed) {
            index = 12;
        } 
        else if (m_keys[VK_NUMPAD0].bPressed) {
            g_manager.load(0);
            indexMap = 0;
            player.setIA(new GameEngine::IA_Left());
            player.setPos({ 0, 0 });
            IA_Name = L"IA_Left";
        }else if (m_keys[VK_NUMPAD1].bPressed) {
            g_manager.load(1);
            indexMap = 1;
            player.setIA(new GameEngine::IA_Left());
            player.setPos({ 0, 0 });
            IA_Name = L"IA_Left";
        }else if (m_keys[VK_NUMPAD2].bPressed) {
            g_manager.load(2);
            indexMap = 2;
            player.setIA(new GameEngine::IA_Left());
            player.setPos({ 0, 0 });
            IA_Name = L"IA_Left";
        }else if (m_keys[VK_NUMPAD3].bPressed) {
            g_manager.load(3);
            indexMap = 3;
            player.setIA(new GameEngine::IA_Left());
            player.setPos({ 0, 0 });
            IA_Name = L"IA_Left";
        }else if (m_keys[VK_NUMPAD4].bPressed) {
            g_manager.load(4);
            indexMap = 4;
            player.setIA(new GameEngine::IA_Left());
            player.setPos({ 0, 0 });
            IA_Name = L"IA_Left";
        }
        else if (m_keys[0x41].bPressed) {
            player.setPos({ 0, 0 });
            player.setIA(new GameEngine::IA_Left);
            IA_Name = L"IA_Left";
        }
        else if (m_keys[0x5A].bPressed) {
            player.setPos({ 0, 0 });
            player.setIA(new GameEngine::IA_Right);
            IA_Name = L"IA_Right";
        }
        else if (m_keys[0x45].bPressed) {
            player.setPos({ 0, 0 });
            player.setIA(new GameEngine::IA_Random);
            IA_Name = L"IA_Random";
        }
        else if (m_keys[0x52].bPressed) {
            player.setPos({ 0, 0 });
            player.setIA(new GameEngine::IA_Stair);
            IA_Name = L"IA_Stair";
        }
        else if (m_keys[0x54].bPressed) {
            player.setPos({ 0, 0 });
            player.setIA(new GameEngine::IA_Solve);
            IA_Name = L"IA_Solve";
        }
        else if (m_keys[VK_ESCAPE].bPressed) {
            m_bAtomActive = false;
        }

        switch (index)
        {
        case 0:
            menu();
            break;
        case 10:
            mapsMenu();
            break;
        case 11:
            player.step();
            displayMap();
            break;
        case 12:
            switch (indexMap)
            {
            case 0:
                mapsInfos1();
                break;
            case 1:
                mapsInfos2();
                break;
            case 2:
                mapsInfos3();
                break;
            case 3:
                mapsInfos4();
                break;
            default:
                menu();
                break;
            }
            break;
        default:
            break;
        }
        return true;
    }

private :
    void menu() {
        beginPaint();

        drawText(0, 40, L"Menu :");
        drawText(3, 0, L"Utilisez les touches pour choisir un menu :");
        drawText(5, 10, L"F1 : Ce Menu");
        drawText(6, 10, L"F2 : Menu des cartes");
        drawText(7, 10, L"F3 : Credits");
        drawText(8, 10, L"escape : Quit");

        endPaint();
    }

    void mapsMenu() {
        beginPaint();

        drawText(0, 40, L"Cartes :");
        drawText(3, 0, L"Carte actuellement disponibles :");
        drawText(5, 10, L"0 : lab1");
        drawText(6, 10, L"1 : lab2");
        drawText(7, 10, L"2 : lab3");
        drawText(8, 10, L"3 : lab4");

        drawText(11, 0, L"Utilisez les touches :");
        drawText(13, 10, L"d");
        drawText(13, 150, L"afficher la carte");

        drawText(14, 10, L"i");
        drawText(14, 150, L"afficher les infos de la carte");

        drawText(15, 10, L"PAGE_UP");
        drawText(15, 150, L"zoom in");

        drawText(16, 10, L"PAGE_DOWN");
        drawText(16, 150, L"zoom out");

        drawText(17, 10, L"LEFT");
        drawText(17, 150, L"move left");

        drawText(18, 10, L"RIGHT");
        drawText(18, 150, L"move right");

        drawText(19, 10, L"UP");
        drawText(19, 150, L"move up");

        drawText(20, 10, L"DOWN");
        drawText(20, 150, L"move down");
        
        drawText(21, 10, L"A");
        drawText(21, 150, L"change IA to IA_Left");
        drawText(22, 10, L"Z");
        drawText(22, 150, L"change IA to IA_Right");
        drawText(23, 10, L"E");
        drawText(23, 150, L"change IA to IA_Random");
        drawText(24, 10, L"R");
        drawText(24, 150, L"change IA to IA_Stair");
        drawText(25, 10, L"T");
        drawText(25, 150, L"change IA to IA_Solve");

        endPaint();
    }
    void displayMap() {
        beginPaint();
        std::unique_ptr<GameEngine::Grid>* grid = g_manager.current();
        
        if (grid != nullptr) {
            size_t sx = grid->operator->()->size_x();
            size_t sy = grid->operator->()->size_y();

            for (size_t y = 0; y < sy; ++y) {
                for (size_t x = 0; x < sx; ++x) {
                    GameEngine::TileType type = grid->operator->()->at(x, y);
                    if (type == GameEngine::TileType::Wall) {
                        drawRect((y + cam_pos_y) * scale, (x + cam_pos_x) * scale, (y + cam_pos_y) * scale + scale, (x + cam_pos_x) * scale + scale, WHITE);
                    }
                    else if (type == GameEngine::TileType::Start) {
                        drawRect((y + cam_pos_y) * scale, (x + cam_pos_x) * scale, (y + cam_pos_y) * scale + scale, (x + cam_pos_x) * scale + scale, GREEN);
                    }
                    else if (type == GameEngine::TileType::End) {
                        drawRect((y + cam_pos_y) * scale, (x + cam_pos_x) * scale, (y + cam_pos_y) * scale + scale, (x + cam_pos_x) * scale + scale, RED);
                    }
                    else {
                        drawRect((y + cam_pos_y) * scale, (x + cam_pos_x) * scale, (y + cam_pos_y) * scale + scale, (x + cam_pos_x) * scale + scale, GREY);
                    }
                }
            }


            GameEngine::Position playerPos = player.getPosition();
            drawCircle((playerPos.x + cam_pos_x) * scale, (playerPos.y + cam_pos_y) * scale, (playerPos.x + cam_pos_x) * scale + scale, (playerPos.y + cam_pos_y) * scale + scale, WHITE);
            drawText(0, 10, IA_Name.c_str());
            drawText(1, 10, L"Steps :");
            std::wstring s = std::to_wstring(player.getIA()->count());
            drawText(1, 80, s.c_str());
        }
        endPaint();
    }

    void mapsInfos1() {
        beginPaint();

        drawText(0, 40, L"Infos de la carte :" );
        drawText(0, 160, g_manager.current()->operator->()->m_name);

        drawText(2, 0, L"IA_Left :");
        drawText(3, 20, L"nombre de déplacements :");
        drawText(3, 200, L"infini");
        drawText(4, 20, L"est arrivé :");
        drawText(4, 200, L"non");

        drawText(6, 0, L"IA_Right :");
        drawText(7, 20, L"nombre de déplacements :");
        drawText(7, 200, L"infini");
        drawText(8, 20, L"est arrivé :");
        drawText(8, 200, L"non");

        drawText(10, 0, L"IA_Random :");
        drawText(11, 20, L"nombre de déplacements :");
        drawText(11, 200, L"très variable (entre meilleur chemin et infini)");
        drawText(12, 20, L"est arrivé :");
        drawText(12, 200, L"non");

        drawText(14, 0, L"IA_Stair :");
        drawText(15, 20, L"nombre de déplacements :");
        drawText(15, 200, L"infini");
        drawText(16, 20, L"est arrivé :");
        drawText(16, 200, L"non");

        drawText(18, 0, L"IA_Solver :");
        drawText(19, 20, L"Résoud en :");
        drawText(19, 200, L"454");
        drawText(20, 20, L"nombre de déplacements :");
        drawText(20, 200, L"83");
        drawText(21, 20, L"est arrivé :");
        drawText(21, 200, L"oui");

        endPaint();
    }
    void mapsInfos2() {
        beginPaint();

        drawText(0, 40, L"Infos de la carte :" );
        drawText(0, 160, g_manager.current()->operator->()->m_name);

        drawText(2, 0, L"IA_Left :");
        drawText(3, 20, L"nombre de déplacements :");
        drawText(3, 200, L"infini");
        drawText(4, 20, L"est arrivé :");
        drawText(4, 200, L"non");

        drawText(6, 0, L"IA_Right :");
        drawText(7, 20, L"nombre de déplacements :");
        drawText(7, 200, L"infini");
        drawText(8, 20, L"est arrivé :");
        drawText(8, 200, L"non");

        drawText(10, 0, L"IA_Random :");
        drawText(11, 20, L"nombre de déplacements :");
        drawText(11, 200, L"très variable (entre meilleur chemin et infini)");
        drawText(12, 20, L"est arrivé :");
        drawText(12, 200, L"non");

        drawText(14, 0, L"IA_Stair :");
        drawText(15, 20, L"nombre de déplacements :");
        drawText(15, 200, L"infini");
        drawText(16, 20, L"est arrivé :");
        drawText(16, 200, L"non");

        drawText(18, 0, L"IA_Solver :");
        drawText(19, 20, L"Résoud en :");
        drawText(19, 200, L"439");
        drawText(20, 20, L"nombre de déplacements :");
        drawText(20, 200, L"62");
        drawText(21, 20, L"est arrivé :");
        drawText(21, 200, L"oui");

        endPaint();
    }
    void mapsInfos3() {
        beginPaint();

        drawText(0, 40, L"Infos de la carte :" );
        drawText(0, 160, g_manager.current()->operator->()->m_name);

        drawText(2, 0, L"IA_Left :");
        drawText(3, 20, L"nombre de déplacements :");
        drawText(3, 200, L"infini");
        drawText(4, 20, L"est arrivé :");
        drawText(4, 200, L"non");

        drawText(6, 0, L"IA_Right :");
        drawText(7, 20, L"nombre de déplacements :");
        drawText(7, 200, L"infini");
        drawText(8, 20, L"est arrivé :");
        drawText(8, 200, L"non");

        drawText(10, 0, L"IA_Random :");
        drawText(11, 20, L"nombre de déplacements :");
        drawText(11, 200, L"très variable 107 coups");
        drawText(12, 20, L"est arrivé :");
        drawText(12, 200, L"oui");

        drawText(14, 0, L"IA_Stair :");
        drawText(15, 20, L"nombre de déplacements :");
        drawText(15, 200, L"17");
        drawText(16, 20, L"est arrivé :");
        drawText(16, 200, L"oui");

        drawText(18, 0, L"IA_Solver :");
        drawText(19, 20, L"Résoud en :");
        drawText(19, 200, L"20");
        drawText(20, 20, L"nombre de déplacements :");
        drawText(20, 200, L"17");
        drawText(21, 20, L"est arrivé :");
        drawText(21, 200, L"oui");

        endPaint();
    }
    void mapsInfos4() {
        beginPaint();

        drawText(0, 40, L"Infos de la carte :" );
        drawText(0, 160, g_manager.current()->operator->()->m_name);

        drawText(2, 0, L"IA_Left :");
        drawText(3, 20, L"nombre de déplacements :");
        drawText(3, 200, L"infini");
        drawText(4, 20, L"est arrivé :");
        drawText(4, 200, L"non");

        drawText(6, 0, L"IA_Right :");
        drawText(7, 20, L"nombre de déplacements :");
        drawText(7, 200, L"infini");
        drawText(8, 20, L"est arrivé :");
        drawText(8, 200, L"non");

        drawText(10, 0, L"IA_Random :");
        drawText(11, 20, L"nombre de déplacements :");
        drawText(11, 200, L"très variable (entre meilleur chemin et infini)");
        drawText(12, 20, L"est arrivé :");
        drawText(12, 200, L"non");

        drawText(14, 0, L"IA_Stair :");
        drawText(15, 20, L"nombre de déplacements :");
        drawText(15, 200, L"infini");
        drawText(16, 20, L"est arrivé :");
        drawText(16, 200, L"non");

        drawText(18, 0, L"IA_Solver :");
        drawText(19, 20, L"Résoud en :");
        drawText(19, 200, L"infini (impossible)");
        drawText(20, 20, L"nombre de déplacements :");
        drawText(20, 200, L"infini");
        drawText(21, 20, L"est arrivé :");
        drawText(21, 200, L"non");

        endPaint();
    }
};
int main()
{
    Demo game;
    game.Start();
    

    return 0;
}