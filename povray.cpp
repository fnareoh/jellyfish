#include "povray.hpp"


void povray_face_output(std::ostream& stream, const MeshFace& face)
{
    stream << "  triangle { ";

    double x1, y1, z1, x2, y2, z2, x3, y3, z3;

    std::tie(x1, y1, z1) = * std::get<0>(face);
    std::tie(x2, y2, z2) = * std::get<1>(face);
    std::tie(x3, y3, z3) = * std::get<2>(face);

    stream << std::setprecision(6)
           << '<' << x1 << ',' << y1 << ',' << z1 << '>'
           << '<' << x2 << ',' << y2 << ',' << z2 << '>'
           << '<' << x3 << ',' << y3 << ',' << z3 << '>';

    stream << " }" << std::endl;
}

void povray_output(std::ostream& stream, const Mesh& mesh)
{
    stream << "mesh {" << std::endl;

    for (const auto& face: mesh.faces)
        povray_face_output(stream, face);

    stream << '}' << std::endl;
}
