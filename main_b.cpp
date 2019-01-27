#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    std::string reference_filename = "../dataset/sod/ref.ply";
    std::string reconstruction_filename = "../dataset/sod/003.ply";

    // Read meshes
    Mesh reference_mesh = ReadPly(reference_filename);
    Mesh reconstruction_mesh = ReadPly(reconstruction_filename);

    std::cout << "Reference mesh: "
            << "\n\tnum vertices: " << reference_mesh.NumVertices()
            << "\n\tnum faces: " << reference_mesh.NumFaces() << std::endl;

    std::cout << "Reconstruction mesh: "
              << "\n\tnum vertices: " << reconstruction_mesh.NumVertices()
              << "\n\tnum faces: " << reconstruction_mesh.NumFaces() << std::endl;

    PointCloud reference_pc = reference_mesh.AsPointCloud();
    int num_samples = reconstruction_mesh.NumVertices() * 2;
    PointCloud reconstruction_pc = reconstruction_mesh.Sample(num_samples);

    std::cout << "Reference point cloud: "
              << "\n\tnum points: " << reference_pc.NumPoints() << std::endl;

    std::cout << "Reconstruction point cloud: "
              << "\n\tnum points: " << reconstruction_pc.NumPoints() << std::endl;

    // Compute accuracy (rec to ref)
    std::cout << "Computing distance ... " << std::flush;
    std::vector<float> rec_to_ref = reference_pc.ComputeDistance(reconstruction_pc);
    float accuracy = MeanDistance(rec_to_ref);
    std::cout << "DONE" << std::endl;

    // Compute completeness (ref to rec)
    std::cout << "Computing distance ... " << std::flush;
    std::vector<float> ref_to_rec = reconstruction_pc.ComputeDistance(reference_pc);
    float completeness = MeanDistance(ref_to_rec);
    std::cout << "DONE" << std::endl;

    // Output
    std::cout << "Accuracy (input to reference): " << accuracy << std::endl;
    std::cout << "Completeness (reference to input): " << completeness << std::endl;

    return EXIT_SUCCESS;
}