#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "macros.h"
#include "Animation.h"

class Resources
{
public:
	~Resources();
	static Resources& instance();

	sf::Texture* getTexture(char c);
	sf::Texture* getTexture(int i , int j);
	sf::Texture* getTexture(int i);
	sf::Texture* getBackground(int index);
	sf::RectangleShape* getPauseButtons(int index);
	sf::Font* getFont();
	void drawPauseScreen(sf::RenderWindow& window);
	void playMusic();
	void playSound(int index);
	void setVolume();
	void setAnimation(int i ,sf::Time deltaTime, sf::Sprite& player , int dir);

private:
	Resources();
	Resources(const Resources&) = default;
	Resources& operator=(const Resources&) = default;

	sf::SoundBuffer m_buffers[NUM_OF_SOUNDS];
	sf::Sound m_sounds[NUM_OF_SOUNDS];
	sf::Music m_music;

	void loadTextures();
	void loadBuffers();
	void loadBackground();
	void setPauseScreen();
	void SetButtons();

	sf::RectangleShape m_pauseWindow;
	sf::RectangleShape m_pauseButtons[MENU_BUTTONS];
	sf::Text m_pauseText;

	sf::Texture m_pauseTextures[MENU_BUTTONS];

	sf::Texture m_textures[NUM_OF_PICS][DIRECTIONS];
	std::vector < sf::Texture > m_bg;
	sf::Font m_font;

	Animation m_animation[5];

};

