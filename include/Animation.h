#pragma once

#include <SFML/Graphics.hpp>

#include "macros.h"

class Animation
{
public:
    Animation();
    Animation(sf::Texture* texture, sf::Vector2u imageCount, int dir);
    void direction(int dir);
    void update(int row, sf::Time delta);

    sf::IntRect uvRect;

private:

    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage; 
    float m_elapsed;
    int m_dir;

};
