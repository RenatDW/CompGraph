#include "gtest/gtest.h"
#include "../../objreader/src/ObjReader.cpp"
#include "../../model/src/Polygon.cpp"
#include "../../model/src/Triangle.cpp"

TEST(ObjReader, parse_vertex)
{
    std::string file_path = "obj_reader/TestCase/test1.obj";
    Model a(ObjReader::read(file_path));
    std::vector<Vector3D> vertices{
        {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}, {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}
    };
    for (int i = 0; i < vertices.size(); i++) {
        EXPECT_EQ(a.vertices[i], vertices[i]);
    }
    std::vector<Vector3D> normals{{0, 0, -1}, {0, 0, 1}, {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}};
    for (int i = 0; i < normals.size(); i++) {
        EXPECT_EQ(a.normals[i], normals[i]);
    }
    std::vector<Vector2D> texcoords{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    for (int i = 0; i < texcoords.size(); i++) {
        EXPECT_EQ(a.textureVertices[i], texcoords[i]);
    }
    Polygon polygon;
    Polygon polygon2;
    polygon.set_vertex_indices({1, 2, 3, 4});
    polygon.set_normal_indices({1, 2, 3, 4});
    polygon.set_texture_indices({1, 2, 3, 4});
    polygon2.set_vertex_indices({4, 1, 5, 8});
    polygon2.set_normal_indices({1, 2, 3, 4});
    polygon2.set_texture_indices({6, 6, 6, 6});

    for (int i = 0; i < a.polygons[0].get_normal_indices().size(); i++) {
        EXPECT_EQ(a.polygons[0].get_normal_indices()[i], polygon.get_normal_indices()[i] - 1);
    }

    for (int i = 0; i < a.polygons[0].get_texture_indices().size(); i++) {
        EXPECT_EQ(a.polygons[0].get_texture_indices()[i], polygon.get_texture_indices()[i] - 1);
    }

    for (int i = 0; i < a.polygons[0].get_vertex_indices().size(); i++) {
        EXPECT_EQ(a.polygons[0].get_vertex_indices()[i], polygon.get_vertex_indices()[i] - 1);
    }
}
