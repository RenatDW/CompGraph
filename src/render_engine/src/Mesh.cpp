
#include "../headers/Mesh.h"

#include <cmath>
#include <QPainter>
#include <iostream>

#include "../../math/headers/Point3D.h"

void Mesh::show_mesh(float weight_a, float weight_b, float weight_c, int& r, int& g, int& b, QColor background)
{
    if (weight_a > 0.02f && weight_b > 0.02f && weight_c > 0.02f) {
		r = background.red(), g = background.green(), b = background.blue();
	}
}

bool Mesh::show_selection(float weight_a, float weight_b, float weight_c, int cursorX, int cursorY, int pixelX, int pixelY)
{
	int epsi = 4;
//	std::cout << cursorX - pixelX << ", " << cursorY- pixelY << std::endl;

	if ((abs(cursorX - pixelX)*abs(cursorX - pixelX) + abs(cursorY- pixelY)*abs(cursorY- pixelY) < epsi*epsi)) {
		return true;
	}

	return false;
}

