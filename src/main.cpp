#include "luaState.hpp"
#include "external/zmprinter.hpp"

#include <filesystem>
#include <chrono>
#include <thread>

using namespace zm;
namespace fs = std::filesystem;

printer globalLog("{%t} main log:\n\t{%m}\n");
luaState &ls = luaState::instance();
std::string filePath;

fs::file_time_type last_write;

// this is where is the config reloading happens
void config_reload() {
	while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // check every 0.5s
		auto current_write = fs::last_write_time(filePath);
		if (current_write != last_write) {
			globalLog.print("a change detected");
			last_write = current_write;

			ls.reload();
		}
	}
}




int main (int argc, char *argv[]) {
	// loading the arguments and the file path
	std::vector<std::string> sv;
	for(int i=0; i<argc; i++) {
		sv.push_back(argv[i]);
	}
	// checking for errors
	if(sv.size()<= 1 || sv[1].empty()) {
		globalLog.print("file path not proivided");
		return 1;
	}
	filePath=sv[1];
	if(!ls.load(filePath.c_str())) {
		// initial run
		globalLog.print("could not open file ({%0})", filePath);
		return 1;
	}
	last_write = fs::last_write_time(filePath);
	//reloading loop happens here
	std::thread refresh(config_reload);
	refresh.join();
	return 0;
}
