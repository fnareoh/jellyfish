#pragma once

#include "points.hpp"

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <tuple>


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

    void recompute_normals();

    /** Output the mesh as a list of triangles */
    friend std::ostream& operator<<(std::ostream&, const Mesh&);

    /** Output the mesh for povray */
    friend void stl_output_mesh(std::ostream&, Mesh);
    friend void povray_output_mesh(std::ostream&, const Mesh&);
    friend void povray_output_mesh2(std::ostream&, Mesh);

private:
    std::set<Point3> points;
    std::set<MeshFace, MeshCmp> faces;
    std::map<MeshFace, Point3, MeshCmp> face_normals;
    std::map<Point3, Point3> node_normals;
};
