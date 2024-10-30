#include "../headers/Triangle.h"

Triangle::Triangle() = default;

void Triangle::set_vertex_indices(const std::vector<int> &t_vertex_indices)
{
    this->vertex_indices = t_vertex_indices;
}

Triangle::~Triangle() =default;
