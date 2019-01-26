#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    int sample_points = 10000;
    std::string reference_filename = "../dataset/sod/ref.ply";
    std::string reconstruction_filename = "../dataset/sod/003.ply";

    // Read meshes
    Mesh reference_mesh = ReadPly(reference_filename);
    Mesh reconstruction_mesh = ReadPly(reconstruction_filename);

    // Compute accuracy (rec to ref)
    std::cout << "Sampling reconstruction mesh ... " << std::flush;
    PointCloud reconstruction_pc;
    reconstruction_mesh.sample(sample_points, reconstruction_pc);
    std::cout << "DONE" << std::endl;

    std::cout << "Computing distance ... " << std::flush;
    float accuracy = 0;
    reconstruction_pc.compute_distance(reference_mesh, accuracy);
    std::cout << "DONE" << std::endl;

    // Compute completeness (ref to rec)
    std::cout << "Sampling reference mesh ... " << std::flush;
    PointCloud reference_pc;
    reference_mesh.sample(sample_points, reference_pc);
    std::cout << "DONE" << std::endl;

    std::cout << "Computing distance ... " << std::flush;
    float completeness = 0;
    reference_pc.compute_distance(reconstruction_mesh, completeness);
    std::cout << "DONE" << std::endl;

    // Output
    std::cout << "Accuracy (input to reference): " << accuracy << std::endl;
    std::cout << "Completeness (reference to input): " << completeness << std::endl;

    return EXIT_SUCCESS;
}