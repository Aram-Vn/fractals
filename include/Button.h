#ifndef __FRACTALS_INCLUDE_BUTTON_H__
#define __FRACTALS_INCLUDE_BUTTON_H__

#include <SFML/Graphics.hpp>

class Button
{
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text);

public:
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePosition) const;

private:
    sf::RectangleShape m_buttonShape;
    sf::Text           m_buttonText;
    sf::Font           m_font;
};

#endif // __FRACTALS_INCLUDE_BUTTON_H__