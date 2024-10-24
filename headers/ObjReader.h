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
// private:
//     static const std::string OBJ_VERTEX_TOKEN;
//     static const std::string OBJ_TEXTURE_TOKEN;
//     static const std::string OBJ_NORMAL_TOKEN;
//     static const std::string OBJ_FACE_TOKEN;
protected:

    static Vector3D parse_vertex(const std::vector<std::string>& words_in_line_without_token, int lineInd);

    static Vector2D parseTextureVertex(const std::vector<std::string>& words_in_line_without_token, int lineInd);

    static Vector3D parse_normal(const std::vector<std::string>& words_in_line_without_words_in_line_without_token, int lineInd) ;

    static Polygon parse_face(const std::vector<std::string>& words_in_line_without_token, int lineInd);

    static void parseFaceWord(std::string word_in_line,
                std::vector<int>& one_polygon_vertex_indices,
                std::vector<int>& one_polygon_texture_vertex_indices,
                std::vector<int>& one_polygon_normal_indices, int lineInd);

};
#endif
