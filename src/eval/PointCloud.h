#ifndef SANDBOX_EVALUATION_POINTCLOUD_H
#define SANDBOX_EVALUATION_POINTCLOUD_H

#include <vector>
#include <string>
#include <Eigen/Core>

class Mesh;

class PointCloud {
public:
    PointCloud() = default;
    PointCloud(const PointCloud &point_cloud);

    void add_point(const Eigen::Vector3f &point);
    unsigned int num_points() const;

    bool compute_distance(const Mesh &mesh, float &_distance);

private:
    std::vector<Eigen::Vector3f> points;

    /** \brief Compute triangle point distance and corresponding closest point.
     * \param[in] point point
     * \param[in] v1 first vertex
     * \param[in] v2 second vertex
     * \param[in] v3 third vertex
     * \param[out] ray corresponding closest point
     * \return distance
     */
    float triangle_point_distance(const Eigen::Vector3f point,
                                  const Eigen::Vector3f v1,
                                  const Eigen::Vector3f v2,
                                  const Eigen::Vector3f v3,
                                  Eigen::Vector3f& closest_point);
};

#endif //SANDBOX_EVALUATION_POINTCLOUD_H
