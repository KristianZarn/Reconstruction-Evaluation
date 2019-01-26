#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <cstdio>
#include <cmath>

#include <Eigen/Core>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"

int main(int argc, char** argv) {

    int sample_points = 10000;
    std::string reference_filename = "../resources/reference/0.off";
    std::string reconstruction_filename = "../resources/input/0.off";
    bool success;

    // Read meshes
    Mesh reference_mesh;
    success = Mesh::from_off(reference_filename, reference_mesh);

    Mesh reconstruction_mesh;
    success = Mesh::from_off(reconstruction_filename, reconstruction_mesh);

    // Compute accuracy
    PointCloud reconstruction_pc;
    success = reconstruction_mesh.sample(sample_points, reconstruction_pc);

    float accuracy = 0;
    success = reconstruction_pc.compute_distance(reference_mesh, accuracy);

    // Compute completeness
    PointCloud reference_pc;
    reference_mesh.sample(sample_points, reference_pc);

    float completeness = 0;
    success = reference_pc.compute_distance(reconstruction_mesh, completeness);

    // Output
    std::cout << "Accuracy (input to reference): " << accuracy << std::endl;
    std::cout << "Completeness (reference to input): " << completeness << std::endl;

    return EXIT_SUCCESS;
}