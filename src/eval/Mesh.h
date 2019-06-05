#ifndef SANDBOX_EVALUATION_MESH_H
#define SANDBOX_EVALUATION_MESH_H

#include <vector>
#include <string>
#include <Eigen/Core>

class PointCloud;

class Mesh {
public:
    void AddVertex(Eigen::Vector3f& vertex);
    int NumVertices() const;
    Eigen::Vector3f Vertex(int v) const;

    void AddFace(Eigen::Vector3i& face);
    int NumFaces() const;
    Eigen::Vector3i Face(int f) const;

    void AddVertexQuality(double q);
    double VertexQuality(int v) const;

    void AddFaceQuality(double q);
    double FaceQuality(int f) const;

    void ComputeVertexQualityFromFaceQuality();
    PointCloud Sample(int num_samples) const;
    PointCloud SampleSpecial(int num_samples) const;
    PointCloud AsPointCloud() const;

private:
    std::vector<Eigen::Vector3f> vertices;
    std::vector<Eigen::Vector3i> faces;

    std::vector<double> vertex_quality;
    std::vector<double> face_quality;
};

#endif //SANDBOX_EVALUATION_MESH_H
