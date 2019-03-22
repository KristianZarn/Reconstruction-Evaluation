#include "PointCloud.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <omp.h>

#include "nanoflann.hpp"

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

void PointCloud::AddPointQuality(double q) {
    point_quality.push_back(q);
}

double PointCloud::PointQuality(int p) const {
    assert(points.size() == point_quality.size() && p < point_quality.size());
    return point_quality[p];
}

bool PointCloud::HasQuality() const {
    return points.size() == point_quality.size();
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
    Eigen::MatrixXf this_data(points.size(), 3);
    for (int i = 0; i < points.size(); i++) {
        this_data.row(i) = points[i];
    }

    // Initialize kd tree
    typedef nanoflann::KDTreeEigenMatrixAdaptor<Eigen::MatrixXf> KDTree;
    KDTree kd_tree(3, std::cref(this_data), 10);
    kd_tree.index->buildIndex();

    // Compute closest distances
    std::vector<float> distances(static_cast<unsigned long>(query.NumPoints()));
    for (int i = 0; i < query.NumPoints(); i++) {
        Eigen::Vector3f point = query.Point(i);

        unsigned long num_results = 1;
        std::vector<size_t> idx(num_results);
        std::vector<float> dist_sqr(num_results);
        nanoflann::KNNResultSet<float> result_set(num_results);
        result_set.init(&idx[0], &dist_sqr[0]);

        kd_tree.index->findNeighbors(result_set, point.data(), nanoflann::SearchParams(10));

        distances[i] = static_cast<float>(sqrt(dist_sqr[0]));
    }

    return distances;
}

void PointCloud::WriteToTxt(const std::string& filename) const {
    std::ofstream outfile(filename);

    if (!outfile) {
        std::cout << "Could not open file: " << filename << std::endl;
        return;
    }

    for (int i = 0; i < points.size(); i++) {
        const auto& point = points[i];
        outfile << point(0) << " " << point(1) << " " << point(2);

        if (point_quality.size() == points.size()) {
            outfile << " " << point_quality[i];
        }

        outfile << "\n";
    }
}
