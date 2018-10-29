#include <algorithm>
#include <array>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

#include "mesh.hpp"
#include "stl.hpp"

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

			Point3 a {&
				pos_x + r_comp_i*cos(i*d_alpha)*cos(j*d_theta),
				pos_y + r_comp_i*cos(i*d_alpha)*sin(j*d_theta),
				pos_z + r_comp_i*sin(i*d_alpha)
			};

			Point3 b {
				pos_x + r_comp_i*cos(i*d_alpha)*cos(j*d_theta+d_t),
				pos_y + r_comp_i*cos(i*d_alpha)*sin(j*d_theta+d_t),
				pos_z + r_comp_i*sin(i*d_alpha)
			};

			Point3 c {
				pos_x + r_comp_i_plus*cos(i*d_alpha+d_a)*cos(j*d_theta),
				pos_y + r_comp_i_plus*cos(i*d_alpha+d_a)*sin(j*d_theta),
				pos_z + r_comp_i_plus*sin(i*d_alpha+d_a)
			};

			Point3 d {
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

Point3 ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double nb_step_alpha_i, double nb_step_alpha,
	double step_alpha, double step_theta)
{
	Point3 a = {
		pos_x + r*squeeze_status*(1-pow((nb_step_alpha_i)/nb_step_alpha,4.0)*skirt_status)*cos(step_alpha)*cos(step_theta),
		pos_y + r*squeeze_status*(1-pow((nb_step_alpha_i)/nb_step_alpha,4.0)*skirt_status)*cos(step_alpha)*sin(step_theta),
		pos_z + 0.8*r*squeeze_status*(1-pow((nb_step_alpha_i)/nb_step_alpha,4.0)*skirt_status)*sin(step_alpha)
	};
	return a;
}

