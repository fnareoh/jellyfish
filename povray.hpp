#pragma once

#include <iomanip>
#include <iostream>

#include "mesh.hpp"


/** Output a face as povray format */
void povray_face_output(std::ostream& stream, const MeshFace& face);

/** Outputs a mesh as a povray mesh format */
void povray_output(std::ostream& stream, const Mesh& mesh);
