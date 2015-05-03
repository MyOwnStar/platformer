#include "Music/MusicSettings.h"
#include "MusicScreen.h"


MusicScreen::MusicScreen()
{}

MusicScreen::~MusicScreen()
{}

int MusicScreen::Run(sf::RenderWindow &window)
{
	sf::Event event;

	sf::Texture texture;
	if (!texture.loadFromFile("res/img/setScrMode_1280x1024.png"))
	{
		std::cerr << "Error loading fon" << std::endl;
		return (-1);
	}

	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::Font font;
	if (!font.loadFromFile("res/font/menuFont.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}

	sf::Music keyPressedSound;
	if (!keyPressedSound.openFromFile("res/music/keyPressed.ogg"))
	{
		std::cerr << "Error loading music" << std::endl;
		return (-1);
	}

	sf::Music okSound;
	if (!okSound.openFromFile("res/music/okSound.ogg"))
	{
		std::cerr << "Error loading music" << std::endl;
		return (-1);
	}

	sf::Text musicVolume;
	sf::FloatRect textRect;

	musicVolume.setFont(font);
	musicVolume.setString("Music Volume");
	musicVolume.setColor(sf::Color::Black);
	textRect = musicVolume.getLocalBounds();
	musicVolume.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	musicVolume.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150));

	sf::Font font1;
	if (!font1.loadFromFile("res/font/musicSet.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return (-1);
	}

	sf::Text selectedVolume;
	selectedVolume.setFont(font1);
	selectedVolume.setColor(sf::Color::Red);
	textRect = selectedVolume.getLocalBounds();
	selectedVolume.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	selectedVolume.setPosition(sf::Vector2f(window.getSize().x / 2.0f - 20, window.getSize().y / 2.0f - 55));


	float volume;
	float selection;

	MusicSettings musSet;
	musSet.getSoundSettings(volume);
	selection = volume;

	std::stringstream selectionStream;

	bool running = true;
	int menu = 0;

	while (running)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return (-1);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						return (3);
						break;

					case sf::Keyboard::Right:
						if (selection < 100)
						{
							selection += 5;
						}
						else
						{
							selection = 100;
						}
						break;

					case sf::Keyboard::Left:
						if (selection > 0)
						{
							selection -= 5;
						}
						break;

					case sf::Keyboard::Return:
							musSet.setSoundSettings(selection);
							return (3);
					default:
						break;
				}
			}
		}

		// Updating music volume
		selectedVolume.setString(selectionStream.str());
		selectionStream.str("");
		selectionStream << selection;

		window.clear();

		window.draw(sprite);
		window.draw(musicVolume);
		window.draw(selectedVolume);

		window.display();
	}

	return (-1);
}