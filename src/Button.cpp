#include "../include/Button.h"

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& text)
{
    m_buttonShape.setPosition(position);
    m_buttonShape.setSize(size);
    m_buttonShape.setFillColor(sf::Color::Blue);

    if (!m_font.loadFromFile("path/to/font.ttf"))
    {
        // Handle error
    }

    m_buttonText.setFont(m_font);
    m_buttonText.setString(text);
    m_buttonText.setCharacterSize(24);
    m_buttonText.setFillColor(sf::Color::White);
    m_buttonText.setPosition(position.x + (size.x - m_buttonText.getLocalBounds().width) / 2,
                             position.y + (size.y - m_buttonText.getLocalBounds().height) / 2);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(m_buttonShape);
    window.draw(m_buttonText);
}

bool Button::isClicked(const sf::Vector2f& mousePosition) const
{
    return m_buttonShape.getGlobalBounds().contains(mousePosition);
}