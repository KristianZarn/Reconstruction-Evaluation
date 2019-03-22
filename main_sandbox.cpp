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
    std::string root_folder = "../dataset/frank_gen/";
    std::string reference_filename = root_folder + "meshes/ref.ply";

    int mesh_num = 30;
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << std::to_string(mesh_num);
    std::string reconstruction_filename = root_folder + "meshes/" + ss.str() + ".ply";
    std::string ppa_filename = root_folder + "meshes/" + ss.str() + ".ppa";
    std::string gsd_filename = root_folder + "meshes/" + ss.str() + ".gsd";
    std::string mpa_filename = root_folder + "meshes/" + ss.str() + ".mpa";

    // Evaluation parameters
    int ref_samples = 50000;
    int rec_samples_mult = 2;

    // Read meshes
    Mesh reference_mesh = ReadPly(reference_filename);
    Mesh mesh_with_ppa = ReadPlyWithQuality(reconstruction_filename, ppa_filename);
    Mesh mesh_with_gsd = ReadPlyWithQuality(reconstruction_filename, gsd_filename);
    Mesh mesh_with_mpa = ReadPlyWithQuality(reconstruction_filename, mpa_filename);
    // reconstruction_mesh.ComputeVertexQualityFromFaceQuality();

    std::cout << "Reference mesh: "
              << "\n\tnum vertices: " << reference_mesh.NumVertices()
              << "\n\tnum faces: " << reference_mesh.NumFaces() << std::endl;

    std::cout << "Reconstruction mesh: "
              << "\n\tnum vertices: " << mesh_with_ppa.NumVertices()
              << "\n\tnum faces: " << mesh_with_ppa.NumFaces() << std::endl;

    std::cout << "Reference point cloud: "
              << "\n\tnum points: " << ref_samples << std::endl;

    std::cout << "Reconstruction point cloud: "
              << "\n\tnum points: " << (mesh_with_ppa.NumVertices() * rec_samples_mult) << std::endl;


    // PointCloud reference_pc = reference_mesh.AsPointCloud();
    PointCloud reference_pc = reference_mesh.Sample(ref_samples);

    // PointCloud reconstruction_pc = reconstruction_mesh.AsPointCloud();
    PointCloud pc_with_ppa = mesh_with_ppa.Sample(mesh_with_ppa.NumVertices() * rec_samples_mult);
    PointCloud pc_with_gsd = mesh_with_gsd.Sample(mesh_with_gsd.NumVertices() * rec_samples_mult);
    PointCloud pc_with_mpa = mesh_with_mpa.Sample(mesh_with_mpa.NumVertices() * rec_samples_mult);

    // Compute distances
    std::vector<float> pc_ppa_to_ref = reference_pc.ComputeDistance(pc_with_ppa);
    std::vector<float> pc_gsd_to_ref = reference_pc.ComputeDistance(pc_with_gsd);
    std::vector<float> pc_mpa_to_ref = reference_pc.ComputeDistance(pc_with_mpa);

    // Write point clouds to file (for debugging)
    reference_pc.WriteToTxt(root_folder + "ref_pc.dat");
    WritePointCloudWithDistance(root_folder + "rec_pc_with_ppa.dat", pc_with_ppa, pc_ppa_to_ref);
    WritePointCloudWithDistance(root_folder + "rec_pc_with_gsd.dat", pc_with_gsd, pc_gsd_to_ref);
    WritePointCloudWithDistance(root_folder + "rec_pc_with_mpa.dat", pc_with_mpa, pc_mpa_to_ref);

    return EXIT_SUCCESS;
}