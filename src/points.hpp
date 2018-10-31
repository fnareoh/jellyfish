#pragma once

#include <cmath>
#include <tuple>


/**
 * Reprensentation of a 3D point.
 */
typedef std::tuple<double, double, double> Point3;


double norm(Point3 p);

/** Normalise a vector */
Point3 normalize(Point3 p);

Point3 sum(Point3 a, Point3 b);

Point3 mean(Point3 a, Point3 b, Point3 c);
