#pragma once
#include <string>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

namespace zm {
	class luaState {
		public:
			static luaState &instance() {
				static luaState ls;
				return ls;
			}
			bool load(const char * file);
			bool reload();
		private:
			luaState();
			luaState(const luaState &) = delete;
			luaState &operator =(const luaState &) = delete;
			~luaState();


			lua_State* _state;
			std::string _path;
	};
}
