
#ifndef __phony_stdinc_hpp_

#define __phony_stdinc_hpp_

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <memory>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <future>
#include <algorithm>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>

#include "fwk/gstate.hpp"
#include "fwk/gstatea.hpp"
#include "fwk/estate.hpp"
#include "fwk/stmgr.hpp"
#include "fwk/game.hpp"

#include "util/tweener.hpp"
#include "util/camera.hpp"
#include "util/perlin.hpp"
#include "util/lscape.hpp"
#include "util/prim.hpp"

#endif //__phony_stdinc_hpp_
