#include "colors.inc"


camera {
    location <15, 15, -15>
    look_at 0
    angle 0
}

#declare Deepblue = rgb <0, 0, 0.18>;

light_source { <1000, 1000, -1000> White }
light_source { <30, 0, 0> color White }


#include "build/jellyfish.inc"
