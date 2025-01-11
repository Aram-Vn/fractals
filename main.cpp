#include "include/FractalWindow.h"

int main()
{
    const int width          = 800;
    const int height         = 600;
    const int max_iterations = 500;

    FractalWindow window(width, height, max_iterations);
    window.run();

    return 0;
}
