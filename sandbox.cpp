#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "eval/Mesh.h"
#include "eval/PointCloud.h"
#include "eval/Helpers.h"

int main(int argc, char** argv) {

    // Folders and filenames
    std::string root_folder = "../dataset/_other/ex/";
    std::string reference_filename = root_folder + "ref.ply";

    int mesh_num = 7;
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << std::to_string(mesh_num);
    std::string reconstruction_filename = root_folder + ss.str() + ".ply";

    // Evaluation parameters
    int ref_samples = 100000;
    int rec_samples_mult = 4;

    // Read meshes
    Mesh reference_mesh = ReadPly(reference_filename);
    Mesh reconstruction_mesh = ReadPly(reconstruction_filename);

    std::cout << "Reference mesh: "
              << "\n\tnum vertices: " << reference_mesh.NumVertices()
              << "\n\tnum faces: " << reference_mesh.NumFaces() << std::endl;

    std::cout << "Reconstruction mesh: "
              << "\n\tnum vertices: " << reconstruction_mesh.NumVertices()
              << "\n\tnum faces: " << reconstruction_mesh.NumFaces() << std::endl;

    // Sample meshes
    PointCloud reference_pc = reference_mesh.Sample(ref_samples);
    PointCloud reconstruction_pc = reconstruction_mesh.SampleSpecial(reconstruction_mesh.NumVertices() * rec_samples_mult);

    // Compute distances
    std::vector<float> rec_to_ref = reference_pc.ComputeDistance(reconstruction_pc);

    // Write point clouds to file (for debugging)
    reference_pc.WriteToTxt(root_folder + "ref_pc.dat");

    for (const auto& dist : rec_to_ref) {
        reconstruction_pc.AddPointQuality(dist);
    }
    reconstruction_pc.WriteToTxt(root_folder + "007_pc.dat");

    return EXIT_SUCCESS;
}