#include "colors.inc"
camera {
  location <15, 15, -15>
  look_at 0
  angle 0
}

#declare Deepblue = rgb <0, 0, 0.18>;

mesh {
  texture { pigment { color Deepblue } }
  finish {
    ambient .1
    diffuse .4
    reflection .25
  }
}


light_source { <1000, 1000, -1000> White }
light_source { <30, 0, 0> color White }
