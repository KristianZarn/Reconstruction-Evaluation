#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <iterator>

#include "eval/IPCameraStats.h"

std::string clean_string(std::string str) {
    // Get content between brackets if it exist
    auto first = str.find('(');
    auto last = str.find(')');
    if (first != std::string::npos && last != std::string::npos) {
        str = str.substr(first, last-first);
    }

    // Remove alpha and some special characters
    str.erase(std::remove_if(str.begin(), str.end(),
            []( auto const& c ) -> bool { return std::isalpha(c) || c == ':' || c == '(' || c == ')' || c == ','; } ), str.end());
    return str;
}

int main(int argc, char** argv) {

    // Camera stats file
    std::string filename = "../resources/camera_stats_cesnja.txt";

    // Open file
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return EXIT_FAILURE;
    }

    // Read data
    std::vector<int> pose_ids;
    std::vector<glm::vec3> camera_positions;
    std::vector<glm::vec3> camera_rotations;
    std::vector<glm::vec3> nbv_positions;
    std::vector<glm::vec3> nbv_rotations;
    std::vector<int> best_view_picks;

    std::string line;
    while (std::getline(infile, line)) {
        if (line.find("View id") != std::string::npos) {
            std::string clean_line = clean_string(line);

            std::istringstream stream(clean_line);
            int pose_id;
            stream >> pose_id;
            pose_ids.push_back(pose_id);
        }

        if (line.find("Camera pos") != std::string::npos) {
            std::string clean_line = clean_string(line);
            std::istringstream stream(clean_line);
            double x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            glm::vec3 camera_pos = glm::vec3(x, y, z);
            camera_positions.push_back(camera_pos);
        }

        if (line.find("Camera rot") != std::string::npos) {
            std::string clean_line = clean_string(line);
            std::istringstream stream(clean_line);
            double x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            glm::vec3 camera_rot = glm::vec3(x, y, z);
            camera_rotations.push_back(camera_rot);
        }

        if (line.find("NBV pos") != std::string::npos) {
            std::string clean_line = clean_string(line);
            std::istringstream stream(clean_line);
            double x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            glm::vec3 nbv_pos = glm::vec3(x, y, z);
            nbv_positions.push_back(nbv_pos);
        }

        if (line.find("NBV rot") != std::string::npos) {
            std::string clean_line = clean_string(line);
            std::istringstream stream(clean_line);
            double x, y, z;
            stream >> x;
            stream >> y;
            stream >> z;
            glm::vec3 nbv_rot = glm::vec3(x, y, z);
            nbv_rotations.push_back(nbv_rot);
        }

        if (line.find("Best view pick") != std::string::npos) {
            std::string clean_line = clean_string(line);

            std::istringstream stream(clean_line);
            int best_view_pick;
            stream >> best_view_pick;
            best_view_picks.push_back(best_view_pick);
        }
    }

    // Close file
    infile.close();

    // Copy data to camera_stats
    IPCameraStats camera_stats;
    for (int i = 0; i < pose_ids.size(); i++) {
        camera_stats.AddPose(pose_ids[i], camera_positions[i], camera_rotations[i],
                nbv_positions[i], nbv_rotations[i], best_view_picks[i]);
    }

    // Print stats
    int num_views = camera_stats.Size();
    std::cout << "Num views: " << "\n\t" << num_views << std::endl;

    double nbv_index = camera_stats.ComputeAvgIndex();
    std::cout << "Average nbv index: " << "\n\t" << nbv_index << std::endl;

    double pos_error = camera_stats.ComputeMeanPosError();
    std::cout << "Position error: " << "\n\t" << pos_error << std::endl;

    double pos_error_relative = pos_error / camera_stats.ComputeMaxCameraDistance();
    pos_error_relative *= 100;
    std::cout << "Position error (relative): " << "\n\t" << pos_error_relative << "%" << std::endl;

    double rot_error = camera_stats.ComputeMeanRotError();
    std::cout << "Rotation error: " << "\n\t" << rot_error << "°" << std::endl;

    return EXIT_SUCCESS;
}