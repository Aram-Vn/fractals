
#include "../include/MandelbrotFractal.h"

namespace my {
    MandelbrotFractal::MandelbrotFractal(int width, int height, double zoom, std::complex<double> center,
                                         int max_iterations)
        : m_width(width),
          m_height(height),
          m_zoom(zoom),
          m_center(center),
          m_max_iterations(max_iterations)
    {
    }

    void MandelbrotFractal::generateFractal(sf::Image& image, bool colorful)
    {
        int                      numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        int                      rowsPerThread = m_height / numThreads;

        for (int i = 0; i < numThreads; ++i)
        {
            int startRow = i * rowsPerThread;
            int endRow   = (i == numThreads - 1) ? m_height : startRow + rowsPerThread;
            threads.emplace_back(&MandelbrotFractal::generateFractalSection, this, std::ref(image), startRow, endRow,
                                 colorful);
        }

        for (auto& t : threads)
        {
            t.join();
        }
    }

    void MandelbrotFractal::generateFractalSection(sf::Image& image, int startRow, int endRow, bool colorful) const
    {
        for (int x = 0; x < m_width; ++x)
        {
            for (int y = startRow; y < endRow; ++y)
            {
                std::complex<double> c((x - m_width / 2.0) / m_zoom + m_center.real(),
                                       (y - m_height / 2.0) / m_zoom + m_center.imag());
                int                  iterations = mandelbrot(c);
                sf::Color            color      = getColor(iterations, colorful);
                image.setPixel(x, y, color);
            }
        }
    }

    int MandelbrotFractal::mandelbrot(const std::complex<double>& c) const
    {
        std::complex<double> z = 0;
        int                  n = 0;
        while (abs(z) <= 2 && n < m_max_iterations)
        {
            z = z * z + c;
            ++n;
        }
        return n;
    }

    sf::Color MandelbrotFractal::getColor(int iterations, bool colorful) const
    {
        return colorful ? getColor_black_blue(iterations) : getColor_colorful(iterations);
    }

    sf::Color MandelbrotFractal::getColor_black_blue(int iterations) const
    {
        if (iterations == m_max_iterations)
        {
            return sf::Color::Black;
        }

        float t = static_cast<float>(iterations) / m_max_iterations;
        int   r = static_cast<int>(9 * (1 - t) * t * t * t * 255);
        int   g = static_cast<int>(15 * (1 - t) * (1 - t) * t * t * 255);
        int   b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

        return sf::Color(r, g, b);
    }

    sf::Color MandelbrotFractal::getColor_colorful(int iterations) const
    {
        if (iterations == m_max_iterations)
        {
            return sf::Color::Black;
        }

        int cycle = iterations % 12;

        switch (cycle)
        {
            case 0: return sf::Color(255, 0, 0);      // Red
            case 1: return sf::Color(255, 165, 0);    // Orange
            case 2: return sf::Color(255, 255, 0);    // Yellow
            case 3: return sf::Color(0, 255, 0);      // Green
            case 4: return sf::Color(0, 255, 255);    // Cyan
            case 5: return sf::Color(0, 0, 255);      // Blue
            case 6: return sf::Color(75, 0, 130);     // Indigo
            case 7: return sf::Color(238, 130, 238);  // Violet
            case 8: return sf::Color(255, 20, 147);   // Deep Pink
            case 9: return sf::Color(255, 105, 180);  // Hot Pink
            case 10: return sf::Color(255, 69, 0);    // Red-Orange
            case 11: return sf::Color(255, 255, 255); // White
            default: return sf::Color::Black;
        }
    }
} // namespace my
