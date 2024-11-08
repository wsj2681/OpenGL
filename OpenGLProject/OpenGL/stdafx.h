#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "GL/GL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
using namespace glm;

constexpr float M_PI = 3.1415926f;

#define FOURCC_DXT1 0x31545844 // "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // "DXT5" in ASCII
