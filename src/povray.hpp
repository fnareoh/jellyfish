#pragma once

#include <iomanip>
#include <iostream>
#include <map>

#include "mesh.hpp"


/** Outputs a mesh as a povray mesh format */
void povray_output_mesh(std::ostream& stream, const Mesh& mesh);

/** Outputs a mesh as a povray mesh2 format */
void povray_output_mesh2(std::ostream& stream, const Mesh& mesh);
