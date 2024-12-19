#include "../headers/RenderEngine.h"

#include <iostream>
#include <omp.h>
#include "../headers/GraphicConveyor.h"
#include "../../forms/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"
#include "../headers/Illumination.h"
#include "../headers/Mesh.h"
#include "../headers/Texture.h"
#include "../../math/headers/MathCast.h"
#include "../../math/headers/PixelBuffer.h"
#include "../headers/Rasterization.h"
#include "../headers/Material.h"

void RenderEngine::render()
{
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
	model_view_projection_matrix = model_view_projection_matrix * projection_matrix * view_matrix;

    render_triangles(model_view_projection_matrix, mesh.triangles.size());
}

Point2D RenderEngine::render_with_selection(int x, int y)
{
	posX = x;
	posY = y;
	selection = true;
	render();
	return nearest_vertex_point;
}

RenderEngine::RenderEngine(Camera& camera,
	Model& model,
	int width,
	int height,
	DepthBuffer& depth_buffer,
	PixelBuffer& pixels,
	Material& mt)
	: depth_buffer(depth_buffer),
	  mesh(model), camera(camera),
	  width(width), height(height), pixels(pixels), mt(mt)
{
	show_mesh = mt.is_show_mesh();
	show_texture = mt.is_show_texture();
	show_illumination = mt.is_show_illumination();
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
void RenderEngine::is_point_in_triangle(Point2D P, Point3D A, Point3D B, Point3D C)
{
	float total_area = (A.getX() * (B.getY() - C.getY()) +
		B.getX() * (C.getY() - A.getY()) +
		C.getX() * (A.getY() - B.getY()));
	float w_a = (B.getX() * (C.getY() - P.getY()) + C.getX() * (P.getY() - B.getY()) + P.getX() * (B.getY() - C.getY()))
		/ total_area;
	float w_b = (C.getX() * (A.getY() - P.getY()) + A.getX() * (P.getY() - C.getY()) + P.getX() * (C.getY() - A.getY()))
		/ total_area;
	float w_c = (A.getX() * (B.getY() - P.getY()) + B.getX() * (P.getY() - A.getY()) + P.getX() * (A.getY() - B.getY()))
		/ total_area;
	float z = (A.getZ() * w_a + B.getZ() * w_b + C.getZ() * w_c);

//	nearest_vertex = -1;
	if (w_a > 0 && w_b > 0 && w_c > 0)
	{
		if (nearest_triangle == -1 || z < posZ) // Сравниваем текущую глубину с минимальной
		{
			posZ = z;
			nearest_triangle = сurrent_triangle;

			if ((A.getX() - posX) * (A.getX() - posX) + (A.getY() - posY) * (A.getY() - posY) < 100)
			{
				nearest_vertex_point = Point2D(A.getX(), A.getY());
				nearest_vertex = 0;
			}
			else if ((B.getX() - posX) * (B.getX() - posX) + (B.getY() - posY) * (B.getY() - posY) < 100)
			{
				nearest_vertex_point = Point2D(B.getX(), B.getY());
				nearest_vertex = 1;
			}
			else if ((C.getX() - posX) * (C.getX() - posX) + (C.getY() - posY) * (C.getY() - posY) < 100)
			{
				nearest_vertex_point = Point2D(C.getX(), C.getY());
				nearest_vertex = 2;
			}
		}
	}
}

void RenderEngine::universal_render(const std::array<Point3D, 3>& result_points,
	const std::array<Point3D, 3>& normal_vectors,
	const std::array<Point2D, 3>& texture_vectors)
{
	Point3D A =result_points[0];
	Point3D B =result_points[1];
	Point3D C =result_points[2];


	int x_left, x_right, y_down, y_up;
    initialize_loop_varibles(A, B, C, x_left, x_right, y_down, y_up);


    float ABC;
    ABC = Rasterization::get_triangle_area_float(A, B, C);
	is_point_in_triangle(Point2D(posX, posY), A, B, C);
	
    for (int y = y_down; y < y_up + 1; y++) {
		for (int x = x_left; x < x_right + 1; x++)
		{
			if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) continue;
			Point3D P(static_cast<float>(x), static_cast<float>(y), 0);
			float ABP;
			float BCP;
			float CAP;
//			if (show_mesh && !show_texture && !show_illumination)
//			{
//				ABP = Rasterization::get_triangle_area_round(A, B, P);
//				BCP = Rasterization::get_triangle_area_round(B, C, P);
//				CAP = Rasterization::get_triangle_area_round(C, A, P);
//			}
//			else
//			{
				ABP = Rasterization::get_triangle_area_float(A, B, P);
				BCP = Rasterization::get_triangle_area_float(B, C, P);
				CAP = Rasterization::get_triangle_area_float(C, A, P);
//			}
            if (ABP < 0 || BCP < 0 || CAP < 0) continue;

            auto [weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A, B, C, ABC, ABP, BCP, CAP);
			if (depth_buffer.get(x, y) < z) continue;

			mt.set_cam(camera);

			pixels.add(Point2D(x, y), mt.use_material(weight_a,
				weight_b,
				weight_c,
				texture_vectors,
				normal_vectors,P));
			depth_buffer.set(x, y, z);
        }
    }

}

void RenderEngine::highlight_triangle(const std::array<Point3D, 3>& result_points)
{
	Point3D A = result_points[0];
	Point3D B = result_points[1];
	Point3D C = result_points[2];

	int x_left, x_right, y_down, y_up;
	initialize_loop_varibles(A, B, C, x_left, x_right, y_down, y_up);


	for (int y = y_down; y < y_up + 1; y++)
	{
		for (int x = x_left; x < x_right + 1; x++)
		{
			if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) continue;
			Point3D P(static_cast<float>(x), static_cast<float>(y), 0);
			float ABP;
			float BCP;
			float CAP;
			if (show_mesh && !show_texture && !show_illumination)
			{
				ABP = Rasterization::get_triangle_area_round(A, B, P);
				BCP = Rasterization::get_triangle_area_round(B, C, P);
				CAP = Rasterization::get_triangle_area_round(C, A, P);
			}
			else
			{
				ABP = Rasterization::get_triangle_area_float(A, B, P);
				BCP = Rasterization::get_triangle_area_float(B, C, P);
				CAP = Rasterization::get_triangle_area_float(C, A, P);
			}
			if (ABP < 0 || BCP < 0 || CAP < 0) continue;


			pixels.add(Point2D(x, y), QColor(255, 215, 50));
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
		if (show_illumination)
		{
			int texture_vertex_ind = mesh.triangles[triangle_ind].get_normal_indices()[vertex_in_triangle_ind];
			Point3D normal_point(mesh.normals[texture_vertex_ind]);
			normal_vectors[vertex_in_triangle_ind] = (normal_point);
		}
        //Texture
		if (show_texture)
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
		сurrent_triangle = triangle_ind;
		universal_render(result_points, normal_vectors, texture_vectors);
    }

	if (nearest_vertex != -1)
	{
		return;
	}
	else if (nearest_triangle != -1)
	{

		std::array<Point3D, 3> result_points, normal_vectors;
		std::array<Point2D, 3> texture_vectors;
		get_triangles_vectors(result_points, normal_vectors, texture_vectors, model_view_projection_matrix,
			nearest_triangle);
		highlight_triangle(result_points);
	}

}
