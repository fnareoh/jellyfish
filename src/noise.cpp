#include "noise.hpp"


std::vector<std::vector<std::vector<double>>> Gradient;
int xmin, xmax, ymin, ymax;

void init_perlin(double x_min, double x_max, double y_min, double y_max)
{
    extern std::vector<std::vector<std::vector<double>>> Gradient;
    extern int xmin, xmax, ymin, ymax;

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(0, 1);

    xmin = floor(x_min);
    xmax = ceil(x_max);
    ymin = floor(y_min);
    ymax = ceil(y_max);

    int xm = xmax - xmin + 1;
    int ym = ymax - ymin + 1;

    Gradient = std::vector<std::vector<std::vector<double>>>(
        xm, std::vector<std::vector<double>>(
            ym, std::vector<double>(2)
        )
    );

    for (int x = 0 ; x < xm ; x++) {
        for (int y = 0 ; y < ym ; y++) {
            double xv = distribution(generator);
            double yv = distribution(generator);

            Gradient[x][y][0] = xv / (std::abs(xv) + std::abs(yv));
            Gradient[x][y][1] = yv / (std::abs(xv) + std::abs(yv));
        }
    }
}

// Function to linearly interpolate between a0 and a1
// Weight w should be in the range [0.0, 1.0]
double lerp(double a0, double a1, double w)
{
    return (1.0 - w)*a0 + w*a1;

    // as an alternative, this slightly faster equivalent formula can be used:
    // return a0 + w*(a1 - a0);
}

// Computes the dot product of the distance and gradient vectors.
double dotGridGradient(int ix, int iy, double x, double y)
{

    // Precomputed (or otherwise) gradient vectors at each grid node
    extern std::vector<std::vector<std::vector<double>>> Gradient;
    extern int xmin, ymin;

    // Compute the distance vector
    double dx = x - (double)ix;
    double dy = y - (double)iy;

    // Compute the dot-product
    return (dx * Gradient[ix-xmin][iy-ymin][0] + dy * Gradient[ix-xmin][iy-ymin][1]);
}

// Compute Perlin noise at coordinates x, y
double perlin(double x, double y)
{

    // Determine grid cell coordinates
    int x0 = int(x);
    int x1 = x0 + 1;
    int y0 = int(y);
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    double sx = x - (double)x0;
    double sy = y - (double)y0;

    // Interpolate between grid point gradients
    double n0, n1, ix0, ix1, value;
    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = lerp(n0, n1, sx);
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = lerp(n0, n1, sx);
    value = lerp(ix0, ix1, sy);

    return value;
}
