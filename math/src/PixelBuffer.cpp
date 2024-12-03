//
// Created by Ренат Асланов on 03.12.2024.
//

#include "../headers/PixelBuffer.h"
void PixelBuffer::add_element(Point2D point, QColor color)
{
	pixel_buffer[point] = color;
}
void PixelBuffer::parse_colors()
{
	for (auto [key, val] : pixel_buffer)
	{
		if(color_pixel_relationship.contains(val))
		{
			color_pixel_relationship[val].emplace_back(key);
		}else{
			color_pixel_relationship[val] = {};
		}
	}
}
PixelBuffer::PixelBuffer()
{
}
