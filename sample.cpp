#include <algorithm>
#include <math.h>
#include <vector>

#include "mesh.hpp"

# define PI           3.14159265358979323846


// d_theta and d_alpha are angles in radient.
Mesh sample_half_sphere(double r, double d_theta, double d_alpha){
	Mesh mesh_half_sphere;
	for(int i=0; i*d_alpha < PI/2; i++){
		for(int j=0; j*d_theta < 2*M_PI; j++){

			double d_t = std::min(d_theta, 2*PI-j*d_theta);
			double d_a = std::min(d_alpha, PI/2-j*d_alpha);

			Point3 a = {
				r*cos(i*d_alpha)*cos(j*d_theta),
				r*cos(i*d_alpha)*sin(j*d_theta),
				r*cos(i*d_alpha)
			};

			Point3 b = {
				r*cos(i*d_alpha)*cos(j*(d_theta+d_t)),
				r*cos(i*d_alpha)*sin(j*(d_theta+d_t)),
				r*cos(i*d_alpha)
			};

			Point3 c = {
				r*cos(i*(d_alpha+d_a))*cos(j*d_theta),
				r*cos(i*(d_alpha+d_a))*sin(j*d_theta),
				r*cos(i*(d_alpha+d_a))
			};

			Point3 d = {
				r*cos(i*(d_alpha+d_a))*cos(j*(d_theta+d_t)),
				r*cos(i*(d_alpha+d_a))*sin(j*(d_theta+d_t)),
				r*cos(i*(d_alpha+d_a))
			};
			
			mesh_half_sphere.insert(a,b,c);
			mesh_half_sphere.insert(b,c,d);
		}
	}
	return mesh_half_sphere;
}


main(){
	sample_half_sphere(5, PI/100, PI/100);
	return 0;
}