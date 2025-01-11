
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

    void MandelbrotFractal::generateFractal(sf::Image& image)
    {
        int                      numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        int                      rowsPerThread = m_height / numThreads;

        for (int i = 0; i < numThreads; ++i)
        {
            int startRow = i * rowsPerThread;
            int endRow   = (i == numThreads - 1) ? m_height : startRow + rowsPerThread;
            threads.emplace_back(&MandelbrotFractal::generateFractalSection, this, std::ref(image), startRow, endRow);
        }

        for (auto& t : threads)
        {
            t.join();
        }
    }

    void MandelbrotFractal::generateFractalSection(sf::Image& image, int startRow, int endRow) const
    {
        for (int x = 0; x < m_width; ++x)
        {
            for (int y = startRow; y < endRow; ++y)
            {
                std::complex<double> c((x - m_width / 2.0) / m_zoom + m_center.real(),
                                       (y - m_height / 2.0) / m_zoom + m_center.imag());
                int                  iterations = mandelbrot(c);
                sf::Color            color      = getColor(iterations);
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

    sf::Color MandelbrotFractal::getColor(int iterations) const
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
} // namespace my
