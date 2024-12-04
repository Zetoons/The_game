#include <SFML/Graphics.hpp>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include "Cell_class.h"
#include "Cell_SaveLoader.h"

using namespace sf;
using namespace std;

Vector2f WinSize = { 512,512 };
float Cell_S = 25;
Vector2i Cell_offset = { 0,0 };
/*
Level name - str
Create - btn


*/

//*
// vector<Obj>
// vector<rect>
// vector<circle>
// vector<line>
// 
// 
//*

vector<Obj> objects = {};

char lvl_name[512] = {};

Vector2i map_size = { 32,32 };

float f;
int started = 0;
bool magnet_enable = true;
int pressed_num = 0;
bool movable = true;

vector<Texture> textures = {};

void setAllTextures()
{
    Texture txtr;
    txtr.loadFromFile("placeholder.png");
    textures.push_back(txtr);
    txtr.loadFromFile("yes_plhl.png");
    textures.push_back(txtr);
    txtr.loadFromFile("crate_plhl.png");
    textures.push_back(txtr);
    txtr.loadFromFile("chess_board.png");
    textures.push_back(txtr);
    txtr.loadFromFile("Block.png");
    textures.push_back(txtr);
}

void cell_foo(RenderWindow& window)
{

    for (int i = 0; i < objects.size(); i++)
    {
        
        //cout << "spr indx:" << objects[i].GetTextureIndex() << endl;
        //spr.setPosition(objects[i].getGridPos().x * Cell_S, objects[i].getGridPos().y * Cell_S);
        objects[i].getRect().setTexture(&textures[objects[i].GetTextureIndex()]);
        objects[i].getRect().setPosition(objects[i].getGridPos().x * Cell_S - Cell_offset.x, objects[i].getGridPos().y * Cell_S - Cell_offset.y);
        window.draw(objects[i].getRect());
    }
}

