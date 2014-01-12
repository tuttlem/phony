
#ifndef __phony_stdinc_hpp_

#define __phony_stdinc_hpp_

extern "C" {
#include <SDL.h>
#include <SDL_mixer.h>

#include <GL/gl.h>
#include <GL/glu.h>
}

#include <cstring>
#include <memory>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <future>
#include <algorithm>
#include <chrono>
#include <exception>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iterator>

#include <glm/glm.hpp>

#include <lua.hpp>

#include "fwk/gstate.hpp"
#include "fwk/gstatea.hpp"
#include "fwk/estate.hpp"
#include "fwk/stmgr.hpp"
#include "fwk/game.hpp"
#include "fwk/mgrbase.hpp"
#include "fwk/tmgr.hpp"
#include "fwk/smgr.hpp"

#include "util/strutil.hpp"
#include "util/timer.hpp"
#include "util/tweener.hpp"
#include "util/camera.hpp"
#include "util/perlin.hpp"
#include "util/lscape.hpp"
#include "util/prim.hpp"
#include "util/tga.hpp"
#include "util/luaconf.hpp"

#endif //__phony_stdinc_hpp_
