#include "Helpers.h"

#include <Eigen/Core>

Mesh ReadPly(const std::string& filename) {

    // Open file
    std::ifstream fs(filename, std::ios::binary);
    if (fs.fail()) {
        throw std::runtime_error("failed to open " + filename);
    }

    tinyply::PlyFile file;
    file.parse_header(fs);

    // Read data
    std::shared_ptr<tinyply::PlyData> vertices;
    try {
        vertices = file.request_properties_from_element("vertex", { "x", "y", "z" });
    } catch (const std::exception & e) {
        std::cerr << "tinyply exception: " << e.what() << std::endl;
    }

    std::shared_ptr<tinyply::PlyData> faces;
    try {
        faces = file.request_properties_from_element("face", { "vertex_indices" });
    } catch (const std::exception & e) {
        std::cerr << "tinyply exception: " << e.what() << std::endl;
    }

    file.read(fs);

    // Cast to data to vectors
    const size_t vertices_bytes = vertices->buffer.size_bytes();
    std::vector<float> vertices_raw(vertices->count * 3);
    std::memcpy(vertices_raw.data(), vertices->buffer.get(), vertices_bytes);

    const size_t faces_bytes = faces->buffer.size_bytes();
    std::vector<unsigned int> faces_raw(faces->count * 3);
    std::memcpy(faces_raw.data(), faces->buffer.get(), faces_bytes);

    // Create mesh
    Mesh mesh;
    for (int i = 0; i < vertices->count; i++) {
        Eigen::Vector3f vertex_eig(vertices_raw[i * 3 + 0],
                                   vertices_raw[i * 3 + 1],
                                   vertices_raw[i * 3 + 2]);
        mesh.AddVertex(vertex_eig);
    }
    for (int i = 0; i < faces->count; i++) {
        Eigen::Vector3i face_eig(faces_raw[i * 3 + 0],
                                 faces_raw[i * 3 + 1],
                                 faces_raw[i * 3 + 2]);
        mesh.AddFace(face_eig);
    }
    return mesh;
}

double MeanDistance(const std::vector<float>& distances) {
    double sum = 0.0;
    for (const auto distance : distances) {
        sum += distance;
    }
    return (sum / distances.size());
}

double Percentile(const std::vector<float>& distances, double percentage) {
    assert(percentage >= 0.0 && percentage < 1.0);

    // Copy original vector and sort it
    auto distances_copy = distances;
    std::sort(distances_copy.begin(), distances_copy.end());

    // Get value
    int idx = static_cast<int>(floor(distances.size() * percentage));
    return distances_copy[idx];
}

double Completeness(const std::vector<float>& distances, double tolerance) {
    int inlier_sum = 0;
    for (float distance : distances) {
        if (distance <= tolerance) {
            inlier_sum++;
        }
    }
    double percentage = static_cast<double>(inlier_sum) / distances.size();
    return percentage;
}