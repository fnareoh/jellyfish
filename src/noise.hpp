#pragma once

#include <cmath>
#include <random>
#include <vector>


void init_perlin(double x_max, double y_max, int seed = 0);
double perlin(double x, double y);
