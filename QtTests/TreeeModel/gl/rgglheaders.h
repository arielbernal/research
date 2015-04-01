#ifndef RGGLHEADERS_H
#define RGGLHEADERS_H

#define GLM_FORCE_RADIANS
#define GLM_LEFT_HANDED
#define GLM_FORCE_PURE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef M_PI
#define M_PI 3.14159265358f
#endif

#ifndef _WIN32
#define ATTRALIGN __attribute__((aligned(16)))
#else
#define ATTRALIGN __declspec(align(16))
#endif

#endif // RGGLHEADERS_H

