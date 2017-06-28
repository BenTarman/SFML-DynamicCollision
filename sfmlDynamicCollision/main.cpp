#include <SFML\Graphics.hpp>	

#include <iostream>

int main()
{
	//set constant framerate
	sf::RenderWindow window(sf::VideoMode(800, 600), "collision fun");
	window.setFramerateLimit(60);


	//ground will be modifiable for this demonstration to jump on top of box
	double ground = 550;

	//constant values that should apply to any dynamic body
	const float gravity = 1.0, jumpSpeed = 5.0, speed = 1.0;


	//player velocity
	sf::Vector2f playerVelocity(sf::Vector2f(0, 0));
	

	//player rectangle
	sf::RectangleShape player;
	player.setSize(sf::Vector2f(50, 50));
	player.setPosition(100, 100);
	player.setFillColor(sf::Color::Red);

	//box you can push
	sf::RectangleShape dynamicBody;
	dynamicBody.setSize(sf::Vector2f(50, 50));
	dynamicBody.setPosition(200, 500);
	dynamicBody.setFillColor(sf::Color::Blue);

	//bool (i think you need two bools to make them both independent events)



	//start game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}





		//collide from left side
		if (player.getPosition().x == (dynamicBody.getPosition().x - dynamicBody.getSize().x) && (player.getPosition().y == dynamicBody.getPosition().y))
		{

			dynamicBody.move(1, 0);
			
			//release push
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
			{
				player.setPosition(player.getPosition().x - 1.0, player.getPosition().y);
				
			}

		}

		//collide from right side
		if ((player.getPosition().x - player.getSize().x) == dynamicBody.getPosition().x && (player.getPosition().y == dynamicBody.getPosition().y))
		{

			dynamicBody.move(-1, 0);
		
			//release push
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
			{
				player.setPosition(player.getPosition().x + 1.0, player.getPosition().y);
				
			}

		}


		//jump on top of box
		if ((player.getPosition().y >= (dynamicBody.getPosition().y - dynamicBody.getSize().y) && player.getPosition().y < ground) && 
			
			(player.getPosition().x - player.getSize().x) < dynamicBody.getPosition().x && player.getPosition().x > (dynamicBody.getPosition().x - dynamicBody.getSize().x))
		{
			ground = 550 - dynamicBody.getSize().y;
		}
		else
			ground = 550; //reset ground
		
		
	






		//PLAYER MOVEMENT LOGIC

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			playerVelocity.x = -speed;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			playerVelocity.x = speed;
		else
			playerVelocity.x = 0;


		//PLYAER JUMP LOGIC
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			playerVelocity.y = -jumpSpeed;


		//update player position
		player.move(playerVelocity.x, playerVelocity.y);


		//GRAVITY LOGIC
		if ((player.getPosition().y + player.getSize().y) < ground)
		{
			playerVelocity.y += gravity;
		}

		else
		{
			player.setPosition(player.getPosition().x, ground - player.getSize().y);
		}


	

		//draw stuff
		window.clear();
		window.draw(player);
		window.draw(dynamicBody);
		window.display();
	}

	return 0;
}