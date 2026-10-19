// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define GLM_ENABLE_EXPERIMENTAL

// add headers that you want to pre-compile here
#include "Framework\framework.h"

//Standard Library Includes
#include <map>
#include <list>
#include <array>
#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

//Third Party Includes

#include <fmod.hpp>
#include <fmod_errors.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include <rapidjson/error/en.h>
#include <rapidjson/istreamwrapper.h>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#endif //PCH_H
