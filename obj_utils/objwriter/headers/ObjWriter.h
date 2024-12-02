#ifndef OBJWRITER_H
#define OBJWRITER_H

#include "../../../model/headers/Model.h"

#include <string>
#include <fstream>

class ObjWriter
{
public:
	static void write(const Model& model, const std::string& filename);

};

#endif