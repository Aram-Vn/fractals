#include "../include/FractalWindow.h"

FractalWindow::FractalWindow(int width, int height, int max_iterations)
    : m_width(width),
      m_height(height),
      m_max_iterations(max_iterations),
      m_zoom(300),
      m_center(-0.7, 0.0),
      m_window(sf::VideoMode(m_width, m_height), "Mandelbrot Fractal with Multi-threading"),
      m_fractal(m_width, m_height, m_zoom, m_center, m_max_iterations),
      m_lastInputTime(sf::Time::Zero),
      m_debounceTime(sf::seconds(0.9)),
      m_button1(sf::Vector2f(10, 10), sf::Vector2f(100, 50), "Standard"),
      m_button2(sf::Vector2f(120, 10), sf::Vector2f(100, 50), "Colorful"),
      m_useColorful(false)
{
    m_image.create(m_width, m_height, sf::Color::Black);
    m_fractal.generateFractal(m_image, m_useColorful);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
}

void FractalWindow::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            m_zoom *= (event.mouseWheelScroll.delta > 0) ? 1.1 : 0.9;
            m_fractal.setZoom(m_zoom);
            m_lastInputTime = m_clock.getElapsedTime();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
            if (m_button1.isClicked(mousePosition))
            {
                m_useColorful = false;
            }
            else if (m_button2.isClicked(mousePosition))
            {
                m_useColorful = true;
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            double panAmount = 20 / m_fractal.getZoom();
            if (event.key.code == sf::Keyboard::Up)
            {
                m_center.imag(m_center.imag() - panAmount);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                m_center.imag(m_center.imag() + panAmount);
            }
            else if (event.key.code == sf::Keyboard::Left)
            {
                m_center.real(m_center.real() - panAmount);
            }
            else if (event.key.code == sf::Keyboard::Right)
            {
                m_center.real(m_center.real() + panAmount);
            }

            m_fractal.setCenter(m_center);
            m_lastInputTime = m_clock.getElapsedTime();
        }
    }
}

void FractalWindow::update()
{
    debounceUpdate();
}

void FractalWindow::debounceUpdate()
{
    // Check if enough time has passed since the last input
    if (m_clock.getElapsedTime() - m_lastInputTime >= m_debounceTime)
    {
        m_fractal.generateFractal(m_image, m_useColorful);
        m_texture.loadFromImage(m_image);
        m_sprite.setTexture(m_texture);
        m_lastInputTime = m_clock.getElapsedTime();
    }
}

void FractalWindow::render()
{
    m_window.clear();
    m_window.draw(m_sprite);
    m_button1.draw(m_window);
    m_button2.draw(m_window);
    m_window.display();
}

void FractalWindow::run()
{
    while (m_window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}
