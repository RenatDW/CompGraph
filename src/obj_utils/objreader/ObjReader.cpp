#include "ObjReader.h"
#include "../../model/headers/Model.h"
#include "../../model/headers/Polygon.h"
#include "../../math/headers/Vector3D.h"
#include "ObjReaderException.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

static const std::string OBJ_VERTEX_TOKEN{"v"};
static const std::string OBJ_TEXTURE_TOKEN{"vt"};
static const std::string OBJ_NORMAL_TOKEN{"vn"};
static const std::string OBJ_FACE_TOKEN{"f"};

std::vector<Triangle> ObjReader::triangulation(const Model &result)
{
    std::vector<Triangle> triangles;
    Triangle add;
    for (const Polygon &element: result.polygons) {
        // Polygon &element: result.polygons 13354
        // Polygon element = result.polygons[k];
        for (int i = 0; i < element.get_vertex_indices().size() - 2; ++i) {
            std::vector<int> vertices;
            std::vector<int> normale;
            std::vector<int> texture;
            vertices.emplace_back(element.get_vertex_indices()[0]);
            normale.emplace_back(element.get_normal_indices()[0]);
            texture.emplace_back(element.get_texture_indices()[0]);
            for (int j = 1; j < 3; ++j) {
                vertices.emplace_back(element.get_vertex_indices()[i + j]);
                normale.emplace_back(element.get_normal_indices()[i + j]);
                texture.emplace_back(element.get_texture_indices()[i + j]);
            }
            add.set_vertex_indices(vertices);
            add.set_normal_indices(normale);
            add.set_texture_indices(texture);
            triangles.emplace_back(add);
        }
    }
    return triangles;
}

std::vector<Vector3D>::value_type ObjReader::get_vertex(Model &result, Polygon &element, int i, int j)
{
    Vector3D vertex1 = result.vertices[element.get_vertex_indices()[i]];
    Vector3D vertex2 = result.vertices[element.get_vertex_indices()[j]];
    return vertex1 - vertex2;
}

Vector3D ObjReader::calculate_normal_vector(Model &result, Polygon &element, int main_vertex,
                                            int next_vertex, int prev_vertex)
{
    Vector3D v1 = get_vertex(result, element, next_vertex, main_vertex);
    Vector3D v2 = get_vertex(result, element, prev_vertex, main_vertex);
    return Vector3D::cross(v1, v2).normalize();
}

void ObjReader::normale_recalculate(Model &result)
{
    int cnt = 0;
    //TODO не забыть изменить

    for (Polygon &element: result.polygons) {
        const int max_vector_size = element.get_vertex_indices().size() - 1;
        Vector3D last_ans = calculate_normal_vector(result, element, 0, 1, max_vector_size);
        Vector3D ans;
        std::vector<int> normale;
        result.normals.emplace_back(last_ans);
        normale.emplace_back(cnt);
        for (int i = 1; i < element.get_vertex_indices().size() - 1; i++) {
            ans = calculate_normal_vector(result, element, i, i + 1, i - 1);
            if (last_ans != ans) {
                cnt++;
                result.normals.emplace_back(ans);
                normale.emplace_back(cnt);
                last_ans = ans;
            } else {
                normale.emplace_back(cnt);
            }
        }
        ans = calculate_normal_vector(result, element, max_vector_size, 0, max_vector_size - 1);
        if (last_ans != ans) {
            cnt++;
            result.normals.emplace_back(ans);
            normale.emplace_back(cnt);
        } else {
            normale.emplace_back(cnt);
        }
        cnt++;
        element.set_normal_indices(normale);
    }
}

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
            } else if (token == OBJ_FACE_TOKEN) {
                result.polygons.emplace_back(parse_face(words_in_line, line_ind));
            }
        }
        normale_recalculate(result);
        result.triangles = triangulation(result);
        return result;
    } else {
        throw ObjReaderException("Не удалось открыть файл", 0);
    }
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
    result.set_vertex_indices(one_polygon_vertex_indices);
    result.set_texture_indices(one_polygon_texture_vertex_indices);
    result.set_normal_indices(one_polygon_normal_indices);
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
