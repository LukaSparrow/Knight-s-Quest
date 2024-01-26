#include "MainMenu.h"

MainMenu::MainMenu(float width, float height)
{
	if (!font.loadFromFile("content/Fonts/isocpeui.ttf"))
	{
		cout << "No font is here!";
	}

	//Kontynuuj
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(Color::Red);
	mainMenu[0].setOutlineColor(Color::Black);
	mainMenu[0].setOutlineThickness(1);
	mainMenu[0].setString("Kontynuuj");
	mainMenu[0].setCharacterSize(30);
	mainMenu[0].setPosition(width - 200, height - 250);
	//Nowa gra
	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(Color::White);
	mainMenu[1].setOutlineColor(Color::Black);
	mainMenu[1].setOutlineThickness(1);
	mainMenu[1].setString("Nowa gra");
	mainMenu[1].setCharacterSize(30);
	mainMenu[1].setPosition(width - 200, height - 200);
	//Opcje
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(Color::White);
	mainMenu[2].setOutlineColor(Color::Black);
	mainMenu[2].setOutlineThickness(1);
	mainMenu[2].setString("Opcje");
	mainMenu[2].setCharacterSize(30);
	mainMenu[2].setPosition(width - 200, height - 150);
	//Wyjście
	mainMenu[3].setFont(font);
	mainMenu[3].setFillColor(Color::White);
	mainMenu[3].setOutlineColor(Color::Black);
	mainMenu[3].setOutlineThickness(1);
	mainMenu[3].setString(L"Wyjście");
	mainMenu[3].setCharacterSize(30);
	mainMenu[3].setPosition(width - 200, height - 100);

	MainMenuSelected = 0;
}

MainMenu::~MainMenu()
{
}

//Rysowanie Menu
void MainMenu::draw(RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; i++)
	{
		window.draw(mainMenu[i]);
	}
}

//Wybierz w góre
void MainMenu::MoveUp()
{
	if (MainMenuSelected >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 3;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Red);
	}
}

//Wybierz w dół
void MainMenu::MoveDown()
{
	if (MainMenuSelected <= Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(Color::White);
		MainMenuSelected++;
		if (MainMenuSelected == 4)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(Color::Red);
	}
}

//Sterowanie myszką
int MainMenu::MouseSelect(int x, int y)
{
	int correction = 10;
	for (int i = 0; i < 4; i++)
	{
		if (x >= mainMenu[i].getPosition().x - correction && x <= mainMenu[i].getPosition().x + mainMenu[i].getLocalBounds().width + correction && y >= mainMenu[i].getPosition().y - correction && y <= mainMenu[i].getPosition().y + mainMenu[i].getLocalBounds().height + correction)
		{
			mainMenu[0].setFillColor(Color::White);
			mainMenu[1].setFillColor(Color::White);
			mainMenu[2].setFillColor(Color::White);
			mainMenu[3].setFillColor(Color::White);
			MainMenuSelected = i;
			mainMenu[MainMenuSelected].setFillColor(Color::Red);
			return 1;
		}
	}
	return 0;
}