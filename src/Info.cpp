#include "Info.h"

Info::Info(float width, float height, const wchar_t text[])
{
	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	//Komunikat
	info[0].setString(text);
	info[0].setFont(font);
	info[0].setFillColor(Color::White);
	info[0].setOutlineColor(Color::Black);
	info[0].setOutlineThickness(3);
	info[0].setLineSpacing(1.2);
	info[0].setCharacterSize(30);
	FloatRect textRect = info[0].getLocalBounds();
	info[0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	info[0].setPosition(300 + width / 2.0f, height - 600);

	//Kontynuuj
	info[1].setString(L"Kontynuuj");
	info[1].setFont(font);
	info[1].setFillColor(Color::Red);
	info[1].setOutlineColor(Color::Black);
	info[1].setOutlineThickness(2);
	info[1].setCharacterSize(30);
	textRect = info[1].getLocalBounds();
	info[1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	info[1].setPosition(300 + width / 2.0f, height - 250);

	optionSelected = 1;
}

Info::~Info()
{
}

void Info::draw(RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(info[i]);
	}
}

int Info::MouseSelect(int x, int y)
{
	if (x >= info[optionSelected].getPosition().x - info[optionSelected].getLocalBounds().width / 2.0f && x <= info[optionSelected].getPosition().x + info[optionSelected].getLocalBounds().width / 2.0f && y >= info[optionSelected].getPosition().y - info[optionSelected].getLocalBounds().height / 2.0f && y <= info[optionSelected].getPosition().y + info[optionSelected].getLocalBounds().height / 2.0f)
	{
		return 1;
	}
	return 0;
}