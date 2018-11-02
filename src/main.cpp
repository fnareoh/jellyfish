#include <iostream>
#include <string>
#include <vector>

#include "noise.hpp"
#include "sample.hpp"


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

    // Parse parameters for main
    int frame = 0, seed = 0;
    std::string format = "pov";

    if (argc > 1)
        format = argv[1];

    if (argc > 2)
        frame = std::atoi(argv[2]);

    if (argc > 3)
        seed = std::atoi(argv[3]);

    // Init perlin gradient
    init_perlin(100, 100, seed);

    // Add a random offset to the frame
    std::random_device rd;
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> off_frame(0, 119);

    off_frame(gen);
    frame = frame + off_frame(gen);

    // Distance traveled by the jelly during one period
    double period_travel = frame_states[nb_frames - 1][0] - frame_states[0][0];
    // Number of complete periods that have been traveled
    int period_count = frame / nb_frames;

    // Render the jelly
    double z_position = \
        frame_states[frame % nb_frames][0] + period_count * period_travel;
    double squeeze = frame_states[frame % nb_frames][1];

    std::vector<Mesh> jelly = jellyfish(0, 0, z_position, 4, 0.05, squeeze);

    for (Mesh& mesh : jelly)
        if (format == "pov" || format == "pov_mesh2")
            povray_output_mesh2(std::cout, mesh);
        else if (format == "pov_mesh")
            povray_output_mesh(std::cout, mesh);
        else if (format == "stl")
            stl_output_mesh(std::cout, mesh);
        else
            std::cerr << "Unknown file format" << std::endl;
}
