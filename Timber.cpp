// Timeber Game!!!

#include<SFML\Graphics.hpp>
#include<sstream>
#include<SFML\Audio.hpp>

// Function declaration

void updateBranches(int seed);

const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPosition[NUM_BRANCHES];

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

	// Creating the tree branches

	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);

	// Creating the player
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");

	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT;

	// Gravestone
	sf::Texture textureGraveStone;
	textureGraveStone.loadFromFile("graphics/rip.png");
	sf::Sprite spriteGraveStone;
	spriteGraveStone.setTexture(textureGraveStone);
	spriteGraveStone.setPosition(600, 860);

	// Axe
	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// FLying log
	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	sf::Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	bool acceptInput = false;

	// Creating the sound objects;

	sf::SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	sf::Sound chop;
	chop.setBuffer(chopBuffer);

	sf::SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	sf::Sound death;
	death.setBuffer(deathBuffer);

	sf::SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	sf::Sound oot;
	oot.setBuffer(ootBuffer);

	while (window.isOpen())
	{
		/*
		Handle player input
		*/

		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::KeyReleased) && (event.type != pause))
			{
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			pause = true;

			score = 0;
			timeRemaining = 6;

			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				branchPosition[i] = side::NONE;
			}

			spriteGraveStone.setPosition(675, 2000);
			spritePlayer.setPosition(580, 720);

			acceptInput = true;
		}

		if (acceptInput)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerSide = side::RIGHT;
				score++;
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);
				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerSide = side::LEFT;
				score++;
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);
				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;

				chop.play();

			}

		}
		/*
		Update the scene
		*/

		if (pause)
		{
			sf::Time dt = clock.restart();

			// time bar setup
			timeRemaining -= dt.asSeconds();
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSec * timeRemaining, tbHeight));

			if (timeRemaining < 0.0f)
			{
				pause = false;

				messageText.setString("Game over");

				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				oot.play();
			}

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

			// Animating the tree branch
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPosition[i] == side::LEFT)
				{
					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPosition[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else
				{
					branches[i].setPosition(3000, height);
				}
			}

			// Flying log
			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x>2000)
				{
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			if (branchPosition[5] == playerSide)
			{
				pause = false;
			    acceptInput = false;

				spriteGraveStone.setPosition(525, 760);
				spritePlayer.setPosition(2000, 660);

				messageText.setString("Squiesheed");

				sf::FloatRect textrect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 /2.0f,1080 / 2.0f);

				death.play();

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

		// Drwing the branches
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		// Tree
		window.draw(spriteTree);

		// The player
		window.draw(spritePlayer);

		// The axe
		window.draw(spriteAxe);

		// FLying log
		window.draw(spriteLog);

		//Graveestone
		window.draw(spriteGraveStone);

		//Bee
		window.draw(spriteBee);

		// Display the message and score text;
		window.draw(scoreText);

		// Display timebar
		window.draw(timeBar);

		if (!pause)
			window.draw(messageText);

		//Show everythin we just drew
		window.display();

	}
}

// Funtion definition

void updateBranches(int seed)
{
	for (int j = NUM_BRANCHES - 1; j >= 0; j--)
		branchPosition[j] = branchPosition[j - 1];

	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r)
	{
	case 0:
		branchPosition[0] = side::LEFT;
		break;
	case 1:
		branchPosition[0] = side::RIGHT;
		break;
	default:
		branchPosition[0] = side::NONE;
		break;

	}
}