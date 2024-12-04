#include "../headers/RenderEngine.h"

#include <iostream>
#include <omp.h>
#include "../headers/GraphicConveyor.h"
#include "../../forms/headers/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"
#include "../headers/Illumination.h"
#include "../headers/Mesh.h"
#include "../headers/Texturezation.h"
#include "../../math/headers/MathCast.h"
#include "../../math/headers/PixelBuffer.h"
#include "../headers/Rasterization.h"

void RenderEngine::render()
{
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix = model_view_projection_matrix * view_matrix * projection_matrix;

    render_triangles(model_view_projection_matrix, mesh.triangles.size());
}

RenderEngine::RenderEngine(QPainter& painter,
	Camera& camera,
	std::string& string,
	QColor& color,
	Model& model,
	int width,
	int height,
	bool show_mesh_param,
	bool show_texture_param,
	bool show_illumination_param,
	DepthBuffer& depth_buffer,
	PixelBuffer& pixels)
	: depth_buffer(depth_buffer), painter(painter),
	  mesh(model), camera(camera), filename(string),
	  width(width), height(height),
	  show_texture_param(show_texture_param),
	  show_mesh_param(show_mesh_param),
	  show_illumination_param(show_illumination_param),
	  fill_model_color(color), pixels(pixels)
{

}




void RenderEngine::initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C,
                                            int &x_left, int &x_right, int &y_down, int &y_up) const
{
    x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth())
    }));
    x_right = static_cast<int>(std::max({A.getX() + 1, B.getX() + 1, C.getX() + 1, 0.0f}));
    y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight())
    }));
    y_up = static_cast<int>(std::max({A.getY() + 1, B.getY() + 1, C.getY() + 1, 0.0f}));
}


void RenderEngine::universal_render(const std::array<Point3D, 3>& result_points,
	const std::array<Point3D, 3>& normal_vectors,
	const std::array<Point2D, 3>& texture_vectors)
{
    QImage image = (!filename.empty()) ? QImage(filename.data()) : QImage();
	Point3D A =result_points[0];
	Point3D B =result_points[1];
	Point3D C =result_points[2];
    int x_left, x_right, y_down, y_up;
    initialize_loop_varibles(A, B, C, x_left, x_right, y_down, y_up);
    float ABC;
    ABC = Rasterization::get_triangle_area_float(A, B, C);
    for (int y = y_down; y < y_up + 1; y++) {
        for (int x = x_left; x < x_right + 1; x++) {
            if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) continue;
            Point3D P(static_cast<float>(x), static_cast<float>(y), 0);
			float ABP = Rasterization::get_triangle_area_float(A, B, P);
			float BCP = Rasterization::get_triangle_area_float(B, C, P);
			float CAP = Rasterization::get_triangle_area_float(C, A, P);
            if (ABP < 0 || BCP < 0 || CAP < 0) continue;

            auto [weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A, B, C, ABC, ABP, BCP, CAP);
            if (depth_buffer.get(x, y) <= z) continue;

            int r = fill_model_color.red(), g = fill_model_color.green(), b = fill_model_color.blue();

            if (show_mesh_param)
                if (Mesh::show_mesh(weight_a, weight_b, weight_c, r, g, b)) continue;
            if (show_illumination_param)
                Illumination::illumination(normal_vectors, P, camera, weight_a, weight_b, weight_c, r, g, b);
            if (show_texture_param)
                Texturezation::texturation(texture_vectors, image, weight_a, weight_b, weight_c, r, g, b);
			pixels.add(Point2D(x, y), QColor(r, g, b));
			depth_buffer.set(x, y, z);
        }
    }
}

void RenderEngine::get_triangles_vectors(std::array<Point3D, 3> &result_points, std::array<Point3D, 3> &normal_vectors,
                                         std::array<Point2D, 3> &texture_vectors,
                                         const Matrix4D &model_view_projection_matrix, int triangle_ind) const
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < 3; ++vertex_in_triangle_ind) {
        //Points
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Point3D result_point = MathCast::to_Point3D(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex), width, height);
        result_points[vertex_in_triangle_ind] = (result_point);
        //Illumination
		if (show_illumination_param)
		{
			int texture_vertex_ind = mesh.triangles[triangle_ind].get_normal_indices()[vertex_in_triangle_ind];
			Point3D normal_point(mesh.normals[texture_vertex_ind]);
			normal_vectors[vertex_in_triangle_ind] = (normal_point);
		}
        //Texture
		if (show_texture_param)
		{
			int texture_vertex_ind = mesh.triangles[triangle_ind].get_texture_indices()[vertex_in_triangle_ind];
			Point2D texture_point = (mesh.textureVertices[texture_vertex_ind]);
			texture_vectors[vertex_in_triangle_ind] = (texture_point);
		}
    }
}

void RenderEngine::render_triangles(const Matrix4D &model_view_projection_matrix, int n_triangles)
{
    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        std::array<Point3D, 3> result_points, normal_vectors;
        std::array<Point2D, 3> texture_vectors;
        get_triangles_vectors(result_points, normal_vectors, texture_vectors, model_view_projection_matrix,
                              triangle_ind);
		universal_render(result_points, normal_vectors, texture_vectors);
    }
<<<<<<< HEAD
	//УДАЛИТЬ СТРОКУ - pixels.parse_colors();
	for (const auto& [key, val] : pixels.color_pixel_relationship)
	{
		painter.setPen(key);
		for(auto elem: val){
			painter.drawPoint(elem.getX(),elem.getY());
		}
	}
=======

//	QColor oldval = QColor(1,1,1);
//	for (auto [key, val] : pixels.data)
//	{
//		if(oldval != val){
//			painter.setPen(val);
//		}
//		painter.drawPoint(key.getX(),key.getY());
//	}
>>>>>>> 607ffe4d9b18c9eabbd928b165c0e01cfa1602ab
}
