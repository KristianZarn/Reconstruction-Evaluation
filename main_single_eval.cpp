#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    // Parameters
    std::string root_folder = "../dataset/sod/";
    std::string reference_filename = root_folder + "meshes/ref.ply";
    std::string reconstruction_filename = root_folder + "meshes/024.ply";

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
    PointCloud reference_pc = reference_mesh.Sample(30000);
    int num_samples = reconstruction_mesh.NumVertices() * 2;
    PointCloud reconstruction_pc = reconstruction_mesh.Sample(num_samples);

    std::cout << "Reference point cloud: "
              << "\n\tnum points: " << reference_pc.NumPoints() << std::endl;

    std::cout << "Reconstruction point cloud: "
              << "\n\tnum points: " << reconstruction_pc.NumPoints() << std::endl;

    // Compute accuracy (rec to ref)
    double accuracy_percentage = 0.95;

    std::cout << "Computing distance ... " << std::flush;
    auto time_begin = std::chrono::steady_clock::now();

    std::vector<float> rec_to_ref = reference_pc.ComputeDistance(reconstruction_pc);
    double rec_to_ref_dist = MeanDistance(rec_to_ref);
    double accuracy = AccuracyMeasure(rec_to_ref, accuracy_percentage);

    auto time_end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_elapsed = time_end - time_begin;
    std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;

    // Compute completeness (ref to rec)
    double completeness_tolerance = 2 * accuracy;

    std::cout << "Computing distance ... " << std::flush;
    time_begin = std::chrono::steady_clock::now();

    std::vector<float> ref_to_rec = reconstruction_pc.ComputeDistance(reference_pc);
    double ref_to_rec_dist = MeanDistance(ref_to_rec);
    double completeness = CompletenessMeausre(ref_to_rec, completeness_tolerance);

    time_end = std::chrono::steady_clock::now();
    time_elapsed = time_end - time_begin;
    std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;

    // Output
    std::cout << "Rec to ref distance: " << rec_to_ref_dist << std::endl;
    std::cout << "Accuracy (" << accuracy_percentage << "): " << accuracy << std::endl;

    std::cout << "Ref to rec distance: " << ref_to_rec_dist << std::endl;
    std::cout << "Completeness (" << completeness_tolerance << "): " << completeness << std::endl;

    // Write point clouds to file (for debugging)
    reference_pc.WriteToTxt("../resources/ref_pc.dat");
    reconstruction_pc.WriteToTxt("../resources/rec_pc.dat");

    return EXIT_SUCCESS;
}