#ifndef SANDBOX_EVALUATION_HELPERS_H
#define SANDBOX_EVALUATION_HELPERS_H

#include <iostream>
#include <fstream>

#include "Mesh.h"
#include "tinyply/tinyply.h"

Mesh ReadPly(std::string filename);

#endif //SANDBOX_EVALUATION_HELPERS_H
