#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"
#include "eval/EvaluationStats.h"
#include "eval/Pca.h"

int main(int argc, char** argv) {

    // Folders and filenames
    std::string dataset_name = "frank";
    // std::vector<std::string> labels = {"gen_20", "gen_40",  "gen_60", "nbv"};
    // std::vector<std::string> labels = {"gen_20", "gen_40",  "gen_60"};
    std::vector<std::string> labels = {"nbv"};

    std::string root_folder = "../dataset/" + dataset_name + "/";
    std::string ref_filename = dataset_name + ".ply";

    int rec_min = 2;
    int rec_max = 81;

    // Evaluation parameters
    int ref_samples = 100000;
    int rec_sample_mult = 2;

    double accuracy_percentage = 0.90;
    double completeness_percentage = 0.01;

    // Read and sample reference mesh
    Mesh ref_mesh = ReadPly(root_folder + ref_filename);
    PointCloud ref_pc = ref_mesh.Sample(ref_samples);

    // PCA for completeness tolerance
    Eigen::MatrixXf data = ref_pc.PointMatrix();
    Pca<float> pca;
    pca.SetInput(data);
    pca.Compute();
    Eigen::VectorXf eigen_values = pca.GetEigenValues();
    double completeness_tolerance = eigen_values(0) * completeness_percentage;
    std::cout << "Completeness tolerance: \n\t" << completeness_tolerance << std::endl;

    // Perform evaluation for given labels
    for (const auto& label : labels) {
        std::string meshes_folder = "evaluation_" + label + "/";
        std::string result_filename = "eval_" + dataset_name + "_" + label + ".txt";

        EvaluationStats eval_stats(ref_filename, ref_samples,
                                   accuracy_percentage, completeness_tolerance);

        std::cout << "Performing evaluation (" << label << "): " << std::endl;
        auto time_begin = std::chrono::steady_clock::now();

        // Evaluate meshes
        for (int i = rec_min; i <= rec_max; i++) {
            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << std::to_string(i);
            std::string rec_filename = ss.str() + ".ply";
            std::cout << "\tEvaluating mesh " << rec_filename << std::endl;

            // Check if mesh file exists
            std::ifstream file(root_folder + meshes_folder + rec_filename);
            bool file_exists = file.good();
            file.close();

            if (file_exists) {
                Mesh rec_mesh = ReadPly(root_folder + meshes_folder + rec_filename);
                int rec_samples = rec_mesh.NumVertices() * rec_sample_mult;
                PointCloud rec_pc = rec_mesh.Sample(rec_samples);

                // Rec to ref
                std::vector<float> rec_to_ref = ref_pc.ComputeDistance(rec_pc);
                double rec_to_ref_dist = MeanDistance(rec_to_ref);
                double accuracy = Percentile(rec_to_ref, accuracy_percentage);

                // Ref to rec
                std::vector<float> ref_to_rec = rec_pc.ComputeDistance(ref_pc);
                double ref_to_rec_dist = MeanDistance(ref_to_rec);
                double completeness = Completeness(ref_to_rec, completeness_tolerance);

                // Add to stats
                eval_stats.AddMeshComparison(rec_filename, i, rec_samples,
                                             rec_to_ref_dist, accuracy,
                                             ref_to_rec_dist, completeness);
            }
        }

        // Timing information
        auto time_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_elapsed = time_end - time_begin;
        std::cout << "DONE in " << time_elapsed.count() << " s" << std::endl;

        // Write results
        eval_stats.WriteStatsToFile(root_folder + result_filename);
        std::cout << "Stats written to: \n\t" << root_folder + result_filename << std::endl;
    }

    return EXIT_SUCCESS;
}