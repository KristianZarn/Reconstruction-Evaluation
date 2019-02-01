#ifndef SANDBOX_EVALUATION_HELPERS_H
#define SANDBOX_EVALUATION_HELPERS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Mesh.h"
#include "tinyply/tinyply.h"

Mesh ReadPly(const std::string& filename);

double MeanDistance(const std::vector<float>& distances);
double Percentile(const std::vector<float>& distances, double percentage);
double Completeness(const std::vector<float>& distances, double tolerance);

#endif //SANDBOX_EVALUATION_HELPERS_H
