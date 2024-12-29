//
// Created by Ренат Асланов on 11.12.2024.
//
#include "../headers/Material.h"
Material::Material(bool show_mesh, bool show_illumination, bool show_texture)
	: show_texture(show_texture), show_illumination(show_illumination), show_mesh(show_mesh)
{
}
QColor Material::use_material(float w_a,
	float w_b,
	float w_c,
	std::array<Point2D, 3> texture_vectors,
	std::array<Point3D, 3> normal_vectors,
	Point3D P)
{
	int r = main_color.red();
	int g = main_color.green();
	int b = main_color.blue();
	if (show_texture)
		Texturing::texturing(texture_vectors, texture, w_a, w_b, w_c, r, g, b);
	if (show_illumination)
		Illumination::illumination(normal_vectors, P, lights, w_a, w_b, w_c, r, g, b);
	if (show_mesh)
		Mesh::show_mesh(w_a, w_b, w_c, r, g, b, background);
//
//	if (show_mesh)
//	{
//		if (Mesh::show_mesh(w_a, w_b, w_c, r, g, b))
//		{
//			if (show_illumination)
//				Illumination::illumination(normal_vectors, P, lights, w_a, w_b, w_c, r, g, b);
//			if (show_texture)
//				Texturing::texturing(texture_vectors, texture, w_a, w_b, w_c, r, g, b);
//		}else{
//			r = background.red(), g = background.green(), b = background.blue();
//		}
//	}else{
//		if (show_texture)
//			Texturing::texturing(texture_vectors, texture, w_a, w_b, w_c, r, g, b);
//		if (show_illumination)
//			Illumination::illumination(normal_vectors, P, lights, w_a, w_b, w_c, r, g, b);
//
//	}

	return QColor(r, g, b);
}
Texture& Material::get_texture()
{
	return texture;
}
void Material::set_texture(Texture& texture)
{
	this->texture = texture;
	this->show_texture = !texture.is_null();
}
bool Material::is_show_mesh() const
{
	return show_mesh;
}
bool Material::is_show_texture() const
{
	return show_texture;
}
bool Material::is_show_illumination() const
{
	return show_illumination;
}
Material::Material()
{
	show_illumination = false;
	show_texture = false;
	show_mesh = false;
}
void Material::set_show_mesh(bool showMesh)
{
	show_mesh = showMesh;
}
void Material::set_show_texture(bool showTexture)
{
	show_texture = showTexture;
}
void Material::set_show_illumination(bool showIllumination)
{
	show_illumination = showIllumination;
}
void Material::select_highlightcolor()
{
	this->main_color = highlight_color;
}
void Material::select_basic_color()
{
	this->main_color = basic_color;
}
const QColor& Material::get_highlightcolor() const
{
	return highlight_color;
}
void Material::set_basic_color(const QColor& basicColor)
{
	this->basic_color = basicColor;

}
const std::vector<Light>& Material::get_lights() const
{
	return lights;
}
void Material::set_lights(std::vector<Light> t_lights)
{
	this->lights = t_lights;
}
