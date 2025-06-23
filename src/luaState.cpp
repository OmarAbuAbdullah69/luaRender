#include "luaState.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

namespace zm {
	luaState::luaState() {
		_state = luaL_newstate();
  	luaL_openlibs(_state);
	}
	luaState::~luaState() {
		lua_close(_state);
	}
	bool luaState::load(const char *path) {
		_path = path;
		return !luaL_dofile(_state, _path.c_str());
	}
	bool luaState::reload() {
		lua_close(_state);
		_state = luaL_newstate();
		luaL_openlibs(_state);
		if(luaL_dofile(_state, _path.c_str()) != LUA_OK) {
			lua_pop(_state, 1);
			return false;
		}
		return true;
	}
}
