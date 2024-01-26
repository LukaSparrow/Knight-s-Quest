#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Info
{
public:
	Info(float width, float height, const wchar_t text[]);

	int optionSelected;
	void draw(RenderWindow& window);
	int MouseSelect(int x, int y);
	Text info[2];

	~Info();

private:
	Font font;
};