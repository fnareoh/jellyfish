#include "povray.hpp"


void povray_face_output_mesh(std::ostream& stream, const MeshFace& face)
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

void povray_output_mesh(std::ostream& stream, const Mesh& mesh)
{
    stream << "mesh {" << std::endl;

    for (const auto& face: mesh.faces)
        povray_face_output_mesh(stream, face);

    stream << std::endl;
    stream << "  #include \"jellyfish_properties.inc\"" << std::endl;
    stream << '}' << std::endl;
}

void povray_output_mesh2(std::ostream& stream, const Mesh& mesh)
{
    stream << "mesh2 {" << std::endl;

    stream << "  vertex_vectors {" << std::endl;
    stream << "    " << mesh.points.size() << "," << std::endl;
    stream << "    ";

    // Output and index vertices
    std::map<Point3, size_t> point_index;
    size_t point_counter = 0;

    for (const Point3& point: mesh.points) {
        double x, y, z;
        std::tie(x, y, z) = point;

        point_index[point] = point_counter;
        point_counter++;

        stream << std::setprecision(6) << '<' << x << ',' << y << ',' << z << "> ";
    }

    stream << std::endl << "  }" << std::endl;

    // Output faces
    size_t mesh_counter = 0;

    stream << "  face_indices {" << std::endl;
    stream << "    " << mesh.faces.size() << "," << std::endl;
    stream << "    ";

    for (const MeshFace& face: mesh.faces) {
        mesh_counter++;

        const auto& a = std::get<0>(face);
        const auto& b = std::get<1>(face);
        const auto& c = std::get<2>(face);

        stream << '<' << point_index[*a] << ','
                      << point_index[*b] << ','
                      << point_index[*c] << "> ";
    }

    stream << std::endl << "  }" << std::endl << std::endl;

    // Meta informations
    stream << "  #include \"jellyfish_properties.inc\"" << std::endl;
    stream << '}' << std::endl;
}
