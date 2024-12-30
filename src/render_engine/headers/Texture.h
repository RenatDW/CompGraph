#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <vector>
#include "../../math/headers/Point2D.h"
#include <QImage>
#include <QColor>

class Texture
{
private:
	QImage texture;
	int width;
	int height;

public:
	Texture(const QImage& texture);
	Texture();

	const Texture& get_texture() const;
	void set_texture(const QImage& texture);

	bool is_null() const;
	int get_width() const;
	int get_height() const;

	QColor get_pixel(int x, int y) const;
};


#endif //TEXTURE_H
