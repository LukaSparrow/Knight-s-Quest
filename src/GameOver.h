#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class GameOver
{
public:
	GameOver(float width, float height);

	int optionSelected;
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int MouseSelect(int x, int y);

	~GameOver();

private:
	Font font;
	Text gameOver[3];
};