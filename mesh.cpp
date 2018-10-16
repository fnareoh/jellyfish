#include "mesh.hpp"


bool MeshCmp::operator()(const MeshFace &a, const MeshFace &b) const
{
    Point3 a1 = *std::get<0>(a);
    Point3 a2 = *std::get<1>(a);
    Point3 a3 = *std::get<2>(a);
    Point3 b1 = *std::get<0>(b);
    Point3 b2 = *std::get<1>(b);
    Point3 b3 = *std::get<2>(b);

    if (a1 < b1)
        return true;
    if (a1 == b1 && a2 < b2)
        return true;
    if (a1 == b1 && a2 == b2 && a3 < b3)
        return true;

    return false;
}


double filter_double(const double x)
{
    long long x_cpy = x * 1e6;
    return ((double) x_cpy) * 1e-6;
}

Point3 filter_point(const Point3 p)
{
    Point3 p_cpy;
    std::get<0>(p_cpy) = filter_double(std::get<0>(p));
    std::get<1>(p_cpy) = filter_double(std::get<1>(p));
    std::get<2>(p_cpy) = filter_double(std::get<2>(p));
    return p_cpy;
}

int Mesh::insert(const Point3 a, const Point3 b, const Point3 c)
{
    // Round up points
    Point3 a_cpy = filter_point(a);
    Point3 b_cpy = filter_point(b);
    Point3 c_cpy = filter_point(c);

    // Insert points in the set
    bool inserted_a, inserted_b, inserted_c;
    std::set<Point3>::iterator iter_a, iter_b, iter_c;

    std::tie(iter_a, inserted_a) = points.insert(a_cpy);
    std::tie(iter_b, inserted_b) = points.insert(b_cpy);
    std::tie(iter_c, inserted_c) = points.insert(c_cpy);

    // Check if new points have been created and that the triangle has a
    // non-empty area.
    int created_points_count = inserted_a + inserted_b + inserted_c;

    if (created_points_count == 0)
        return created_points_count;

    if (iter_a == iter_b || iter_b == iter_c || iter_c == iter_a)
        return created_points_count;

    // Insert the face
    faces.insert({iter_a, iter_b, iter_c});
    return created_points_count;
}
