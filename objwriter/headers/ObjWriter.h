#ifndef OBJWRITER_H
#define OBJWRITER_H

#include "../../model/headers/Model.h"

#include <string>
#include <fstream>

class ObjWriter
{
public:
	ObjWriter(const std::string& filename);

	void write(const Model& model);

	~ObjWriter();
	
private:
	std::ofstream file;
};

#endif