Mesh jelly_shape(double pos_x, double pos_y, double pos_z,
					 double r, double precision,
					 double squeeze){
	Mesh mesh_half_sphere;
	double d_alpha = precision;
	double d_theta = precision;
	double nb_step_alpha = PI/(2*d_alpha);
	for(int i=0; i*d_alpha < PI/2; i++){
		for(int j=0; j*d_theta < 2*PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double d_a = std::min(d_alpha, PI/2-i*d_alpha);

			double skirt_status = 0.05*cos(PI/6+12*j*d_theta);
			double skirt_status_plus = 0.05*cos(PI/6+12*(j*d_theta+d_t));
			//double skirt_status = 0.5*pow((double)round((double) 6*((double)j*d_theta)/PI) - (double) 6*((double)j*d_theta)/PI,2.0);
			//double skirt_status_plus = 0.5*pow((double)round((double) 6*((double)j*d_theta+d_t)/PI) - (double) 6*((double)j*d_theta+d_t)/PI,2.0);

			double squeeze_status = (1+ squeeze*((nb_step_alpha-i)/nb_step_alpha));
			double squeeze_status_plus = (1+ squeeze*((nb_step_alpha-i-1)/nb_step_alpha));

			Point3 a = ondulation(pos_x, pos_y, pos_z, r, squeeze_status, skirt_status, nb_step_alpha-i, nb_step_alpha, i*d_alpha, j*d_theta);

			Point3 b = ondulation(pos_x, pos_y, pos_z, r, squeeze_status, skirt_status_plus, nb_step_alpha-i, nb_step_alpha, i*d_alpha, j*d_theta+d_t);

			Point3 c = ondulation(pos_x, pos_y, pos_z, r, squeeze_status_plus, skirt_status, nb_step_alpha-i-1, nb_step_alpha, i*d_alpha+d_a, j*d_theta);

			Point3 d = ondulation(pos_x, pos_y, pos_z, r, squeeze_status_plus, skirt_status_plus, nb_step_alpha-i-1, nb_step_alpha, i*d_alpha+d_a, j*d_theta+d_t);

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
			point_high.emplace_back(pos_x + r_pos[i], pos_y + r_pos[j],pos_z);
			point_low.emplace_back(pos_x + r_pos[i], pos_y + r_pos[j],pos_z-len);
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

Mesh sinus_tentacle(double angle, double pos_x, double pos_y, double  pos_z, double len, double width, double precision, double squeeze){
	Mesh tentacles;
	double d_theta = precision;
	double d_z = precision;
	double omega = 0.9;
	double ampl = 0.5;
	double init = 0 - squeeze; //rand();
	double real_length = len;
	for(int i=0; i < real_length/d_z; i++){
		for(int j=0; j*d_theta < 2*PI; j++){
			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double dif_z = std::min(d_z, real_length-i*d_z);

			double comp = (real_length - i*d_z)/real_length;
			double comp_plus = (real_length - i*d_z - dif_z)/real_length;
			Point3 a {
				pos_x + ampl*cos(angle)*sin(init+omega*i*d_z) + width*comp*cos(j*d_theta),
				pos_y + ampl*sin(angle)*sin(init+omega*i*d_z) + width*comp*sin(j*d_theta),
				pos_z - i*d_z
			};

			Point3 b {
				pos_x + ampl*cos(angle)*sin(init+omega*i*d_z) + width*comp*cos(j*d_theta+d_t),
				pos_y + ampl*sin(angle)*sin(init+omega*i*d_z) + width*comp*sin(j*d_theta+d_t),
				pos_z - i*d_z
				};

			Point3 c {
				pos_x + ampl*cos(angle)*sin(init+omega*(i*d_z+dif_z)) + width*comp_plus*cos(j*d_theta),
				pos_y + ampl*sin(angle)*sin(init+omega*(i*d_z+dif_z)) + width*comp_plus*sin(j*d_theta),
				pos_z - i*d_z - dif_z
			};

			Point3 d {
				pos_x + ampl*cos(angle)*sin(init+omega*(i*d_z+dif_z)) + width*comp_plus*cos(j*d_theta+d_t),
				pos_y + ampl*sin(angle)*sin(init+omega*(i*d_z+dif_z)) + width*comp_plus*sin(j*d_theta+d_t),
				pos_z - i*d_z - dif_z
			};

			tentacles.insert(a,b,c);
			tentacles.insert(b,c,d);
		}
	}
	return tentacles;
}

Point3 tentacles_ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double step_alpha, double step_theta)
{
	Point3 a = {
		pos_x + r*(1-squeeze_status)*(1-skirt_status)*cos(step_theta),
		pos_y + r*(1-squeeze_status)*(1-skirt_status)*sin(step_theta),
		pos_z - step_alpha
	};
	return a;
}

Mesh folded_tentacle(double pos_x, double pos_y, double  pos_z, double len, double width, double precision, double squeeze, double in){
	Mesh tentacles;
	double d_theta = precision;
	double d_z = precision;
	double omega = 1;
	double ampl = 0.3;
	double init = in + squeeze;
	double real_length = len;

	double d_alpha = precision;
	double nb_folds = 15;
	double reg_folds = real_length/nb_folds;

	for(int i=0; i < real_length/d_z; i++){
		for(int j=0; j*d_theta < 2*PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double dif_z = std::min(d_z, real_length-i*d_z);
			double d_a = dif_z;


			double skirt_status = 0.2*cos(4*j*d_theta);
			double skirt_status_plus = 0.2*cos(4*(j*d_theta+d_t));

			double comp = 0.5*(real_length - i*d_z)/real_length;
			double comp_plus = 0.5*(real_length - i*d_z - dif_z)/real_length;

			double squeeze_status = 0.2*sin(i*d_alpha*PI/reg_folds);
			double squeeze_status_plus = 0.2*sin((i*d_alpha+d_a)*PI/reg_folds);

			double real_pos_x = pos_x + ampl*sin(init+omega*i*d_z);
			double real_pos_y = pos_y + ampl*sin(init+omega*i*d_z);
			double real_pos_x_plus = pos_x + ampl*sin(init+omega*(i*d_z+dif_z));
			double real_pos_y_plus = pos_y + ampl*sin(init+omega*(i*d_z+dif_z));

			Point3 a = tentacles_ondulation(real_pos_x, real_pos_y, pos_z, width*comp, squeeze_status, skirt_status, i*d_alpha, j*d_theta);

			Point3 b = tentacles_ondulation(real_pos_x, real_pos_y, pos_z, width*comp, squeeze_status, skirt_status_plus, i*d_alpha, j*d_theta+d_t);

			Point3 c = tentacles_ondulation(real_pos_x_plus, real_pos_y_plus, pos_z, width*comp_plus, squeeze_status_plus, skirt_status, i*d_alpha+d_a, j*d_theta);

			Point3 d = tentacles_ondulation(real_pos_x_plus, real_pos_y_plus, pos_z, width*comp_plus, squeeze_status_plus, skirt_status_plus, i*d_alpha+d_a, j*d_theta+d_t);

			tentacles.insert(a,b,c);
			tentacles.insert(b,c,d);
		}
	}
	return tentacles;
}

void jellyfish_simple(double pos_x, double pos_y, double pos_z, double squeeze) {
	povray_output_mesh2(std::cout, sample_half_sphere(pos_x,pos_y,pos_z,5, PI/100, PI/100, squeeze));
	povray_output_mesh2(std::cout, simple_tentacle(7, 0.5, pos_x , pos_y , pos_z));

	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y + 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y + 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x + 1, pos_y - 1, pos_z));
	povray_output_mesh2(std::cout, simple_tentacle(4, 0.5, pos_x - 1, pos_y - 1, pos_z));
}


