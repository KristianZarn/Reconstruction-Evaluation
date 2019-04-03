#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    // Folders and filenames
    std::string dataset_name = "fountain_nbv";
    std::string reference_filename = "ref.ply";
    std::string reconstruction_filename = "072.ply";

    std::string root_folder = "../dataset/" + dataset_name + "/";
    std::string meshes_folder = "meshes/";
    std::string result_filename = "ctol_" + dataset_name + ".txt";

    // Evaluation parameters
    int ref_samples = 100000;
    int rec_sample_mult = 3;

    // Completeness tolerance parameters
    double ctol_min = 0;
    double ctol_step = 0.01;
    double ctol_max = 0.2;

    // Read meshes
    Mesh reference_mesh = ReadPly(root_folder + meshes_folder + reference_filename);
    Mesh reconstruction_mesh = ReadPly(root_folder + meshes_folder + reconstruction_filename);

    PointCloud reference_pc = reference_mesh.Sample(ref_samples);
    int num_samples = reconstruction_mesh.NumVertices() * rec_sample_mult;
    PointCloud reconstruction_pc = reconstruction_mesh.Sample(num_samples);

    // Compute distance (ref to rec)
    std::vector<float> ref_to_rec = reconstruction_pc.ComputeDistance(reference_pc);

    // Open file
    std::ofstream outfile(root_folder + result_filename);
    if (!outfile) {
        std::cout << "Could not open file: " << (root_folder + result_filename) << std::endl;
        return EXIT_FAILURE;
    }

    auto time_begin = std::chrono::steady_clock::now();
    double completeness_tolerance = ctol_min;
    while (completeness_tolerance < ctol_max) {

        // Compute completeness
        double completeness = Completeness(ref_to_rec, completeness_tolerance);

        // Write to file
        outfile << completeness_tolerance << "\t" << completeness << "\n";

        completeness_tolerance += ctol_step;
    }
    auto time_end = std::chrono::steady_clock::now();
    auto time_elapsed = time_end - time_begin;
    std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;
    std::cout << "Results written to: \n\t" << root_folder + result_filename;

    return EXIT_SUCCESS;
}