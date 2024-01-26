#include "City.h"

City::City(float width, float height)
{

	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	city[0][0].setString(L"Witaj w mieście!");
	city[0][0].setFont(font);
	city[0][0].setFillColor(Color::Yellow);
	city[0][0].setOutlineColor(Color::Black);
	city[0][0].setLineSpacing(1.2);
	city[0][0].setOutlineThickness(1);
	city[0][0].setCharacterSize(30);
	FloatRect textRect = city[0][0].getLocalBounds();
	city[0][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[0][0].setPosition(300 + width / 2.0f, height - 800);

	city[1][0].setString(L"Trening z kukłami\n  (zwiększ atak)\n  10 szt. złota");
	city[1][0].setFont(font);
	city[1][0].setFillColor(Color::Red);
	city[1][0].setOutlineColor(Color::Black);
	city[1][0].setOutlineThickness(1);
	city[1][0].setCharacterSize(30);
	textRect = city[1][0].getLocalBounds();
	city[1][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[1][0].setPosition(300 + width / 2.0f - 250, height - 550);

	city[1][1].setString(L"  Przekuj zbroję\n(zwiększ obronę)\n  10 szt. złota");
	city[1][1].setFont(font);
	city[1][1].setFillColor(Color::White);
	city[1][1].setOutlineColor(Color::Black);
	city[1][1].setOutlineThickness(1);
	city[1][1].setCharacterSize(30);
	textRect = city[1][1].getLocalBounds();
	city[1][1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[1][1].setPosition(300 + width / 2.0f + 250, height - 550);

	city[2][0].setString(L"	  Trening kondycyjny\n(zwiększ maksymalne zdrowie)\n		10 szt. złota");
	city[2][0].setFont(font);
	city[2][0].setFillColor(Color::White);
	city[2][0].setOutlineColor(Color::Black);
	city[2][0].setOutlineThickness(1);
	city[2][0].setCharacterSize(30);
	textRect = city[2][0].getLocalBounds();
	city[2][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[2][0].setPosition(300 + width / 2.0f - 250, height - 350);

	city[2][1].setString(L"Kup miksturę zdrowia\n    50 szt. złota");
	city[2][1].setFont(font);
	city[2][1].setFillColor(Color::White);
	city[2][1].setOutlineColor(Color::Black);
	city[2][1].setOutlineThickness(1);
	city[2][1].setCharacterSize(30);
	textRect = city[2][1].getLocalBounds();
	city[2][1].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[2][1].setPosition(300 + width / 2.0f + 250, height - 350);

	city[3][0].setString(L"Opuść miasto");
	city[3][0].setFont(font);
	city[3][0].setFillColor(Color::Yellow);
	city[3][0].setOutlineColor(Color::Black);
	city[3][0].setOutlineThickness(1);
	city[3][0].setCharacterSize(30);
	textRect = city[3][0].getLocalBounds();
	city[3][0].setOrigin(textRect.width / 2.0f, textRect.height / 2.0f);
	city[3][0].setPosition(300 + width / 2.0f, height - 150);

	optionSelected = 1;
	valueSelected = 0;
}

City::~City()
{
}

void City::draw(RenderWindow& window)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			window.draw(city[i][j]);
		}
	}
}

void City::MoveUp()
{
	if (optionSelected >= 1)
	{
		if (optionSelected == 3)
		{
			city[optionSelected][valueSelected].setFillColor(Color::Yellow);
		}
		else
		{
			city[optionSelected][valueSelected].setFillColor(Color::White);
		}
		if (optionSelected == 1 && valueSelected == 1)
		{
			valueSelected = 0;
		}
		optionSelected--;
		if (optionSelected == 0)
		{
			optionSelected = 3;
		}
		city[optionSelected][valueSelected].setFillColor(Color::Red);
	}
}

void City::MoveDown()
{
	if (optionSelected <= 3)
	{
		if (optionSelected == 3)
		{
			city[optionSelected][valueSelected].setFillColor(Color::Yellow);
		}
		else
		{
			city[optionSelected][valueSelected].setFillColor(Color::White);
		}
		if (optionSelected == 2)
		{
			valueSelected = 0;
		}
		optionSelected++;
		if (optionSelected == 4)
		{
			optionSelected = 1;
		}
		city[optionSelected][valueSelected].setFillColor(Color::Red);
	}
}

void City::MoveSide()
{
	if (optionSelected == 3)
	{
		valueSelected = 0;
	}
	else
	{
		city[optionSelected][valueSelected].setFillColor(Color::White);
		if (valueSelected == 0)
		{
			valueSelected = 1;
		}
		else
		{
			valueSelected = 0;
		}
		city[optionSelected][valueSelected].setFillColor(Color::Red);
	}
}

int City::MouseSelect(int x, int y)
{
	int correction = 15;
	if (x > correction && y > correction)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (x >= city[i][j].getPosition().x - city[i][j].getLocalBounds().width / 2.0f - correction && x <= city[i][j].getPosition().x + city[i][j].getLocalBounds().width / 2.0f + correction && y >= city[i][j].getPosition().y - city[i][j].getLocalBounds().height / 2.0f - correction && y <= city[i][j].getPosition().y + city[i][j].getLocalBounds().height / 2.0f + 15)
				{
					city[1][0].setFillColor(Color::White);
					city[1][1].setFillColor(Color::White);
					city[2][0].setFillColor(Color::White);
					city[2][1].setFillColor(Color::White);
					city[3][0].setFillColor(Color::Yellow);
					optionSelected = i;
					if (i == 3)
					{
						valueSelected = 0;
					}
					else
					{
						valueSelected = j;
					}
					city[optionSelected][valueSelected].setFillColor(Color::Red);
					return 1;
				}
			}
		}
		return 0;
	}
	return 0;
}