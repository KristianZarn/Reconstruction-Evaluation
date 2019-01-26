#include "Mesh.h"
#include "PointCloud.h"

#include <iostream>
#include <fstream>

void Mesh::add_vertex(Eigen::Vector3f& vertex) {
    this->vertices.push_back(vertex);
}

int Mesh::num_vertices() const {
    return static_cast<int>(this->vertices.size());
}

Eigen::Vector3f Mesh::vertex(int v) const {
    assert(v >= 0 && v < this->num_vertices());
    return this->vertices[v];
}

void Mesh::add_face(Eigen::Vector3i& face) {
    this->faces.push_back(face);
}

int Mesh::num_faces() const {
    return static_cast<int>(this->faces.size());
}

Eigen::Vector3i Mesh::face(int f) const {
    assert(f >= 0 && f < this->num_faces());
    return this->faces[f];
}

bool Mesh::sample(const int N, PointCloud &point_cloud) const {

    // Stores the areas of faces.
    std::vector<float> areas(this->num_faces());
    float sum = 0;

    // Build a probability distribution over faces.
    for (int f = 0; f < this->num_faces(); f++) {
        Eigen::Vector3f a = this->vertices[this->faces[f][0]];
        Eigen::Vector3f b = this->vertices[this->faces[f][1]];
        Eigen::Vector3f c = this->vertices[this->faces[f][2]];

        // Angle between a->b and a->c.
        Eigen::Vector3f ab = b - a;
        Eigen::Vector3f ac = c - a;
        float cos_angle = ab.dot(ac)/(ab.norm()*ac.norm());
        float angle = std::acos(cos_angle);

        // Compute triangle area.
        float area = std::max(0., 0.5*ab.norm()*ac.norm()*std::sin(angle));
        //std::cout << area << " " << std::pow(area, 1./4.) << " " << angle << " " << ab.norm() << " " << ac.norm() << " " << std::sin(angle) << std::endl;

        // Accumulate.
        //area = std::sqrt(area);
        areas[f] = area;
        sum += area;
        //areas.push_back(1);
        //sum += 1;
    }

    //std::cout << sum << std::endl;
    if (sum < 1e-6) {
        std::cout << "[Error] face area sum of " << sum << std::endl;
        return false;
    }

    for (int f = 0; f < this->num_faces(); f++) {
        //std::cout << areas[f] << " ";
        areas[f] /= sum;
        //std::cout << areas[f] << std::endl;
    }

    std::vector<float> cum_areas(areas.size());
    cum_areas[0] = areas[0];

    for (int f = 1; f < this->num_faces(); f++) {
        cum_areas[f] = areas[f] + cum_areas[f - 1];
    }

    for (int f = 0; f < this->num_faces(); f++) {
        int n = std::max(static_cast<int>(areas[f]*N), 1);

        for (int i = 0; i < n; i++) {
            float r1 = 0;
            float r2 = 0;
            do {
                r1 = static_cast<float>(std::rand())/static_cast<float>(RAND_MAX);
                r2 = static_cast<float>(std::rand())/static_cast<float>(RAND_MAX);
            }
            while (r1 + r2 > 1.f);

            int s = std::rand()%3;
            //std::cout << face << " " << areas[face] << std::endl;

            Eigen::Vector3f a = this->vertices[this->faces[f](s)];
            Eigen::Vector3f b = this->vertices[this->faces[f]((s + 1)%3)];
            Eigen::Vector3f c = this->vertices[this->faces[f]((s + 2)%3)];

            Eigen::Vector3f ab = b - a;
            Eigen::Vector3f ac = c - a;

            Eigen::Vector3f point = a + r1*ab + r2*ac;
            point_cloud.add_point(point);
        }
    }

    return true;
}

