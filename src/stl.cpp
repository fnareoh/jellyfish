#include "stl.hpp"


void stl_face_output_mesh(std::ostream& stream, const MeshFace& face)
{
    double x1, y1, z1, x2, y2, z2, x3, y3, z3;

    std::tie(x1, y1, z1) = * std::get<0>(face);
    std::tie(x2, y2, z2) = * std::get<1>(face);
    std::tie(x3, y3, z3) = * std::get<2>(face);


    stream << "    outer loop" << std::endl;
    stream << std::setprecision(6)
           << "      vertex " << x1 << ' ' << y1 << ' ' << z1 << std::endl
           << "      vertex " << x2 << ' ' << y2 << ' ' << z2 << std::endl
           << "      vertex " << x3 << ' ' << y3 << ' ' << z3 << std::endl;
    stream << "    endloop" << std::endl;
}

void stl_output_mesh(std::ostream& stream, const Mesh& mesh)
{
    stream << "solid " << std::endl;

    for (const auto& face : mesh.faces) {
        stream << "  facet " << std::endl;
        stl_face_output_mesh(stream, face);
        stream << "  endfacet" << std::endl;
    }

    stream << "endsolid" << std::endl;
}
