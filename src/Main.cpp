#include "City.h"
#include "Fight.h"
#include "GameOver.h"
#include "Info.h"
#include "MainMenu.h"
#include "Options.h"
#include "Player.h"
#include "TwoChoice.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

void save(Player player, String path);
void load(Player* player, String path);

int main()
{
	RenderWindow MENU(VideoMode(1600, 900), L"Menu Główne", Style::Titlebar | Style::Close);

	//Tło postaci
	Player player(300, 900);
	RectangleShape playerBackground;
	playerBackground.setSize(Vector2f(300, 900));
	Texture playerBG;
	playerBG.loadFromFile("content/Graphics/other/playerbg.jpg");
	playerBackground.setTexture(&playerBG);

	//Tło menu głownego
	MainMenu mainMenu(1600, 900);
	RectangleShape background;
	background.setSize(Vector2f(1600, 900));
	Texture MainMenuBG;
	MainMenuBG.loadFromFile("content/Graphics/other/menubg.jpg");
	background.setTexture(&MainMenuBG);

	//Tło opcji
	Options options(1600, 900);
	RectangleShape backgroundOptions;
	backgroundOptions.setSize(Vector2f(1600, 900));
	Texture optionsBG;
	optionsBG.loadFromFile("content/Graphics/other/optionsbg.jpg");
	backgroundOptions.setTexture(&optionsBG);

	//Tło ekranu końca gry
	GameOver gameOver(1600, 900);
	RectangleShape gameOverBackground;
	gameOverBackground.setSize(Vector2f(1600, 900));
	Texture gameOverBG;
	gameOverBG.loadFromFile("content/Graphics/other/gameover.jpg");
	gameOverBackground.setTexture(&gameOverBG);

	//Tło ekranu dwóch opcji
	TwoChoice twoChoice(1300, 900);
	RectangleShape twoChoiceBackground;
	twoChoiceBackground.setSize(Vector2f(1600, 900));
	Texture twoChoiceBG;
	twoChoiceBG.loadFromFile("content/Graphics/locations/travel.jpg");
	twoChoiceBackground.setTexture(&twoChoiceBG);

	//Tło ekrany komunikatu
	Info info(1300, 900, L"");
	RectangleShape infoBackground;
	infoBackground.setSize(Vector2f(1600, 900));
	Texture infoBG;
	infoBG.loadFromFile("content/Graphics/locations/travel.jpg");
	infoBackground.setTexture(&infoBG);

	//Tło miasta
	City city(1300, 900);
	RectangleShape cityBackground;
	cityBackground.setSize(Vector2f(1600, 900));
	Texture cityBG;
	cityBG.loadFromFile("content/Graphics/cities/city.jpg");
	cityBackground.setTexture(&cityBG);

	//Tło walki
	RectangleShape fightBackground;
	fightBackground.setSize(Vector2f(1600, 900));
	Texture fightBG;
	fightBG.loadFromFile("content/Graphics/locations/fightbg.jpg");
	fightBackground.setTexture(&fightBG);

	Player enemy(0, 0);
	enemy.attack = 10;
	enemy.defense = 10;
	enemy.maxHP = 100;
	enemy.HP = enemy.maxHP;

	Player* playerPointer = &player;
	Player* enemyPointer = &enemy;

	Fight fight(1600, 900, playerPointer, enemyPointer);

	RectangleShape PlayerAvatar;
	PlayerAvatar.setSize(Vector2f(400, 400));
	Texture PlayerAvatarTexture;
	PlayerAvatarTexture.loadFromFile("content/Graphics/other/avatar1.jpg");
	PlayerAvatar.setTexture(&PlayerAvatarTexture);
	PlayerAvatar.setOrigin(PlayerAvatar.getGlobalBounds().width / 2.0f, PlayerAvatar.getGlobalBounds().height / 2.0f);
	PlayerAvatar.setPosition(1600 / 4.0f, 900 / 3.0f);
	PlayerAvatar.setOutlineColor(Color::Black);
	PlayerAvatar.setOutlineThickness(2);

	RectangleShape EnemyAvatar;
	EnemyAvatar.setSize(Vector2f(400, 400));
	Texture EnemyAvatarTexture;
	EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/traveler.jpg");
	EnemyAvatar.setTexture(&EnemyAvatarTexture);
	EnemyAvatar.setOrigin(EnemyAvatar.getGlobalBounds().width / 2.0f, EnemyAvatar.getGlobalBounds().height / 2.0f);
	EnemyAvatar.setPosition(1600 - (1600 / 4.0f), 900 / 3.0f);
	EnemyAvatar.setOutlineColor(Color::Black);
	EnemyAvatar.setOutlineThickness(2);

	//Ikonka okna
	Image icon;
	icon.loadFromFile("content/Graphics/other/ikona2.png");
	MENU.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	int soundVol = 5;
	//Dźwięk przycisku
	SoundBuffer buffer;
	if (!buffer.loadFromFile("content/Sounds/click.wav"))
		return -1;
	Sound button;
	button.setBuffer(buffer);
	button.setVolume(soundVol);

	//Dźwięk monet
	SoundBuffer goldBuffer;
	if (!goldBuffer.loadFromFile("content/Sounds/gold.wav"))
		return -1;
	Sound goldSound;
	goldSound.setBuffer(goldBuffer);
	goldSound.setVolume(soundVol);

	SoundBuffer soundTrackBuffer;
	if (!soundTrackBuffer.loadFromFile("content/Sounds/soundtrack.wav"))
		return -1;
	Sound soundTrack;
	soundTrack.setBuffer(soundTrackBuffer);
	soundTrack.setVolume(soundVol);
	//soundTrack.play();

	SoundBuffer swordSoundBuffer;
	if (!swordSoundBuffer.loadFromFile("content/Sounds/sword.wav"))
		return -1;
	Sound swordSound;
	swordSound.setBuffer(swordSoundBuffer);
	swordSound.setVolume(soundVol);
	Sound* swordSoundPointer = &swordSound;

	SoundBuffer potionSoundBuffer;
	if (!potionSoundBuffer.loadFromFile("content/Sounds/potion.wav"))
		return -1;
	Sound potionSound;
	potionSound.setBuffer(potionSoundBuffer);
	potionSound.setVolume(soundVol);
	Sound* potionSoundPointer = &potionSound;

	SoundBuffer fightWonSoundBuffer;
	if (!fightWonSoundBuffer.loadFromFile("content/Sounds/fightwon.wav"))
		return -1;
	Sound fightWonSound;
	fightWonSound.setBuffer(fightWonSoundBuffer);
	fightWonSound.setVolume(soundVol);
	//Sound* fightWonSoundPointer = &fightWonSound;

	SoundBuffer fightLostSoundBuffer;
	if (!fightLostSoundBuffer.loadFromFile("content/Sounds/fightlost.wav"))
		return -1;
	Sound fightLostSound;
	fightLostSound.setBuffer(fightLostSoundBuffer);
	fightLostSound.setVolume(soundVol);
	//Sound* fightLostSoundPointer = &fightLostSound;

	bool diffSet = false;
	bool doOnce = true;
	bool doOnce2 = true;
	int loadedProgress = -1;

	srand(time(NULL));

	Player latestPlayer(1600, 900);

	while (MENU.isOpen())
	{
		Vector2i localPosition = sf::Mouse::getPosition(MENU);
		Event event;
		while (MENU.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				MENU.close();
			}
			if (event.type == Event::KeyPressed || event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)
				{
					mainMenu.MoveUp();
					break;
				}
				if (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)
				{
					mainMenu.MoveDown();
					break;
				}
				if (event.key.code == Keyboard::Return || event.key.code == Keyboard::E || (event.type == Event::MouseButtonPressed && mainMenu.MouseSelect(localPosition.x, localPosition.y)))
				{
					button.play();
					RenderWindow Gra(VideoMode(MENU.getSize().x, MENU.getSize().y), "Gra", Style::Titlebar | Style::Close);
					Gra.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
					RenderWindow Opcje(VideoMode(MENU.getSize().x, MENU.getSize().y), "Opcje", Style::Titlebar | Style::Close);
					Opcje.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

					int menuChosen = mainMenu.MainMenuPressed();
					int loaded = 0;
					if (menuChosen == 0)
					{
						//powrót do zapisu
						load(playerPointer, "content/Save.txt");
						loaded = 1;
						loadedProgress = player.progress;
						menuChosen = 1;
					}
					if (menuChosen == 1)
					{
						if (!loaded || loadedProgress < player.progress)
						{
							player.progress = 0;
							if (!diffSet)
							{
								player.difficulty = 1;
							}
							player.attack = 10;
							player.defense = 10;
							player.maxHP = 100;
							player.HP = player.maxHP;
							player.gold = 0;
							player.level = 1;
							player.exp = 0;
							player.potions = 0;
							loadedProgress = 0;
							doOnce = true;
						}
						while (Gra.isOpen())
						{
							Event aevent;
							Vector2i localGamePosition = sf::Mouse::getPosition(Gra);
							switch (player.progress)
							{
								case 0:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										info.info[0].setString(L"								  Witaj w grze Knight's Quest! \n  Twoim celem jest dotarcie do Xendoru, krainy władanej przez Raygara - władcę ciemności,\n pochłoniętego przez żądzę władzy. Jeżeli go nie powstrzymasz, świat opanują mroczne moce.\n	Uważaj jednak, na swojej drodze napotkasz wiele przeszkód, jak i wielu przeciwników!\n 								Strzeż się i powodzenia!\n\n			  Po lewej stronie ekranu znajduje się sekcja statystyk twojej postaci.\n			  Statystyki postaci jak i postępy dokonane w grze są automatycznie\n  zapisywane w momencie zamknięcia okna gry. Po zapisaniu gry kliknij przycisk kontynuuj\n		   		  w menu głównym, by powrócić do zapisanego stanu gry.\n 		  Żeby wyjść do menu głównego zamknij to okno, lub wciśnij klawisz Escape. \n										  Miłej zabawy!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);

										infoBG.loadFromFile("content/Graphics/locations/travel.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress += 1;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 1:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										city.city[0][0].setString(L"Witaj w mieście! Podczas swojej podróży będziesz odwiedzał lokacje tego typu.\n    Będąc w mieście, możesz wykorzystać złoto zdobyte podczas podróży.\n		    Za jego pomocą zwiększysz statystyki swojej postaci,\n	    co pomoże Ci w dalszej wędrówce. Wydawaj złoto rozsądnie.\n      Na początek otrzymasz 100 szt. złota na ulepszenie statystyk.\n		  Gdy wydasz już całe złoto, lub zechcesz opuścić miasto\n 				     kliknij przycisk \"Opuść miasto\".");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Opuść miasto");

										cityBG.loadFromFile("content/Graphics/cities/city.jpg");
										cityBackground.setTexture(&cityBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.gold += 100;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 2:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"	  Po opuszczeniu miasta wyruszyłeś na południe w poszukiwaniu drogi do Xendoru.\nNapotykasz podróżnika i pytasz go o drogę, jednak ten tylko parska pod nosem z kpiną.\n 			Po chwili jednak odpowiada by odpuścić, jeśli życie Ci miłe.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Groźba? Nie daruję!");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Nie poddam się dopóki nie pokonam Raygara");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 3;
														player.opt = 0;
														doOnce = true;
														break;
													case 2:
														player.progress = 4;
														player.opt = 1;
														player.gold += 50;
														player.expEarned = 1000;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 3:
									if (doOnce)
									{
										enemy.level = 1;
										enemy.attack = 8;
										enemy.defense = 4;
										enemy.maxHP = 60;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Podróżnik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/traveler.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) + 40);
														player.expEarned = 1000;
														player.gold += player.goldFound;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														player.progress = 4;
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else
												{
													button.play();
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 4:
									if (doOnce)
									{
										if (player.opt)
										{
											info.info[0].setString(L"Podróżnik widząc Twoją reakcję stwierdził, że może jesteś kimś kto może odmienić losy wszystkich.\n 						Podarował Ci 50 szt. złota i odszedł w milczeniu.\n 										Uzyskałeś poziom 2.\n                    Uzyskując kolejny poziom doświadczenia twoja postać odnawia\n                       50% maksymalnego zdrowia i 20 punktów maks. zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"       Po pokonaniu przeciwnika odnalazłeś przy nim " + to_string(player.goldFound) + L" szt. złota. \n      Ostatnim tchnieniem podróżnik wyszeptał, że popełniasz błąd\n                i czyha na Ciebie wielkie niebezpieczeństwo.\n                            Uzyskałeś poziom 2.\n          Uzyskując kolejny poziom doświadczenia twoja postać\nodnawia 50% maksymalnego zdrowia i zyskuje 20 punktów maks. zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress = 5;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 5:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"Zbliża się noc. Idąc szlakiem zauważasz, że zza wzgórza nadchodzą\n 				wściekli i pijani chłopi z pochodniami.\nCzyżby podróżnik słusznie ostrzegał Cię przed niebezpieczeństwem?\n							Co zamierzasz?");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Zejdź chłopom z drogi, rozbij obóz i odpocznij do rana");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Spróbuj zapytać o drogę");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 7;
														player.opt = 0;
														player.HP += 0.5 * player.maxHP;
														if (player.HP > player.maxHP)
														{
															player.HP = player.maxHP;
														}
														player.expEarned = 250;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress = 6;
														player.opt = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 6:
									if (doOnce)
									{
										enemy.level = 2;
										enemy.attack = 5;
										enemy.defense = 5;
										enemy.maxHP = 300;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Wściekli chłopi (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/peasants.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) + 50);
														player.gold += player.goldFound;
														player.progress = 7;
														player.expEarned = 500;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 7:
									if (doOnce)
									{
										if (player.opt)
										{
											info.info[0].setString(L"		    Po pokonaniu przeciwników odnalazłeś przy nich " + to_string(player.goldFound) + L" szt. złota.\nJeden z chłopów wyznał Ci, że pare dni drogi stąd znajduje się miasto Ravenstrand,\n			  w którym podobno przebywa jeden z posłańców Raygara.\n 	   Postanowiłeś niezwłocznie tam wyruszyć i odnaleźć owego wojownika.");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L" Podczas gdy odpoczywałeś niedaleko szlaku, usłyszałeś rozmowę przechodzących chłopów.\nMówili o pewnym wojowniku, który przybył do miasta Ravenstrand odległego o pare dni stąd.\n							   Postanowiłeś sprawdzić ten trop.");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										doOnce2 = true;
										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/travel3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 8:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"   W oddali widać już mury Ravenstrand, jednak pozostało jeszcze trochę drogi do przebycia.\nDostrzegasz, że idąc wzdłuż ścieżki będziesz musiał przeprawić się przez posterunek bandytów.\n    Istnieje szansa, że uda się go ominąć zbaczając lekko ze ścieżki przechodząc przez las. ");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Podążaj ścieżką");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Przejdź przez las");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/travel6.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 9;
														player.expEarned = 100;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress = 12;
														player.expEarned = 200;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 9:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"                     Zdecydowałeś się przejść przez obóz bandytów.\nPo drodze na ścieżce znalazłeś fragment dziwnego pancerza, postanowiłeś go założyć.\n                              Twoja obrona wzrosła o 2.\n    Wchodząc do obozu zauważyłeś, że obecni tam bandyci właśnie kogoś rabują.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Stań w obronie ofiary złodziei");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Spróbuj przejść przez obóz niezauważony");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/forestoutpost.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.defense += 2;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 10;
														player.opt = 0;
														doOnce = true;
														break;
													case 2:
														player.opt = 1;
														player.progress = 11;
														player.expEarned = 450;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 10:
									if (doOnce)
									{
										enemy.level = 2;
										enemy.attack = 8;
										enemy.defense = 6;
										enemy.maxHP = 250;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Grupa bandytów (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/bandits.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/forestoutpost.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) + 50);
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 800;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 11:
									if (doOnce)
									{
										if (player.opt)
										{
											info.info[0].setString(L"Udało Ci się przemknąć przez obóz, jednak ofiara bandytów nie przeżyła.\n                        Ravenstrand jest już o krok.");
										}
										else
										{
											info.info[0].setString(L"  Udało Ci się pokonać bandytów i uratować ich ofiarę.\nOcalony człowiek w podzięce podarował Ci 80 szt. złota.\n               Ravenstrand jest już o krok.");
										}
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/forestoutpost.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress = 16;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 12:
									if (doOnce)
									{
										info.info[0].setString(L"Udało Ci się ominąć obóz bandytów, jednak czujesz, że ktoś lub coś Cię obserwuje.\n                                 Miej się na baczności.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/forest.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 13:
									if (doOnce)
									{
										info.info[0].setString(L"Słychać dźwięk łamanych gałęzi, jesteś atakowany!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/forest.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 14:
									if (doOnce)
									{
										enemy.level = 3;
										enemy.attack = 12;
										enemy.defense = 1;
										enemy.maxHP = 150;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Goblin zabójca (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/goblinassassin.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/forest.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)));
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 750;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 15:
									if (doOnce)
									{
										info.info[0].setString(L"                  Udało Ci się przeżyć atak skrytobójcy.\nOdgarniając kolejne gałęzie dostrzegasz, że Ravenstrand jest już o krok.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;
										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/forest.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 16: // miasto
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										city.city[0][0].setString(L"Ravenstrand");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Szukaj wojownika Raygara");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/ravenstrand.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 17:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"  Udałeś się do karczmy w której podobno przebywał Sathur.\n         Takie imię nosi wojownik, którego poszukujesz.\nChwilę po wejściu do gospody zaczepia Cię tajemniczy mężczyzna.\n    Zaproponował dużo złota i informacje na temat Sathura\n          w zamian za oczyszczenie Jaskiń Goblinów ");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Wypytaj karczmarza o Sathura");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Przyjmij zlecenie");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/cities/ravenstrand.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 18;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress = 19;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 18:
									if (doOnce)
									{
										info.info[0].setString(L"Karczmarz potwierdził, że przebywał tu niedawno Sathur, ale opuścił już Ravenstrand.\n    W czasie rozmowy karczmarz dowiedział się, że szukany przez Ciebie człowiek\n              wyruszył szlakiem w stronę Xendoru przez Dolinę Gigantów.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/cities/ravenstrand.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress = 28;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 19:
									if (doOnce)
									{
										info.info[0].setString(L"                        Mężczyzna wskazał Ci jak dostać się do jaskiń\ni wręczył Ci dwie mikstury zdrowia. Zachowaj ostrożność, jaskinie to niebezpieczne miejsce!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/cave.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.potions += 2;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 20:
									if (doOnce)
									{
										info.info[0].setString(L"Po wejściu do jaskiń od razu czujesz, że to niebezpieczne miejsce.\n     Słychać charczenie i szepty wywodzące się z ciemności.\n                  Nadciągają pierwsi przeciwnicy!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/cave.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 21:
									if (doOnce)
									{
										enemy.level = 3;
										enemy.attack = 10;
										enemy.defense = 6;
										enemy.maxHP = 300;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Gobliny z procami (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/goblinslingshot.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/cave3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) - 50);
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 500;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 22:
									if (doOnce)
									{
										info.info[0].setString(L"Pokonałeś przeciwników, ale nadciągają kolejni!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/cave3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 23:
									if (doOnce)
									{
										enemy.level = 3;
										enemy.attack = 10;
										enemy.defense = 10;
										enemy.maxHP = 350;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Gobliny wojownicy (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/goblins.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/cave3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) - 40);
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 500;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 24:
									if (doOnce)
									{
										info.info[0].setString(L"              Wydaje się, że to już wszyscy przeciwnicy.\nCo to? Przechodząc do dalszej części jaskini dostrzegasz jakby... tron?\n     Podchodzisz bliżej, a Twoim oczom ukazuje się król goblinów!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/cave2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 25:
									if (doOnce)
									{
										enemy.level = 5;
										enemy.attack = 10;
										enemy.defense = 10;
										enemy.maxHP = 750;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Król goblinów (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/goblinking.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/cave2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) - 30);
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 1000;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 26:
									if (doOnce)
									{
										info.info[0].setString(L"Po powrocie z jaskiń do Ravenstrand, czeka na Ciebie zleceniodawca.\n         Zgodnie z umową wynagrodził Cię 250 szt. złota.\n      Wyjawił także, że Sathur wyruszył do Doliny Gigantów.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/cities/ravenstrand.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.gold += 250;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 27:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										city.city[0][0].setString(L"Ravenstrand");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Opuść miasto");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/ravenstrand.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 28:
									if (doOnce)
									{

										twoChoice.twoChoice[0].setString(L"       Informatorzy z miasta doprowadzili Cię do Doliny Gigantów.\n  W oddali widać ślady po rozstawionym obozie. Może to obóz Sathura?\n             Przed obozem napotykasz na opuszczone ruiny.\nMoże wewnatrz znajdują się jakieś łupy? Mogą to być również przeciwniy.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Przeszukaj opuszczoną wieżę");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Od razu zbadaj obóz");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/travel8.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.expEarned = 150;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress += 2;
														player.expEarned = 350;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 29:
									if (doOnce)
									{
										info.info[0].setString(L"W wieży udało Ci się znaleźć fragmenty pancerza, miecz pokryty runami,\n                    50 szt. złota i 3 mikstury zdrowia.\n                        Obrona i atak wzrosły o 3.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/tower.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.attack += 3;
											player.defense += 3;
											player.gold += 50;
											player.potions += 3;
											player.update();
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 30:
									if (doOnce)
									{
										info.info[0].setString(L"    Kontynuujesz podążanie tropem Sathura, jednak ślady\nwydają się być zbyt wyraźne, zupełnie jakby to była pułapka.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/travel2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 31:
									if (doOnce)
									{
										info.info[0].setString(L"Twoim oczom ukazuje się uzbrojony wojownik w czerwieni. To musi być Sathur.\n        Zapytał Cię dlaczego go szukasz. Wyjawiłeś mu swoje plany.\n    Sathur zaśmiał się szyderczo i stwierdził, że nigdy Ci się to nie uda.\n           Jako prawa ręka Raygar jest zmuszony Cię zniszczyć!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/travel2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 32:
									if (doOnce)
									{
										enemy.level = 6;
										enemy.attack = 20;
										enemy.defense = 12;
										enemy.maxHP = 1000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Sathur (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/mage.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/travel2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)) + 100);
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 2000;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 33:
									if (doOnce)
									{
										info.info[0].setString(L"                 Sathur poległ broniąc swojego mistrza.\nWśród jego rzeczy odnalazłeś mapę, która prowadzi do siedziby Raygara.\n           Czeka Cię dalsza wędrówka. Kolejnym celem podróży\n              według mapy jest zniszczone miasto Midborn.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;
										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/travel14.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 34:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"                         Od Midborn dzieli Cię już tylko rzeka.\n               Z odległości Midborn wcale nie wygląda na zniszczone.\n                           Ludzie byli w stanie je odbudować?\n   Woda w rzece wydaje się mieć dziwny kolor, nie widać co znajduje się pod taflą.\n                           Przy brzegu stoi zacumowana łódź.\nW oddali widzisz, że po przedarciu się przez las możesz przekroczyć rzekę mostem.\n              Lasy w tej krainie są szczególnie niebezpiecznym miejscem,\n           szczególnie w okresie pełni księżyca, więc przekroczenie puszczy\n                      może okazać się trudniejsze niż się wydaje.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Przepłyń rzekę");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Przejdź przez puszczę");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/river.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.expEarned = 250;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress = 38;
														player.expEarned = 250;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 35:
									if (doOnce)
									{
										info.info[0].setString(L"     Jesteś już w połowie szerokości rzeki, gdy wokół łódki spod powierzchni wody\nzaczynają wydostawać się pęcherze powietrza, woda staje się coraz bardziej niespokojna.\n                           To na pewno jakieś wodne monstrum!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/travel10.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 36:
									if (doOnce)
									{
										enemy.level = 7;
										enemy.attack = 16;
										enemy.defense = 24;
										enemy.maxHP = 800;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Wodny potwór (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/watermonster.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/travel10.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)));
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 750;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 37:
									if (doOnce)
									{
										info.info[0].setString(L"        Pokonałeś wodnego potwora. Możesz już dopłynąć do drugiego brzegu.\n  Po dokładnym przyjrzeniu zanuważyłeś, że potwór miał na sobie świecący amulet.\nZabierając go czujesz płynącą z niego moc. Nic dziwnego, że przeciwnik był tak silny.\n                                  Obrona wzrasta o 5.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/travel10.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.defense += 5;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress = 41;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 38:
									if (doOnce)
									{
										info.info[0].setString(L"   Zapada zmrok. Z głębi puszczy słychać donośne wycie.\n  Czujesz dreszcze na plecach i powoli zaczynasz żałować\ndecyzji o przejściu przez las, ale już za późno by zawrócić.\n      Słychać coraz głośniejsze wycie, coś się zbliża!");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/forest2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 39:
									if (doOnce)
									{
										enemy.level = 6;
										enemy.attack = 26;
										enemy.defense = 8;
										enemy.maxHP = 900;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Wilkołak (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/monster.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/forest2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = (rand() % (3 * player.progress) + (3 * (player.progress + player.level)));
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 750;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 40:
									if (doOnce)
									{
										info.info[0].setString(L"    Pokonałeś wilkołaka. Możesz już przejść przez most na drugą stronę brzegu.\n  Po dokładnym przyjrzeniu zanuważyłeś, że potwór miał na sobie świecący amulet.\nZabierając go czujesz płynącą z niego moc. Nic dziwnego, że przeciwnik był tak silny.\n                                  Atak wzrasta o 5.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/forest2.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.attack += 5;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress = 41;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 41:
									if (doOnce)
									{
										info.info[0].setString(L"Zbliżasz się do Midbornu. Przeciwnicy tutaj są silniejsi niż pozostali.\n         Musi to mieć związek ze zbliżaniem się do Raygara.\n    Midborn wygląda na bardzo żywe, jak na opuszczone miasto.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/plains.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 42:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										city.city[0][0].setString(L"Midborn");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Przejdź do karczmy");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/city4.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 43:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"Po starciu z Sathurem i po utrudnieniach na szlaku masz okazję odpocząć przed dalszą podrózą,\n    lub też rozejrzeć się za jakimiś nowymi zleceniami, by ulepszyć swój sprzęt i statystyki.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Odpocznij i ruszaj dalej tropem Raygara");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Zapytaj karczmarza o pracę");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/cities/tavern.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 58;
														player.expEarned = 500;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress++;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 44:
									if (doOnce)
									{
										info.info[0].setString(L" Karczmarz opowiedział Ci o kopalniach żelaza, w których zalęgają się potwory.\n     Było już wielu śmiałków, którzy podejmowali się oczyszczenia kopalni,\n                jednak po jakimś czasie potwory zawsze wracały.\n             Za oczyszczenie kopalni zaoferowano Ci 250 szt. złota.\nMożliwe jest, że po pewnym czasie od wykonania, zlecenie znów będzie dostępne.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/cities/tavern.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 45:
									if (doOnce)
									{
										info.info[0].setString(L"Po wejściu do kopalni rozlegają się trzaski uderzających o siebie kości.\n                         Nadchodzą przeciwnicy.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 46:
									if (doOnce)
									{
										enemy.level = 8;
										enemy.attack = 20;
										enemy.defense = 16;
										enemy.maxHP = 500;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Szkielet wojownik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton4.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 32;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 47:
									if (doOnce)
									{
										enemy.level = 8;
										enemy.attack = 32;
										enemy.defense = 12;
										enemy.maxHP = 400;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Szkielet łucznik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton2.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce2 = true;
										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 24;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 48:
									if (doOnce)
									{
										info.info[0].setString(L"Udało Ci się pokonać szkielety, ale to jeszcze nie koniec.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 49:
									if (doOnce)
									{
										enemy.level = 9;
										enemy.attack = 40;
										enemy.defense = 20;
										enemy.maxHP = 600;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Elitarny szkielet (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 40;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 50:
									if (doOnce)
									{
										info.info[0].setString(L"Twoim oczom ukazuje się przejście nad przepaścią, a za nim szkrzynia. Może zawiera jakieś łupy?\n                       Na drodze do przejścia staje największy ze szkieletów.\n            Żeby dostać się do skrzyni i oczyścić kopalnię będziesz musiał go pokonać.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 51:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 40;
										enemy.defense = 30;
										enemy.maxHP = 1500;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Król szkieletów (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeletonking.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 50;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 800;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 52:
									if (doOnce)
									{
										info.info[0].setString(L"Wróciłeś do miasta odebrać nagrodę.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/cities/city4.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 53:
									if (doOnce)
									{
										info.info[0].setString(L"Karczmarz zgodnie z umową wręcza Ci 250 szt. złota\n    i oferuje, żebyś odpoczął po ciężkim zadaniu.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;
										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/cities/tavern.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.gold += 250;
											player.HP += player.maxHP * 0.5;
											if (player.HP > player.maxHP)
											{
												player.HP = player.maxHP;
											}
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 54:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										city.city[0][0].setString(L"Midborn");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Opuść miasto");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/city4.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 55:
									if (doOnce)
									{

										twoChoice.twoChoice[0].setString(L"Wychodząc z miasta zaczepia Cię jakiś podejrzany mężczyzna.\n            Zażądał, byś dał mu 100 szt. złota.\n     Jeśli tego nie zrobisz prawdopodobnie zaatakuje Cię.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Zapłać 100 szt. złota");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Odmów złodziejowi");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/cities/city2.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												if (player.gold >= 100)
													twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												if (player.gold >= 100)
													twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														if (player.gold >= 100)
														{
															player.gold -= 100;
															player.progress = 58;
															player.expEarned = 300;
															player.exp += player.expEarned;
															while (player.exp >= 1000)
															{
																player.exp -= 1000;
																player.level++;
																player.maxHP += 20;
																player.HP += 20;
																player.HP += 0.5 * player.maxHP;
																if (player.HP > player.maxHP)
																{
																	player.HP = player.maxHP;
																}
															}
															doOnce = true;
														}
														break;
													case 2:
														player.progress++;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									if (player.gold < 100)
									{
										twoChoice.optionSelected = 2;
										twoChoice.twoChoice[2].setFillColor(Color::Red);
										twoChoice.twoChoice[1].setFillColor(Color(128, 128, 128, 255));
										if (localGamePosition.x < twoChoice.twoChoice[1].getPosition().x - twoChoice.twoChoice[1].getLocalBounds().width / 2.0f && localGamePosition.x > twoChoice.twoChoice[1].getPosition().x + twoChoice.twoChoice[1].getLocalBounds().width / 2.0f && localGamePosition.y < twoChoice.twoChoice[1].getPosition().y - twoChoice.twoChoice[1].getLocalBounds().height / 2.0f && localGamePosition.y > twoChoice.twoChoice[1].getPosition().y + twoChoice.twoChoice[1].getLocalBounds().height / 2.0f)
										{
											twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
										}
									}
									else
									{
										twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									}
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 56:
									if (doOnce)
									{
										enemy.level = 5;
										enemy.attack = 27;
										enemy.defense = 19;
										enemy.maxHP = 400;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Złodziej (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/thief.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/cities/city2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 84;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 57:
									if (doOnce)
									{
										info.info[0].setString(L"      Pokonany złodziej, w akcie zadośćuczynienia\npodarował Ci 84 szt. złota i przeprosił, że Cię zaczepił.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/cities/city2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 58:
									if (doOnce)
									{
										info.info[0].setString(L"           Jesteś już bardzo blisko dotarcia do Raygara.\nPozostało Ci jedynie przebić się przez bramę terytorium Xendoru,\n                    strzeżoną przez najemników.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/travel5.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 59:
									if (doOnce)
									{

										twoChoice.twoChoice[0].setString(L"Docierasz do wrot Xendoru. Zza flank wyłaniają się opancerzeni najemnicy.\nPrzestrzegają, że jeśli podejdziesz bliżej to będą zmuszeni Cię zaatakować.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"   Spróbuj przejść przez wrot\n(walka z czterema przeciwnikami)");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Zawróć");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										save(player, "content/Checkpoint.txt");

										twoChoiceBG.loadFromFile("content/Graphics/locations/gates.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 72;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress++;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 60:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");
										city.city[0][0].setString(L"Midborn");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Przejdź do karczmy");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/city4.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress++;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 61:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										twoChoice.twoChoice[0].setString(L"Jeśli uważasz, że jesteś gotowy walczyć z Raygarem i jego najemnikami ruszaj do bram.\n                   Jeśli nie jesteś jeszcze gotowy, przyjmij zlecenie.\n      Zdobędziesz doświadczenie i złoto, które pomoże Ci w kolejnych starciach.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Wróć do bram Xendoru");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Przyjmij zlecenie o kopalniach");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/cities/tavern.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 59;
														player.expEarned = 500;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														doOnce = true;
														break;
													case 2:
														player.progress++;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 62:
									if (doOnce)
									{
										info.info[0].setString(L" Karczmarz opowiedział Ci o kopalniach żelaza, w których zalęgają się potwory.\n     Było już wielu śmiałków, którzy podejmowali się oczyszczenia kopalni,\n                jednak po jakimś czasie potwory zawsze wracały.\n             Za oczyszczenie kopalni zaoferowano Ci 100 szt. złota.\nMożliwe jest, że po pewnym czasie od wykonania, zlecenie znów będzie dostępne.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/cities/tavern.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 63:
									if (doOnce)
									{
										info.info[0].setString(L"Po wejściu do kopalni rozlegają się trzaski uderzających o siebie kości.\n                         Nadchodzą przeciwnicy.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 64:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 24;
										enemy.defense = 24;
										enemy.maxHP = 750;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Szkielet wojownik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton4.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 32;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 65:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 40;
										enemy.defense = 12;
										enemy.maxHP = 800;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Szkielet łucznik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton2.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce2 = true;
										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 40;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 66:
									if (doOnce)
									{
										info.info[0].setString(L"Udało Ci się pokonać szkielety, ale to jeszcze nie koniec.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 67:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 40;
										enemy.defense = 20;
										enemy.maxHP = 800;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Elitarny szkielet (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeleton.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines2.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 60;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 400;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 68:
									if (doOnce)
									{
										info.info[0].setString(L"Twoim oczom ukazuje się przejście nad przepaścią, a za nim szkrzynia. Może zawiera jakieś łupy?\n                       Na drodze do przejścia staje największy ze szkieletów.\n            Żeby dostać się do skrzyni i oczyścić kopalnię będziesz musiał go pokonać.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/mines3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 69:
									if (doOnce)
									{
										enemy.level = 12;
										enemy.attack = 40;
										enemy.defense = 30;
										enemy.maxHP = 3000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Król szkieletów (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/skeletonking.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/mines3.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 100;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 800;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 70:
									if (doOnce)
									{
										info.info[0].setString(L"Wróciłeś do miasta odebrać nagrodę.\n    Otrzymujesz 100 szt. złota.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										if (!loaded || loadedProgress < player.progress)
											player.gold += 100;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/cities/city4.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 71:
									if (doOnce)
									{
										save(player, "content/Checkpoint.txt");

										city.city[0][0].setString(L"Midborn");
										city.city[0][0].setOrigin(city.city[0][0].getLocalBounds().width / 2.0f, city.city[0][0].getLocalBounds().height / 2.0f);
										city.city[0][0].setPosition(950, 150);

										city.city[3][0].setString(L"Wróć do bram Xendoru");
										city.city[3][0].setOrigin(city.city[3][0].getLocalBounds().width / 2.0f, city.city[3][0].getLocalBounds().height / 2.0f);
										city.city[3][0].setPosition(950, 750);

										cityBG.loadFromFile("content/Graphics/cities/city4.jpg");
										cityBackground.setTexture(&cityBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												city.MoveUp();
												break;
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												city.MoveDown();
												break;
											}
											if ((aevent.key.code == Keyboard::A || aevent.key.code == Keyboard::D || aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::Right) && aevent.type != Event::MouseButtonPressed)
											{
												city.MoveSide();
												break;
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && city.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												switch (city.optionSelected)
												{
													case 1:
														if (player.gold >= 10)
														{
															if (city.valueSelected == 0)
															{
																player.gold -= 10;
																player.attack++;
																player.update();
															}
															else
															{
																player.gold -= 10;
																player.defense++;
																player.update();
															}
															goldSound.play();
														}
														break;
													case 2:
														if (city.valueSelected == 0 && player.gold >= 10)
														{
															player.gold -= 10;
															if (player.HP == player.maxHP)
															{
																player.HP += 10;
															}
															player.maxHP += 10;
															player.update();
															goldSound.play();
														}
														else if (city.valueSelected == 1 && player.gold >= 50)
														{
															player.gold -= 50;
															player.potions++;
															player.update();
															goldSound.play();
														}
														break;
													case 3:
														if (city.valueSelected == 0)
														{
															button.play();
															player.progress = 59;
															save(player, "content/Save.txt");
															doOnce = true;
														}
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									city.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(cityBackground);
									city.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 72:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 45;
										enemy.defense = 45;
										enemy.maxHP = 1000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Najemnik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/mercenary.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/gates.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
										doOnce2 = true;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 50;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 73:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 45;
										enemy.defense = 45;
										enemy.maxHP = 1000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Najemnik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/mercenary2.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/gates.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
										doOnce2 = true;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 50;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 74:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 45;
										enemy.defense = 45;
										enemy.maxHP = 1000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Najemnik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/mercenary3.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/gates.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
										doOnce2 = true;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 50;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 75:
									if (doOnce)
									{
										enemy.level = 10;
										enemy.attack = 45;
										enemy.defense = 45;
										enemy.maxHP = 1000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Najemnik (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/mercenary4.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/gates.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
										doOnce2 = true;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 50;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 300;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 76:
									if (doOnce)
									{
										info.info[0].setString(L"       Bramy Xendoru sforsowane.\nPrzejście do zamku Raygara stoi otworem.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/gates.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 77:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Jesteś wyczerpany po walce z najemnikami. Za chwilę zapadnie noc.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź prosto do zamku");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Przenocuj i wyrusz rano");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/raygarcastle.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress = 81;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 78:
									if (doOnce)
									{
										info.info[0].setString(L"        Udało Ci się chwilę odpocząć, ale obudziły Cię dziwne dźwięki i szelesty.\nWokół Ciebie unosi się jakaś zjawa. To był zły pomysł, żeby nocować tak blisko zamku.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/raygarcastle.jpg");
										infoBackground.setTexture(&infoBG);

										if (!loaded || loadedProgress < player.progress)
										{
											player.HP = player.maxHP;
										}

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 79:
									if (doOnce)
									{
										enemy.level = 11;
										enemy.attack = 60;
										enemy.defense = 10;
										enemy.maxHP = 1200;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Zjawa (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/wraith.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/raygarcastle.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.goldFound = 0;
														player.gold += player.goldFound;
														player.progress++;
														player.expEarned = 150;
														player.exp += player.expEarned;
														while (player.exp >= 1000)
														{
															player.exp -= 1000;
															player.level++;
															player.maxHP += 20;
															player.HP += 20;
															player.HP += 0.5 * player.maxHP;
															if (player.HP > player.maxHP)
															{
																player.HP = player.maxHP;
															}
														}
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 80:
									if (doOnce)
									{
										info.info[0].setString(L"Postanowiłeś wyruszyć do zamku, zanim coś znowu Cię zaatakuje.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/raygarcastle.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 81:
									if (doOnce)
									{
										info.info[0].setString(L"Wchodząc do zamku o mało nie wchodzisz w pułapkę.\n          Zamek musi być pełen takich sideł.\n             Lepiej uważnie stawiać kroki.");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 82:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Wybierz, którym przejściem chcesz przejść.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź w lewo");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Idź w prawo");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/castle.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.opt = 0;
														player.HP -= player.HP * 0.05;
														if (player.HP <= 0)
															player.HP = 1;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														player.opt = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 83:
									if (doOnce)
									{
										if (player.opt == 0)
										{
											info.info[0].setString(L"Wpadłeś w pułapkę! Tracisz 5% zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"Udało Ci się uniknąć pułapek!");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 84:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Wybierz, którym przejściem chcesz przejść.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź w lewo");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Idź w prawo");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/castle2.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.opt = 0;
														player.HP -= player.HP * 0.05;
														if (player.HP <= 0)
															player.HP = 1;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														player.opt = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 85:
									if (doOnce)
									{
										if (player.opt == 0)
										{
											info.info[0].setString(L"Wpadłeś w pułapkę! Tracisz 5% zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"Udało Ci się uniknąć pułapek!");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle2.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 86:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Wybierz, którym przejściem chcesz przejść.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź w lewo");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Idź w prawo");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/castle3.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.opt = 1;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														player.opt = 0;
														player.HP -= player.HP * 0.05;
														if (player.HP <= 0)
															player.HP = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 87:
									if (doOnce)
									{
										if (player.opt == 0)
										{
											info.info[0].setString(L"Wpadłeś w pułapkę! Tracisz 5% zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"Udało Ci się uniknąć pułapek!");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle3.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 88:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Wybierz, którym przejściem chcesz przejść.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź w lewo");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Idź w prawo");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/castle4.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.opt = 0;
														player.HP -= player.HP * 0.05;
														if (player.HP <= 0)
															player.HP = 1;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														player.opt = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 89:
									if (doOnce)
									{
										if (player.opt == 0)
										{
											info.info[0].setString(L"Wpadłeś w pułapkę! Tracisz 5% zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"Udało Ci się uniknąć pułapek!");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle4.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 90:
									if (doOnce)
									{
										twoChoice.twoChoice[0].setString(L"Wybierz, którym przejściem chcesz przejść.");
										twoChoice.twoChoice[0].setOrigin(twoChoice.twoChoice[0].getLocalBounds().width / 2.0f, twoChoice.twoChoice[0].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[0].setPosition(950, 200);

										twoChoice.twoChoice[1].setString(L"Idź w lewo");
										twoChoice.twoChoice[1].setOrigin(twoChoice.twoChoice[1].getLocalBounds().width / 2.0f, twoChoice.twoChoice[1].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[1].setPosition(950, 650);

										twoChoice.twoChoice[2].setString(L"Idź w prawo");
										twoChoice.twoChoice[2].setOrigin(twoChoice.twoChoice[2].getLocalBounds().width / 2.0f, twoChoice.twoChoice[2].getLocalBounds().height / 2.0f);
										twoChoice.twoChoice[2].setPosition(950, 700);

										twoChoiceBG.loadFromFile("content/Graphics/locations/castle6.jpg");
										twoChoiceBackground.setTexture(&twoChoiceBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												twoChoice.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												twoChoice.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (twoChoice.optionSelected)
												{
													case 1:
														player.progress++;
														player.opt = 1;
														doOnce = true;
														break;
													case 2:
														player.progress++;
														player.opt = 0;
														player.HP -= player.HP * 0.05;
														if (player.HP <= 0)
															player.HP = 1;
														doOnce = true;
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									twoChoice.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(twoChoiceBackground);
									twoChoice.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 91:
									if (doOnce)
									{
										if (player.opt == 0)
										{
											info.info[0].setString(L"Wpadłeś w pułapkę! Tracisz 5% zdrowia");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}
										else
										{
											info.info[0].setString(L"Udało Ci się uniknąć pułapek!");
											info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
											info.info[0].setPosition(950, 300);
										}

										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle6.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 92:
									if (doOnce)
									{
										info.info[0].setString(L"Po przeprawie przez korytarze pełne pułapek w końcu docierasz do sali tronowej.\n                           Raygar już tam na Ciebie czeka.\n                     Zdołasz go pokonać i odmienić losy świata?");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										infoBG.loadFromFile("content/Graphics/locations/castle5.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													player.progress++;
													doOnce = true;
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 93:
									if (doOnce)
									{
										enemy.level = 15;
										enemy.attack = 50;
										enemy.defense = 50;
										enemy.maxHP = 5000;
										enemy.HP = enemy.maxHP;

										fight.fight[0].setString(L"Pomiń");
										fight.fight[0].setOrigin(fight.fight[0].getLocalBounds().width / 2.0f, fight.fight[0].getLocalBounds().height / 2.0f);
										fight.fight[0].setPosition(800, 700);
										fight.skip = false;
										fight.fight[5].setString(L"Raygar (Poziom: " + to_string(enemy.level) + ")");

										EnemyAvatarTexture.loadFromFile("content/Graphics/enemies/raygar.jpg");
										EnemyAvatar.setTexture(&EnemyAvatarTexture);

										fightBG.loadFromFile("content/Graphics/locations/castle5.jpg");
										fightBackground.setTexture(&fightBG);

										fight.update(playerPointer, enemyPointer);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && fight.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												if (fight.optionSelected == 0 && (player.HP <= 0 || enemy.HP <= 0))
												{
													button.play();
													doOnce = true;
													if (player.HP > 0)
													{
														player.progress++;
														save(player, "content/Save.txt");
													}
													else
													{
														fightLostSound.play();
														player.progress = 9999 /*Game Over*/;
													}
												}
												else if (fight.optionSelected == 0 && (player.HP > 0 && enemy.HP > 0))
												{
													fight.skip = true;
												}
											}
										}
									}
									Gra.clear();

									Gra.draw(fightBackground);
									Gra.draw(PlayerAvatar);
									Gra.draw(EnemyAvatar);

									if (enemy.HP <= 0)
									{
										if (doOnce2)
										{
											fightWonSound.play();
											doOnce2 = false;
										}
									}
									fight.draw(Gra, playerPointer, enemyPointer, swordSoundPointer, potionSoundPointer);

									Opcje.close();
									Gra.display();
									break;
								case 94:
									if (doOnce)
									{
										info.info[0].setString(L"Udało Ci się pokonać Raygara i wyzwolić świat!\n  Gratulacje, ukończyłeś grę Knight's Quest!\n\n\n            Twórca: Łukasz Wróbel");
										info.info[0].setOrigin(info.info[0].getLocalBounds().width / 2.0f, info.info[0].getLocalBounds().height / 2.0f);
										info.info[0].setPosition(950, 300);
										doOnce2 = true;

										save(player, "content/Checkpoint.txt");

										infoBG.loadFromFile("content/Graphics/locations/endgame.jpg");
										infoBackground.setTexture(&infoBG);

										doOnce = false;
									}
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && info.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												if (info.optionSelected == 1)
												{
													save(player, "content/Save.txt");
													Gra.close();
												}
											}
										}
									}
									Gra.clear();

									info.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(infoBackground);
									info.draw(Gra);

									player.update();
									Gra.draw(playerBackground);
									player.draw(Gra);

									Opcje.close();
									Gra.display();
									break;
								case 9999:
									while (Gra.pollEvent(aevent))
									{
										if (aevent.type == Event::Closed)
										{
											save(player, "content/Save.txt");
											Gra.close();
										}
										if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
										{
											if (aevent.key.code == Keyboard::Escape)
											{
												save(player, "content/Save.txt");
												Gra.close();
											}
											if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
											{
												gameOver.MoveUp();
											}
											if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
											{
												gameOver.MoveDown();
											}
											if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && gameOver.MouseSelect(localGamePosition.x, localGamePosition.y)))
											{
												button.play();
												switch (gameOver.optionSelected)
												{
													case 1:
														load(playerPointer, "content/Checkpoint.txt");
														break;
													case 2:
														load(playerPointer, "content/Checkpoint.txt");
														save(player, "content/Save.txt");
														Gra.close();
														break;
													default:
														break;
												}
											}
										}
									}
									Gra.clear();

									gameOver.MouseSelect(localGamePosition.x, localGamePosition.y);
									Gra.draw(gameOverBackground);
									gameOver.draw(Gra);

									Opcje.close();
									Gra.display();
									doOnce = true;
									break;
								default:
									player.progress = 0;
									break;
							}
						}
					}
					if (menuChosen == 2)
					{
						while (Opcje.isOpen())
						{
							Event aevent;
							Vector2i localOptionsPosition = sf::Mouse::getPosition(Opcje);
							while (Opcje.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Opcje.close();
									save(player, "content/Save.txt");
								}
								if (aevent.type == Event::KeyPressed || aevent.type == Event::MouseButtonPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Opcje.close();
										save(player, "content/Save.txt");
									}
									if (aevent.key.code == Keyboard::Return || aevent.key.code == Keyboard::E || (aevent.type == Event::MouseButtonPressed && options.MouseSelect(localOptionsPosition.x, localOptionsPosition.y)))
									{
										button.play();
										switch (options.optionSelected)
										{
											case 1:
												if (options.valueSelected == 0)
												{
													soundVol = 5;
													options.soundUpdate(L"Aktualny stan dźwięku: Włączony");
												}
												else
												{
													soundVol = 0;
													options.soundUpdate(L"Aktualny stan dźwięku: Wyłączony");
												}
												button.setVolume(soundVol);
												goldSound.setVolume(soundVol);
												soundTrack.setVolume(soundVol);
												swordSound.setVolume(soundVol);
												fightWonSound.setVolume(soundVol);
												fightLostSound.setVolume(soundVol);
												potionSound.setVolume(soundVol);
												break;
											case 3:
												switch (options.valueSelected)
												{
													case 0:
														player.difficulty = 0;
														options.difficultyUpdate(L"Aktualny poziom trudności: Łatwy");
														player.player[7].setString(L"Aktualny poziom trudności: Łatwy");
														player.update();
														diffSet = true;
														break;
													case 1:
														player.difficulty = 1;
														options.difficultyUpdate(L"Aktualny poziom trudności: Normalny");
														player.player[7].setString(L"Aktualny poziom trudności: Normalny");
														player.update();
														diffSet = true;
														break;
													case 2:
														player.difficulty = 2;
														options.difficultyUpdate(L"Aktualny poziom trudności: Trudny");
														player.player[7].setString(L"Aktualny poziom trudności: Trudny");
														player.update();
														diffSet = true;
														break;
													default:
														/*
														player.difficulty = 1;
														options.difficultyUpdate(L"Aktualny poziom trudności: Normalny");
														player.player[7].setString(L"Aktualny poziom trudności: Normalny");
														player.update();
														diffSet = true;
														*/
														break;
												}
												break;
											case 4:
												Opcje.close();
												save(player, "content/Save.txt");
												break;
											default:
												break;
										}
									}
									if (aevent.key.code == Keyboard::Up || aevent.key.code == Keyboard::W)
									{
										options.MoveUp();
										break;
									}
									if (aevent.key.code == Keyboard::Down || aevent.key.code == Keyboard::S)
									{
										options.MoveDown();
										break;
									}
									if ((aevent.key.code == Keyboard::Left || aevent.key.code == Keyboard::A) && aevent.type != Event::MouseButtonPressed)
									{
										options.MoveSide("left");
										break;
									}
									if ((aevent.key.code == Keyboard::Right || aevent.key.code == Keyboard::D) && aevent.type != Event::MouseButtonPressed)
									{
										options.MoveSide("right");
										break;
									}
								}
							}
							options.MouseSelect(localOptionsPosition.x, localOptionsPosition.y);
							Gra.close();
							Opcje.clear();
							Opcje.draw(backgroundOptions);
							options.draw(Opcje);
							Opcje.display();
						}
					}
					if (menuChosen == 3)
					{
						MENU.close();
					}
					break;
				}
			}
		}
		mainMenu.MouseSelect(localPosition.x, localPosition.y);
		MENU.clear();
		MENU.draw(background);
		mainMenu.draw(MENU);
		MENU.display();
	}
	return 1;
}

void save(Player player, String path)
{
	fstream plik;
	plik.open(path, ios::trunc | ios::out);
	if (plik.good())
	{
		plik << player.progress << endl;
		plik << player.difficulty << endl;
		plik << player.attack << endl;
		plik << player.defense << endl;
		plik << player.maxHP << endl;
		plik << player.HP << endl;
		plik << player.gold << endl;
		plik << player.goldFound << endl;
		plik << player.level << endl;
		plik << player.expEarned << endl;
		plik << player.opt << endl;
		plik << player.potions << endl;
	}
	plik.close();
}

void load(Player* player, String path)
{
	fstream plik;
	plik.open(path, ios::in);
	string buffer;
	if (plik.good())
	{
		std::getline(plik, buffer);
		if (buffer != "")
		{
			player->progress = stoi(buffer);
			std::getline(plik, buffer);
			player->difficulty = stoi(buffer);
			std::getline(plik, buffer);
			player->attack = stoi(buffer);
			std::getline(plik, buffer);
			player->defense = stoi(buffer);
			std::getline(plik, buffer);
			player->maxHP = stoi(buffer);
			std::getline(plik, buffer);
			player->HP = stoi(buffer);
			std::getline(plik, buffer);
			player->gold = stoi(buffer);
			std::getline(plik, buffer);
			player->goldFound = stoi(buffer);
			std::getline(plik, buffer);
			player->level = stoi(buffer);
			std::getline(plik, buffer);
			player->expEarned = stoi(buffer);
			std::getline(plik, buffer);
			player->opt = stoi(buffer);
			std::getline(plik, buffer);
			player->potions = stoi(buffer);
		}
		else
		{
			cout << endl
				 << "Plik zapisu pusty!" << endl;
			player->progress = 0;
			player->difficulty = 1;
			player->attack = 10;
			player->defense = 10;
			player->maxHP = 100;
			player->HP = player->maxHP;
			player->gold = 0;
			player->level = 1;
			player->goldFound = 0;
			player->expEarned = 0;
		}
	}
	else
	{
		cout << endl
			 << L"Nie udało się otworzyć pliku!" << endl;
	}
	plik.close();
	player->update();
}

/* Łącznie projekt liczy 9 523 linii kodu */