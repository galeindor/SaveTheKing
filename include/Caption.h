#pragma once
#include <string>
#include "macros.h"
#include "Resources.h"

class Caption
{
public:
	Caption();
	~Caption();

	void updateTime(float timeToAdd); // add amount of time to the timer
	void updateLevel(); // increase the level
	void updateLives(int number); // update number of lives
	
	float getTime() const; //get current time left
	int getLives() const; // get current number of lives
	void resetTime(); // reset the timer to 0
	void draw(sf::RenderWindow&); 

	// print an end messege ( next level / lose / victory)
	void printMessege(const sf::String text, sf::RenderWindow& window);

	int HandleClick(const sf::Vector2f location);

private:

	bool Clicked(int index, const sf::Vector2f location);


	// set the text settings and set the position based on i
	void setText(sf::Text& text , int i );

	sf::Clock m_timer;
	float m_stageTime;
	int m_level;
	int m_lives;

	sf::Text m_stageTimeText;
	sf::Text m_levelText;
	sf::Text m_livesLeft;

	sf::Texture m_hearts;
};