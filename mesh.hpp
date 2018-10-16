#pragma once

#include <iomanip>
#include <iostream>
#include <set>
#include <tuple>


/**
 * Reprensentation of a 3D point.
 */
typedef std::tuple<double, double, double> Point3;


/**
 * A face is represented by three iterators pointing to its vertices.
 * TODO: use something more generic than a set iterator ?
 */
typedef std::tuple<std::set<Point3>::iterator, std::set<Point3>::iterator, std::set<Point3>::iterator> MeshFace;

struct MeshCmp {
    bool operator()(const MeshFace &a, const MeshFace &b) const;
};

/**
 * Main class to represent a mesh.
 * Points will be stored up to a precision of 1e-6.
 */
class Mesh
{
public:
    /** Create an empty mesh */
    Mesh() = default;

    /** Adds a new triangle into the mesh */
    int insert(const Point3 a, const Point3 b, const Point3 c);

    /** Output the mesh as a list of triangles */
    std::ostream& operator<<(std::ostream& stream) const;

private:
    std::set<Point3> points;
    std::set<MeshFace, MeshCmp> faces;
};
