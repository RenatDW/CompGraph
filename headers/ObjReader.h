#ifndef OBJREADER_H
#define OBJREADER_H
#include <vector>
#include "Model.h"
#include "Vector3D.h"
#include "Vector2D.h"

class ObjReader
{
public:
    static Model read(std::string& fileContent);
protected:

    static Vector3D parse_vertex(const std::vector<std::string>& words_in_line_without_token, const int& line_ind);

    static Vector2D parseTextureVertex(const std::vector<std::string>& words_in_line_without_token, const int& line_ind);

    static Vector3D parse_normal(const std::vector<std::string>& words_in_line_without_words_in_line_without_token, const int& line_ind) ;

    static Polygon parse_face(const std::vector<std::string>& words_in_line_without_token, const int& line_ind);

    static void parseFaceWord(const std::string& word_in_line,
                std::vector<int>& one_polygon_vertex_indices,
                std::vector<int>& one_polygon_texture_vertex_indices,
                std::vector<int>& one_polygon_normal_indices, const int& line_ind);

};
#endif
