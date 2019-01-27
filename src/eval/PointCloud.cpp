#include "PointCloud.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <omp.h>

#include "triangle_point/poitri.h"
#include "kdtree_flann.h"

void PointCloud::AddPoint(const Eigen::Vector3f& point) {
    this->points.push_back(point);
}

int PointCloud::NumPoints() const {
    return static_cast<int>(this->points.size());
}

Eigen::Vector3f PointCloud::Point(int p) const {
    assert(p >= 0 && p < NumPoints());
    return points[p];
}

std::vector<float> PointCloud::ComputeDistanceBF(const PointCloud& query) const {
    std::vector<float> distances(static_cast<unsigned long>(query.NumPoints()));

    for (int i = 0; i < query.NumPoints(); i++) {

        float min_distance = std::numeric_limits<float>::max();
        for (int j = 0; j < points.size(); j++) {

            float distance = (query.Point(i) - points[j]).norm();
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
        distances[i] = min_distance;
    }

    return distances;
}

std::vector<float> PointCloud::ComputeDistance(const PointCloud& query) const {

    // Convert points to eigen matrix
    Eigen::MatrixXf this_data(3, points.size());
    for (int i = 0; i < points.size(); i++) {
        this_data.col(i) = points[i];
    }

    Eigen::MatrixXf query_data(3, query.NumPoints());
    for (int i = 0; i < query.NumPoints(); i++) {
        query_data.col(i) = query.Point(i);
    }

    // Compute distances with kd tree
    kdt::KDTreeFlannf kd_tree;
    kd_tree.setData(this_data, true);
    kd_tree.build();

    Eigen::MatrixXf dists;
    Eigen::MatrixXi idx;
    size_t knn = 1;
    kd_tree.query(query_data, knn, idx, dists);

    // Convert result from eigen to vector
    std::vector<float> distances(static_cast<unsigned long>(query.NumPoints()));
    for (int i = 0; i < query.NumPoints(); i++) {
        distances[i] = dists(0, i);
    }

    return distances;
}

void PointCloud::WriteToTxt(const std::string& filename) const {
    std::ofstream outfile(filename);

    if (!outfile) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    for (const auto& point : points) {
        outfile << point(0) << " " << point(1) << " " << point(2) << "\n";
    }
}
