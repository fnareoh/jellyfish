#pragma once

#include <array>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <math.h>
#include <vector>

#include "mesh.hpp"
#include "noise.hpp"
#include "stl.hpp"

constexpr double PI = 3.14159265358979323846;


Mesh sample_half_sphere(double pos_x, double pos_y, double pos_z,
	double r, double d_theta, double d_alpha, double squeeze);

Point3 ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double nb_step_alpha_i, double nb_step_alpha,
	double step_alpha, double step_theta);

Mesh jelly_shape(double pos_x, double pos_y, double pos_z,
	double r, double precision, double squeeze);

Mesh simple_tentacle(double len, double width, double pos_x,
	double pos_y, double  pos_z);

Point3 sinus_tentacles_ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze, double angle,
	double step_z, double step_theta, double attenuation);

Mesh sinus_tentacle(double angle, double pos_x, double pos_y,
	double  pos_z, double len, double width, double precision,
	double squeeze);

Point3 folded_tentacles_ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double step_alpha, double step_theta, double attenuation);

Mesh folded_tentacle(double pos_x, double pos_y, double  pos_z,
	double len, double width, double precision, double squeeze,
	double in);

std::vector<Mesh> jellyfish_simple(double pos_x, double pos_y, double pos_z,
	double squeeze);

std::vector<Mesh> jellyfish(double pos_x, double pos_y, double pos_z,
	double width_jelly, double width_tentacle, double squeeze);
