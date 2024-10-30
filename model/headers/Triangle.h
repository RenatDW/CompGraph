#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>


class Triangle
{
public:
    Triangle();

    void set_vertex_indices(const std::vector<int> &t_vertex_indices);

    void set_normal_indices(const std::vector<int> &t_normal_indices);

    void set_texture_indices(const std::vector<int> &t_texture_indices);

    std::vector<int> get_vertex_indices() const;

    std::vector<int> get_normal_indices() const;

    std::vector<int> get_texture_indices() const;

    ~Triangle();

private:
    std::vector<int> vertex_indices;
    std::vector<int> normal_indices;
    std::vector<int> texture_indices;
};


#endif
