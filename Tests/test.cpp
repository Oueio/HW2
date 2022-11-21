// Copyright 2022 OUEIO

#include <gtest/gtest.h>
#include <Matrix.h>

namespace FIRST {

    TEST(First, Access_to_vector_element) {
        double a[3] = {1, 2, 3};
        VectorDouble vec(a, 3);
        EXPECT_EQ(vec[0], 1);
    }

    TEST(First, Access_to_matrix_element) {
        double a[3] = {1, 2, 3};
        double b[3] = {1, 2, 3};
        double c[3] = {1, 2, 3};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        EXPECT_EQ(obj(0, 0), 1);
    }

    TEST(First, Extract_main_diag) {
        double a[3] = {1, 2, 3};
        double b[3] = {1, 2, 3};
        double c[3] = {1, 2, 3};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        VectorDouble vec = obj.get_main_diag();
        EXPECT_TRUE(vec == p[0]);
    }

    TEST(First, Extract_side_diag) {
        double a[3] = {1, 2, 3};
        double b[3] = {1, 2, 3};
        double c[3] = {1, 2, 3};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        VectorDouble vec = obj.get_side_diag();
        EXPECT_TRUE(vec == p[0]);
    }

    TEST(First, Extract_row) {
        double a[3] = {1, 2, 3};
        double b[3] = {1, 2, 3};
        double c[3] = {1, 2, 3};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        VectorDouble vec = obj.get_row(0);
        EXPECT_TRUE(vec == p[0]);
    }

    TEST(First, Extract_col) {
        double a[3] = {1, 2, 3};
        double b[3] = {1, 2, 3};
        double c[3] = {1, 2, 3};
        double d[3] = {2, 2, 2};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        VectorDouble vec = obj.get_col(1);
        EXPECT_TRUE(vec == VectorDouble(d, 3));
    }

}   // namespace FIRST

namespace SECOND {
    TEST(Second, Matrix_from_numbers) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        Matrix obj(a, 3, 3);
        int i, j;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                ASSERT_EQ(obj(i, j), 1);
            }
        }
    }

    TEST(Second, Matrix_from_vectors) {
        double a[3] = {1, 1, 1};
        double b[3] = {1, 1, 1};
        double c[3] = {1, 1, 1};
        VectorDouble p[3] =
                {VectorDouble(a, 3), VectorDouble(b, 3), VectorDouble(c, 3)};
        Matrix obj(p, 3);
        int i, j;
        for (i = 0; i < 3; ++i) {
            for (j = 0; j < 3; ++j) {
                ASSERT_EQ(obj(i, j), 1);
            }
        }
    }

    TEST(Second, Vector_from_numbers) {
        double a[3] = {1, 1, 1};
        VectorDouble vec(a, 3);
        int i;
        for (i = 0; i < 3; ++i) {
            ASSERT_EQ(vec[i], 1);
        }
    }

}   // namespace SECOND

namespace THIRD {
    TEST(Third, Vector_plus_Vector) {
        double a[3] = {1, 1, 1};
        double b[3] = {1, 1, 1};
        double c[3] = {2, 2, 2};
        VectorDouble vec1(a, 3);
        VectorDouble vec2(b, 3);
        VectorDouble vec3(c, 3);
        VectorDouble vec = vec1 + vec2;
        EXPECT_TRUE(vec == vec3);
    }

    TEST(Third, Vector_minus_Vector) {
        double a[3] = {1, 1, 1};
        double b[3] = {1, 1, 1};
        double c[3] = {0, 0, 0};
        VectorDouble vec1(a, 3);
        VectorDouble vec2(b, 3);
        VectorDouble vec3(c, 3);
        VectorDouble vec = vec1 - vec2;
        EXPECT_TRUE(vec == vec3);
    }

    TEST(Third, Vector_multi_Vector) {
        double a[3] = {1, 1, 1};
        double b[3] = {2, 2, 2};
        double c[3] = {2, 2, 2};
        VectorDouble vec1(a, 3);
        VectorDouble vec2(b, 3);
        VectorDouble vec = vec1 * vec2;
        EXPECT_TRUE(vec == VectorDouble(c, 3));
    }

    TEST(Third, Matrix_plus_Matrix) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double b[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double c[9] = {2, 2, 2,
                       2, 2, 2,
                       2, 2, 2};
        Matrix obj1(a, 3, 3);
        Matrix obj2(b, 3, 3);
        EXPECT_TRUE((obj1 + obj2) == Matrix(c, 3, 3));
    }

    TEST(Third, Matrix_minus_Matrix) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double b[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double c[9] = {0, 0, 0,
                       0, 0, 0,
                       0, 0, 0};
        Matrix obj1(a, 3, 3);
        Matrix obj2(b, 3, 3);
        EXPECT_TRUE((obj1 - obj2) == Matrix(c, 3, 3));
    }

}   // namespace THIRD