int jellyfish(double pos_x, double pos_y, double pos_z, double width_jelly, double width_tentacle, double squeeze){
	double precision_body = PI/100;
	double precision_tentacles = PI/30;
	stl_output_mesh(std::cout, jelly_shape(pos_x,pos_y,pos_z, width_jelly, precision_body, squeeze));

	double step = PI/12;
	double step_r = 3.4*(1+squeeze);
	double len = 2;
	for(int i = 1; i <= 1; i++){
		for(int j = 0; j*step < 2*PI; j++){
			double r_i = i*step_r;
			double posr_x = r_i*cos(j*step);
			double posr_y =  r_i*sin(j*step);
			double posr_z = 0.1;
			double len_i = len;
			double angle = j*step;
			stl_output_mesh(std::cout, sinus_tentacle(angle,pos_x+posr_x, pos_y+posr_y, pos_z+ posr_z, len_i, width_tentacle, precision_tentacles, squeeze));
		}
	}
	stl_output_mesh(std::cout, folded_tentacle(0.7, 0.7, 1, 6, 0.7, precision_tentacles, squeeze, 1));
	stl_output_mesh(std::cout, folded_tentacle(-0.7, 0.7, 1, 6, 0.7, precision_tentacles, squeeze, 2));
	stl_output_mesh(std::cout, folded_tentacle(0.7, -0.7, 1, 6, 0.7, precision_tentacles, squeeze, 3));
	stl_output_mesh(std::cout, folded_tentacle(-0.7, -0.7, 1, 6, 0.7, precision_tentacles, squeeze, 4));
	return 0;
}

int main(int argc, const char** argv) {
    // Successive states of the jellyfish: y_position and squeeze
    std::vector<std::array<double, 2>> frame_states = {
        {0.0, -0.10}, // 0
        {0.0, -0.20}, // 1
        {0.0, -0.20}, // 2
        {0.0, -0.18}, // 3
        {0.0, -0.16}, // 4
        {0.0, -0.14}, // 5
        {0.0, -0.12}, // 6
        {0.0, -0.10}, // 7
        {0.0, -0.08}, // 8
        {0.0, -0.06}, // 9
        {0.0, -0.04}, // 10
        {0.0, -0.02}, // 11
        {0.0, -0.01}, // 12
        {0.0, 0.0}, // 13
        {0.0, 0.0}, // 14
        {0.0, 0.0}, // 15
        {0.0, 0.0}, // 16
        {0.0, 0.0}, // 17
        {0.0, 0.0}, // 18
        {0.0, 0.0}, // 19
        {0.0, 0.0}, // 20
        {0.0, 0.0}, // 21
        {0.0, 0.0}, // 22
        {0.0, 0.0}, // 23
        {0.0, 0.05}, // 24
        {0.0, 0.10}, // 25
        {0.0, 0.10}, // 26
        {0.0, 0.05}, // 27
        {0.0, 0.0}, // 28
        {0.0, -0.05}, // 29
    };
    size_t nb_frames = frame_states.size();

    // Add position (inverse exponential speed)
    for (size_t t = 1 ; t < nb_frames ; t++)
        frame_states[t][0] =\
            frame_states[t-1][0] + 0.05 +  0.2 * exp(-0.0495105 * t);

    // Read the frame we want to render from stdin
    int frame = 0;

    if (argc > 1)
        frame = std::atoi(argv[1]);

    // Distance traveled by the jelly during one period
    double period_travel = frame_states[nb_frames - 1][0] - frame_states[0][0];
    // Number of complete periods that have been traveled
    int period_count = frame / nb_frames;

    // Render the jelly
    double z_position = frame_states[frame % nb_frames][0] + period_count * period_travel;
    double squeeze = frame_states[frame % nb_frames][1];
    jellyfish(0, 0, z_position, 4, 0.05, -0.5);
}