void UI()
{
    ImGui::SetNextWindowBgAlpha(0);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(WinSize.x, WinSize.y));
    ImGui::Begin(" ", NULL, 7);
    
    ImGui::SetNextItemWidth(350);
    ImGui::InputText("Level Name", lvl_name, 512);
    if(ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        {
            ImGui::Text("Max character amount: 512");
        }
        ImGui::EndTooltip();
    }
    if (ImGui::Button("Start"))
    {
        started = 1;
    }
    if (ImGui::Button("Load"))
    {
        started = 2;
    }
    ImGui::End();
}
static const char* items[]
{
    "Blocks",
    "Areas",
    "Enemies spawn",
    "Obstacles",
    "-",
    "-",
    "-",
};
void foo(Texture tx)
{
    ImGui::SetNextWindowPos(ImVec2{ 0,0 });
    ImGui::SetNextWindowSize(ImVec2{ 256,1024 });
    if (ImGui::Begin("Window", NULL, 6))
    {
        if (ImGui::Button("Save"))
        {
            set_obj_file_path("level_1/");
            objectsPosSaver(objects);
        }
        if (ImGui::BeginTabBar("tabs"))
        {
            if (ImGui::BeginTabItem("Paint"))
            {
                static int selected = 0;
                ImGui::ListBox("people", &selected, items, 5,5);
                ImGui::Checkbox("Movable", &movable);
                ImGui::Text(items[selected]);

                Sprite spr;
                switch (selected)
                {
                case 0:
                    spr.setTexture(textures[0]);
                    if (ImGui::ImageButton("plhldr", spr, { 50,50 }))
                    {
                        pressed_num = 0;
                    }
                    ImGui::SameLine();
                    spr.setTexture(textures[1]);
                    if(ImGui::ImageButton("yes", spr, { 50,50 }))
                    {
                        pressed_num = 1;
                    }
                    ImGui::SameLine();
                    spr.setTexture(textures[2]);
                    if (ImGui::ImageButton("crate", spr, { 50,50 }))
                    {
                        pressed_num = 2;
                    }
                    spr.setTexture(textures[3]);
                    if (ImGui::ImageButton("chess", spr, { 50,50 }))
                    {
                        pressed_num = 3;
                    }
                    ImGui::SameLine();
                    spr.setTexture(textures[4]);
                    if (ImGui::ImageButton("Block", spr, { 25,25 }))
                    {
                        pressed_num = 4;
                    }
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    break;
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("redact"))
            {
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("world"))
            {
                ImGui::Checkbox("Enable magnets?",&magnet_enable);

                int grid_s = Cell_S;
                if(ImGui::SliderInt("Grid size", &grid_s, 25, 200))
                {
                    for (int i = 0; i < objects.size(); i++)
                    {
                        objects[i].getRect().setSize(Vector2f{ Cell_S,Cell_S });
                        
                    }
                }
                    Cell_S = grid_s;

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }

        ImGui::End();
    }
}

void main()
{
    RenderWindow window(VideoMode(1920, 1080), "Let's start",4); // 1 - перемащать 4 - перемещать + (свернуть, заурыть)
    ImGui::SFML::Init(window);
    window.setFramerateLimit(60);
    window.setSize(Vector2u{ 512,512 });
    setAllTextures();

    Clock deltaClock;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        if (Keyboard::isKeyPressed(Keyboard::Right))Cell_offset.x += 10;
        if (Keyboard::isKeyPressed(Keyboard::Left)) Cell_offset.x += -10;
        if (Keyboard::isKeyPressed(Keyboard::Up))   Cell_offset.y += -10;
        if (Keyboard::isKeyPressed(Keyboard::Down)) Cell_offset.y += 10;

        Vector2i m_pos = Mouse::getPosition(window);

        int m_pos_x = float(m_pos.x + Cell_offset.x) / Cell_S;
        int m_pos_y = float(m_pos.y + Cell_offset.y) / Cell_S;
        if (m_pos.x + Cell_offset.x < 0)
            m_pos_x--;
        if (m_pos.y + Cell_offset.y < 0)
            m_pos_y--;

        //cout << m_pos_x << ' ' << m_pos_y << endl;
        if (Mouse::isButtonPressed(Mouse::Right) && !ImGui::IsAnyItemHovered() && window.hasFocus() && objects.size() > 0)
        {
            for (int i = 0; i < objects.size();i++)
            {
                if (objects[i].getGridPos().x == m_pos_x && objects[i].getGridPos().y == m_pos_y)
                {
                    objects.erase(objects.cbegin() + i);
                    cout << "Delete " << i << endl;
                    break;
                }
            }
        }
        if (Mouse::isButtonPressed(Mouse::Left) && !ImGui::IsAnyItemHovered() && window.hasFocus())
        {
            Obj obj({ m_pos_x,m_pos_y }, { Cell_S,Cell_S });
            bool flag = true;
            obj.SetTextureIndex(pressed_num);
            obj.SetMovaleVar(movable);
            for (int i = 0; i < objects.size(); i++)
            {
                if (objects[i].getGridPos().x == m_pos_x && objects[i].getGridPos().y == m_pos_y)
                {
                    flag = false;
                }
            }
            if(flag)
                objects.push_back(obj);
        }
        if (started == 2)
        {
            objectsPosLoader(objects);
            started = 0;
        }

        if (started == 0)
            UI();
        if(started == 1)
        {
            window.setSize(Vector2u{ 1920,1080 });
            window.setPosition(Vector2i{ 320,0 });
//            create_map(100,100);
// 
//            
            foo(textures[0]);
        }

        window.clear();
        if(magnet_enable)
        {
            int int_Cell_S = Cell_S;
            Color line_color = { 255,255,255,70 };
            for (int i = 0; i < window.getSize().y / Cell_S; i++)
            {
                Vertex line[] =
                {
                    Vertex{Vector2f{-1 * float(Cell_offset.x % int_Cell_S) - Cell_S,                     i * Cell_S - (Cell_offset.y % int_Cell_S)},    line_color},
                    Vertex{Vector2f{float(window.getSize().x) - (Cell_offset.x % int_Cell_S) + Cell_S,   i * Cell_S - (Cell_offset.y % int_Cell_S) },   line_color},
                };
                window.draw(line, 2, Lines);
            }
            for (int j = 0; j < window.getSize().x / Cell_S; j++) // 
            {
                Vertex line[] =
                {
                    Vertex{Vector2f{j * Cell_S - (Cell_offset.x % int_Cell_S),  -1 * float(Cell_offset.y % int_Cell_S) - Cell_S},                       line_color},
                    Vertex{Vector2f{j * Cell_S - (Cell_offset.x % int_Cell_S),  float(window.getSize().y) - (Cell_offset.y % int_Cell_S) + Cell_S },    line_color},
                };
                window.draw(line, 2, Lines);
            }

            Vertex lineOX[] =
            {
                Vertex{Vector2f{ 0 ,-float(Cell_offset.y) },{200,50,50,255}},
                Vertex{Vector2f{ float(window.getSize().x) ,-float(Cell_offset.y) },{200,50,50,255}},
            };
            window.draw(lineOX, 2, Lines);
            Vertex lineOY[] =
            {
                Vertex{Vector2f{ -float(Cell_offset.x),0 },{50,50,200,255}},
                Vertex{Vector2f{ -float(Cell_offset.x),float(window.getSize().x) },{50,50,200,255}},
            };
            window.draw(lineOY, 2, Lines);
        }
        
        cell_foo(window);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

}