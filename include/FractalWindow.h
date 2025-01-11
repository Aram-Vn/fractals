#ifndef FRACTAL_WINDOW_H
#define FRACTAL_WINDOW_H

#include <SFML/Graphics.hpp>

#include <complex>

#include "MandelbrotFractal.h"

class FractalWindow
{
public:
    FractalWindow(int width, int height, int max_iterations);
    void run();

private:
    void handleEvents();
    void update();
    void render();

    int                  m_width, m_height;
    int                  m_max_iterations;
    double               m_zoom;
    std::complex<double> m_center;

    sf::RenderWindow m_window;
    sf::Image        m_image;
    sf::Texture      m_texture;
    sf::Sprite       m_sprite;

    my::MandelbrotFractal m_fractal;
};

#endif
