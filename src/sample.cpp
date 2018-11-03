#include "sample.hpp"

/* SIMPLE JELLYFISH */
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

			Point3 a {
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

std::vector<Mesh> jellyfish_simple(double pos_x, double pos_y, double pos_z, double squeeze) {
	std::vector<Mesh> ret;

	ret.push_back(
		sample_half_sphere(pos_x,pos_y,pos_z,5, PI/100, PI/100, squeeze)
	);
	ret.push_back(simple_tentacle(7, 0.5, pos_x , pos_y , pos_z));
	ret.push_back(simple_tentacle(4, 0.5, pos_x + 1, pos_y + 1, pos_z));
	ret.push_back(simple_tentacle(4, 0.5, pos_x - 1, pos_y + 1, pos_z));
	ret.push_back(simple_tentacle(4, 0.5, pos_x + 1, pos_y - 1, pos_z));
	ret.push_back(simple_tentacle(4, 0.5, pos_x - 1, pos_y - 1, pos_z));

	return ret;
}

/* REALISTIC JELLYFISH */

Point3 ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double nb_step_alpha_i, double nb_step_alpha,
	double step_alpha, double step_theta)
{
	double attenuation = pow((nb_step_alpha_i)/nb_step_alpha,4.0);
	double x = pos_x + r*squeeze_status*(1-attenuation*skirt_status)*cos(step_alpha)*cos(step_theta);
	double y = pos_y + r*squeeze_status*(1-attenuation*skirt_status)*cos(step_alpha)*sin(step_theta);
	double perlin_noise = perlin(x,y + 1*pos_z);
	Point3 a {
		x + perlin_noise*attenuation,
		y + perlin_noise*attenuation,
		pos_z + Z_COMPRESSION_BODY*r*squeeze_status*(1-pow((nb_step_alpha_i)/nb_step_alpha,4.0)*skirt_status)*sin(step_alpha)
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

			double skirt_status = AMPL_SINUS_BODY*cos(PI/6+12*j*d_theta);
			double skirt_status_plus = AMPL_SINUS_BODY*cos(PI/6+12*(j*d_theta+d_t));

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


Point3 sinus_tentacles_ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze, double angle,
	double step_z, double step_theta, double attenuation)
{
	double omega = 0.9;
	double ampl = 0.5;
	double init =10*squeeze;
	double x = pos_x + ampl*cos(angle)*sin(init+omega*step_z) + r*cos(step_theta);
	double y = pos_y + ampl*sin(angle)*sin(init+omega*step_z) + r*sin(step_theta);
	double perli_noise = perlin(x,y + 1*pos_z);
	Point3 a {
		x + perli_noise*attenuation,
		y + perli_noise*attenuation,
		pos_z - step_z
	};
	return a;
}

Mesh sinus_tentacle(double angle, double pos_x, double pos_y, double  pos_z, double len, double width, double precision, double squeeze){
	Mesh tentacles;
	double d_theta = precision;
	double d_z = precision;
	double real_length = len;
	for(int i=0; i < real_length/d_z; i++){
		for(int j=0; j*d_theta < 2*PI; j++){
			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double dif_z = std::min(d_z, real_length-i*d_z);

			double comp = (real_length - i*d_z)/real_length;
			double comp_plus = (real_length - i*d_z - dif_z)/real_length;

			Point3 a = sinus_tentacles_ondulation(pos_x, pos_y, pos_z, width*comp, squeeze, angle, i*d_z, j*d_theta, 1-comp);
			Point3 b = sinus_tentacles_ondulation(pos_x, pos_y, pos_z, width*comp, squeeze, angle, i*d_z, j*d_theta+d_t, 1-comp);
			Point3 c = sinus_tentacles_ondulation(pos_x, pos_y, pos_z, width*comp_plus, squeeze, angle, i*d_z+dif_z, j*d_theta, 1-comp_plus);
			Point3 d = sinus_tentacles_ondulation(pos_x, pos_y, pos_z, width*comp_plus, squeeze, angle, i*d_z+dif_z, j*d_theta+d_t, 1-comp_plus);

			tentacles.insert(a,b,c);
			tentacles.insert(b,c,d);
		}
	}
	return tentacles;
}

Point3 folded_tentacles_ondulation(
	double pos_x, double pos_y, double pos_z, double r,
	double squeeze_status, double skirt_status,
	double step_alpha, double step_theta, double attenuation)
{
	double x = pos_x + r*(1-squeeze_status)*(1-skirt_status)*cos(step_theta);
	double y = pos_y + r*(1-squeeze_status)*(1-skirt_status)*sin(step_theta);
	double perli_noise = perlin(x,y + 1*pos_z);
	Point3 a {
		x + perli_noise*attenuation,
		y + perli_noise*attenuation,
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
	double nb_folds = 30;
	double reg_folds = real_length/nb_folds;

	for(int i=0; i < real_length/d_z; i++){
		for(int j=0; j*d_theta < 2*PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double dif_z = std::min(d_z, real_length-i*d_z);
			double d_a = dif_z;


			double skirt_status = 0.2*cos(4*j*d_theta);
			double skirt_status_plus = 0.2*cos(4*(j*d_theta+d_t));

			double comp = COMP_FACTOR_FOLDED*(real_length - i*d_z)/real_length;
			double comp_plus = COMP_FACTOR_FOLDED*(real_length - i*d_z - dif_z)/real_length;

			double squeeze_status = SQUEEZE_FACTOR*sin(i*d_alpha*PI/reg_folds);
			double squeeze_status_plus = SQUEEZE_FACTOR*sin((i*d_alpha+d_a)*PI/reg_folds);

			double real_pos_x = pos_x + ampl*sin(init+omega*i*d_z);
			double real_pos_y = pos_y + ampl*sin(init+omega*i*d_z);
			double real_pos_x_plus = pos_x + ampl*sin(init+omega*(i*d_z+dif_z));
			double real_pos_y_plus = pos_y + ampl*sin(init+omega*(i*d_z+dif_z));


			Point3 a = folded_tentacles_ondulation(real_pos_x, real_pos_y, pos_z, width*comp, squeeze_status, skirt_status, i*d_alpha, j*d_theta, 1-comp);
			Point3 b = folded_tentacles_ondulation(real_pos_x, real_pos_y, pos_z, width*comp, squeeze_status, skirt_status_plus, i*d_alpha, j*d_theta+d_t, 1-comp);
			Point3 c = folded_tentacles_ondulation(real_pos_x_plus, real_pos_y_plus, pos_z, width*comp_plus, squeeze_status_plus, skirt_status, i*d_alpha+d_a, j*d_theta, 1-comp_plus);
			Point3 d = folded_tentacles_ondulation(real_pos_x_plus, real_pos_y_plus, pos_z, width*comp_plus, squeeze_status_plus, skirt_status_plus, i*d_alpha+d_a, j*d_theta+d_t, 1-comp_plus);

			tentacles.insert(a,b,c);
			tentacles.insert(b,c,d);
		}
	}
	return tentacles;
}



std::vector<Mesh> jellyfish(double pos_x, double pos_y, double pos_z, double width_jelly, double width_tentacle, double squeeze){
	double precision_body = PI/10;
	double precision_tentacles = PI/30;

	std::vector<Mesh> ret;

	ret.push_back(jelly_shape(pos_x,pos_y,pos_z, width_jelly, PRECISION_BODY, squeeze));

	double step = PI/12;
	double step_r = 3.4*(1+squeeze);
	double len = 2;
	for(int i = 1; i <= 1; i++){
		for(int j = 0; j*step < 2*PI; j++){
			double r_i = i*step_r;
			double posr_x = r_i*cos(j*step);
			double posr_y =  r_i*sin(j*step);
			double posr_z = Z_REL_POSITION_SINUS;
			double len_i = len;
			double angle = j*step;
			ret.push_back(sinus_tentacle(angle,pos_x+posr_x, pos_y+posr_y, pos_z+ posr_z, len_i, width_tentacle, PRECISION_TENTACLES, squeeze));
		}
	}
	ret.push_back(folded_tentacle(pos_x + XY_REL_POSITION_FOLDED, pos_y + XY_REL_POSITION_FOLDED,
		 pos_z + Z_REL_POSITION_FOLDED, LENGTH_FOLDED_TENTACLES, RADIUS_FOLDED_TENTACLES, PRECISION_TENTACLES, squeeze, 1));
	ret.push_back(folded_tentacle(pos_x - XY_REL_POSITION_FOLDED, pos_y + XY_REL_POSITION_FOLDED,
		 pos_z + Z_REL_POSITION_FOLDED, LENGTH_FOLDED_TENTACLES, RADIUS_FOLDED_TENTACLES, PRECISION_TENTACLES, squeeze, 2));
	ret.push_back(folded_tentacle(pos_x + XY_REL_POSITION_FOLDED, pos_y - XY_REL_POSITION_FOLDED,
		pos_z + Z_REL_POSITION_FOLDED, LENGTH_FOLDED_TENTACLES, RADIUS_FOLDED_TENTACLES, PRECISION_TENTACLES, squeeze, 3));
	ret.push_back(folded_tentacle(pos_x - XY_REL_POSITION_FOLDED, pos_y - XY_REL_POSITION_FOLDED,
		pos_z + Z_REL_POSITION_FOLDED, LENGTH_FOLDED_TENTACLES, RADIUS_FOLDED_TENTACLES, PRECISION_TENTACLES, squeeze, 4));

	return ret;
}
