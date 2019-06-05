#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"
#include "eval/Pca.h"

int main(int argc, char** argv) {

    // Folders and filenames
    // std::string dataset_name = "frank";
    // std::string root_folder = "../dataset/" + dataset_name + "/";
    // std::string ref_filename = dataset_name + ".ply";

    std::string root_folder = "../dataset/_other/";
    std::string ref_filename = "mesh.ply";

    // Prepare reference
    Mesh reference_mesh = ReadPly(root_folder + ref_filename);
    int ref_samples = 100000;
    PointCloud reference_pc = reference_mesh.Sample(ref_samples);

    // PCA
    Eigen::MatrixXf data = reference_pc.PointMatrix();
    Pca<float> pca;
    pca.SetInput(data);
    pca.Compute();
    Eigen::VectorXf eigen_values = pca.GetEigenValues();
    std::cout << "Eigen values:\n" << eigen_values << std::endl;
    std::cout << "Biggest eigen value:\n" << eigen_values(0) << std::endl;

    // Completeness
    // double completeness_percentage = 0.01;
    // double completeness_tolerance = eigen_values(0) * completeness_percentage;
    // std::cout << "Completeness tolerance: \n\t" << completeness_tolerance << std::endl;

    return EXIT_SUCCESS;
}