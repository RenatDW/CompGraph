//
// Created by Ренат Асланов on 24.12.2024.
//
#include "../../math/headers/Vector3D.h"
#include <QColor>
#ifndef LIGHT_H
#define LIGHT_H
struct Light{
	QColor color;
	Vector3D pos;
};

#endif //LIGHT_H