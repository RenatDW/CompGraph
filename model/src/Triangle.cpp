#include "../headers/Triangle.h"

Triangle::Triangle() = default;

void Triangle::set_vertex_indices(const std::vector<int> &t_vertex_indices)
{
    this->vertex_indices = t_vertex_indices;
}

void Triangle::set_normal_indices(const std::vector<int> &t_normal_indices)
{
    this->normal_indices = t_normal_indices;
}

void Triangle::set_texture_indices(const std::vector<int> &t_texture_indices)
{
    this->texture_indices = t_texture_indices;
}

std::vector<int> Triangle::get_vertex_indices() const
{
    return this->vertex_indices;
}

std::vector<int> Triangle::get_normal_indices() const
{
    return this->normal_indices;
}

std::vector<int> Triangle::get_texture_indices() const
{
    return this->texture_indices;
}

Triangle::~Triangle() = default;