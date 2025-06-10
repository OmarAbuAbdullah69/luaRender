#include "renderer/image.hpp"

#include "external/stbi_image_write.hpp"
#include <cstdlib>
#include <cstring>
namespace zm {
	printer image::s_logger("{%t}:imageLog\n\t{%m}\n");
	image::image(unsigned width, unsigned height, unsigned channels)
		:_width(width), _height(height), _channels(channels) {
		if (!width || !height || !channels) {
			s_logger.print("ERROR: creating a file with atribs => width({%0}), height({%1}), channels({%2})", width, height, channels);
			std::exit(1);
		}
		unsigned size = _width*_height*_channels;
		_data = static_cast<unsigned char *>(std::malloc(size));
		if(!_data) {
			s_logger.print("ERROR couldn't createemory for the image loaded with width({%0}), height({%1}), channels({%2})", width, height, channels);
			std::exit(1);
		}
		std::memset(_data, 0, size);
		stbi_flip_vertically_on_write(true);
	}
	image::image(const image &img) {
		_width = img._width;
		_height = img._height;
		_channels = img._channels;

		std::memcpy(_data, img._data, _width*_height*_channels);
	}
	image::~image() {
		std::free(_data);
	}
	void image::setPixel(unsigned x, unsigned y, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		unsigned char *pixel= &_data[(y*_width+x)*_channels];
		*(pixel+0) = r;
		*(pixel+1) = g;
		*(pixel+2) = b;
		if(_channels == 3) return;
		*(pixel+3) = b;
	}
	void image::write(const char *dist) {
		stbi_write_png(dist, _width, _height, _channels, _data, 0);
	}

}
