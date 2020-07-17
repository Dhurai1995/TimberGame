// Timeber Game!!!

#include<SFML\Graphics.hpp>
#include<sstream>

int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	// backgreoudn sprite

	sf::Texture texturebackground;
	texturebackground.loadFromFile("graphics/background.png");
	sf::Sprite spriteBackground;
	spriteBackground.setTexture(texturebackground);
	spriteBackground.setPosition(0, 0);

	// Tree sprite

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Prepare the bee

	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	bool beeActive = false;
	float beeSpeed = 0.0f;

	// Cloud
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	sf::Sprite spritecloud1;
	sf::Sprite spritecloud2;
	sf::Sprite spritecloud3;

	spritecloud1.setTexture(textureCloud);
	spritecloud2.setTexture(textureCloud);
	spritecloud3.setTexture(textureCloud);

	spritecloud1.setPosition(0, 0);
	spritecloud2.setPosition(0, 250);
	spritecloud3.setPosition(0, 500);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	sf::Clock clock;

	// Define a time bar

	sf::RectangleShape timeBar;
	float tbStartWidth = 400;
	float tbHeight = 80;
	timeBar.setSize(sf::Vector2f(tbStartWidth, tbHeight));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((1920 / 2.0) - tbStartWidth / 2, 980);

	sf::Time totalGameTime;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSec = tbStartWidth / timeRemaining;

	bool pause = false;

	// Get the score
	int score = 0;

	//LOAD THE FONT
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	//Iniate the text objects
	sf::Text messageText;
	sf::Text scoreText;

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press ENTER to start the game");
	scoreText.setString("Your score = 0");

	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	messageText.setCharacterSize(100);
	scoreText.setCharacterSize(50);

	//Positioning the texts in the screem

	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);


	while (window.isOpen())
	{
		/*
		Handle player input
		*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			pause = true;

			score = 0;
			timeRemaining = 6;
		}
		/*
		Update the scene
		*/

		if (pause)
		{
			sf::Time dt = clock.restart();

			// setup the bee
			if (!beeActive)
			{
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// Height
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else
			{
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

				if (spriteBee.getPosition().x < -100)
				{
					beeActive = false;
				}
			}

			// setup the Cloud animation

			if (!cloud1Active)
			{
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// Height
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spritecloud1.setPosition(2000, height);
				cloud1Active = true;
			}
			else
			{
				spritecloud1.setPosition(spritecloud1.getPosition().x - (cloud1Speed * dt.asSeconds()), spritecloud1.getPosition().y);

				if (spritecloud1.getPosition().x < -100)
				{
					cloud1Active = false;
				}
			}

			if (!cloud2Active)
			{
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				// Height
				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spritecloud2.setPosition(-200, height);
				cloud2Active = true;
			}
			else
			{
				spritecloud2.setPosition(spritecloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spritecloud2.getPosition().y);

				if (spritecloud2.getPosition().x > 1920)
				{
					cloud2Active = false;
				}
			}

			if (!cloud3Active)
			{
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				// Height
				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spritecloud3.setPosition(-200, height);
				cloud3Active = true;
			}
			else
			{
				spritecloud3.setPosition(spritecloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spritecloud3.getPosition().y);

				if (spritecloud3.getPosition().x > 1920)
				{
					cloud3Active = false;
				}
			}
		}

		//update the score values
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());

		/*
		draw the scene
		*/

		window.clear();

		//Draw our game scene here
		window.draw(spriteBackground);

		//cloud
		window.draw(spritecloud1);
		window.draw(spritecloud2);
		window.draw(spritecloud3);

		// Tree
		window.draw(spriteTree);

		//Bee
		window.draw(spriteBee);

		// Display the message and score text;
		window.draw(scoreText);

		if (!pause)
			window.draw(messageText);

		//Show everythin we just drew
		window.display();

	}
}