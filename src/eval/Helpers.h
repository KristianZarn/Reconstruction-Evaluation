#ifndef SANDBOX_EVALUATION_HELPERS_H
#define SANDBOX_EVALUATION_HELPERS_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Mesh.h"
#include "tinyply/tinyply.h"

Mesh ReadPly(std::string filename);

float MeanDistance(std::vector<float> distances);
float AccuracyMeasure(std::vector<float> distances, float percentage);
float CompletenessMeausre(std::vector<float> distances, float tolerance);

#endif //SANDBOX_EVALUATION_HELPERS_H
