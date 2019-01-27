#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    std::string reference_filename = "../dataset/sod/ref.ply";
    std::string reconstruction_filename = "../dataset/sod/030.ply";

    // Read meshes
    Mesh reference_mesh = ReadPly(reference_filename);
    Mesh reconstruction_mesh = ReadPly(reconstruction_filename);

    std::cout << "Reference mesh: "
            << "\n\tnum vertices: " << reference_mesh.NumVertices()
            << "\n\tnum faces: " << reference_mesh.NumFaces() << std::endl;

    std::cout << "Reconstruction mesh: "
              << "\n\tnum vertices: " << reconstruction_mesh.NumVertices()
              << "\n\tnum faces: " << reconstruction_mesh.NumFaces() << std::endl;


    // PointCloud reference_pc = reference_mesh.AsPointCloud();
    PointCloud reference_pc = reference_mesh.Sample(20000);

    // int num_samples = reconstruction_mesh.NumVertices() * 2;
    int num_samples = 10000;
    PointCloud reconstruction_pc = reconstruction_mesh.Sample(num_samples);

    std::cout << "Reference point cloud: "
              << "\n\tnum points: " << reference_pc.NumPoints() << std::endl;

    std::cout << "Reconstruction point cloud: "
              << "\n\tnum points: " << reconstruction_pc.NumPoints() << std::endl;

    // Compute accuracy (rec to ref)
    std::cout << "Computing distance ... " << std::flush;
    auto time_begin = std::chrono::steady_clock::now();

    std::vector<float> rec_to_ref = reference_pc.ComputeDistance(reconstruction_pc);
    float accuracy = MeanDistance(rec_to_ref);

    auto time_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_elapsed = time_end - time_begin;
    std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;

    // Compute completeness (ref to rec)
    std::cout << "Computing distance ... " << std::flush;
    time_begin = std::chrono::steady_clock::now();

    std::vector<float> ref_to_rec = reconstruction_pc.ComputeDistance(reference_pc);
    float completeness = MeanDistance(ref_to_rec);

    time_end = std::chrono::steady_clock::now();
    time_elapsed = time_end - time_begin;
    std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;

    // Output
    std::cout << "Accuracy (input to reference): " << accuracy << std::endl;
    std::cout << "Completeness (reference to input): " << completeness << std::endl;

    // Write point clouds to file
    reference_pc.WriteToTxt("../resources/ref_pc.dat");
    reconstruction_pc.WriteToTxt("../resources/rec_pc.dat");

    return EXIT_SUCCESS;
}