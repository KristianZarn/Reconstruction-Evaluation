#ifndef SANDBOX_EVALUATION_HELPERS_H
#define SANDBOX_EVALUATION_HELPERS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Mesh.h"
#include "PointCloud.h"
#include "tinyply/tinyply.h"

Mesh ReadPly(const std::string& filename);
Mesh ReadPlyWithQuality(const std::string& ply_file, const std::string& quality_file);

bool WritePointCloudWithDistance(const std::string& filename,
                                 const PointCloud& pc,
                                 const std::vector<float>& distances);

double MeanDistance(const std::vector<float>& distances);
double Percentile(const std::vector<float>& distances, double percentage);
double Completeness(const std::vector<float>& distances, double tolerance);

#endif //SANDBOX_EVALUATION_HELPERS_H
