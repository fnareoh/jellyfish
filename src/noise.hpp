#pragma once

#include <chrono>
#include <cmath>
#include <random>
#include <vector>


void init_perlin(double x_min, double x_max, double y_min, double y_max);
double perlin(double x, double y);
