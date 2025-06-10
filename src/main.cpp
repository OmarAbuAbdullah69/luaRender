#include "renderer/image.hpp"
#include <cmath>
using namespace zm;
int main (int argc, char *argv[]) {
	image img1(680, 460, 3);
	image img2(680, 460, 3);

	for(int i=0; i<640; i++) {
		unsigned g;
		g = std::round(255*(i/float(640)));
		for(int j=0; j<460; j++) {
			unsigned r;
			r = std::round(255*(j/float(640)));
			img1.setPixel(i, j, r, g, 0);
			img2.setPixel(i, j, r, g, 0);
		}
	}

	img1.write("img1.png");
	img2.write("img2.png");
	return 0;
}
