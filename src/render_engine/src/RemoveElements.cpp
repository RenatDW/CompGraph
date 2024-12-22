//
// Created by Ренат Асланов on 09.12.2024.
//
#include "../../obj_utils/objreader/ObjReader.h"
#include "../headers/RemoveElements.h"
void RemoveElements::deleteVertice(int vertex, Model& mt)
{
	std::set<int> te

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
	mt.normals.clear();

	ObjReader::normale_recalculate(mt);
	mt.triangles = ObjReader::triangulation(mt);


};
