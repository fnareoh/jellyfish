#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

#include "mesh.hpp"

# define PI           3.14159265358979323846


// d_theta and d_alpha are angles in radient.
Mesh sample_half_sphere(double pos_x, double pos_y, double pos_z,
					 double r, double d_theta, double d_alpha,
					 double squeeze){
	Mesh mesh_half_sphere;
	double nb_step_alpha = PI/(2*d_alpha);
	for(int i=0; i*d_alpha < PI/2; i++){
		for(int j=0; j*d_theta < 2*PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double d_a = std::min(d_alpha, PI/2-i*d_alpha);
			double r_comp_i = r*(1+ squeeze*((nb_step_alpha-i)/nb_step_alpha));
			double r_comp_i_plus = r*(1+ squeeze*((nb_step_alpha-i-1)/nb_step_alpha));
			Point3 a = {
				pos_x + r_comp_i*cos(i*d_alpha)*cos(j*d_theta),
				pos_y + r_comp_i*cos(i*d_alpha)*sin(j*d_theta),
				pos_z + r_comp_i*sin(i*d_alpha)
			};

			Point3 b = {
				pos_x + r_comp_i*cos(i*d_alpha)*cos(j*d_theta+d_t),
				pos_y + r_comp_i*cos(i*d_alpha)*sin(j*d_theta+d_t),
				pos_z + r_comp_i*sin(i*d_alpha)
			};

			Point3 c = {
				pos_x + r_comp_i_plus*cos(i*d_alpha+d_a)*cos(j*d_theta),
				pos_y + r_comp_i_plus*cos(i*d_alpha+d_a)*sin(j*d_theta),
				pos_z + r_comp_i_plus*sin(i*d_alpha+d_a)
			};

			Point3 d = {
				pos_x + r_comp_i_plus*cos(i*d_alpha+d_a)*cos(j*d_theta+d_t),
				pos_y + r_comp_i_plus*cos(i*d_alpha+d_a)*sin(j*d_theta+d_t),
				pos_z + r_comp_i_plus*sin(i*d_alpha+d_a)
			};

			mesh_half_sphere.insert(a,b,c);
			mesh_half_sphere.insert(b,c,d);
		}
	}
	return mesh_half_sphere;
}

Mesh simple_tentacle(double len, double width, double pos_x, double pos_y){
	Mesh tentacles;
	std::vector<double> r_pos{-0.5*width,0.5*width};
	std::vector<Point3> point_high;
	std::vector<Point3> point_low;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			point_high.push_back({pos_x + r_pos[i], pos_y + r_pos[j],0});
			point_low.push_back({pos_x + r_pos[i], pos_y + r_pos[j],-len});
		}
	}
	tentacles.insert(point_high[0],point_high[1],point_high[2]);
	tentacles.insert(point_high[1],point_high[2],point_high[3]);


	tentacles.insert(point_low[0],point_low[1],point_low[2]);
	tentacles.insert(point_low[1],point_low[2],point_low[3]);

	tentacles.insert(point_high[0],point_high[1],point_low[0]);
	tentacles.insert(point_low[0],point_low[1],point_high[1]);

	tentacles.insert(point_high[2],point_high[3],point_low[2]);
	tentacles.insert(point_low[2],point_low[3],point_high[3]);

	tentacles.insert(point_high[0],point_high[2],point_low[0]);
	tentacles.insert(point_low[0],point_low[2],point_high[2]);

	tentacles.insert(point_high[1],point_high[3],point_low[1]);
	tentacles.insert(point_low[1],point_low[3],point_high[3]);


	return tentacles;
}

int main() {
	povray_output_mesh(std::cout, sample_half_sphere(0,0,0,5, PI/50, PI/50, -0.2));
	povray_output_mesh(std::cout, simple_tentacle(7, 1, 0, 0));
	povray_output_mesh(std::cout, simple_tentacle(4, 0.5, 1, 1));
	povray_output_mesh(std::cout, simple_tentacle(4, 0.5, -1, 1));
	povray_output_mesh(std::cout, simple_tentacle(4, 0.5, 1, -1));
	povray_output_mesh(std::cout, simple_tentacle(4, 0.5, -1, -1));
	return 0;
}
