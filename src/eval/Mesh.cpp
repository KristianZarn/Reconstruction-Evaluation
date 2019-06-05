#include "Mesh.h"
#include "PointCloud.h"

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

void Mesh::AddVertex(Eigen::Vector3f& vertex) {
    this->vertices.push_back(vertex);
}

int Mesh::NumVertices() const {
    return static_cast<int>(this->vertices.size());
}

Eigen::Vector3f Mesh::Vertex(int v) const {
    assert(v >= 0 && v < this->NumVertices());
    return this->vertices[v];
}

void Mesh::AddFace(Eigen::Vector3i& face) {
    this->faces.push_back(face);
}

int Mesh::NumFaces() const {
    return static_cast<int>(this->faces.size());
}

Eigen::Vector3i Mesh::Face(int f) const {
    assert(f >= 0 && f < this->NumFaces());
    return this->faces[f];
}

void Mesh::AddVertexQuality(double q) {
    vertex_quality.push_back(q);
}

double Mesh::VertexQuality(int v) const {
    assert(vertices.size() == vertex_quality.size() && v < vertex_quality.size());
    return vertex_quality[v];
}

void Mesh::AddFaceQuality(double q) {
    face_quality.push_back(q);
}

double Mesh::FaceQuality(int f) const {
    assert(faces.size() == face_quality.size() && f < face_quality.size());
    return face_quality[f];
}

void Mesh::ComputeVertexQualityFromFaceQuality() {
    assert(faces.size() == face_quality.size());
    vertex_quality.clear();

    // Colect face quality per vertex
    std::vector<std::vector<double>> quality_vec(vertices.size());

    for (int i = 0; i < faces.size(); i++) {
        Eigen::Vector3i face = faces[i];
        double q = face_quality[i];
        for (int j = 0; j < face.size(); j++) {
            quality_vec[face[j]].push_back(q);
        }
    }

    // Average quality of faces in vertex neighborhood
    for (const auto& vec : quality_vec) {
        double sum = 0.0;
        for (double q : vec) {
            sum += q;
        }
        vertex_quality.push_back(sum / vec.size());
    }
}

PointCloud Mesh::Sample(const int num_samples) const {

    // Build probability distribution over faces
    double area_sum = 0.0;
    std::vector<double> cumsum_area(faces.size());
    for (int i = 0; i < faces.size(); i++) {

        const Eigen::Vector3i& face = faces[i];
        const Eigen::Vector3f& a = vertices[face(0)];
        const Eigen::Vector3f& b = vertices[face(1)];
        const Eigen::Vector3f& c = vertices[face(2)];

        // Compute face area
        double ab_x = b(0) - a(0);
        double ab_y = b(1) - a(1);
        double ab_z = b(2) - a(2);

        double ac_x = c(0) - a(0);
        double ac_y = c(1) - a(1);
        double ac_z = c(2) - a(2);

        double face_area = 0.5 * sqrt(
                pow(ab_y * ac_z - ab_z * ac_y , 2.0) +
                pow(ab_z * ac_x - ab_x * ac_z , 2.0) +
                pow(ab_x * ac_y - ab_y * ac_x , 2.0));

        area_sum += face_area;
        cumsum_area[i] = area_sum;
    }

    // Generate sampled point cloud
    std::mt19937 generator(0);
    std::uniform_real_distribution<double> distribution_face(0.0, area_sum);
    std::uniform_real_distribution<double> distribution_point(0.0, 1.0);
    PointCloud point_cloud;
    for (int i = 0; i < num_samples; i++) {

        // Pick random face
        double rand = distribution_face(generator);
        // int face_id = 0;
        // while (cumsum_area[face_id] < rand) {
        //     face_id++;
        // }
        int face_id = std::lower_bound(cumsum_area.begin(), cumsum_area.end(), rand) - cumsum_area.begin();

        // Pick random point on face
        float r1 = distribution_point(generator);
        float r2 = distribution_point(generator);

        const Eigen::Vector3i& face = faces[face_id];
        const Eigen::Vector3f& a = vertices[face(0)];
        const Eigen::Vector3f& b = vertices[face(1)];
        const Eigen::Vector3f& c = vertices[face(2)];

        float tmp = sqrt(r1);
        Eigen::Vector3f point = (1 - tmp) * a + (tmp * (1 - r2)) * b + (tmp * r2) * c;

        // Add point to point cloud
        point_cloud.AddPoint(point);
        point_cloud.AddPointId(face_id);
        if (face_quality.size() == faces.size()) {
            point_cloud.AddPointQuality(face_quality[face_id]);
        }
    }
    return point_cloud;
}

PointCloud Mesh::SampleSpecial(int num_samples) const {

    // Same as sample but also includes triangle centers
    PointCloud point_cloud = this->Sample(num_samples);
    for (int i = 0; i < faces.size(); i++) {

        const Eigen::Vector3i& face = faces[i];
        const Eigen::Vector3f& a = vertices[face(0)];
        const Eigen::Vector3f& b = vertices[face(1)];
        const Eigen::Vector3f& c = vertices[face(2)];

        // Face center
        Eigen::Vector3f point = (a + b + c) / 3.0f;

        // Add point to point cloud
        point_cloud.AddPoint(point);
        point_cloud.AddPointId(i);
        if (face_quality.size() == faces.size()) {
            point_cloud.AddPointQuality(face_quality[i]);
        }
    }
    return point_cloud;
}

PointCloud Mesh::AsPointCloud() const {
    PointCloud point_cloud;
    for (const auto& vertex : vertices) {
        point_cloud.AddPoint(vertex);
    }

    if (vertex_quality.size() == vertices.size()) {
        for (const auto& q : vertex_quality) {
            point_cloud.AddPointQuality(q);
        }
    }

    return point_cloud;
}

