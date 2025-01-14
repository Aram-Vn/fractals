#ifndef __FRACTALS_INCLUDE_FRACTAL_WINDOW_H__
#define __FRACTALS_INCLUDE_FRACTAL_WINDOW_H__

#include "Button.h"
#include "MandelbrotFractal.h"
#include <SFML/Graphics.hpp>
#include <complex>

class FractalWindow
{
public:
    FractalWindow(int width, int height, int max_iterations);
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void debounceUpdate();

    int                  m_width, m_height;
    int                  m_max_iterations;
    double               m_zoom;
    std::complex<double> m_center;

    sf::RenderWindow m_window;
    sf::Image        m_image;
    sf::Texture      m_texture;
    sf::Sprite       m_sprite;

    my::MandelbrotFractal m_fractal;

    // Time tracking for debouncing
    sf::Clock      m_clock;
    sf::Time       m_lastInputTime;
    const sf::Time m_debounceTime;

    Button m_button1;
    Button m_button2;
    bool   m_useColorful;
};

#endif // __FRACTALS_INCLUDE_FRACTAL_WINDOW_H__