#include "colors.inc"


#declare Deepblue = rgb <0, 0, 0.18>;
#declare Deepwhite = rgb <1, 0.8, 1>;

global_settings{max_trace_level 15}
#declare AreaOK=false;

#include "colors.inc"
#include "functions.inc"

#declare JellyFish=union {
    #include "build/jellyfish.inc"
}

// Camera
#declare PoV=<-20, -20, -400>;
camera{
        location PoV
        look_at <0, 0, 0>
}

// Reorientation Macro
#macro mOrient(P1,P2)
#local yV1=vnormalize(P2-P1);
#local xV1=vnormalize(vcross(yV1,z));
#local zV1=vcross(xV1,yV1);
                matrix <xV1.x,xV1.y,xV1.z,yV1.x,yV1.y,yV1.z,zV1.x,zV1.y,zV1.z,P1.x,P1.y,P1.z>
#end


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
    object{JellyFish scale 1/50 rotate <-90, 5, -10> translate <0, -0.3, 1>}
    object{JellyFish scale 1/50 rotate <-90, 5, -10> translate <0.3, -0.3, 1.2>}
    object{JellyFish scale 1/50 rotate <-90, 5, -10> translate <1.2, 0.5, 1.1>}
    object{JellyFish scale 1/50 rotate <-90, -5, 10> translate <0, 0.2, 0.2>}
    object{JellyFish scale 1/50 rotate <-90, 10, 3> translate <0.05, -0, 0.05>}

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
