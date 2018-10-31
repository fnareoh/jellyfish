#include "points.hpp"


double norm(Point3 p)
{
    return std::abs(std::get<0>(p)) + std::abs(std::get<1>(p)) + std::abs(std::get<2>(p));
}

Point3 normalize(Point3 p)
{
    const double n = norm(p);
    double x, y, z;
    std::tie(x, y, z) = p;
    return std::make_tuple(x / n, y / n, z / n);
}

Point3 sum(Point3 a, Point3 b)
{
    return std::make_tuple(
        std::get<0>(a) + std::get<0>(b),
        std::get<1>(a) + std::get<1>(b),
        std::get<2>(a) + std::get<2>(b)
    );
}

Point3 mean(Point3 a, Point3 b, Point3 c)
{
    Point3 s = sum(a, sum(b, c));
    return std::make_tuple(
        std::get<0>(s) / 3,
        std::get<1>(s) / 3,
        std::get<2>(s) / 3
    );
}
