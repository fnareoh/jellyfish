#include "colors.inc"


#declare Deepblue = rgb <0, 0, 0.18>;
#declare Deepwhite = rgb <1, 0.8, 1>;

global_settings{max_trace_level 15}
#declare AreaOK = false;  // shadow under objects (slow)

#include "colors.inc"
#include "functions.inc"

#declare JellyFish0=union {
    #include "build/jellyfish0.inc"
}
#declare JellyFish1=union {
    #include "build/jellyfish1.inc"
}
#declare JellyFish2=union {
    #include "build/jellyfish2.inc"
}
#declare JellyFish3=union {
    #include "build/jellyfish3.inc"
}
#declare JellyFish4=union {
    #include "build/jellyfish4.inc"
}
#declare JellyFish5=union {
    #include "build/jellyfish5.inc"
}
#declare JellyFish6=union {
    #include "build/jellyfish6.inc"
}
#declare JellyFish7=union {
    #include "build/jellyfish7.inc"
}
#declare JellyFish8=union {
    #include "build/jellyfish8.inc"
}
#declare JellyFish9=union {
    #include "build/jellyfish9.inc"
}

// Camera
#declare PoV=<-20, -20, -400>;
camera{
    right x * 16/9
    location PoV
    look_at <0, 0, 0>
}

// Lights
#declare colWater=rgb<7,146,217>/255;

light_source {
    <-10, 1000, -10> color colWater*10
    #if (AreaOK)
        area_light x*200, z*200, 3, 3 adaptive 1 jitter orient
    #end
}
light_source {<-200, -1000, -300> color colWater*2 shadowless media_interaction off}
light_source {PoV color colWater*2 shadowless media_interaction off}

// Final
#declare posSub=<19,5,0>;
#declare rotSub=-15;

union{
    sphere{0,1 scale <2,1,2>}



    #for (zPos, -10, 10)
        object {
            JellyFish0 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 10, 3> translate <0.05, -0, 0.05>}
        object {
            JellyFish1 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 10, 3> translate <0.5, -0.1, 0.15>}
        object {
            JellyFish2 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 10, 3> translate <0, -0.1, 0.14>}
        object {
            JellyFish3 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 10, 3> translate <0.5, -0.3, 0.09>}
        object {
            JellyFish4 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 5, -10> translate <0, -0.3, 1>}
        object {
            JellyFish5 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 5, -10> translate <0.3, -0.3, 1.2>}
        object {
            JellyFish6 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 5, -10> translate <1.2, 0.5, 1.1>}
        object {
            JellyFish7 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -5, 10> translate <0, 0.2, 0.2>}
        object {
            JellyFish8 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -50, 0> translate <-1, 0.2, 0.2>}
        object {
            JellyFish9 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -20, 5> translate <-2, 0.2, 0.2>}
        object {
            JellyFish0 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -3, 10> translate <-0.5, -0.7, 1.2>}
        object {
            JellyFish1 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -10, 30> translate <-0, -0.7, 0.6>}
        /* object {
            JellyFish2 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -5, 10> translate <0.1, 0.3, 0>} */
        object {
            JellyFish1 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -5, 20> translate <-0.5, -0.1, 0.23>}
        object {
            JellyFish2 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, -25, 10> translate <-0.5, -0.2, 0.4>}
        object {
            JellyFish3 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 14, 30> translate <-0.4, -0.3, 0.15>}
        object {
            JellyFish4 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 10, -10> translate <-1.4, -0.2, 0.22>}
        object {
            JellyFish5 translate <0, 0, 4.45286 * 4 * zPos> scale 1/50
            rotate <-90, 0, -20> translate <-1.4, -0.05, 0.13>}
    #end

    sphere{<0,1,0>,1/1.5}

     texture{pigment{Clear}}
     scale 410 hollow
     interior{
      media{
           scattering {5,0.00133 eccentricity 0.90 extinction 1.0}
           //samples 667
           //aa_level 9
           //aa_threshold 0.05
      }
     }

    scale 4
    rotate y*rotSub  translate posSub
}
