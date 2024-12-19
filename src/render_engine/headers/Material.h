
//
// Created by Ренат Асланов on 11.12.2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include <QImage>
#include "Camera.h"
#include "Mesh.h"
#include "Illumination.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(bool show_mesh, bool show_illumination, bool show_texture);
private:
	bool show_mesh;
	bool show_texture;
	bool show_illumination;
	QImage texture;
	QColor basic_color = QColor(255, 255, 255);
	QColor background = QColor(45,45,45);
public:
	Camera cam;
	QColor use_material(float w_a,
		float w_b,
		float w_c,
		std::array<Point2D, 3> texture_vectors,
		std::array<Point3D, 3> normal_vectors,
		Point3D P);
	const Camera& get_cam();
	void set_cam(Camera& cam);
	bool is_show_mesh() const;
	bool is_show_texture() const;
	bool is_show_illumination() const;
	QImage& get_texture();
	void set_texture(QImage& texture);
	void set_show_mesh(bool showMesh);
	void set_show_texture(bool showTexture);
	void set_show_illumination(bool showIllumination);
};

#endif //MATERIAL_H
