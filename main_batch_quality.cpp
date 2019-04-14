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
    std::string root_folder = "../dataset/statue_gen/";
    std::string export_folder = root_folder + "raw_export/";

    std::string reference_filename = root_folder + "meshes/ref.ply";

    // Prepare reference
    Mesh reference_mesh = ReadPly(reference_filename);
    int ref_samples = 100000;
    PointCloud reference_pc = reference_mesh.Sample(ref_samples);
    reference_pc.WriteToTxt(export_folder + "ref_pc.dat");

    int min_mesh_num = 3;
    int max_mesh_num = 72;
    for (int i = min_mesh_num; i <= max_mesh_num; i++) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << std::to_string(i);
        std::string rec_filename = root_folder + "meshes/" + ss.str() + ".ply";
        std::string ppa_filename = root_folder + "meshes/" + ss.str() + ".ppa";
        std::string gsd_filename = root_folder + "meshes/" + ss.str() + ".gsd";
        std::string mpa_filename = root_folder + "meshes/" + ss.str() + ".mpa";

        std::cout << "\tProcessing mesh " << rec_filename << std::endl;

        // Evaluation parameters
        int rec_samples_mult = 3;

        // Read meshes
        Mesh mesh_with_ppa = ReadPlyWithQuality(rec_filename, ppa_filename);
        Mesh mesh_with_gsd = ReadPlyWithQuality(rec_filename, gsd_filename);
        Mesh mesh_with_mpa = ReadPlyWithQuality(rec_filename, mpa_filename);

        // Convert to point cloud
        PointCloud pc_with_ppa = mesh_with_ppa.Sample(mesh_with_ppa.NumVertices() * rec_samples_mult);
        PointCloud pc_with_gsd = mesh_with_gsd.Sample(mesh_with_gsd.NumVertices() * rec_samples_mult);
        PointCloud pc_with_mpa = mesh_with_mpa.Sample(mesh_with_mpa.NumVertices() * rec_samples_mult);

        // Compute distances
        std::vector<float> pc_ppa_to_ref = reference_pc.ComputeDistance(pc_with_ppa);
        std::vector<float> pc_gsd_to_ref = reference_pc.ComputeDistance(pc_with_gsd);
        std::vector<float> pc_mpa_to_ref = reference_pc.ComputeDistance(pc_with_mpa);

        // Write point clouds with quality and distances to file
        WritePointCloudWithDistance(export_folder + ss.str() + "_ppa.dat", pc_with_ppa, pc_ppa_to_ref);
        WritePointCloudWithDistance(export_folder + ss.str() + "_gsd.dat", pc_with_gsd, pc_gsd_to_ref);
        WritePointCloudWithDistance(export_folder + ss.str() + "_mpa.dat", pc_with_mpa, pc_mpa_to_ref);
    }

    return EXIT_SUCCESS;
}