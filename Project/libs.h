#pragma once
#include <GL/glew.h>
#include <iostream>
#include <filesystem>
#include  <GLFW/glfw3.h>

#include "audio.h"
#include "material.h"

#include "miscmethods.h"


#include "daeloader.h"
#include "mesh.h"
#include "ddsimporter.h"
#include "Model.h"
extern "C" {
#include "Libs/lua540/include/lua.h"
#include "Libs/lua540/include/lualib.h"
#include "Libs/lua540/include/lauxlib.h"
}
#ifdef _WIN64
#pragma comment(lib,"Libs/lua540/liblua54.a")
#endif // DEBUG
