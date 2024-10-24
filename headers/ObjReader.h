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
private:
    static const std::string OBJ_VERTEX_TOKEN = "v";
    static const std::string OBJ_TEXTURE_TOKEN = "vt";
    static const std::string OBJ_NORMAL_TOKEN = "vn";
    static const std::string OBJ_FACE_TOKEN = "f";
protected:

    static Vector3D parseVertex(const std::vector<std::string>& wordsInLineWithoutToken, int lineInd&);

    static Vector2D parseTextureVertex(const std::vector<std::string>& wordsInLineWithoutToken, int lineInd&);

    static Vector3D parseNormal(const std::vector<std::string>& wordsInLineWithoutToken, int lineInd&) ;

    static Polygon parseFace(const std::vector<std::string>& wordsInLineWithoutToken, int lineInd&);

    static void parseFaceWord(std::string wordInLine,
                std::vector<int> onePolygonVertexIndices,
                std::vector<int> onePolygonTextureVertexIndices,
                std::vector<int> onePolygonNormalIndices, int lineInd);

};
#endif
