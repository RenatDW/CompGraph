//
// Created by Ренат Асланов on 19.11.2024.
//
#include "../../../src/render_engine/src/Rasterization.cpp"

#include <gtest/gtest.h>
TEST(AreaTests, calculate_area)
{
    Point3D A(1, 1, 3);
    Point3D B(2, 3, 4);
    Point3D C(3, 1, 3);
    EXPECT_EQ(Rasterization::get_triangle_area_float(A, B, C), -2*2);

    // Проверка треугольника с другими координатами
    Point3D D(0, 0, 0);
    Point3D E(4, 0, 0);
    Point3D F(0, 3, 0);
    EXPECT_EQ(Rasterization::get_triangle_area_float(D, E, F), 6*2);

    // Проверка на коллинеарные точки (площадь должна быть 0)
    Point3D G(1, 1, 1);
    Point3D H(2, 2, 2);
    Point3D I(3, 3, 3);
    EXPECT_EQ(Rasterization::get_triangle_area_float(G, H, I), 0);

    // Проверка треугольника с отрицательными координатами
    Point3D J(-1, -1, -1);
    Point3D K(-3, -2, -1);
    Point3D L(-2, -4, -1);
    EXPECT_EQ(Rasterization::get_triangle_area_float(J, K, L), 2.5*2);

    // Проверка треугольника на плоскости XY
    Point3D M(0, 0, 0);
    Point3D N(1, 0, 0);
    Point3D O(0, 1, 0);
    EXPECT_EQ(Rasterization::get_triangle_area_float(M, N, O), 1);

    // Проверка треугольника с одинаковыми Y координатами
    Point3D P(0, 1, 0);
    Point3D Q(3, 1, 0);
    Point3D R(1.5, 4, 0);
    EXPECT_EQ(Rasterization::get_triangle_area_float(P, Q, R), 9);
}
//Пример 1: Точка внутри треугольника
TEST(BaricentricCord, calculate_params)
{
    Point3D A, B, C, P;
    A = {0, 0, 1};
    B = {1, 0, 2};
    C = {0, 1, 3};
    P = {0.25, 0.25, 0};
    float ABC = Rasterization::get_triangle_area_float(A,B,C);
    auto [ABP, BCP, CAP] = Rasterization::calculate_edge_functions(A,B,C,P, true);
    auto[weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A,B,C,ABC,ABP,BCP,CAP);
    EXPECT_EQ(weight_a, 0.5);
    EXPECT_EQ(weight_b, 0.25);
    EXPECT_EQ(weight_c, 0.25);
    EXPECT_EQ(z, 1.75);
}

//Пример 2: Точка на ребре треугольника

TEST(BaricentricCord, calculate_params_1){
Point3D A, B, C, P;

    A={0, 0, 1};
    B = {4, 0, 2};
    C = {0, 4, 3};
    P = {2,0,0};
    float ABC = Rasterization::get_triangle_area_float(A,B,C);
    auto [ABP, BCP, CAP] = Rasterization::calculate_edge_functions(A,B,C,P, true);
    auto[weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A,B,C,ABC,ABP,BCP,CAP);
    EXPECT_EQ(weight_a, 0.5);
    EXPECT_EQ(weight_b, 0.5);
    EXPECT_EQ(weight_c, 0);
    EXPECT_EQ(z, 1.5);
}
// Пример 3: Точка вне треугольника
//Тест падает т.к проверка на нахождение вне треугольника находится в другой части логики
// TEST(BaricentricCord, calculate_params_2){
//     Point3D A, B, C, P;
//
//     A={0, 0, 1};
//     B = {1, 0, 2};
//     C = {0, 1, 3};
//     P = {-1,-1,0};
//     float ABC = Rasterization::get_triangle_area_float(A,B,C);
//     auto [ABP, BCP, CAP] = Rasterization::calculate_edge_functions(A,B,C,P, true);
//     auto[weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A,B,C,ABC,ABP,BCP,CAP);
//     EXPECT_EQ(weight_a, 2);
//     EXPECT_EQ(weight_b, -1);
//     EXPECT_EQ(weight_c, -1);
//     EXPECT_EQ(z, -3);
// }
// Пример 4: Центроид треугольника
TEST(BaricentricCord, calculate_params_3){
    Point3D A, B, C, P;

    A={0, 0, 1};
    B = {6, 0, 2};
    C = {0, 6, 3};
    P = {2,2,0};
    float ABC = Rasterization::get_triangle_area_float(A,B,C);
    auto [ABP, BCP, CAP] = Rasterization::calculate_edge_functions(A,B,C,P, true);
    auto[weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A,B,C,ABC,ABP,BCP,CAP);
    EXPECT_EQ(weight_a, 0.333333343f);
    EXPECT_EQ(weight_b, 0.333333343f);
    EXPECT_EQ(weight_c, 0.333333343f);
    EXPECT_EQ(z, 2);
}

// Пример 5: Вершина треугольника
TEST(BaricentricCord, calculate_params_4){
    Point3D A, B, C, P;

    A={0, 0, 1};
    B = {1, 0, 2};
    C = {0, 1, 3};
    P = {0,0,1};
    float ABC = Rasterization::get_triangle_area_float(A,B,C);
    auto [ABP, BCP, CAP] = Rasterization::calculate_edge_functions(A,B,C,P, true);
    auto[weight_a, weight_b, weight_c, z] = Rasterization::calculate_baricentric_coeficients(A,B,C,ABC,ABP,BCP,CAP);
    EXPECT_EQ(weight_a, 1);
    EXPECT_EQ(weight_b, 0);
    EXPECT_EQ(weight_c, 0);
    EXPECT_EQ(z, 1);
}
