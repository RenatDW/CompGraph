//
// Created by Ренат Асланов on 09.12.2024.
//
#include "../../obj_utils/objreader/ObjReader.h"
#include "../headers/RemoveElements.h"
#include <set>
void RemoveElements::delete_vertex(int vertex, Model& mt)
{
	//TODO Добавить удаление висячих текстур
	//Удалить вершину из списка вершин
	mt.vertices.erase(mt.vertices.begin() + vertex);
	//Удалить вершину из полигонов
	//Тут мы проходимся по всем полигонам, получаем
	// в каждом полигоне массив векторов, и если удаленный
	// вектор находится в этом списке, то мы удаляем полигон
	for (int i = 0; i < mt.polygons.size();)
	{ // Используем `i++` только при необходимости
		bool polygonRemoved = false;

		for (int j = 0; j < mt.polygons[i].get_vertex_indices().size(); j++)
		{
			int currentVertex = mt.polygons[i].get_vertex_indices()[j];

			// Проверяем, нужно ли удалить полигон
			if (currentVertex == vertex)
			{
				mt.polygons.erase(mt.polygons.begin() + i); // Удаляем текущий полигон
				polygonRemoved = true; // Помечаем, что удаление произошло
				break; // Выходим из внутреннего цикла
			}
		}

		// Увеличиваем индекс только если полигон не был удалён
		if (!polygonRemoved)
		{
			i++;
		}
	}


	for (int i = 0; i < mt.polygons.size(); i++)
	{ // Используем `i++` только при необходимости
		for (int j = 0; j < mt.polygons[i].get_vertex_indices().size(); j++)
		{
			int currentVertex = mt.polygons[i].get_vertex_indices()[j];
			// Проверяем, нужно ли удалить полигон
			// Обновляем индексы вершин, если они больше удаляемого `vertex`
			if (currentVertex > vertex)
			{
				std::vector<int> temp = mt.polygons[i].get_vertex_indices();
				temp[j] = currentVertex - 1;
				mt.polygons[i].set_vertex_indices(temp);
			}
		}
	}


	delete_redundant_texture_vertex(mt);

	mt.normals.clear();

	ObjReader::normale_recalculate(mt);
	mt.triangles = ObjReader::triangulation(mt);

}
void RemoveElements::delete_redundant_texture_vertex(Model& mt)
{
	std::set<int> texture;
	for(int i = 0;i < mt.polygons.size(); i++){
		for(int j = 0;j < mt.polygons[i].get_texture_indices().size(); j++){
			texture.insert(mt.polygons[i].get_texture_indices()[j]);
		}
	}
	std::set<int> redundant_texture;
	for(int i = 0; i < mt.textureVertices.size(); i++){
		if(!texture.contains(i)){
			redundant_texture.insert(i);
		}
	}

	for (std::set<int>::iterator it = redundant_texture.end(); it != redundant_texture.begin(); --it)
	{
		mt.textureVertices.erase(mt.textureVertices.begin() + *it);

	}

	int minimal_texture_index = *redundant_texture.begin();
	for (int i = 0; i < mt.textureVertices.size(); i++)
	{ // Используем `i++` только при необходимости
		for (int j = 0; j < mt.polygons[i].get_texture_indices().size(); j++)
		{
			int currentVertex = mt.polygons[i].get_texture_indices()[j];
			// Проверяем, нужно ли удалить полигон
			// Обновляем индексы вершин, если они больше удаляемого `vertex`
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
};
