
//
// Created by Ренат Асланов on 11.12.2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include <QImage>
#include "Camera.h"
#include "Mesh.h"
#include "Illumination.h"
#include "Texturing.h"
class Material
{
public:
	Material();
	Material(bool show_mesh, bool show_illumination, bool show_texture);
private:
	bool show_mesh;
	bool show_texture;
	bool show_illumination;
	Texture texture;
public:
	void set_basic_color(const QColor& basicColor);
private:
	QColor basic_color = QColor(255, 255, 255);
	QColor highlight_color = QColor(255, 215, 50);
	QColor main_color = basic_color;
	QColor background = QColor(45, 45, 45);
public:
	std::vector<Light> lights;
	QColor use_material(float w_a,
		float w_b,
		float w_c,
		std::array<Point2D, 3> texture_vectors,
		std::array<Point3D, 3> normal_vectors,
		Point3D P);
	[[nodiscard]] const std::vector<Light>& get_lights() const;
	void set_lights(std::vector<Light>& lights);
	[[nodiscard]] bool is_show_mesh() const;
	[[nodiscard]] bool is_show_texture() const;
	[[nodiscard]] bool is_show_illumination() const;
	Texture& get_texture();
	void set_texture(Texture& texture);
	void set_show_mesh(bool showMesh);
	void set_show_texture(bool showTexture);
	void set_show_illumination(bool showIllumination);
	void select_highlightcolor();
	[[nodiscard]] const QColor& get_highlightcolor() const;
	void select_basic_color();
};

#endif //MATERIAL_H
