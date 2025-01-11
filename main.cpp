#include <SFML/Graphics.hpp>

#include <complex>
#include <thread>
#include <vector>

#include "include/MandelbrotFractal.h"

int main()
{
    const int        width  = 800;
    const int        height = 600;
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Fractal with Multi-threading");

    sf::Image image;
    image.create(width, height, sf::Color::Black);

    const int            max_iterations = 500;
    double               zoom           = 300;
    std::complex<double> center(-0.7, 0.0);

    my::MandelbrotFractal fractal(width, height, zoom, center, max_iterations);
    fractal.generateFractal(image);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseWheelScrolled)
            {
                zoom *= (event.mouseWheelScroll.delta > 0) ? 1.1 : 0.9;
                fractal.setZoom(zoom);
                fractal.generateFractal(image);
                texture.loadFromImage(image);
                sprite.setTexture(texture);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                double panAmount = 20 / fractal.getZoom();
                if (event.key.code == sf::Keyboard::Up)
                    center.imag(center.imag() - panAmount);
                else if (event.key.code == sf::Keyboard::Down)
                    center.imag(center.imag() + panAmount);
                else if (event.key.code == sf::Keyboard::Left)
                    center.real(center.real() - panAmount);
                else if (event.key.code == sf::Keyboard::Right)
                    center.real(center.real() + panAmount);

                fractal.setCenter(center);
                fractal.generateFractal(image);
                texture.loadFromImage(image);
                sprite.setTexture(texture);
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
