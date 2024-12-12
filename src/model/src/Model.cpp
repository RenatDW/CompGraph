//
// Created by Ренат Асланов on 09.12.2024.
//

#include "../headers/Model.h"

void Model::deleteVertice(int vertex) {
	//Удалить вершину из списка вершин
	vertices.erase(vertices.begin() + vertex);
	//Удалить вершину из полигонов
	//Тут мы проходимся по всем полигонам, получаем
	// в каждом полигоне массив векторов, и если удаленный
	// вектор находится в этом списке, то мы удаляем полигон
	for (int i = 0; i < polygons.size(); ) { // Используем `i++` только при необходимости
		bool polygonRemoved = false;

		for (int j = 0; j < polygons[i].get_vertex_indices().size(); j++) {
			int currentVertex = polygons[i].get_vertex_indices()[j];

			// Проверяем, нужно ли удалить полигон
			if (currentVertex == vertex) {
				polygons.erase(polygons.begin() + i); // Удаляем текущий полигон
				polygonRemoved = true; // Помечаем, что удаление произошло
				break; // Выходим из внутреннего цикла
			}

			// Обновляем индексы вершин, если они больше удаляемого `vertex`
			if (currentVertex > vertex) {
				polygons[i].get_vertex_indices()[j] =  currentVertex - 1;
			}
		}

		// Увеличиваем индекс только если полигон не был удалён
		if (!polygonRemoved) {
			i++;
		}
	}
}