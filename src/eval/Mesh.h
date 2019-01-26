#ifndef SANDBOX_EVALUATION_MESH_H
#define SANDBOX_EVALUATION_MESH_H

#include <vector>
#include <string>
#include <Eigen/Core>

class PointCloud;

class Mesh {
public:
    void add_vertex(Eigen::Vector3f& vertex);
    int num_vertices() const;
    Eigen::Vector3f vertex(int v) const;

    void add_face(Eigen::Vector3i& face);
    int num_faces() const;
    Eigen::Vector3i face(int f) const;

    bool sample(const int N, PointCloud &point_cloud) const;

private:
    std::vector<Eigen::Vector3f> vertices;
    std::vector<Eigen::Vector3i> faces;
};

#endif //SANDBOX_EVALUATION_MESH_H
