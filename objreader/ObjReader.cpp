#include "../headers/ObjReader.h"
#include "../headers/Model.h"
#include "../headers/Polygon.h"
#include "../headers/Vector3D.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
static const std::string OBJ_VERTEX_TOKEN {"v"};
static const std::string OBJ_TEXTURE_TOKEN {"vt"};
static const std::string OBJ_NORMAL_TOKEN {"vn"};
static const std::string OBJ_FACE_TOKEN {"f"};

Model ObjReader::read(std::string &fileContent) {
    Model result = Model();
    std::string line;
    int lineInd = 0;

    std::ifstream in(fileContent); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            std::vector<std::string> words_in_line;
            std::istringstream stream(line);
            std::string word;
            while (stream >> word)
            {
                words_in_line.push_back(word);
            }

       if (words_in_line.empty()) {
            continue;
       }// TODO Возможно стоит сделать через указатель

            std::string token(words_in_line.front());
            words_in_line.erase(words_in_line.begin());

        ++lineInd;
            //Возможно стоит заменить на push_back()
            if (token == OBJ_VERTEX_TOKEN) {
                result.vertices.emplace_back(parse_vertex(words_in_line, lineInd));
            }else if (token == OBJ_TEXTURE_TOKEN) {
                result.textureVertices.emplace_back(parseTextureVertex(words_in_line, lineInd));
            }else if (token == OBJ_NORMAL_TOKEN) {
                result.normals.emplace_back(parse_normal(words_in_line, lineInd));
            }else if (token == OBJ_FACE_TOKEN) {
                result.polygons.emplace_back(parse_face(words_in_line, lineInd));
            }
    std::cout << line << std::endl;
    }
    in.close();     // закрываем файл
    }
    return result;
}
//TODO Доделать обработку ошибок и Понять как сюда добавить указатели
Vector3D ObjReader::parse_vertex(const std::vector<std::string> &words_in_line_without_token, int lineInd) {
    try {
        return Vector3D(
                std::stof(words_in_line_without_token.at(0)),
                std::stof(words_in_line_without_token.at(1)),
                std::stof(words_in_line_without_token.at(2)));
    }catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    std::cout << "The End..." << std::endl;

        // } catch(NumberFormatException e) {
        //     throw new ObjReaderException("Failed to parse float value.", lineInd);
        //
        // } catch(IndexOutOfBoundsException e) {
        //     throw new ObjReaderException("Too few vertex arguments.", lineInd);
        // }
}

Vector2D ObjReader::parseTextureVertex(const std::vector<std::string> &words_in_line_without_token, int lineInd) {
    try {
        return Vector2D(
        std::stof(words_in_line_without_token.at(0)),
        std::stof(words_in_line_without_token.at(1)));

    }catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    std::cout << "The End..." << std::endl;

}

Vector3D ObjReader::parse_normal(const std::vector<std::string> &words_in_line_without_words_in_line_without_token, int lineInd) {
    try {
        return Vector3D(
                std::stof(words_in_line_without_words_in_line_without_token.at(0)),
                std::stof(words_in_line_without_words_in_line_without_token.at(1)),
                std::stof(words_in_line_without_words_in_line_without_token.at(2)));
    }catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    std::cout << "The End..." << std::endl;

}

Polygon ObjReader::parse_face(const std::vector<std::string> &words_in_line_without_token, int lineInd) {
    std::vector<int> one_polygon_vertex_indices = std::vector<int>() ;
    std::vector<int>  one_polygon_texture_vertex_indices = std::vector<int>();
    std::vector<int> one_polygon_normal_indices = std::vector<int>();

    for (std::string s : words_in_line_without_token) {
        parseFaceWord(s, one_polygon_vertex_indices, one_polygon_texture_vertex_indices, one_polygon_normal_indices, lineInd);
    }

    Polygon result = Polygon();
    result.set_vertex_indices(one_polygon_vertex_indices);
    result.set_texture_indices(one_polygon_texture_vertex_indices);
    result.set_normal_indices(one_polygon_normal_indices);
    // result.triangulation();
    return result;
}

void ObjReader::parseFaceWord(std::string word_in_line, std::vector<int> &one_polygon_vertex_indices,
                              std::vector<int> &one_polygon_texture_vertex_indices, std::vector<int> &one_polygon_normal_indices, int lineInd) {
    try {
        std::vector<std::string> word_indices = std::vector<std::string>();

        std::vector<std::string> words_in_line;
        std::istringstream stream(word_in_line);
        std::string word;
        while (std::getline(stream, word, '/')) {
            word_indices.push_back(word);
        }

        switch (word_indices.size()) {
            case 1 :{
                one_polygon_vertex_indices.push_back(std::stof(word_indices[0]) - 1);
            }
            case 2 : {
                one_polygon_vertex_indices.push_back(std::stof(word_indices[0]) - 1);
                 one_polygon_texture_vertex_indices.push_back(std::stof(word_indices[1]) - 1);
            }
            case 3 : {
                one_polygon_vertex_indices.push_back(std::stof(word_indices[0]) - 1);
                one_polygon_normal_indices.push_back(std::stof(word_indices[2]) - 1);
                if (!word_indices[1].empty()) {
                    one_polygon_texture_vertex_indices.push_back(std::stof(word_indices[1]) - 1);
                }
            }
            default :{
                // throw new ObjReaderException("Invalid element size.", lineInd);
            }
        }
    }catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
    std::cout << "The End..." << std::endl;
}


// Для структур типа вершин методы написаны так, чтобы ничего не знать о внешней среде.
// Они принимают только то, что им нужно для работы, а возвращают только то, что могут создать.
// Исключение - индекс строки. Он прокидывается, чтобы выводить сообщение об ошибке.
// Могло быть иначе. Например, метод parseVertex мог вместо возвращения вершины принимать вектор вершин
// модели или сам класс модели, работать с ним.
// Но такой подход может привести к большему количеству ошибок в коде. Например, в нем что-то может
// тайно сделаться с классом модели.
// А еще это портит читаемость
// И не стоит забывать про тесты. Чем проще вам задать данные для теста, проверить, что метод рабочий,
// тем лучше.