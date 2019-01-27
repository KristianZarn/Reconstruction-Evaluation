#ifndef SANDBOX_EVALUATION_POINTCLOUD_H
#define SANDBOX_EVALUATION_POINTCLOUD_H

#include <vector>
#include <string>
#include <Eigen/Core>

class Mesh;

class PointCloud {
public:
    void AddPoint(const Eigen::Vector3f& point);
    int NumPoints() const;
    Eigen::Vector3f Point(int p) const;

    std::vector<float> ComputeDistanceBF(const PointCloud& query) const;
    std::vector<float> ComputeDistance(const PointCloud& query) const;

    void WriteToTxt(const std::string& filename) const;

private:
    std::vector<Eigen::Vector3f> points;
};

#endif //SANDBOX_EVALUATION_POINTCLOUD_H
