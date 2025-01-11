
#ifndef __FRACTALS_INCLUDE_FRACTALS_H__
#define __FRACTALS_INCLUDE_FRACTALS_H__

#include <SFML/Graphics.hpp>
#include <complex>
#include <thread>
#include <vector>

namespace my {
    class MandelbrotFractal
    {
    public:
        MandelbrotFractal(int width, int height, double zoom, std::complex<double> center, int max_iterations);

    public:
        void      generateFractal(sf::Image& image);
        sf::Color getColor(int iterations) const;
        int       mandelbrot(const std::complex<double>& c) const;

        inline double getZoom() const
        {
            return m_zoom;
        }
        inline void setZoom(double zoom)
        {
            m_zoom = zoom;
        }

        inline std::complex<double> getCenter() const
        {
            return m_center;
        }

        inline void setCenter(std::complex<double> center)
        {
            m_center = center;
        }

    private:
        void generateFractalSection(sf::Image& image, int startRow, int endRow) const;

    private:
        int                  m_width, m_height;
        double               m_zoom;
        std::complex<double> m_center;
        int                  m_max_iterations;
    };
} // namespace my

#endif // __FRACTALS_INCLUDE_FRACTALS_H__
