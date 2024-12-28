#include "../headers/Texture.h"
const Texture& Texture::get_texture() const {
	return texture;
}

void Texture::set_texture(const QImage& texture) {
	this->texture = texture;
}

Texture::Texture(const QImage& texture)
	: texture(texture), width(texture.width()), height(texture.height()) {}

bool Texture::is_null() const {
	return texture.isNull();
}

int Texture::get_width() const {
	return width;
}

int Texture::get_height() const {
	return height;
}

QColor Texture::get_pixel(int x, int y) const {
	return QColor(texture.pixel(x, y));
}
Texture::Texture()
{
}
