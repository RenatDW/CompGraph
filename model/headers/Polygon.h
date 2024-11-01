#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

class Polygon
{
public:
	Polygon();

	void set_vertex_indices(const std::vector<int> &t_vertex_indices);

	void set_normal_indices(const std::vector<int> &t_normal_indices);

	friend bool operator==(const Polygon &lhs, const Polygon &rhs)
	{
		return lhs.vertex_indices == rhs.vertex_indices
		       && lhs.normal_indices == rhs.normal_indices
		       && lhs.texture_indices == rhs.texture_indices;
	}

	friend bool operator!=(const Polygon &lhs, const Polygon &rhs)
	{
		return !(lhs == rhs);
	}

	 std::vector<int> get_vertex_indices() const
	{
		return vertex_indices;
	}

	 std::vector<int> get_normal_indices() const
	{
		return normal_indices;
	}

	 std::vector<int> get_texture_indices() const
	{
		return texture_indices;
	}

	void set_texture_indices(const std::vector<int> &t_texture_indices);

	std::vector<int> get_vertex_indices();

	std::vector<int> get_normal_indices();

	std::vector<int> get_texture_indices();

	~Polygon();

private:
	std::vector<int> vertex_indices;
	std::vector<int> normal_indices;
	std::vector<int> texture_indices;
};

#endif