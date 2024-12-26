#ifndef REMOVEELEMENTS_H
#define REMOVEELEMENTS_H

#include "../model/headers/Model.h"
#include "../../obj_utils/objreader/ObjReader.h"

class RemoveElements
{
public:
	static void delete_vertex(int vertex, Model& mt);
	static void delete_triangle(int triangle_id, Model& mt);
	static void delete_redundant_texture_vertex(Model& mt);
};

#endif //REMOVEELEMENTS_H
