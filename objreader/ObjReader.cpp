#include "../headers/ObjReader.h"
#include "../headers/Model.h"
#include "../headers/Polygon.h"
#include "../headers/Vector3D.h"
#include "../headers/ObjReaderException.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
static const std::string OBJ_VERTEX_TOKEN{"v"};
static const std::string OBJ_TEXTURE_TOKEN{"vt"};
static const std::string OBJ_NORMAL_TOKEN{"vn"};
static const std::string OBJ_FACE_TOKEN{"f"};

Model ObjReader::read(std::string &fileContent)
{
    Model result = Model();

    if (std::ifstream in(fileContent); in.is_open()) {
        std::string line;
        int line_ind = 0;
        while (std::getline(in, line)) {
            std::vector<std::string> words_in_line;
            std::istringstream stream(line);
            std::string word;

            while (stream >> word) {
                words_in_line.push_back(word);
            }

            if (words_in_line.empty()) {
                continue;
            }

            std::string token(words_in_line.front());
            words_in_line.erase(words_in_line.begin());
            ++line_ind;

            if (token == OBJ_VERTEX_TOKEN) {
                result.vertices.emplace_back(parse_vertex(words_in_line, line_ind));
            } else if (token == OBJ_TEXTURE_TOKEN) {
                result.textureVertices.emplace_back(parse_texture_vertex(words_in_line, line_ind));
            } else if (token == OBJ_NORMAL_TOKEN) {
                result.normals.emplace_back(parse_normal(words_in_line, line_ind));
            } else if (token == OBJ_FACE_TOKEN) {
                result.polygons.emplace_back(parse_face(words_in_line, line_ind));
            }
        }
    }
    std::vector<Triangle> triangles;
    Triangle add;
    for (Polygon element: result.polygons) {
        std::vector<int> vertices;
        vertices.emplace_back(element.get_vertex_indices()[0]);
        for (int i = 0; i < element.get_vertex_indices().size(); ++i) {
            for (int j = 1; j < 3; ++j) {
                if (element.get_vertex_indices().size() < 2 + i) {
                    break;
                }
                vertices.emplace_back(element.get_vertex_indices()[i + j]);
            }
        }
        add.set_vertex_indices(vertices);
        triangles.emplace_back(add);
    }
    result.triangles = triangles;
    return result;
}


//TODO Понять как сюда добавить указатели
Vector3D ObjReader::parse_vertex(const std::vector<std::string> &words_in_line_without_token,
                                 const int &line_ind)
{
    try {
        return {
            std::stof(words_in_line_without_token.at(0)),
            std::stof(words_in_line_without_token.at(1)),
            std::stof(words_in_line_without_token.at(2))
        };
    } catch (const std::invalid_argument &) {
        throw ObjReaderException("Failed to parse float value.", line_ind);
    } catch (const std::out_of_range &) {
        throw ObjReaderException("Too few vertex arguments.", line_ind);
    }
}

Vector2D ObjReader::parse_texture_vertex(const std::vector<std::string> &words_in_line_without_token,
                                         const int &line_ind)
{
    try {
        return {
            std::stof(words_in_line_without_token.at(0)),
            std::stof(words_in_line_without_token.at(1))
        };
    } catch (const std::invalid_argument &) {
        throw ObjReaderException("Failed to parse float value.", line_ind);
    } catch (const std::out_of_range &) {
        throw ObjReaderException("Too few vertex arguments.", line_ind);
    }
}

Vector3D ObjReader::parse_normal(
    const std::vector<std::string> &words_in_line_without_words_in_line_without_token,
    const int &line_ind)
{
    try {
        return {
            std::stof(words_in_line_without_words_in_line_without_token.at(0)),
            std::stof(words_in_line_without_words_in_line_without_token.at(1)),
            std::stof(words_in_line_without_words_in_line_without_token.at(2))
        };
    } catch (const std::invalid_argument &) {
        throw ObjReaderException("Failed to parse float value.", line_ind);
    } catch (const std::out_of_range &) {
        throw ObjReaderException("Too few vertex arguments.", line_ind);
    }
}

Polygon ObjReader::parse_face(const std::vector<std::string> &words_in_line_without_token,
                              const int &line_ind)
{
    std::vector<int> one_polygon_vertex_indices = std::vector<int>();
    std::vector<int> one_polygon_texture_vertex_indices = std::vector<int>();
    std::vector<int> one_polygon_normal_indices = std::vector<int>();

    for (const std::string &s: words_in_line_without_token) {
        parse_face_word(s, one_polygon_vertex_indices, one_polygon_texture_vertex_indices,
                        one_polygon_normal_indices,
                        line_ind);
    }


    Polygon result = Polygon();
    std::vector<Triangle> triangles();
    result.set_vertex_indices(one_polygon_vertex_indices);
    result.set_texture_indices(one_polygon_texture_vertex_indices);
    result.set_normal_indices(one_polygon_normal_indices);
    std::vector<Triangle> result2;
    // result.triangulation();
    return result;
}

void ObjReader::parse_face_word(const std::string &word_in_line, std::vector<int> &one_polygon_vertex_indices,
                                std::vector<int> &one_polygon_texture_vertex_indices,
                                std::vector<int> &one_polygon_normal_indices, const int &line_ind)
{
    try {
        std::vector<std::string> word_indices = std::vector<std::string>();

        std::vector<std::string> words_in_line;
        std::istringstream stream(word_in_line);
        std::string word;
        while (std::getline(stream, word, '/')) {
            word_indices.emplace_back(word);
        }

        switch (word_indices.size()) {
            case 1:
            {
                one_polygon_vertex_indices.emplace_back(std::stoi(word_indices[0]) - 1);
                break;
            }
            case 2:
            {
                one_polygon_vertex_indices.emplace_back(std::stoi(word_indices[0]) - 1);
                one_polygon_texture_vertex_indices.emplace_back(std::stoi(word_indices[1]) - 1);
                break;
            }
            case 3:
            {
                one_polygon_vertex_indices.emplace_back(std::stoi(word_indices[0]) - 1);
                one_polygon_normal_indices.emplace_back(std::stoi(word_indices[2]) - 1);
                if (!word_indices[1].empty()) {
                    one_polygon_texture_vertex_indices.emplace_back(std::stoi(word_indices[1]) - 1);
                }
                break;
            }
            default:
            {
                // throw ObjReaderException("Invalid element size.", line_ind);
            }
        }
    } catch (const std::invalid_argument &) {
        throw ObjReaderException("Failed to parse float value.", line_ind);
    } catch (const std::out_of_range &) {
        throw ObjReaderException("Too few vertex arguments.", line_ind);
    }
}
