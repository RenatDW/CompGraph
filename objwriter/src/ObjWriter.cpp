#include "../headers/ObjWriter.h"

#include <fstream>
#include <string>
#include <iostream>

ObjWriter::ObjWriter(const std::string& filename) :
    file(filename, std::ios::binary | std::ios::out | std::ios::trunc)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Ошибка при открытии файла!");
    }
}

void ObjWriter::write(const Model& model)
{
  for (auto& vertex : model.vertices)
  {
	file << "v " << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << std::endl;
  }

  for (auto& texture : model.textureVertices)
  {
	file << "vt " << texture.getX() << " " << texture.getY() << std::endl;
  }

  for (auto& normal : model.normals)
  {
	file << "vn " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
  }

  for (auto& polygon : model.polygons)
  {
	file << "f ";
	
	for (int i = 0; i < polygon.get_vertex_indices().size(); i++)
	{
		file << polygon.get_vertex_indices()[i] << "/";
		
		if (!polygon.get_texture_indices().empty())
		{
			file << polygon.get_texture_indices()[i];
		}

		file << "/";
		
		if (!polygon.get_normal_indices().empty())
		{
			file << polygon.get_normal_indices()[i];
		}

		file << " ";
	}

	file << std::endl;
  }
}

ObjWriter::~ObjWriter()
{
    file.close();
}