namespace FOURTH {
    TEST(Fourth, Matrix_multi_Number) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double b[9] = {2, 2, 2,
                       2, 2, 2,
                       2, 2, 2};
        Matrix obj1(a, 3, 3);
        EXPECT_TRUE((obj1 *= 2) == Matrix(b, 3, 3));
    }

    TEST(Fourth, Matrix_multi_Vector) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double b[3] = {3, 3, 3};
        double c[3] = {9, 9, 9};
        Matrix obj1(a, 3, 3);
        EXPECT_TRUE((obj1 * VectorDouble(b, 3)) == VectorDouble(c, 3));
    }

    TEST(Fourth, Matrix_multi_Matrix) {
        double a[9] = {1, 1, 1,
                       1, 1, 1,
                       1, 1, 1};
        double b[9] = {2, 2, 2,
                       2, 2, 2,
                       2, 2, 2};
        double c[9] = {6, 6, 6,
                       6, 6, 6,
                       6, 6, 6};
        Matrix obj1(a, 3, 3);
        Matrix obj2(b, 3, 3);
        EXPECT_TRUE((obj1 * obj2) == Matrix(c, 3, 3));
    }

}   // namespace FOURTH

namespace FIFTH {
    TEST(Fifth, Vector_plus_Number) {
        double a[3] = {1, 1, 1};
        VectorDouble vec(a, 3);
        EXPECT_EQ(vec[0] += 3, 4);
    }

    TEST(Fifth, Matrix_plus_Number) {
        double a[4] = {1, 1, 1, 1};
        Matrix obj(a, 2, 2);
        EXPECT_EQ(a[0] += 3, 4);
    }

    TEST(Fifth, Vector_minus_Number) {
        double a[3] = {1, 1, 1};
        VectorDouble vec(a, 3);
        EXPECT_EQ(vec[0] -= 3, -2);
    }

    TEST(Fifth, Matrix_minus_Number) {
        double a[4] = {1, 1, 1, 1};
        Matrix obj(a, 2, 2);
        EXPECT_EQ(a[0] -= 3, -2);
    }

    TEST(Fifth, Matrix_plus_Vector_row) {
        double a[4] = {1, 1, 1, 1};
        double b[2] = {1, 1};
        double c[4] = {2, 2, 1, 1};
        Matrix obj(a, 2, 2);
        VectorDouble vec(b, 2);
        obj.put_row(vec, 0, '+');
        EXPECT_TRUE(obj == Matrix(c, 2, 2));
    }

    TEST(Fifth, Matrix_minus_Vector_row) {
        double a[4] = {1, 1, 1, 1};
        double b[2] = {1, 1};
        double c[4] = {0, 0, 1, 1};
        Matrix obj(a, 2, 2);
        VectorDouble vec(b, 2);
        obj.put_row(vec, 0, '-');
        EXPECT_TRUE(obj == Matrix(c, 2, 2));
    }

    TEST(Fifth, Matrix_plus_Vector_col) {
        double a[4] = {1, 1, 1, 1};
        double b[2] = {1, 1};
        double c[4] = {2, 1, 2, 1};
        Matrix obj(a, 2, 2);
        VectorDouble vec(b, 2);
        obj.put_col(vec, 0, '+');
        EXPECT_TRUE(obj == Matrix(c, 2, 2));
    }

    TEST(Fifth, Matrix_minus_Vector_col) {
        double a[4] = {1, 1, 1, 1};
        double b[2] = {1, 1};
        double c[4] = {0, 1, 0, 1};
        Matrix obj(a, 2, 2);
        VectorDouble vec(b, 2);
        obj.put_col(vec, 0, '-');
        EXPECT_TRUE(obj == Matrix(c, 2, 2));
    }
}   // namespace FIFTH

namespace SIXTH {
    TEST(Sixth, Trans) {
        double a[9] = {2, 5, 7,
                       6, 3, 4,
                       5, -2, -3};
        double b[9] = {2, 6, 5,
                       5, 3, -2,
                       7, 4, -3};
        EXPECT_TRUE(Matrix(a, 3, 3).trans() == Matrix(b, 3, 3));
    }

    TEST(Sixth, Reverse) {
        double a[9] = {2, 5, 7,
                       6, 3, 4,
                       5, -2, -3};
        double b[9] = {1, -1, 1,
                       -38, 41, -34,
                       27, -29, 24};
        Matrix obj(a, 3, 3);
        EXPECT_TRUE(obj.reverse() == Matrix(b, 3, 3));
    }

}   // namespace SIXTH

namespace SEVENTH {
    TEST(Seventh, Determinant) {
        double a[9] = {2, 5, 7,
                       6, 3, 4,
                       5, -2, -3};
        EXPECT_EQ(Matrix(a, 3, 3).determinant(), -1);
    }
}   // namespace SEVENTH

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
