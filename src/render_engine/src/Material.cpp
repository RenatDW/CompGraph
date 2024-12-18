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
	int r = basic_color.red();
	int g = basic_color.green();
	int b = basic_color.blue();
	if (show_mesh)
	{
		if (Mesh::show_mesh(w_a, w_b, w_c, r, g, b))
		{
			if (show_illumination)
				Illumination::illumination(normal_vectors, P, cam, w_a, w_b, w_c, r, g, b);
			if (show_texture)
				Texture::texturing(texture_vectors, texture, w_a, w_b, w_c, r, g, b);
		}else{
			r = background.red(), g = background.green(), b = background.blue();
		}
	}else{
		if (show_texture)
			Texture::texturing(texture_vectors, texture, w_a, w_b, w_c, r, g, b);
		if (show_illumination)
			Illumination::illumination(normal_vectors, P, cam, w_a, w_b, w_c, r, g, b);

	}

	return QColor(r, g, b);
}
const Camera& Material::get_cam()
{
	return cam;
}
void Material::set_cam(Camera& cam)
{
	Material::cam = cam;
}
QImage& Material::get_texture()
{
	return texture;
}
void Material::set_texture(QImage& texture)
{
	this->texture = texture;
	this->show_texture = !texture.isNull();
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
