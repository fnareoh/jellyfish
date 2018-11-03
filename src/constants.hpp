#pragma once

// Pi constant
constexpr double PI = 3.14159265358979323846;

/* PARAMETERS FOR THE PRECISION OF THE SAMPLING */
// precision for the body
constexpr double PRECISION_BODY = PI/10;
// precision for the tentacles (both sinus and folded)
constexpr double PRECISION_TENTACLES = PI/30;


/* PARAMETERS FOR THE JELLYFISH */

/* BODY */
// radius of the jellyfish body
constexpr double RADIUS_BODY = 4;
// ampl sinus of the skirt of the body
constexpr double AMPL_SINUS_BODY = 0.05;
// z compression of the body
constexpr double Z_COMPRESSION_BODY = 0.8;

/* SINUS TENTACLES */
// raduis of the small sinus tentacles
constexpr double RADIUS_SINUS_TENTACLES = 0.05;
// relative z position to the body
constexpr double Z_REL_POSITION_SINUS = 0.1;

/* FOLDED TENTACLES */
// radius of the folded tentacles
constexpr double RADIUS_FOLDED_TENTACLES = 0.05;
// length of the folded_tentacle
constexpr double LENGTH_FOLDED_TENTACLES = 6;
// relative z position to the body
constexpr double Z_REL_POSITION_FOLDED = 1;
// relative x and y position to the center of the sphere of the body
constexpr double XY_REL_POSITION_FOLDED = 0.7;
// compression of the tentacles at the end
constexpr double COMP_FACTOR_FOLDED = 0.5;
// influence of the squeeze parameter on the mouvement of the tentacles
constexpr double SQUEEZE_FACTOR = 0.2;
