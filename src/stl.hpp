#pragma once

#include "mesh.hpp"

#include <iostream>


void stl_face_output_mesh(std::ostream& stream, const MeshFace& face);
void stl_output_mesh(std::ostream& stream, const Mesh& mesh);
