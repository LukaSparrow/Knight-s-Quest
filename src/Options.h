#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Options
{
public:
	Options(float width, float height);

	int optionSelected;
	int valueSelected;
	void draw(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void MoveSide(String side);
	int MouseSelect(int x, int y);
	void difficultyUpdate(const wchar_t* diff);
	void soundUpdate(const wchar_t* snd);

	~Options();

private:
	Font font;
	Text options[5][3];
	Text currentSound;
	Text currentDifficulty;
};