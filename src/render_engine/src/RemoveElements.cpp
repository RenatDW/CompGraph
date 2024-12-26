#include "../../obj_utils/objreader/ObjReader.h"
#include "../headers/RemoveElements.h"

#include <set>

void RemoveElements::delete_vertex(int vertex, Model& mt)
{
	//TODO Добавить удаление висячих текстур
	mt.vertices.erase(mt.vertices.begin() + vertex);
	for (int i = 0; i < mt.polygons.size();)
	{
		bool polygonRemoved = false;

		for (int j = 0; j < mt.polygons[i].get_vertex_indices().size(); j++)
		{
			int currentVertex = mt.polygons[i].get_vertex_indices()[j];

			if (currentVertex == vertex)
			{
				mt.polygons.erase(mt.polygons.begin() + i);
				polygonRemoved = true;
				break;
			}
		}

		if (!polygonRemoved)
		{
			i++;
		}
	}

	for (auto & polygon : mt.polygons)
	{
		for (int j = 0; j < polygon.get_vertex_indices().size(); j++)
		{
			int currentVertex = polygon.get_vertex_indices()[j];

			if (currentVertex > vertex)
			{
				std::vector<int> temp = polygon.get_vertex_indices();
				temp[j] = currentVertex - 1;
				polygon.set_vertex_indices(temp);
			}
		}
	}
//	delete_redundant_texture_vertex(mt);
	mt.normals.clear();

	ObjReader::normale_recalculate(mt);
	mt.triangles = ObjReader::triangulation(mt);

}
void RemoveElements::delete_redundant_texture_vertex(Model& mt)
{
	std::set<int> texture;
	for(auto & polygon : mt.polygons){
		for(int j = 0;j < polygon.get_texture_indices().size(); j++){
			texture.insert(polygon.get_texture_indices()[j]);
		}
	}
	std::set<int> redundant_texture;
	for(int i = 0; i < mt.textureVertices.size(); i++){
		if(!texture.contains(i)){
			redundant_texture.insert(i);
		}
	}

	for (auto it = redundant_texture.end(); it != redundant_texture.begin(); --it)
	{
		mt.textureVertices.erase(mt.textureVertices.begin() + *it);

	}

	int minimal_texture_index = *redundant_texture.begin();
	for (int i = 0; i < mt.textureVertices.size(); i++)
	{
		for (int j = 0; j < mt.polygons[i].get_texture_indices().size(); j++)
		{
			int currentVertex = mt.polygons[i].get_texture_indices()[j];

			if (currentVertex > minimal_texture_index)
			{
				std::vector<int> temp = mt.polygons[i].get_texture_indices();
				temp[j] = currentVertex;

				for(auto elem: redundant_texture)
				{
					if(currentVertex < elem)
					{
						temp[j]--;
					}
				}
				mt.polygons[i].set_texture_indices(temp);
			}
		}
	}
}
void RemoveElements::delete_triangle(int triangle_id, Model& mt)
{
	mt.triangles.erase(mt.triangles.begin() + triangle_id);
};
