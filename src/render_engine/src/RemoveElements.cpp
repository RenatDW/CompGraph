//
// Created by Ренат Асланов on 09.12.2024.
//

#include "../headers/RemoveElements.h"
void RemoveElements::deleteVertice(int vertex, Model& mt)
{

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
				mt.polygons.erase(mt.polygons.begin() + vertex); // Удаляем текущий полигон
				polygonRemoved = true; // Помечаем, что удаление произошло
				break; // Выходим из внутреннего цикла
			}

			// Обновляем индексы вершин, если они больше удаляемого `vertex`
			if (currentVertex > vertex)
			{
				mt.polygons[i].get_vertex_indices()[j] = currentVertex - 1;
			}
		}

		// Увеличиваем индекс только если полигон не был удалён
		if (!polygonRemoved)
		{
			i++;
		}
	}

};
