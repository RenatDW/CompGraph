#include "ObjWriter.h"

#include <fstream>
#include <string>
#include <iostream>

void ObjWriter::write(const Model &model, const std::string &filename)
{
    std::ofstream file(filename, std::ios::binary | std::ios::out | std::ios::trunc);

    for (auto &vertex: model.vertices) {
        file << "v " << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << std::endl;
    }

    for (auto &texture: model.textureVertices) {
        file << "vt " << texture.getX() << " " << texture.getY() << std::endl;
    }

    for (auto &normal: model.normals) {
        file << "vn " << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
    }

    for (auto &polygon: model.polygons) {
        file << "f ";

        for (int i = 0; i < polygon.get_vertex_indices().size(); i++) {
            file << 1 + polygon.get_vertex_indices()[i] << "/";

            if (!polygon.get_texture_indices().empty()) {
                file << 1 + polygon.get_texture_indices()[i];
            }

            file << "/";

            if (!polygon.get_normal_indices().empty()) {
                file << 1 + polygon.get_normal_indices()[i];
            }

            file << " ";
        }

        file << std::endl;
    }

    file.close();
}