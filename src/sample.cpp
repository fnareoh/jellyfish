#include <algorithm>
#include <iostream>
#include <math.h>
#include <cmath>
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


Mesh jelly_shape(double pos_x, double pos_y, double pos_z,
					 double r, double d_theta, double d_alpha,
					 double squeeze){
	Mesh mesh_half_sphere;
	double nb_step_alpha = PI/(2*d_alpha);
	for(int i=0; i*d_alpha < PI/2; i++){
		for(int j=0; j*d_theta < 2*PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double d_a = std::min(d_alpha, PI/2-i*d_alpha);

			double skirt_status = 0.3*pow((double)round((double) 6*((double)j*d_theta)/PI) - (double) 6*((double)j*d_theta)/PI,2.0);
			double skirt_status_plus = 0.3*pow((double)round((double) 6*((double)j*d_theta+d_t)/PI) - (double) 6*((double)j*d_theta+d_t)/PI,2.0);
			
			double squeeze_status = (1+ squeeze*((nb_step_alpha-i)/nb_step_alpha));
			double squeeze_status_plus = (1+ squeeze*((nb_step_alpha-i-1)/nb_step_alpha));

			//std::cout << (1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status) << std::endl;
			//std::cout << (1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status_plus) << std::endl;

			Point3 a = {
				pos_x + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status)*cos(i*d_alpha)*cos(j*d_theta),
				pos_y + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status)*cos(i*d_alpha)*sin(j*d_theta),
				pos_z + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status)*sin(i*d_alpha)
			};

			Point3 b = {
				pos_x + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status_plus)*cos(i*d_alpha)*cos(j*d_theta+d_t),
				pos_y + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status_plus)*cos(i*d_alpha)*sin(j*d_theta+d_t),
				pos_z + r*squeeze_status*(1-((nb_step_alpha-i)/nb_step_alpha)*skirt_status_plus)*sin(i*d_alpha)
			};

			Point3 c = {
				pos_x + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status)*cos(i*d_alpha+d_a)*cos(j*d_theta),
				pos_y + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status)*cos(i*d_alpha+d_a)*sin(j*d_theta),
				pos_z + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status)*sin(i*d_alpha+d_a)
			};

			Point3 d = {
				pos_x + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status_plus)*cos(i*d_alpha+d_a)*cos(j*d_theta+d_t),
				pos_y + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status_plus)*cos(i*d_alpha+d_a)*sin(j*d_theta+d_t),
				pos_z + r*squeeze_status_plus*(1-((nb_step_alpha-i-1)/nb_step_alpha)*skirt_status_plus)*sin(i*d_alpha+d_a)
			};

			mesh_half_sphere.insert(a,b,c);
			mesh_half_sphere.insert(b,c,d);
		}
	}
	return mesh_half_sphere;
}

Mesh simple_tentacle(double len, double width, double pos_x, double pos_y, double  pos_z){
	Mesh tentacles;
	std::vector<double> r_pos{-0.5*width,0.5*width};
	std::vector<Point3> point_high;
	std::vector<Point3> point_low;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			point_high.push_back({pos_x + r_pos[i], pos_y + r_pos[j],pos_z});
			point_low.push_back({pos_x + r_pos[i], pos_y + r_pos[j],pos_z-len});
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

Mesh sinus_tentacle(double len, double width, double d_z, double d_theta, double pos_x, double pos_y, double  pos_z){
	Mesh tentacles;
	double omega = 0.6;
	double ampl = 0.5;
	double init = rand();
	for(int i=0; i < len/d_z; i++){
		for(int j=0; j*d_theta < 2*PI; j++){
			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double dif_z = std::min(d_z, len-i*d_z);

			double comp = (len - i*d_z)/len;
			double comp_plus = (len - i*d_z - dif_z)/len;
			Point3 a = {
				pos_x + width*comp*cos(j*d_theta) + ampl*sin(init+omega*i*d_z),
				pos_y + width*comp*sin(j*d_theta) + ampl*sin(init+omega*i*d_z),
				pos_z - i*d_z
			};

			Point3 b = {
				pos_x + width*comp*cos(j*d_theta+d_t) + ampl*sin(init+omega*i*d_z),
				pos_y + width*comp*sin(j*d_theta+d_t) + ampl*sin(init+omega*i*d_z),
				pos_z - i*d_z
				};

			Point3 c = {
				pos_x + width*comp_plus*cos(j*d_theta) + ampl*sin(init+omega*(i*d_z+dif_z)),
				pos_y + width*comp_plus*sin(j*d_theta) + ampl*sin(init+omega*(i*d_z+dif_z)),
				pos_z - i*d_z - dif_z
			};

			Point3 d = {
				pos_x + width*comp_plus*cos(j*d_theta+d_t) + ampl*sin(init+omega*(i*d_z+dif_z)),
				pos_y + width*comp_plus*sin(j*d_theta+d_t) + ampl*sin(init+omega*(i*d_z+dif_z)),
				pos_z - i*d_z - dif_z
			};

			tentacles.insert(a,b,c);
			tentacles.insert(b,c,d);
		}
	}
	return tentacles;
}

int jellyfish_simple(double pos_x, double pos_y, double pos_z, double squeeze){
	povray_output_mesh2(std::cout, sample_half_sphere(pos_x,pos_y,pos_z,5, PI/100, PI/100, squeeze));
	povray_output_mesh2(std::cout, simple_tentacle(7, 0.5, pos_x , pos_y , pos_z));

	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y + 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y + 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y - 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y - 1, pos_z));
}

int jellyfish(double pos_x, double pos_y, double pos_z, double r, double width, double squeeze){
	povray_output_mesh2(std::cout, jelly_shape(pos_x,pos_y,pos_z,5, PI/100, PI/100, squeeze));
	double step = PI/8;
	double step_r = 1;
	double len = 5;
	for(int i = 0; i*step_r < r; i++){
		for(int j = 0; j*step < 2*PI; j++){
			double r_i = i+1*step_r;
			double posr_x = r_i*cos(j*step);
			double posr_y =  r_i*sin(j*step);
			double posr_z = 0;
			double len_i = len + r - i; 
			povray_output_mesh2(std::cout, sinus_tentacle(len_i, width, PI/100, PI/100, pos_x+posr_x, pos_y+posr_y, pos_z+ posr_z));
		}
	}

	//povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y + 1, pos_z));
	//povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y + 1, pos_z));
	//povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y - 1, pos_z));
	//povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y - 1, pos_z));
}

int main() {
	//high begin 0
	//vector<double> list_of_hights = {0,0,0,0,0.2,0.5,1,1.8,2.2,2.3,2.4,2.4,2.4};
	//vector<double> list_of_squeeze = {0,0.1,0.2,0.3,0.2,0.1,0,-0.1,-0.2,-0.3,-0.2,-0.1};
	jellyfish_simple(0,0,0,0);

	//jellyfish(0,0,0,5,0.1,0);
	
	//repeat for high begin 2.4
}
