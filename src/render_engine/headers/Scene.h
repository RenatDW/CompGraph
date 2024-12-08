//
// Created by Ренат Асланов on 08.12.2024.
//
#include <iosfwd>
#include <QPainter>
#include <cfloat>

#include "Camera.h"
#include "Renderable.h"
#include "../../model/headers/Model.h"
#include "../../math/headers/Point2D.h"
#include "../../math/headers/Point3D.h"
#include "../../math/headers/PixelBuffer.h"


#include "../../math/headers/DepthBuffer.h"
#ifndef SCENE_H
#define SCENE_H


class Scene
{
public:
	 Scene(const std::vector<Model>& models);
	 void render();
private:
	std::vector<Model> models;
};


#endif //SCENE_H
