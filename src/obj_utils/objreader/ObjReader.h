#ifndef OBJREADER_H
#define OBJREADER_H

#include "../../model/headers/Model.h"
#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Vector2D.h"

#include <vector>
#include <string>

class ObjReader
{
public:
    static std::vector<Triangle> triangulation(const Model &result);

    static std::vector<Vector3D>::value_type get_vertex(Model &result, Polygon &element, int i, int j);

    static Vector3D calculate_normal_vector(Model &result, Polygon &element, int main_vertex, int next_vertex, int prev_vertex);

    static void normale_recalculate(Model &result);

    static Model read(std::string &fileContent);

protected:
    static Vector3D parse_vertex(const std::vector<std::string> &words_in_line_without_token, const int &line_ind);

    static Vector2D parse_texture_vertex(const std::vector<std::string> &words_in_line_without_token,
                                         const int &line_ind);

    static Vector3D parse_normal(const std::vector<std::string> &words_in_line_without_words_in_line_without_token,
                                 const int &line_ind);

    static Polygon parse_face(const std::vector<std::string> &words_in_line_without_token, const int &line_ind);

    static void parse_face_word(const std::string &word_in_line,
                                std::vector<int> &one_polygon_vertex_indices,
                                std::vector<int> &one_polygon_texture_vertex_indices,
                                std::vector<int> &one_polygon_normal_indices, const int &line_ind);

    static std::vector<int> normale_recalculate();
};
#endif
