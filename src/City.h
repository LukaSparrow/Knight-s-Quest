#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class City
{
public:
	City(float width, float height);

	int optionSelected;
	int valueSelected;
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void MoveSide();
	int MouseSelect(int x, int y);
	Text city[4][2];

	~City();

private:
	Font font;
};