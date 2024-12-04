#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Cell_class.h"
using namespace std;


string file_path;

void set_obj_file_path(string folder_name)
{
    file_path = folder_name + "position.txt";
}

vector<Obj> objectsPosLoader(vector<Obj>& objects) // ,float& x, float& y, float& w, float& h, float& x2, float& y2, int& r, int& g, int& b, int& a, int& texture_id
{
    //файл слоёв, открывает файл и записывает данные в слои
    ifstream input;
    string str;
    input.open(file_path);
    float x = 0, y = 0, w = 0, h = 0, r = 0, g = 0, b = 0, a = 0, texture_id = 0, offset_x = 0, offset_y = 0;
    bool movable = true;
    for (int i = 0; i < objects.size(); i++)
    {
        cout << i << ' ';
        input >> str;
        x = stof(str);
        input >> str;
        y = stof(str);
        cout << x << ' ' << y << ' ';
        objects[i].getRect().setPosition(x, y);
        input >> str;
        w = stof(str);
        input >> str;
        h = stof(str);
        cout << w << ' ' << h << ' ' << endl;
        objects[i].getRect().setSize(Vector2f{ w,h });
        input >> str;
        movable = stoi(str);
        input >> str;
        r = stoi(str);
        input >> str;
        g = stoi(str);
        input >> str;
        b = stoi(str);
        input >> str;
        a = stoi(str);
        objects[i].getRect().setFillColor({ Uint8(r),Uint8(g),Uint8(b),Uint8(a) });
        input >> str;
        texture_id = stoi(str);
        input >> str;
        offset_x = stof(str);
        input >> str;
        offset_y = stof(str);
    }
    input.close();
    return objects;
}

void objectsPosSaver(vector<Obj> objects) // float x, float y, float w, float h, float x2, float y2, int r, int g, int b, int a, int texture_id
{
    ofstream output;
    string str;
    output.open(file_path);
    for (int i = 0; i < objects.size(); i++)
    {
        str = to_string(objects[i].getGridPos().x);
        output << str << ' ';
        str = to_string(objects[i].getGridPos().y);
        output << str << ' ';
        str = to_string(NULL/*objects[i].getRect().getSize().x*/);
        output << str << ' ';
        str = to_string(NULL/*objects[i].getRect().getSize().y*/);
        output << str << ' ';
        output << to_string(objects[i].GetMovaleVar()) << ' ';
        str = to_string(objects[i].getRect().getFillColor().r);
        output << str << ' ';
        str = to_string(objects[i].getRect().getFillColor().g);
        output << str << ' ';
        str = to_string(objects[i].getRect().getFillColor().b);
        output << str << ' ';
        str = to_string(objects[i].getRect().getFillColor().a);
        output << str << ' ';
        str = to_string(objects[i].GetTextureIndex());
        output << str << ' ';
        str = to_string(14); //  14 - debug
        output << str << ' ';
        str = to_string(14); //  14 - debug
        output << str << endl;

    }
    output.close();
}