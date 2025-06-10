#pragma once

#include "external/zmprinter.hpp"
namespace zm {
	class image {
		public:
			image(unsigned width, unsigned height, unsigned channels);
			image(const image &img);
			~image();
			void setPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a=255);
			void write(const char *dist);
		private:
			static printer s_logger;
			unsigned _width, _height, _channels;
			unsigned char *_data;
	};
}
