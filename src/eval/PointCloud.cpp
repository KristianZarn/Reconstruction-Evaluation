#include "PointCloud.h"
#include "Mesh.h"

#include <iostream>
#include <fstream>
#include <omp.h>
#include <cfloat>
#include "triangle_point/poitri.h"

PointCloud::PointCloud(const PointCloud &point_cloud) {
    this->points.clear();

    for (unsigned int i = 0; i < point_cloud.points.size(); i++) {
        this->points.push_back(point_cloud.points[i]);
    }
}

void PointCloud::add_point(const Eigen::Vector3f &point) {
    this->points.push_back(point);
}

unsigned int PointCloud::num_points() const {
    return this->points.size();
}

bool PointCloud::compute_distance(const Mesh &mesh, float &_distance) {
    _distance = 0;

    if (this->num_points() <= 0) {
        std::cout << "[Error] no points in this point clouds" << std::endl;
        return false;
    }

    if (mesh.num_faces() <= 0) {
        std::cout << "[Error] no faces in given mesh" << std::endl;
        return false;
    }

    #pragma omp parallel
    {
        #pragma omp for
        for (unsigned int i = 0; i < this->points.size(); i++) {

            float min_distance = FLT_MAX;
            for (int f = 0; f < mesh.num_faces(); f++) {
                Eigen::Vector3f closest_point;
                Eigen::Vector3f v1 = mesh.vertex(mesh.face(f)(0));
                Eigen::Vector3f v2 = mesh.vertex(mesh.face(f)(1));
                Eigen::Vector3f v3 = mesh.vertex(mesh.face(f)(2));

                triangle_point_distance(this->points[i], v1, v2, v3, closest_point);
                float distance = (this->points[i] - closest_point).norm();

                if (distance < min_distance) {
                    min_distance = distance;
                }
            }

            #pragma omp atomic
            _distance += min_distance;
        }
    }

    _distance /= this->num_points();
    return true;
}

float PointCloud::triangle_point_distance(const Eigen::Vector3f point,
                                          const Eigen::Vector3f v1,
                                          const Eigen::Vector3f v2,
                                          const Eigen::Vector3f v3,
                                          Eigen::Vector3f& closest_point) {

    Vec3f x0(point.data());
    Vec3f x1(v1.data());
    Vec3f x2(v2.data());
    Vec3f x3(v3.data());

    Vec3f r(0);
    float distance = point_triangle_distance(x0, x1, x2, x3, r);

    for (int d = 0; d < 3; d++) {
        closest_point(d) = r[d];
    }

    return distance;
}