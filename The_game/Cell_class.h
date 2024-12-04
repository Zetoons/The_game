#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Obj
{
public:
	Obj(Vector2i grid_pos = { 0,0 }, Vector2f size = { 50,50}, Color color = { 255,255,255,255 })
	{
		this->grid_pos = grid_pos;
		this->rect.setSize(size);
		this->rect.setFillColor(color);
		this->texture_index = 0;
		this->movable = 1;
	}

	void SetTextureIndex(int index)
	{
		this->texture_index = index;
	}
	int GetTextureIndex()
	{
		return texture_index;
	}
	void SetMovaleVar(bool movable)
	{
		this->movable = movable;
	}
	bool GetMovaleVar()
	{
		return this->movable;
	}

	RectangleShape& getRect()
	{
		return this->rect;
	}

	void setGridPos(Vector2i grid_pos)
	{
		this->grid_pos = grid_pos;
	}
	Vector2i getGridPos()
	{
		return this->grid_pos;
	}
protected:
	Vector2i grid_pos;
	RectangleShape rect;
	int texture_index;
	bool movable;
};

class Rect : public Obj
{
public:

private:
	FloatRect hitbox;
};

class Cirlce : public Obj
{
public:

private:
	float a;
	/*
	Radius(size.x) is enough for hitbox
	*/
};

class line: public Obj
{
public:
	line(Vector2f pos1 = {0,0}, Vector2f pos2 = { 10,10 })
	{
		//this->pos = pos1;
		this->pos2 = pos2;
	}
private:
	Vector2f pos2;
	Color color;
};
