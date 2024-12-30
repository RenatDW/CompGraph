#include "../../math/headers/Vector3D.h"
#include <QColor>
#ifndef LIGHT_H
#define LIGHT_H
struct Light{
	QColor color;
	Vector3D pos;
};

#endif
