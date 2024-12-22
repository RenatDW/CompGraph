#include "../../src/render_engine/src/RemoveElements.cpp"
#include "../../src/obj_utils/objreader/ObjReader.h"
#include "../../src/obj_utils/objwriter/ObjWriter.h"

#include <gtest/gtest.h>
TEST(DeleteVertex, delete_vertex)
{
	std::string filepath = "/Users/renat/CLionProjects/CompGraph/resources/camera_model.obj";
	std::string filepath2 = "/Users/renat/CLionProjects/CompGraph/resources/camera_model2.obj";
	Model mt(ObjReader::read(filepath));
	RemoveElements::deleteVertice(1, mt);
	ObjWriter::write(mt, filepath2);
}