#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <iosfwd>
#include <QPainter>
#include <cfloat>

#include "Camera.h"
#include "Renderable.h"
#include "../headers/TriangleCoord.h"
#include "../../model/headers/Model.h"
#include "../../math/headers/Point2D.h"
#include "../../math/headers/Point3D.h"
#include "../../math/headers/PixelBuffer.h"


#include "../../math/headers/DepthBuffer.h"
#include "Material.h"


static const int VERTEX_SCAN_RADIUS = 100;

class RenderEngine
{
public:

	void render();
	TriangleCoordinates render_with_selection(int x, int y);

	RenderEngine(Camera& camera,
		Model& model,
		int width,
		int height,
		DepthBuffer& depth_buffer,
		PixelBuffer& pixels,
		Material & mt);

    ~RenderEngine() = default;

private:
	DepthBuffer& depth_buffer;
    Model &mesh;
    Camera &camera;
	PixelBuffer& pixels;
    int width;
    int height;
	bool show_mesh;
	bool show_texture;
	bool show_illumination;
	bool selection = false;
	int current_triangle;
	int nearest_vertex = -1;
	Point2D nearest_vertex_point;
	int nearest_triangle = -1;
	int posX = 0;
	int posY = 0;
	float posZ = std::numeric_limits<float>::min();
	Material mt;

    void initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C, int &x_left,
                                  int &x_right,
                                  int &y_down, int &y_up) const;

    void render(const std::array<Point3D, 3>& result_points,
		const std::array<Point3D, 3>& normal_vectors,
		const std::array<Point2D, 3>& texture_vectors);

    void get_triangles_vectors(std::array<Point3D, 3> &result_points, std::array<Point3D, 3> &normal_vectors,
                               std::array<Point2D, 3> &texture_vectors, const
                               Matrix4D &model_view_projection_matrix, int triangle_ind) const;

    void render_triangles(
        const Matrix4D &model_view_projection_matrix, int n_triangles);

	void is_point_in_triangle(Point3D P, Point3D A, Point3D B, Point3D C);
	void highlight_triangle(const std::array<Point3D, 3>& result_points);
	void render_triangle(const std::array<Point3D, 3>& normal_vectors,
		const std::array<Point2D, 3>& texture_vectors,
		Point3D& A,
		Point3D& B,
		Point3D& C);
	float is_around_vertex(const Point3D& A) const;
};

#endif //RENDERENGINE_H
